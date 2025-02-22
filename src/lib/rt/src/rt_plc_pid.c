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

#include "rt_plc.h"

/* 		PLC RUTINER			*/

/*_*
  INC3P
  function:	accumulate output change from controller
                and convert to Open or Close orders.

  2014-02-18	Werner	Limit acc to new attribute "MaxWindup"

  @aref inc3p Inc3p
*/

void inc3p_init(pwr_sClass_inc3p* object)
{
  object->Acc = 0;
}

void inc3p_exec(plc_sThread* tp, pwr_sClass_inc3p* object)
{
  /*  Clear old orders */

  if (object->Open && object->Acc <= 0)
    object->Open = FALSE;
  if (object->Close && object->Acc >= 0)
    object->Close = FALSE;

  /* Get  Incremental input */

  object->OutChange = *object->OutChangeP;
  object->Acc += object->OutChange * object->Gain;

  if /* Open */
      ((object->Acc >= object->MinTim)
          || ((object->Open == TRUE) && (object->Acc > 0)
                 && (object->TimerFlag == TRUE))) {
    *object->CloseP = FALSE;
    object->Close = FALSE;
    object->TimerDO = object->OpenP;
    object->TimerTime = object->Acc;
    timer_in(tp, object);
    if (object->TimerCount > 0) {
      object->Open = TRUE;
      *object->OpenP = TRUE;
      object->AccTim = 0;
      if (object->Acc > *object->ScanTime)
        object->Acc -= *object->ScanTime;
      else
        object->Acc = 0;
    } else {
      object->Open = FALSE;
      *object->OpenP = TRUE;
      object->TimerCount = 0;
      object->AccTim += *object->ScanTime;
    }
  } else if /* Close */
      ((object->Acc <= -object->MinTim)
          || ((object->Close == TRUE) && (object->Acc < 0)
                 && (object->TimerFlag == TRUE))) {
    *object->OpenP = FALSE;
    object->Open = FALSE;
    object->TimerDO = object->CloseP;
    object->TimerTime = -object->Acc;
    timer_in(tp, object);
    if (object->TimerCount > 0) {
      object->Close = TRUE;
      *object->CloseP = TRUE;
      object->AccTim = 0;
      if (object->Acc < -*object->ScanTime)
        object->Acc += *object->ScanTime;
      else
        object->Acc = 0;
    } else {
      object->Close = FALSE;
      *object->CloseP = TRUE;
      object->TimerCount = 0;
      object->AccTim += *object->ScanTime;
    }
  } else /* No output */
  {
    object->Open = FALSE;
    *object->OpenP = FALSE;
    object->Close = FALSE;
    *object->CloseP = FALSE;
    object->TimerCount = 0;
    if (object->MaxTim > 0) /* Limit integration */
    {
      object->AccTim += *object->ScanTime;
      if (object->AccTim >= object->MaxTim) {
        object->Acc = 0;
        object->AccTim = 0;
      }
    }
  }

  /* Limit output 2014-02-18 / Werner */
  if ((object->Acc > object->MaxWindup) && (object->MaxWindup > 0.0))
    object->Acc = object->MaxWindup;
  if ((object->Acc < -object->MaxWindup) && (object->MaxWindup > 0.0))
    object->Acc = -object->MaxWindup;
}

