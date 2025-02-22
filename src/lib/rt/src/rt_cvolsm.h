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

#ifndef rt_cvolsm_h
#define rt_cvolsm_h

/* rt_cvolsm.h -- Cached volumes, server monitor API.
   This module contains the cache handling routines.  */

#include "rt_cvol.h"

gdb_sMountedOn* cvolsm_AddMountedOn(
    pwr_tStatus* sts, pwr_tVolumeId vid, gdb_sNode* np);

void cvolsm_FlushNode(pwr_tStatus* sts, gdb_sNode* np);

void cvolsm_GetObjectInfo(qcom_sGet* get);

void cvolsm_NameToObject(qcom_sGet* get);

void cvolsm_OidToObject(qcom_sGet* get);

void cvolsm_RemoveMountedOn(pwr_tStatus* sts, gdb_sMountedOn* mop);

void cvolsm_SetObjectInfo(qcom_sGet* get);

#endif
