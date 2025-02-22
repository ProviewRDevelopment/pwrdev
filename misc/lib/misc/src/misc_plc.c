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

/* misc_plc.c  Plc function object code. */

#include <math.h>
#include <stdlib.h>

#include "co_math.h"
#include "co_time.h"

#include "misc.h"

#define BASE_SPEED 10
#define MAX_ANGLE 60

static float my_random()
{
  static unsigned int seed = 100;

  seed = rand_r(&seed);

  return (float)seed / RAND_MAX * 2 - 1;
}

/*_*
  Misc_PingPongFo

  @aref misc_pingpong
  @aref misc_pingpongfo Misc_PingPongFo
*/
void Misc_PingPongFo_init(pwr_sClass_Misc_PingPongFo* o)
{
  pwr_tDlid dlid;
  pwr_tStatus sts;
  pwr_sClass_Misc_PingPong* co;

  sts = gdh_DLRefObjectInfoAttrref(
      &o->PlcConnect, (void**)&o->PlcConnectP, &dlid);
  if (EVEN(sts))
    o->PlcConnectP = 0;

  co = (pwr_sClass_Misc_PingPong*)o->PlcConnectP;
  co->LeftKnobPtr = (pwr_tFloat32*)gdh_TranslateRtdbPointer(
      (unsigned long)co->LeftKnob.ActualValue);
  co->RightKnobPtr = (pwr_tFloat32*)gdh_TranslateRtdbPointer(
      (unsigned long)co->RightKnob.ActualValue);
  co->XCoordinate = co->Height / 2;
  co->YCoordinate = -co->BallRadius;
  co->Speed = 15;
  co->Direction = -20;
}