/*_*
  POS3P
  function:	Compare controller output to actual position
                Open or close if outside of deadzone.

  @aref pos3p Pos3p

*/
void pos3p_exec(plc_sThread* tp, pwr_sClass_pos3p* object)
{
  float error;

  /* Get  Setpoint and pos */
  object->OutVal = *object->OutValP;
  object->Pos = *object->PosP;
  error = *object->OutValP - *object->PosP;

  /* Open ? */
  if ((error > object->ErrSta)
      || ((object->Open == TRUE) && (error > object->ErrSto))) {
    *object->CloseP = FALSE;
    object->Close = FALSE;
    object->Open = TRUE;
    object->TimerDO = object->OpenP;
    object->TimerTime = error * object->Gain;
    if ((error <= object->ErrSta) && (*object->OpenP == FALSE))
      object->TimerTime = 0;
    timer_in(tp, object);
    if (object->TimerCount > 0) {
      *object->OpenP = TRUE;
    } else {
      *object->OpenP = FALSE;
      object->TimerCount = 0;
    }
  }
  /* Close ? */
  else if ((error < -object->ErrSta)
      || ((object->Close == TRUE) && (error < -object->ErrSto))) {
    *object->OpenP = FALSE;
    object->Open = FALSE;
    object->Close = TRUE;
    object->TimerDO = object->CloseP;
    object->TimerTime = -error * object->Gain;
    if ((error >= -object->ErrSta) && (*object->CloseP == FALSE))
      object->TimerTime = 0;
    timer_in(tp, object);
    if (object->TimerCount > 0) {
      *object->CloseP = TRUE;
    } else {
      *object->CloseP = FALSE;
      object->TimerCount = 0;
    }
  } else {
    /* No output */
    object->Open = FALSE;
    *object->OpenP = FALSE;
    object->Close = FALSE;
    *object->CloseP = FALSE;
    object->TimerCount = 0;
  }
}
/*_*
  OUT2P
  function:	Konvert analog controll output to binary on / off

  @aref out2p Out2p
*/
void out2p_exec(plc_sThread* tp, pwr_sClass_out2p* object)
{
  float ontime;
  float offtime;
  /* Get  Input */
  object->OutVal = *object->OutValP;

  if (object->MaxOut > object->MinOut) {
    ontime = (object->OutVal - object->MinOut)
        / (object->MaxOut - object->MinOut) * object->Period;
    offtime = object->Period - ontime;
  } else {
    ontime = 0;
    offtime = 0;
  }
  /* Increase Running-time */
  object->RunTime += *object->ScanTime;

  /* Should we turn off ? */
  if (object->Order == TRUE) {
    if ((object->RunTime > ontime) && (object->OutVal < object->MaxOut)) {
      object->Order = FALSE;
      object->RunTime = 0;
    }
  }
  /* Should we turn on ? */
  else {
    if ((object->RunTime > offtime) && (object->OutVal > object->MinOut)) {
      object->Order = TRUE;
      object->RunTime = 0;
    }
  }
}

/*_*
   MODE
  function:	Set controller or drive in different operation mode.
                Pass analog values depending on mode.
  @aref mode Mode
*/

void mode_exec(plc_sThread* tp, pwr_sClass_mode* object)
{
  /* Get indata */
  object->ProcVal = *object->ProcValP;
  object->XSetVal = *object->XSetValP;
  object->XForcVal = *object->XForcValP;
  object->Forc1 = *object->Forc1P;
  object->Forc2 = *object->Forc2P;
  object->OutVal = *object->OutValP;

  /* Make appropriate actions, depending on actual mode */

  /* Manual */
  if (object->OpMod <= 1) {
    object->Force = TRUE;
    object->ManMode = TRUE;
    object->AutMode = FALSE;
    object->CascMod = FALSE;
    /* External setpoint ? */
    if ((object->AccMod & 2) == 0)
      object->SetVal = object->XSetVal;
    /* Test if Force in manual mode */
    if (object->Forc1)
      object->ForcVal = object->XForcVal;
    else {
      if (object->ForcVal < object->MinOut)
	object->ForcVal = object->MinOut;
      else if (object->ForcVal > object->MaxOut)
	object->ForcVal = object->MaxOut;
    }
  } else
  /* Not Manual Mode */
  {
    /* Auto */
    if (object->OpMod == 2) {
      object->ManMode = FALSE;
      object->AutMode = TRUE;
      object->CascMod = FALSE;
    }
    /* Cascade mode */
    else {
      object->ManMode = FALSE;
      object->AutMode = FALSE;
      object->CascMod = TRUE;
      object->SetVal = object->XSetVal;
    }
    /* Test if force in Auto or Cascade */
    if (object->Forc1 || object->Forc2) {
      object->Force = TRUE;
      object->ForcVal = object->XForcVal;
    } else {
      object->Force = FALSE;
      object->ForcVal = object->OutVal;
    }
  }
  object->Error = object->ProcVal - object->SetVal;
}

/*_*
  PID
  function:	PID or PD Controller with basic facilities
                Possible to turn off integration and to force
                output to desired value.

                New Attributes 2014-02-18 / Werner:
                WindupMask	Config
                MinWindup	Config
                MaxWindup	Config
                PDManOffset	Internal
                OutWindup	Internal

  @aref pid Pid
*/

