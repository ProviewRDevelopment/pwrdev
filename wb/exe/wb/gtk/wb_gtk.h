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

#include <gtk/gtk.h>

#ifndef wb_gtk_h
#define wb_gtk_h

#include "wb_main.h"

class WbGtk : public Wb {
public:
  GtkWidget* toplevel;
  GtkWidget* mainwindow;

  WbGtk(int argc, char* argv[]);
  ~WbGtk()
  {
  }
  Wtt* wtt_new(const char* name, const char* iconname, ldh_tWBContext wbctx,
      pwr_tVolumeId volid, ldh_tVolume volctx, wnav_sStartMenu* root_menu,
      pwr_tStatus* status);
  WVsel* vsel_new(pwr_tStatus* status, const char* name, ldh_tWBContext wbctx,
      char* volumename, int (*bc_success)(void*, pwr_tVolumeId*, int),
      void (*bc_cancel)(), int (*bc_time_to_exit)(void*), int show_volumes,
      wb_eType wb_type);
};

#endif
