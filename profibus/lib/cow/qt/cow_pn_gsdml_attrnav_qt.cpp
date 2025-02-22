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

/* cow_pn_gsdml_attrnav_qt.cpp -- Display gsd attributes */

#include "cow_qt_helpers.h"

#include "flow_browwidget_qt.h"

#include "cow_pn_gsdml_attr_qt.h"
#include "cow_pn_gsdml_attrnav_qt.h"

GsdmlAttrNavQt::GsdmlAttrNavQt(void* xn_parent_ctx, const char* xn_name,
                               pn_gsdml* xn_gsdml, int xn_edit_mode,
                               QWidget** w, pwr_tStatus* status)
    : GsdmlAttrNav(xn_parent_ctx, xn_name, xn_gsdml, xn_edit_mode, status)
{
  form_widget = scrolledbrowwidgetqt_new(init_brow_cb, this, &brow_widget);

  *w = form_widget;

  wow = new CoWowQt(brow_widget);
  trace_timerid = wow->timer_new();
  *status = 1;
}

GsdmlAttrNavQt::~GsdmlAttrNavQt()
{
  delete trace_timerid;
  delete wow;
  delete brow;
  form_widget->close();
}

void GsdmlAttrNavQt::set_inputfocus() { brow_widget->setFocus(); }

void GsdmlAttrNavQt::display_attr_help_text()
{
  brow_tNode* node_list;
  int node_count;
  ItemPn* base_item;

  brow_GetSelectedNodes(brow->ctx, &node_list, &node_count);
  if (!node_count)
    return;

  brow_GetUserData(node_list[0], (void**)&base_item);
  free(node_list);

  switch (base_item->type)
  {
  /*
   * The following two item types could make use of the same info_text that the
   * the base class does,
   * but since they already contained references they were used instead...
   */
  case attrnav_eItemType_PnParValue:
  case attrnav_eItemType_PnParEnum:
  {
    ItemPnParEnum* item = (ItemPnParEnum*)base_item;
    gsdml_ValueItem* vi = 0;

    if (item->value_ref)
      vi = (gsdml_ValueItem*)item->value_ref->Body.ValueItemTarget.p;

    // If we do have help available show it
    if (vi && vi->Body.Help.p)
      ((GsdmlAttrQt*)parent_ctx)->attr_help_text((char*)vi->Body.Help.p);
    else
      ((GsdmlAttrQt*)parent_ctx)->attr_help_text("");

    break;
  }
  default:
  {
    if (base_item->info_text)
      ((GsdmlAttrQt*)parent_ctx)->attr_help_text(base_item->info_text);
    else
      ((GsdmlAttrQt*)parent_ctx)->attr_help_text("");
  }
  }
}