void pid_exec(plc_sThread* tp, pwr_sClass_pid* object)
{
/* Define Algoritm bitmask */
#define IALG 1 /* Integral part -> Incremental algorithm */
#define PALG 2 /* Proportional part exists */
#define PAVV 4 /* Proportional part working on control difference */
#define DALG 8 /* Derivative part exists */
#define DAVV 16 /* Derivative part working on control difference */

//#define IWUP 1 /* Windup limitation on I part */
#define BIWUP 2 /* Windup limitation on Bias and I part */
#define BPIWUP 4 /* Windup limitation on Bias PI part */
#define BPIDWUP 8 /* Windup limitation on Bias and PID part (Default, old funcionality */

  float xold; /* Local variables */
  float eold;
  float bfold;
  float ddiff;
  float derold;
  double ut;
  double dut;
  float kd;
  double absut;
  float gain;

  /* Save old values */
  xold = object->ProcVal;
  eold = object->ControlDiff;
  bfold = object->Bias;
  derold = object->FiltDer;

  /* Get Input */
  object->ProcVal = *object->ProcValP;
  object->SetVal = *object->SetValP;
  object->ForcVal = *object->ForcValP;
  object->Bias = *object->BiasP;
  object->Force = *object->ForceP;
  object->IntOff = *object->IntOffP;

  /* Calculate Controller Error and Filtered derivate */

  object->ControlDiff = object->ProcVal - object->SetVal;
  ddiff = ((object->PidAlg & DAVV) != 0)
      ? (object->ControlDiff - eold) / *object->ScanTime
      : (object->ProcVal - xold) / *object->ScanTime;
  if (((object->DerGain * *object->ScanTime) >= object->DerTime)
      || (object->DerTime <= 0))
    object->FiltDer = ddiff; /* No Filter */
  else {
    kd = 1.0 / (1.0 + object->DerGain * *object->ScanTime / object->DerTime);
    object->FiltDer += (ddiff - derold) * (1.0 - kd);
  }

  if (object->Inverse == 0)
    gain = object->Gain;
  else
    gain = -object->Gain;

  if (object->Force)
  /* Force */
  {
    object->OutChange = object->ForcVal - object->OutVal;
    object->OutVal = object->OutWindup = object->ForcVal;
    object->EndMin = FALSE;
    object->EndMax = FALSE;

    /* Adjust for bumpless transfer to auto */
    object->PDManOffset = object->OutVal - gain * object->ControlDiff
        - object->BiasGain * object->Bias;

    if ((object->PidAlg & IALG) != 0)
      object->AbsOut = 0.0;
    else
      object->AbsOut = object->OutVal;

    if (object->WindupMask < BIWUP)
      object->OutWindup -= object->BiasGain * object->Bias;
    if (object->WindupMask < BPIWUP)
      object->OutWindup -= gain * object->ControlDiff;

    object->AbsOut = object->OutVal - object->OutWindup;

  }

  else
  /* Auto mode */
  {
    dut = absut = 0.0;

    if ((object->PidAlg & IALG) != 0)
    /* Incremental algorithm */
    {
      /* Integral-part */
      if ((*object->IntOffP == FALSE) && (object->IntTime > 0))
        dut = object->ControlDiff * *object->ScanTime / object->IntTime;

      if ((object->PidAlg & PALG) != 0)
        dut *= gain;
      else
        gain = 0.0; /* Pure I-controller */

      /* Bias */
      if (object->WindupMask >= BIWUP) /* Windup on Bias */
        dut += object->BiasGain * (object->Bias - bfold);
      else
        absut = object->BiasGain * object->Bias;

      /* P-part */
      if (object->WindupMask >= BPIWUP) /* Windup on P */
        dut += ((object->PidAlg & PAVV) != 0)
            ? gain * (object->ControlDiff - eold)
            : gain * (object->ProcVal - xold);
      else
        absut += gain * object->ControlDiff;

      /* Derivative-part */
      if ((object->PidAlg & DALG) != 0) {
        if (object->WindupMask >= BPIDWUP) /* Windup on D */
          dut += gain * (object->FiltDer - derold) * object->DerTime;
        else
          absut += gain * object->FiltDer * object->DerTime;
      }

      /* Limit output */
      object->OutWindup += dut;

      if (object->OutWindup > object->MaxWindup) {
        object->OutWindup = object->MaxWindup;
        object->EndMax = TRUE;
      } else if (object->OutWindup < object->MinWindup) {
        object->OutWindup = object->MinWindup;
        object->EndMin = TRUE;
      }

      ut = object->OutWindup + absut;
      if (ut > object->MaxOut)
        ut = object->MaxOut;
      else if (ut < object->MinOut)
        ut = object->MinOut;
      dut += absut - object->AbsOut;
    }

    else
    /* Nonincremental algorithm */
    {
      /* P-part */
      ut = object->ControlDiff;
      /* Derivative-part */
      if ((object->PidAlg & DALG) != 0)
        ut += object->FiltDer * object->DerTime;
      /* Gain */
      ut *= gain;

      /* Bias and Man offset */
      if (object->PDAbsFlag)
        object->PDManOffset = 0;
      ut += object->BiasGain * object->Bias + object->PDManOffset;

      /* Limit output */
      if (object->MaxOut > object->MinOut) {
        if (ut > object->MaxOut)
          ut = object->MaxOut;
        else if (ut < object->MinOut)
          ut = object->MinOut;
      }
      dut = ut - object->OutVal;
      absut = ut;
    }

    /* Output Auto */
    object->OutChange = dut;
    object->OutVal = ut;
    object->AbsOut = absut;
  }
}
