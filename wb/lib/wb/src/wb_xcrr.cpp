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

/* wb_xcrr.cpp -- Display object crossreferences */

#include "co_dcli.h"
#include "co_lng.h"
#include "co_time.h"

#include "wb_watt_msg.h"
#include "wb_xcrr.h"

WCrr::~WCrr()
{
}

WCrr::WCrr(void* xa_parent_ctx, ldh_tSesContext xa_ldhses,
    pwr_sAttrRef* xa_objar, int xa_advanced_user, int* xa_sts)
    : parent_ctx(xa_parent_ctx), ldhses(xa_ldhses), objar(*xa_objar),
      input_open(0), input_multiline(0), close_cb(0), redraw_cb(0),
      popup_menu_cb(0), start_trace_cb(0), client_data(0)
{
  *xa_sts = WATT__SUCCESS;
}

void WCrr::xcrr_popup_menu_cb(void* ctx, pwr_sAttrRef attrref,
    unsigned long item_type, unsigned long utility, char* arg, int x, int y)
{
  if (((WCrr*)ctx)->popup_menu_cb)
    (((WCrr*)ctx)->popup_menu_cb)(
        ((WCrr*)ctx)->parent_ctx, attrref, item_type, utility, arg, x, y);
}

void WCrr::xcrr_start_trace_cb(void* ctx, pwr_tObjid objid, char* name)
{
  if (((WCrr*)ctx)->start_trace_cb)
    ((WCrr*)ctx)->start_trace_cb(((WCrr*)ctx)->parent_ctx, objid, name);
}

void WCrr::xcrr_close_cb(void* ctx)
{
  if (((WCrr*)ctx)->close_cb)
    ((WCrr*)ctx)->close_cb(((WCrr*)ctx)->parent_ctx, ctx);
}
