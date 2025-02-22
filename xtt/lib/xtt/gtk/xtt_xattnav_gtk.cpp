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

/* wb_xattnav.cpp -- Display object info */

#include "pwr_privilege.h"
#include "co_cdh.h"
#include "rt_mh_net.h"
#include "rt_xatt_msg.h"

#include "cow_wow_gtk.h"

#include "flow_browwidget_gtk.h"

#include "xtt_item.h"
#include "xtt_xatt.h"
#include "xtt_xattnav_gtk.h"
#include "xtt_xnav_crr.h"

//
// Create the navigator widget
//
XAttNavGtk::XAttNavGtk(void* xa_parent_ctx, GtkWidget* xa_parent_wid,
    xattnav_eType xa_type, const char* xa_name, pwr_sAttrRef* xa_objar,
    int xa_advanced_user, void* xa_userdata, GtkWidget** w, pwr_tStatus* status)
    : XAttNav(xa_parent_ctx, xa_type, xa_name, xa_objar, xa_advanced_user,
          xa_userdata, status),
      parent_wid(xa_parent_wid)
{
  form_widget = scrolledbrowwidgetgtk_new(init_brow_cb, this, &brow_widget);

  gtk_widget_show_all(brow_widget);

  // Create the root item
  *w = form_widget;

  wow = new CoWowGtk(form_widget);
  trace_timerid = wow->timer_new();
  *status = 1;
}

//
//  Delete a nav context
//
XAttNavGtk::~XAttNavGtk()
{
  if (trace_started)
    trace_timerid->remove();

  delete trace_timerid;
  delete wow;
  delete brow;
  gtk_widget_destroy(form_widget);
}

void XAttNavGtk::set_inputfocus()
{
  if (!displayed)
    return;

  gtk_widget_grab_focus(brow_widget);
}

void XAttNavGtk::popup_position(int x_event, int y_event, int* x, int* y)
{
  CoWowGtk::PopupPosition(brow_widget, x_event, y_event, x, y);
}
