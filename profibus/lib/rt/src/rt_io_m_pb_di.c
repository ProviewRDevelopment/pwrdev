/*
 * ProviewR   Open Source Process Control.
 * Copyright (C) 2005-2019 SSAB EMEA AB.
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

/* rt_io_m_pb_di.c
   PROVIEW/R	*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/ioctl.h>

#include "pwr_profibusclasses.h"
#include "rt_io_base.h"
#include "rt_io_bus.h"
#include "rt_io_msg.h"
#include "rt_io_pb_locals.h"

#define IO_CONVMASK_ALL 0xFFFF

/*----------------------------------------------------------------------------*\
  Move di data word to valuebase.
\*----------------------------------------------------------------------------*/
void pbio_DiUnpackWord(
    io_sCard* cp, pwr_tUInt16 data, pwr_tUInt16 mask, int index)
{
  io_sChannel* chanp;

  if (index == 0)
    chanp = &cp->chanlist[0];
  else
    chanp = &cp->chanlist[16];

  if (mask == IO_CONVMASK_ALL) {
    /* No conversion test */
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 1) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 2) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 4) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 8) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 16) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 32) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 64) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 128) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 256) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 512) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 1024) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 2048) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 4096) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 8192) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 16384) != 0);
    chanp++;
    if (chanp->cop && chanp->sop)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 32768) != 0);
    chanp++;
  } else {
    if (chanp->cop && chanp->sop && mask & 1)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 1) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 2)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 2) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 4)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 4) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 8)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 8) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 16)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 16) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 32)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 32) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 64)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 64) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 128)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 128) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 256)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 256) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 512)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 512) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 1024)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 1024) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 2048)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 2048) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 4096)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 4096) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 8192)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 8192) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 16384)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 16384) != 0);
    chanp++;
    if (chanp->cop && chanp->sop && mask & 32768)
      *(pwr_tUInt16*)(chanp->vbp) = ((data & 32768) != 0);
    chanp++;
  }
}

/*----------------------------------------------------------------------------*\
   Init method for the Pb module Di
\*----------------------------------------------------------------------------*/
static pwr_tStatus IoCardInit(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  io_sCardLocal* local;
  pwr_sClass_Pb_Di* op;

  op = (pwr_sClass_Pb_Di*)cp->op;
  local = (io_sCardLocal*)cp->Local;

  // Check configuration

  if (op->NumberOfChannels != 8 && op->NumberOfChannels != 16
      && op->NumberOfChannels != 32)
    op->Status = PB_MODULE_STATE_NOTINIT;

  if (op->Orientation > op->NumberOfChannels)
    op->Status = PB_MODULE_STATE_NOTINIT;

  if (op->Status < PB_MODULE_STATE_OPERATE)
    errh_Info("Error initializing Pb module Di %s", cp->Name);

  return IO__SUCCESS;
}

/*----------------------------------------------------------------------------*\
   Read method for the Pb module Di
\*----------------------------------------------------------------------------*/
static pwr_tStatus IoCardRead(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  io_sCardLocal* local;
  pwr_sClass_Pb_Di* op;
  pwr_sClass_Pb_DP_Slave* slave;
  int i;
  io_sChannel* chanp;
  pwr_sClass_ChanDi* chan_di;
  pwr_sClass_Di* sig_di;
  pwr_tUInt32 mask = 0;

  pwr_tUInt16 data[2] = { 0, 0 };
  pwr_tUInt32* data32;

  local = (io_sCardLocal*)cp->Local;
  op = (pwr_sClass_Pb_Di*)cp->op;
  slave = (pwr_sClass_Pb_DP_Slave*)rp->op;

  if (op->Status >= PB_MODULE_STATE_OPERATE && slave->DisableSlave != 1) {
    memcpy(&data, local->input_area + op->OffsetInputs, op->BytesOfInput);
    data32 = (pwr_tUInt32*)&data;

    if (slave->ByteOrdering == pwr_eByteOrderingEnum_BigEndian) {
      if (op->Orientation == PB_ORIENTATION_WORD) {
        data[0] = swap16(data[0]);
        data[1] = swap16(data[1]);
      } else if (op->Orientation == PB_ORIENTATION_DWORD) {
        *data32 = swap32(*data32);
      }
    }

    // Mask?
    data[0] = data[0] ^ op->InvMask1;
    data[1] = data[1] ^ op->InvMask2;

    // Packa upp
    for (i = 0; i < cp->ChanListSize; i++) {
      chanp = &cp->chanlist[i];
      chan_di = (pwr_sClass_ChanDi*)chanp->cop;
      sig_di = (pwr_sClass_Di*)chanp->sop;
      if (chan_di && sig_di) {
        mask = 1 << chan_di->Number;
        *(pwr_tUInt16*)(chanp->vbp) = ((*data32 & mask) != 0);
      }
    }
    /*
        data[0] = data[0] ^ op->InvMask1;
        pbio_DiUnpackWord(cp, data[0], op->ConvMask1, 0);

        if (op->NumberOfChannels > 16) {
          data[1] = data[1] ^ op->InvMask2;
          pbio_DiUnpackWord(cp, data[1], op->ConvMask2, 1);
        }
    */
  }
  return IO__SUCCESS;
}

/*----------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------*/
static pwr_tStatus IoCardClose(
    io_tCtx ctx, io_sAgent* ap, io_sRack* rp, io_sCard* cp)
{
  io_sCardLocal* local;
  local = cp->Local;

  free((char*)local);

  return IO__SUCCESS;
}

/*----------------------------------------------------------------------------*\
  Every method to be exported to the workbench should be registred here.
\*----------------------------------------------------------------------------*/

pwr_dExport pwr_BindIoMethods(Pb_Di) = { pwr_BindIoMethod(IoCardInit),
  pwr_BindIoMethod(IoCardRead), pwr_BindIoMethod(IoCardClose), pwr_NullMethod };