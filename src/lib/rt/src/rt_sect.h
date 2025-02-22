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

#ifndef rt_sect_h
#define rt_sect_h

#include <stddef.h>

#include "pwr.h"

typedef enum { sect_mFlags_Create = 1 << 0 } sect_mFlags;

#include "rt_semaphore.h"

typedef sem_t sect_sMutex;

typedef union {
  pwr_tBitMask m;
  pwr_32Bits(pwr_Bits(mapped, 1),

      pwr_Bits(fill, 31), , , , , , , , , , , , , , , , , , , , , , , , , , , ,
      , , ) b;

#define sect_mHead__ 0
#define sect_mHead_mapped pwr_Bit(0)
#define sect_mHead_ (~sect_mHead__)
} sect_mHead;

typedef struct {
  void* base; /* Virtual address of section.  */
  size_t size;
  char name[32]; /* Name of section.  */
  sect_mHead flags;
} sect_sHead;

/* Function prototypes */

sect_sHead* sect_Alloc(pwr_tStatus* sts, pwr_tBoolean* created, sect_sHead* shp,
    size_t size, char* name, unsigned int flags);

pwr_tBoolean sect_Free(pwr_tStatus* sts, sect_sHead* shp);

pwr_tBoolean sect_InitLock(
    pwr_tStatus* sts, sect_sHead* shp, sect_sMutex* sect_mutex);

pwr_tBoolean sect_Lock(
    pwr_tStatus* sts, sect_sHead* shp, sect_sMutex* sect_mutex);

pwr_tBoolean sect_Unlock(
    pwr_tStatus* sts, sect_sHead* shp, sect_sMutex* sect_mutex);

#endif