void Misc_PingPongFo_exec(plc_sThread* tp, pwr_sClass_Misc_PingPongFo* o)
{
  pwr_sClass_Misc_PingPong* co = (pwr_sClass_Misc_PingPong*)o->PlcConnectP;
  if (!co || feqf(co->Width, 0.0f))
    return;

  co->XCoordinate
      += co->Speed * tp->PlcThread->ScanTime * cos(co->Direction / 180 * M_PI);
  co->YCoordinate
      -= co->Speed * tp->PlcThread->ScanTime * sin(co->Direction / 180 * M_PI);

  if (co->UseLeftKnob)
    co->LeftPos = *co->LeftKnobPtr;
  else
    co->LeftPos = co->LeftSlider;

  if (co->UseRightKnob)
    co->RightPos = *co->RightKnobPtr;
  else
    co->RightPos = co->RightSlider;

  switch (co->Mode) {
  case pwr_eMisc_PingPongModeEnum_Idle: {
    if (co->OldMode != co->Mode) {
      co->State = pwr_eMisc_PingPongStateEnum_Playing;
      time_GetTime(&co->StateShiftTime);
      co->LeftScore = 0;
      co->RightScore = 0;
      co->XCoordinate = co->Height / 2;
      co->YCoordinate = -co->BallRadius;
      co->Speed = 15;
      co->Direction = -20;
    }
    if (co->XCoordinate - co->BallRadius < 0) {
      co->XCoordinate = co->BallRadius - (co->XCoordinate - co->BallRadius);
      if (co->Direction > 0)
        co->Direction = -co->Direction + 180 + my_random() * 10;
      else
        co->Direction = -co->Direction - 180 + my_random() * 10;
      if (fabs(co->Direction) > MAX_ANGLE)
        co->Direction = my_random() * 10;
    }
    if (co->XCoordinate + co->BallRadius > co->Width) {
      co->XCoordinate = co->Width - co->BallRadius
          - (co->XCoordinate + co->BallRadius - co->Width);
      if (co->Direction > 0)
        co->Direction = -co->Direction + 180 + my_random() * 10;
      else
        co->Direction = -co->Direction - 180 + my_random() * 10;
      if (fabs(co->Direction) < 135)
        co->Direction = 180 - my_random() * 10;
    }
    if (co->YCoordinate - co->BallRadius < 0) {
      co->YCoordinate = co->BallRadius - (co->YCoordinate - co->BallRadius);
      co->Direction = -co->Direction;
    }
    if (co->YCoordinate + co->BallRadius > co->Height) {
      co->YCoordinate = co->Height - co->BallRadius
          - (co->YCoordinate + co->BallRadius - co->Height);
      co->Direction = -co->Direction;
    }
    break;
  }
  case pwr_eMisc_PingPongModeEnum_OnePlayer: {
    if (co->OldMode != co->Mode) {
      co->State = pwr_eMisc_PingPongStateEnum_ServeLeft;
      time_GetTime(&co->StateShiftTime);
      co->LeftScore = 0;
      co->RightScore = 0;
      co->XCoordinate = co->BallRadius;
      co->YCoordinate = co->Height / 2;
      co->Speed = 0;
    }
    switch (co->State) {
    case pwr_eMisc_PingPongStateEnum_Playing: {
      pwr_tTime current;
      pwr_tDeltaTime diff;

      time_GetTime(&current);
      time_Adiff(&diff, &current, &co->StateShiftTime);
      co->LevelFactor = 1.0 + time_DToFloat(0, &diff) * co->LevelIncrement / 20;

      if (co->XCoordinate - co->BallRadius < 0) {
        co->XCoordinate = co->BallRadius - (co->XCoordinate - co->BallRadius);
        if (co->Direction > 0)
          co->Direction = -co->Direction + 180 + my_random() * 20;
        else
          co->Direction = -co->Direction - 180 + my_random() * 20;
        if (fabs(co->Direction) > MAX_ANGLE)
          co->Direction = my_random() * 10;
        co->Speed = BASE_SPEED * co->LeftLevel * co->LevelFactor;
      }
      if (co->XCoordinate + co->BallRadius > co->Width) {
        if (co->YCoordinate
                >= co->RightPos - co->RacketWidth / 2 - co->BallRadius
            && co->YCoordinate
                <= co->RightPos + co->RacketWidth / 2 + co->BallRadius) {
          // Hit on racket
          if (co->Direction > 0) {
            co->Direction = -co->Direction + 180 + my_random() * 10;
          } else {
            co->Direction = -co->Direction - 180 + my_random() * 10;
          }
          if (fabs(co->Direction) < 135)
            co->Direction = my_random() * 10;
          co->XCoordinate = co->Width - co->BallRadius
              - (co->XCoordinate + co->BallRadius - co->Width);
          co->Speed = BASE_SPEED * co->RightLevel * co->LevelFactor;
          co->BallCount++;
        } else {
          // Failure
          co->State = pwr_eMisc_PingPongStateEnum_ServeLeft;
          time_GetTime(&co->StateShiftTime);
        }
      }
      if (co->YCoordinate - co->BallRadius < 0) {
        co->YCoordinate = co->BallRadius - (co->YCoordinate - co->BallRadius);
        co->Direction = -co->Direction;
      }
      if (co->YCoordinate + co->BallRadius > co->Height) {
        co->YCoordinate = co->Height - co->BallRadius
            - (co->YCoordinate + co->BallRadius - co->Height);
        co->Direction = -co->Direction;
      }
      break;
    }
    case pwr_eMisc_PingPongStateEnum_ServeLeft: {
      pwr_tTime current;
      pwr_tDeltaTime diff;

      if (co->XCoordinate + co->BallRadius > co->Width + 5) {
        co->XCoordinate = co->BallRadius;
        co->YCoordinate = co->Height / 2;
        co->Speed = 0;
      }
      time_GetTime(&current);
      time_Adiff(&diff, &current, &co->StateShiftTime);
      if (time_DToFloat(0, &diff) > 2) {
        co->Speed = BASE_SPEED * co->LeftLevel;
        co->Direction = my_random() * 20;
        co->State = pwr_eMisc_PingPongStateEnum_Playing;
        co->LastBallCount = co->BallCount;
        co->BallCount = 0;
      }
      break;
    }
    }
    break;
  }
  case pwr_eMisc_PingPongModeEnum_TwoPlayers: {
    if (co->OldMode != co->Mode || co->NewMatch) {
      co->NewMatch = 0;
      co->State = pwr_eMisc_PingPongStateEnum_ServeRight;
      time_GetTime(&co->StateShiftTime);
      co->LeftScore = 0;
      co->RightScore = 0;
      co->XCoordinate = co->Width - co->BallRadius;
      co->YCoordinate = co->Height / 2;
      co->Speed = 0;
    }
    switch (co->State) {
    case pwr_eMisc_PingPongStateEnum_Playing: {
      pwr_tTime current;
      pwr_tDeltaTime diff;

      time_GetTime(&current);
      time_Adiff(&diff, &current, &co->StateShiftTime);
      co->LevelFactor = 1.0 + time_DToFloat(0, &diff) * co->LevelIncrement / 20;

      if (co->XCoordinate - co->BallRadius < 0) {
        if (co->YCoordinate
                >= co->LeftPos - co->RacketWidth / 2 - co->BallRadius
            && co->YCoordinate
                <= co->LeftPos + co->RacketWidth / 2 + co->BallRadius) {
          // Hit on racket
          co->XCoordinate = co->BallRadius - (co->XCoordinate - co->BallRadius);
          if (co->Direction > 0)
            co->Direction = -co->Direction + 180 + my_random() * 20;
          else
            co->Direction = -co->Direction - 180 + my_random() * 20;
          if (fabs(co->Direction) > MAX_ANGLE)
            co->Direction = my_random() * 10;
          co->Speed = BASE_SPEED * co->LeftLevel * co->LevelFactor;
        } else {
          // Failure
          co->RightScore++;
          co->State = pwr_eMisc_PingPongStateEnum_ServeRight;
          time_GetTime(&co->StateShiftTime);
        }
      }
      if (co->XCoordinate + co->BallRadius > co->Width) {
        if (co->YCoordinate
                >= co->RightPos - co->RacketWidth / 2 - co->BallRadius
            && co->YCoordinate
                <= co->RightPos + co->RacketWidth / 2 + co->BallRadius) {
          // Hit on racket
          co->XCoordinate = co->Width - co->BallRadius
              - (co->XCoordinate + co->BallRadius - co->Width);
          if (co->Direction > 0)
            co->Direction = -co->Direction + 180 + my_random() * 10;
          else
            co->Direction = -co->Direction - 180 + my_random() * 10;
          if (fabs(co->Direction) < 135)
            co->Direction = my_random() * 10;
          co->Speed = BASE_SPEED * co->RightLevel * co->LevelFactor;
        } else {
          // Failure
          co->LeftScore++;
          co->State = pwr_eMisc_PingPongStateEnum_ServeLeft;
          time_GetTime(&co->StateShiftTime);
        }
      }
      if (co->YCoordinate - co->BallRadius < 0) {
        co->YCoordinate = co->BallRadius - (co->YCoordinate - co->BallRadius);
        co->Direction = -co->Direction;
      }
      if (co->YCoordinate + co->BallRadius > co->Height) {
        co->YCoordinate = co->Height - co->BallRadius
            - (co->YCoordinate + co->BallRadius - co->Height);
        co->Direction = -co->Direction;
      }
      break;
    }
    case pwr_eMisc_PingPongStateEnum_ServeLeft: {
      pwr_tTime current;
      pwr_tDeltaTime diff;

      if (co->XCoordinate + co->BallRadius > co->Width + 5) {
        co->XCoordinate = co->BallRadius;
        co->YCoordinate = co->Height / 2;
        co->Speed = 0;
      }
      time_GetTime(&current);
      time_Adiff(&diff, &current, &co->StateShiftTime);
      if (time_DToFloat(0, &diff) > 2) {
        co->Speed = BASE_SPEED * co->LeftLevel;
        co->Direction = my_random() * 20;
        co->State = pwr_eMisc_PingPongStateEnum_Playing;
      }
      break;
    }
    case pwr_eMisc_PingPongStateEnum_ServeRight: {
      pwr_tTime current;
      pwr_tDeltaTime diff;

      if (co->XCoordinate + co->BallRadius < -5) {
        co->XCoordinate = co->Width - co->BallRadius;
        co->YCoordinate = co->Height / 2;
        co->Speed = 0;
      }
      time_GetTime(&current);
      time_Adiff(&diff, &current, &co->StateShiftTime);
      if (time_DToFloat(0, &diff) > 2) {
        co->Speed = BASE_SPEED * co->LeftLevel;
        co->Direction = 180 + my_random() * 20;
        co->State = pwr_eMisc_PingPongStateEnum_Playing;
      }
      break;
    }
    }
    break;
  }
  }
  float height;
  if (fabs(co->Direction) < 90) {
    if (co->XCoordinate < co->Width * 3 / 4)
      height = (1 - co->XCoordinate / co->Width * 4 / 3);
    else
      height = ((co->XCoordinate - co->Width * 3 / 4) / co->Width * 4);
  } else {
    if (co->XCoordinate < co->Width / 4)
      height = (1 - co->XCoordinate / co->Width * 4);
    else
      height = ((co->XCoordinate - co->Width / 4) / co->Width * 4 / 3);
  }
  co->XShadow = co->XCoordinate + height * 4;
  co->YShadow = co->YCoordinate + height * 1;

  co->OldMode = co->Mode;
}

