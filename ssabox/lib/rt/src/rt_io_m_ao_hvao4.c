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

/* rt_io_m_ao_hvao4.c -- io methods for ssab cards.
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
#include "rt_io_card_write.h"
#include "qbus_io.h"
#include "rt_io_m_ssab_locals.h"
#include "rt_io_bfbeth.h"

/*----------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------*/

#define IO_MAXCHAN 8

typedef struct {
  unsigned int Address;
  int Qbus_fp;
  pwr_tFloat32 OldValue[IO_MAXCHAN];
  pwr_tBoolean OldTestOn[IO_MAXCHAN];
  unsigned int ErrReset;
  unsigned int ErrScanCnt;
} io_sLocal;

static pwr_tStatus AoRangeToCoef(io_sChannel* chanp)
{
  pwr_sClass_ChanAo* cop;
  char buf[120];
  pwr_tStatus sts;
  pwr_tFloat32 PolyCoef1;
  pwr_tFloat32 PolyCoef0;

  cop = chanp->cop;

  if (cop) {
    cop->CalculateNewCoef = 0;

    /* Coef for ActualValue to RawValue conversion */
    if (!feqf(cop->ActValRangeHigh, cop->ActValRangeLow)) {
      cop->SigValPolyCoef1
          = (cop->SensorSigValRangeHigh - cop->SensorSigValRangeLow)
          / (cop->ActValRangeHigh - cop->ActValRangeLow);
      cop->SigValPolyCoef0 = cop->SensorSigValRangeHigh
          - cop->ActValRangeHigh * cop->SigValPolyCoef1;
    } else {
      sts = gdh_ObjidToName(
          chanp->ChanAref.Objid, buf, sizeof(buf), cdh_mName_volumeStrict);
      if (EVEN(sts))
        return sts;
      errh_Error("Invalid ActValueRange in Ao channel %s", buf);
      return IO__CHANRANGE;
    }
    /* Coef for ActualValue to SignalValue conversion */
    if (!feqf(cop->ChannelSigValRangeHigh, 0.0f)) {
      PolyCoef0 = 0;
      PolyCoef1 = cop->RawValRangeHigh / cop->ChannelSigValRangeHigh;
      cop->OutPolyCoef1 = cop->SigValPolyCoef1 * PolyCoef1;
      cop->OutPolyCoef0 = PolyCoef0 + PolyCoef1 * cop->SigValPolyCoef0;
    } else {
      sts = gdh_ObjidToName(
          chanp->ChanAref.Objid, buf, sizeof(buf), cdh_mName_volumeStrict);
      if (EVEN(sts))
        return sts;
      errh_Error("Invalid SigValueRange in Ao channel %s", buf);
      return IO__CHANRANGE;
    }
  }
  return IO__SUCCESS;
}

static pwr_tStatus IoCardInit(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  pwr_sClass_Ao_HVAO4* op;
  io_sChannel* chanp;
  int i;
  io_sLocal* local;

  op = (pwr_sClass_Ao_HVAO4*)cp->op;
  local = calloc(1, sizeof(*local));
  local->Address = op->RegAddress;
  local->Qbus_fp = ((io_sRackLocal*)(rp->Local))->Qbus_fp;

  errh_Info("Init of ao card '%s'", cp->Name);

  cp->Local = local;

  /* Caluclate polycoeff */
  chanp = cp->chanlist;
  for (i = 0; i < cp->ChanListSize; i++) {
    AoRangeToCoef(chanp);
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

  local = (io_sLocal*)cp->Local;

  errh_Info("IO closing ao card '%s'", cp->Name);

  free((char*)local);

  return 1;
}

/*----------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------*/
static pwr_tStatus IoCardWrite(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  io_sLocal* local;
  io_sRackLocal* r_local = (io_sRackLocal*)(rp->Local);
  pwr_sClass_Ao_HVAO4* op;
  int i;
  io_sChannel* chanp;
  pwr_sClass_ChanAo* cop;
  pwr_sClass_Ao* sop;
  pwr_tFloat32 value;
  int fixout;
  pwr_tUInt16 data;
  pwr_tFloat32 rawvalue;
  qbus_io_write wb;
  int sts;

  local = (io_sLocal*)cp->Local;
  op = (pwr_sClass_Ao_HVAO4*)cp->op;

  fixout = ctx->Node->EmergBreakTrue && ctx->Node->EmergBreakSelect == FIXOUT;

  chanp = &cp->chanlist[0];
  for (i = 0; i < cp->ChanListSize; i++) {
    if (!chanp->cop) {
      chanp++;
      continue;
    }
    cop = (pwr_sClass_ChanAo*)chanp->cop;
    sop = (pwr_sClass_Ao*)chanp->sop;

    if (fixout)
      value = cop->FixedOutValue;
    else if (cop->TestOn)
      value = cop->TestValue;
    else
      value = *(pwr_tFloat32*)chanp->vbp;

    if (cop->CalculateNewCoef)
      AoRangeToCoef(chanp);

    /* Convert to rawvalue */
    if (value > cop->ActValRangeHigh)
      value = cop->ActValRangeHigh;
    else if (value < cop->ActValRangeLow)
      value = cop->ActValRangeLow;

    rawvalue = cop->OutPolyCoef1 * value + cop->OutPolyCoef0;
    if (rawvalue > 0)
      sop->RawValue = rawvalue + 0.5;
    else
      sop->RawValue = rawvalue - 0.5;
    data = sop->RawValue;
    
    if (r_local->Qbus_fp != 0 && r_local->s == 0) {
      wb.Data = data;
      wb.Address = local->Address + 2 * i;
      sts = write(local->Qbus_fp, &wb, sizeof(wb));
    } else {
      /* Ethernet I/O, Request a write to current address */
      bfbeth_set_write_req(
			   r_local, (pwr_tUInt16)(local->Address + 2 * i), data);
      sts = 1;
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
	errh_Error(
		   "IO Error hard limit reached on card '%s', IO stopped", cp->Name);
	ctx->Node->EmergBreakTrue = 1;
	ctx->IOHandler->CardErrorHardLimit = 1;
	ctx->IOHandler->ErrorHardLimitObject = cdh_ObjidToAref(cp->Objid);
	return IO__ERRDEVICE;
      }
      chanp++;
      continue;
    } else
      local->OldValue[i] = value;

    local->OldTestOn[i] = cop->TestOn;
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

pwr_dExport pwr_BindIoMethods(Ao_HVAO4)
    = { pwr_BindIoMethod(IoCardInit), pwr_BindIoMethod(IoCardClose),
        pwr_BindIoMethod(IoCardWrite), pwr_NullMethod };

pwr_dExport pwr_BindIoMethods(Ao_AO8uP)
    = { pwr_BindIoMethod(IoCardInit), pwr_BindIoMethod(IoCardClose),
        pwr_BindIoMethod(IoCardWrite), pwr_NullMethod };
