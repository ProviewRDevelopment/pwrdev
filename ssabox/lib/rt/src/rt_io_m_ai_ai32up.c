/*
 * ProviewR   Open Source Process Control.
 * Copyright (C) 2005-2025 SSAB EMEA AB.
 *
 * This file is part of ProviewR.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ProviewR. If not, see <http://www.gnu.org/licenses/>
 *
 * Linking ProviewR statically or dynamically with other modules is
 * making a combined work based on ProviewR. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of
 * ProviewR give you permission to, from the build function in the
 * ProviewR Configurator, combine ProviewR with modules generated by the
 * ProviewR PLC Editor to a PLC program, regardless of the license
 * terms of these modules. You may copy and distribute the resulting
 * combined work under the terms of your choice, provided that every
 * copy of the combined work is accompanied by a complete copy of
 * the source code of ProviewR (the version used to produce the
 * combined work), being distributed under the terms of the GNU
 * General Public License plus this exception.
 */

/* rt_io_m_ai_ai32up.c -- io methods for ssab cards.
   OS Linux
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "co_cdh.h"
#include "co_time.h"
#include "pwr_basecomponentclasses.h"
#include "pwr_ssaboxclasses.h"
#include "rt_io_base.h"
#include "rt_io_msg.h"
#include "rt_io_ssab.h"
#include "rt_io_card_init.h"
#include "rt_io_card_close.h"
#include "rt_io_card_read.h"
#include "qbus_io.h"
#include "rt_io_m_ssab_locals.h"
#include "rt_io_bfbeth.h"

/*----------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------*/

#define IO_MAXCHAN 32

typedef struct {
  unsigned int Address;
  int Qbus_fp;
  unsigned int bfb_item;
  int ScanCount[IO_MAXCHAN];
  unsigned int ErrReset;
  unsigned int ErrScanCnt;
} io_sLocal;

static pwr_tStatus AiRangeToCoef(io_sChannel* chanp)
{
  pwr_sClass_ChanAi* cop;
  char buf[120];
  pwr_tStatus sts;
  pwr_tFloat32 PolyCoef1;
  pwr_tFloat32 PolyCoef0;

  cop = chanp->cop;

  if (cop) {
    cop->CalculateNewCoef = 0;

    /* Coef for RawValue to SignalValue conversion */
    cop->SigValPolyCoef0 = 0;
    cop->SigValPolyCoef1 = cop->ChannelSigValRangeHigh / 30000;

    /* Coef for SignalValue to ActualValue conversion */
    if (chanp->ChanClass != pwr_cClass_ChanAit && cop->SensorPolyType == 1) {
      if (!feqf(cop->SensorSigValRangeHigh, cop->SensorSigValRangeLow)) {
        PolyCoef1 = (cop->ActValRangeHigh - cop->ActValRangeLow)
            / (cop->SensorSigValRangeHigh - cop->SensorSigValRangeLow);
        PolyCoef0
            = cop->ActValRangeHigh - cop->SensorSigValRangeHigh * PolyCoef1;
        cop->SensorPolyCoef1 = cop->SigValPolyCoef1 * PolyCoef1;
        cop->SensorPolyCoef0 = PolyCoef0 + PolyCoef1 * cop->SigValPolyCoef0;
      } else {
        sts = gdh_ObjidToName(
            chanp->ChanAref.Objid, buf, sizeof(buf), cdh_mName_volumeStrict);
        if (EVEN(sts))
          return sts;
        errh_Error("Invalid SigValueRange in Ai channel %s", buf);
        return IO__CHANRANGE;
      }
    }
  }
  return IO__SUCCESS;
}

static pwr_tStatus IoCardInit(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  pwr_sClass_Ai_AI32uP* op;
  io_sLocal* local;
  int i;
  io_sChannel* chanp;
  io_sRackLocal* r_local = (io_sRackLocal*)(rp->Local);

  op = (pwr_sClass_Ai_AI32uP*)cp->op;
  local = calloc(1, sizeof(*local));
  cp->Local = local;
  local->Address = op->RegAddress;
  local->Qbus_fp = r_local->Qbus_fp;

  errh_Info("Init of ai card '%s'", cp->Name);

  /* Caluclate polycoeff */
  chanp = cp->chanlist;
  for (i = 0; i < cp->ChanListSize; i++) {
    AiRangeToCoef(chanp);
    chanp++;
  }

  local->ErrReset = 1.0 / ctx->ScanTime + 0.5;
  if (local->ErrReset < 2)
    local->ErrReset = 2;

  return 1;
}

/*----------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------*/
static pwr_tStatus IoCardClose(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  io_sLocal* local;

  errh_Info("IO closing ai card '%s'", cp->Name);

  local = (io_sLocal*)cp->Local;
  free((char*)local);

  return 1;
}