#define DEMOPATTERN_MAXSTATE 33

void Misc_DemoPattern_exec(plc_sThread* tp, pwr_sClass_Misc_DemoPattern* o)
{
  int new_state;

  if (!*o->OnP) {
    o->Mask1 = 0;
    o->Mask2 = 0;
    o->State = 0;
    o->CycleCnt = 0;
    o->StateCnt = 0;
  } else {
    o->Cycle = o->CycleTime / tp->PlcThread->ScanTime / o->NumberOfOutputs;
    if (o->CycleCnt >= o->Cycle)
      o->CycleCnt = 0;
    else
      o->CycleCnt++;

    if (o->CycleCnt != 1)
      return;

    if (o->StateCnt >= o->NumberOfOutputs - 1)
      o->StateCnt = 0;
    o->StateCnt++;

    if (o->StateCnt == 1) {
      if (o->State >= DEMOPATTERN_MAXSTATE)
        o->State = 0;
      else
        o->State++;
      new_state = 1;

    } else
      new_state = 0;

    switch (o->State) {
    case 0:
      if (new_state) {
        o->Mask1 = 1;
        o->Mask2 = 0;
      } else
        o->Mask1 = o->Mask1 << 1;
      break;
    case 1:
      if (new_state) {
        o->Mask1 = 1 << 31;
        o->Mask2 = 0;
      } else
        o->Mask1 = o->Mask1 >> 1;
      break;
    case 2:
    case 3:
      if (new_state) {
        o->Mask1 = 1;
        o->Mask2 = 1 << 31;
      } else {
        o->Mask1 = o->Mask1 << 1;
        o->Mask2 = o->Mask2 >> 1;
      }
      break;
    case 4:
    case 5:
      if (new_state) {
        o->Mask1 = 1 | (1 << 16);
        o->Mask2 = (1 << 31) | (1 << 16);
      } else {
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
        o->Mask2 = (o->Mask2 << 31) | (o->Mask2 >> 1);
      }
      break;
    case 6:
    case 7:
      if (new_state) {
        o->Mask1 = 1 | (1 << 16);
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 8:
      if (new_state) {
        o->Mask1 = 1 | (1 << 8) | (1 << 16) | (1 << 24);
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 9:
      if (new_state) {
        o->Mask1 = 1 | (1 << 4) | (1 << 8) | (1 << 12) | (1 << 16) | (1 << 20) | (1 << 24)
            | (1 << 28);
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 10:
      if (new_state) {
        o->Mask1 = 1 | (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8) | (1 << 10) | (1 << 12)
            | (1 << 14) | (1 << 16) | (1 << 18) | (1 << 20) | (1 << 22) | (1 << 24)
            | (1 << 26) | (1 << 28) | (1 << 30);
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 11:
      if (new_state) {
        o->Mask1 = ~(1 | (1 << 4) | (1 << 8) | (1 << 12) | (1 << 16) | (1 << 20) | (1 << 24)
            | (1 << 28));
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 12:
      if (new_state) {
        o->Mask1 = ~(1 | (1 << 8) | (1 << 16) | (1 << 24));
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 13:
      if (new_state) {
        o->Mask1 = ~(1 | (1 << 16));
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 14:
      if (new_state) {
        o->Mask1 = ~1;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 15:
      if (new_state) {
        o->Mask1 = ~(1 << 31);
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 << 31) | (o->Mask1 >> 1);
      break;
    case 16:
      if (new_state) {
        o->Mask1 = 1;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 17:
      if (new_state) {
        o->Mask1 = 3;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 18:
      if (new_state) {
        o->Mask1 = 7;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 19:
      if (new_state) {
        o->Mask1 = 0xF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 20:
      if (new_state) {
        o->Mask1 = 0x3F;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 21:
      if (new_state) {
        o->Mask1 = 0x7F;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 22:
      if (new_state) {
        o->Mask1 = 0xFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 23:
      if (new_state) {
        o->Mask1 = 0x3FF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 24:
      if (new_state) {
        o->Mask1 = 0x7FF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 25:
      if (new_state) {
        o->Mask1 = 0xFFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 26:
      if (new_state) {
        o->Mask1 = 0x3FFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 27:
      if (new_state) {
        o->Mask1 = 0x7FFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 28:
      if (new_state) {
        o->Mask1 = 0xFFFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 29:
      if (new_state) {
        o->Mask1 = 0xFFFFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 30:
      if (new_state) {
        o->Mask1 = 0xFFFFFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 31:
      if (new_state) {
        o->Mask1 = 0xFFFFFFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 32:
      if (new_state) {
        o->Mask1 = 0x3FFFFFFF;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    case 33:
      if (new_state) {
        o->Mask1 = ~1;
        o->Mask2 = 0;
      } else
        o->Mask1 = (o->Mask1 >> 31) | (o->Mask1 << 1);
      break;
    }
  }
  o->Out = (pwr_tInt32)(o->Mask1 | o->Mask2);
}
