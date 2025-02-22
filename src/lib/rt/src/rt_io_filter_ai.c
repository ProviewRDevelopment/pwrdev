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

/* rt_io_filter_ai.c -- Runtime environment - I/O filter Ai */

#include <stdlib.h>

#include "rt_gdh.h"
#include "rt_io_msg.h"
#include "rt_io_filter_ai.h"

/* Defines */
#define _FilterType_0 0
#define _FilterType_1 1

/* Enumerations */

/* Structures */
typedef struct s_FilterData_1 sFilterData_1;

/* The structure of filter data used in filter type = 1  */

struct s_FilterData_1 {
  pwr_tFloat32 ScanTime;
  pwr_tFloat32* ActualValue;
};

/* Filtration of one Ai-object.  */

pwr_tStatus io_AiFilter(
    pwr_sClass_Ai* SignalObj, pwr_tFloat32* Value, void* FilterData)
{
  sFilterData_1* Data_1;

  if (SignalObj == NULL)
    return IO__SUCCESS;
  switch (SignalObj->FilterType) {
  case _FilterType_0:
    break;

  case _FilterType_1:
    if (FilterData == NULL)
      return IO__SUCCESS;
    Data_1 = (sFilterData_1*)FilterData;
    if (SignalObj->FilterAttribute[0] > 0
        && SignalObj->FilterAttribute[0] > Data_1->ScanTime) {
      *Value = *Data_1->ActualValue
          + Data_1->ScanTime / SignalObj->FilterAttribute[0]
              * (*Value - *Data_1->ActualValue);
    }
    break;

  default:
    break;
  }

  return IO__SUCCESS;
} /* END io_FilterAi */

/*
* Name:
*   io_InitFilterAi
*
*
* Function:
*   Initialize filter for one Ai-object.
* Description:
*
*/
pwr_tStatus io_InitAiFilter(pwr_sClass_ChanAi* ChanObj,
    pwr_sClass_Ai* SignalObj, void** FilterData, pwr_tFloat32 ScanTime)
{
  sFilterData_1* Data_1;

  if (SignalObj == NULL)
    return IO__SUCCESS;
  switch (SignalObj->FilterType) {
  case _FilterType_0:
    break;

  case _FilterType_1:
    Data_1 = (sFilterData_1*)malloc(sizeof(sFilterData_1));
    Data_1->ActualValue
        = gdh_TranslateRtdbPointer((unsigned long)SignalObj->ActualValue);
    Data_1->ScanTime = (pwr_tFloat32)(
        ScanTime * ChanObj->ScanInterval); /* Scan time (seconds) */
    *FilterData = Data_1;
    break;

  default:
    break;
  }

  return IO__SUCCESS;
} /* END io_InitFilterAi */