/*----------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------*/
static pwr_tStatus IoCardRead(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  io_sLocal* local;
  io_sRackLocal* r_local = (io_sRackLocal*)(rp->Local);
  pwr_tInt16 data = 0;
  pwr_sClass_Ai_AI32uP* op;
  pwr_sClass_Ssab_RemoteRack* rrp;
  int i;
  pwr_tFloat32 actvalue = 0.0;
  io_sChannel* chanp;
  pwr_sClass_ChanAi* cop;
  pwr_sClass_Ai* sop;
  int sts;
  qbus_io_read rb;
  int bfb_error = 0;

  local = (io_sLocal*)cp->Local;
  op = (pwr_sClass_Ai_AI32uP*)cp->op;

  chanp = &cp->chanlist[0];
  for (i = 0; i < cp->ChanListSize; i++) {
    if (!chanp->cop) {
      chanp++;
      continue;
    }
    cop = (pwr_sClass_ChanAi*)chanp->cop;
    sop = (pwr_sClass_Ai*)chanp->sop;

    if (cop->CalculateNewCoef)
      AiRangeToCoef(chanp);

    if (cop->ConversionOn) {
      if (local->ScanCount[i] <= 1) {
        if (r_local->Qbus_fp != 0 && r_local->s == 0) {
          rb.Address = local->Address + 2 * i;
          sts = read(local->Qbus_fp, &rb, sizeof(rb));
          data = (unsigned short)rb.Data;
        } else {
          /* Ethernet I/O, Get data from current address */
          data = bfbeth_get_data(
              r_local, (pwr_tUInt16)(local->Address + 2 * i), &sts);
          /* Yes, we want to read this address the next time aswell */
          bfbeth_set_read_req(r_local, (pwr_tUInt16)(local->Address + 2 * i));

          if (sts == -1) {
            /* Error handling for ethernet Qbus-I/O */
            rrp = (pwr_sClass_Ssab_RemoteRack*)rp->op;
            if (bfb_error == 0) {
              op->ErrorCount++;
              bfb_error = 1;
              if (op->ErrorCount == op->ErrorSoftLimit) {
                errh_Error(
                    "IO Error soft limit reached on card '%s'", cp->Name);
                ctx->IOHandler->CardErrorSoftLimit = 1;
                ctx->IOHandler->ErrorSoftLimitObject
                    = cdh_ObjidToAref(cp->Objid);
              }
              if (op->ErrorCount == op->ErrorHardLimit) {
                errh_Error(
                    "IO Error hard limit reached on card '%s', stall action %d",
                    cp->Name, rrp->StallAction);
                ctx->IOHandler->CardErrorHardLimit = 1;
                ctx->IOHandler->ErrorHardLimitObject
                    = cdh_ObjidToAref(cp->Objid);
              }
              if (op->ErrorCount >= op->ErrorHardLimit
                  && rrp->StallAction == pwr_eSsabStallAction_ResetInputs) {
                data = 0;
                sts = 1;
              }
              if (op->ErrorCount >= op->ErrorHardLimit
                  && rrp->StallAction == pwr_eSsabStallAction_EmergencyBreak) {
                ctx->Node->EmergBreakTrue = 1;
                return IO__ERRDEVICE;
              }
            }
            if (sts == -1) {
              chanp++;
              continue;
            }
          } else {
            op->ErrorCount = 0;
          }
        }

        if (sts == -1) {
          /* Increase error count and check error limits */
          op->ErrorCount++;

          if (op->ErrorCount == op->ErrorSoftLimit) {
            errh_Error("IO Error soft limit reached on card '%s'", cp->Name);
            ctx->IOHandler->CardErrorSoftLimit = 1;
            ctx->IOHandler->ErrorSoftLimitObject = cdh_ObjidToAref(cp->Objid);
          }
          if (op->ErrorCount >= op->ErrorHardLimit) {
            errh_Error("IO Error hard limit reached on card '%s', IO stopped",
                cp->Name);
            ctx->Node->EmergBreakTrue = 1;
            ctx->IOHandler->CardErrorHardLimit = 1;
            ctx->IOHandler->ErrorHardLimitObject = cdh_ObjidToAref(cp->Objid);
            return IO__ERRDEVICE;
          }
          chanp++;
          continue;
        }
        /* Convert rawvalue to sigvalue and actualvalue */
        sop->RawValue = data;
        sop->SigValue = data * cop->SigValPolyCoef1 + cop->SigValPolyCoef0;
        switch (chanp->ChanClass) {
        case pwr_cClass_ChanAi:
          io_ConvertAi(cop, data, &actvalue);
          break;
        case pwr_cClass_ChanAit:
          io_ConvertAit((pwr_sClass_ChanAit*)cop, data, &actvalue);
          break;
        }

        /* Filter */
        if (sop->FilterType == 1 && sop->FilterAttribute[0] > 0
            && sop->FilterAttribute[0] > ctx->ScanTime) {
          actvalue = *(pwr_tFloat32*)chanp->vbp
              + ctx->ScanTime / sop->FilterAttribute[0]
                  * (actvalue - *(pwr_tFloat32*)chanp->vbp);
        }

        *(pwr_tFloat32*)chanp->vbp = actvalue;
        local->ScanCount[i] = cop->ScanInterval + 1;
      }
      local->ScanCount[i]--;
    }
    chanp++;
  }

  /* Fix for qbus errors */
  local->ErrScanCnt++;
  if (local->ErrScanCnt >= local->ErrReset) {
    local->ErrScanCnt = 0;
    if (op->ErrorCount > op->ErrorSoftLimit)
      op->ErrorCount--;
  }

  return 1;
}

/*----------------------------------------------------------------------------*\
  Every method to be exported to the workbench should be registred here.
\*----------------------------------------------------------------------------*/

pwr_dExport pwr_BindIoMethods(Ai_AI32uP) = { pwr_BindIoMethod(IoCardInit),
  pwr_BindIoMethod(IoCardClose), pwr_BindIoMethod(IoCardRead), pwr_NullMethod };
