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

#ifndef xtt_c_pndevice_h
#define xtt_c_pndevice_h

/* xtt_c_pndevice.h -- Profinet gsdml configure method */

typedef struct
{
  pn_gsdml* gsdml;
  std::shared_ptr<ProfinetRuntimeData> pwr_pn_data;
  GsdmlAttr* attr;
  pwr_tAttrRef aref;
  gsdml_sModuleClass* mc;
  void* editor_ctx;
} xtt_pndevice_sCtx;

pwr_tStatus xtt_pndevice_create_ctx(pwr_tAttrRef aref, void* editor_ctx, xtt_pndevice_sCtx** ctxp,
                                    char const* pwr_pn_data_file);
int xtt_pndevice_help_cb(void* sctx, const char* text);
void xtt_pndevice_close_cb(void* sctx);
int xtt_pndevice_save_cb(void* sctx);

#endif
