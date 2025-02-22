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

/* wb_watt.cpp -- Display object attributes */

#include <string.h>

#include "co_time.h"
#include "cow_xhelp.h"
#include "wb_watt_msg.h"
#include "wb_watt.h"
#include "wb_wattnav.h"
#include "wb_wtt.h"

void WAtt::message_cb(void* watt, char severity, const char* message)
{
  ((WAtt*)watt)->message(severity, message);
}

void WAtt::change_value_cb(void* watt)
{
  ((WAtt*)watt)->change_value(1);
}

void WAtt::activate_print()
{
  char* namep;
  pwr_tStatus sts;
  int size;
  pwr_tAName aname;

  sts = ldh_AttrRefToName(ldhses, &aref, ldh_eName_VolPath, &namep, &size);
  if (EVEN(sts))
    return;

  strcpy(aname, namep);
  print(aname);
}

void WAtt::set_editmode(int editmode, ldh_tSesContext ldhses)
{
  if (ldhses != 0)
    this->ldhses = ldhses;
  this->editmode = editmode;
  ((WAttNav*)wattnav)->set_editmode(editmode, ldhses);
}

int WAtt::open_changevalue(const char* name, int close)
{
  int sts;

  pending_close = close;

  sts = ((WAttNav*)wattnav)->select_by_name(name);
  if (EVEN(sts))
    return sts;

  change_value(0);
  return WATT__SUCCESS;
}

WAtt::~WAtt()
{
}

WAtt::WAtt(void* wa_parent_ctx, ldh_tSesContext wa_ldhses, pwr_sAttrRef wa_aref,
    int wa_editmode, int wa_advanced_user, int wa_display_objectname)
    : parent_ctx(wa_parent_ctx), ldhses(wa_ldhses), aref(wa_aref),
      editmode(wa_editmode), input_open(0), input_multiline(0), close_cb(0),
      redraw_cb(0), client_data(0), pending_close(0)
{
}
