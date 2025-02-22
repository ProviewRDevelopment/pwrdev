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

/* cow_pn_gsdml_attr.cpp -- Display gsd attributes */

#include <stdlib.h>

#include "co_cdh.h"
#include "co_dcli.h"
#include "co_time.h"
#include "rt_pb_msg.h"

#include "cow_wow.h"

#include "flow_msg.h"

#include "glow_growapi.h"

#include "cow_pn_gsdml_attrnav.h"

// Static member variables
char GsdmlAttr::value_recall[30][160];

void GsdmlAttr::gsdmlattr_message(void* attr, char severity, const char* message)
{
  ((GsdmlAttr*)attr)->message(severity, message);
}

void GsdmlAttr::gsdmlattr_change_value_cb(void* attr_ctx)
{
  GsdmlAttr* attr = (GsdmlAttr*)attr_ctx;
  attr->change_value();
}

//
//  Callbackfunctions from menu entries
//
void GsdmlAttr::activate_exit()
{
  if (close_cb)
  {
    if (edit_mode && attrnav->is_modified())
    {
      wow->DisplayQuestion((void*)this, "Apply", "Do you want to apply changes", cmd_close_apply_cb,
                           cmd_close_no_cb, 0);
    }
    else
      (close_cb)(parent_ctx);
  }
  else
    delete this;
}

void GsdmlAttr::activate_ordermoduletype(attr_eOrderModuleType type) { attrnav->set_order_moduletype(type); }

void GsdmlAttr::activate_help()
{
  int sts;

  if (help_cb)
    sts = (help_cb)(parent_ctx, "pn_device_editor /helpfile=\"$pwr_exe/profibus_xtthelp.dat\"");
}

void GsdmlAttr::activate_copy()
{
  ItemPnSlot* item;
  int sts;

  sts = attrnav->get_select((ItemPn**)&item);
  if (EVEN(sts))
  {
    message('W', "Nothing selected");
    return;
  }

  if (item->m_type & attrnav_mItemType_Copyable)
  {
    // Save a static reference, enabling us to copy between different devices across different configurators.
    // The slots themself will reset if they do not find the ID. I.e. you copy from an ET200SP to
    // an ABB Frequency Converter :D It's stupid but still safe...
    ProfinetRuntimeData::m_paste_slotdata = item->m_slot_data;
  }
  else
  {
    message('E', "You can only copy slots!");
    return;
  }

  message('I', "Slot copied");
}

void GsdmlAttr::activate_paste()
{
  ItemPnSlot* item;
  int sts;

  sts = attrnav->get_select((ItemPn**)&item);
  if (EVEN(sts))
  {
    message('E', "Select a slot");
    return;
  }

  if (item->m_type & attrnav_mItemType_Movable)
  {
    // Copy assignment constructor of ProfinetSlot will invoke ProfinetSubslot copy constructor to deep copy
    // the data
    attrnav->pn_runtime_data->m_PnDevice->m_slot_list[item->m_slot_data->m_slot_number] =
        *ProfinetRuntimeData::m_paste_slotdata;
  }
  else
  {
    message('E', "Select a slot");
    return;
  }

  attrnav->redraw();
}

void GsdmlAttr::activate_viewio(int set) { attrnav->set_viewio(set); }

void GsdmlAttr::activate_zoom_in()
{
  double zoom_factor;

  attrnav->get_zoom(&zoom_factor);
  if (zoom_factor > 40)
    return;

  attrnav->zoom(1.18);
}

void GsdmlAttr::activate_zoom_out()
{
  double zoom_factor;

  attrnav->get_zoom(&zoom_factor);
  if (zoom_factor < 15)
    return;

  attrnav->zoom(1.0 / 1.18);
}

void GsdmlAttr::activate_zoom_reset() { attrnav->unzoom(); }

void GsdmlAttr::activate_collapse() { attrnav->collapse(); }

void GsdmlAttr::activate_expand_all() { attrnav->expand_all(); }

void GsdmlAttr::activate_print()
{
  char filename[80] = "pwrp_tmp:wnav.ps";
  char cmd[200];
  int sts;

  dcli_translate_filename(filename, filename);
  attrnav->print(filename);

  sprintf(cmd, "wb_gre_print.sh %s", filename);
  sts = system(cmd);
}

void GsdmlAttr::activate_cmd_ok()
{
  int sts;

  attrnav->save();

  if (save_cb)
  {
    sts = (save_cb)(parent_ctx);
    if (EVEN(sts))
      message('E', "Error saving profinet runtime data");
    else if (close_cb)
      (close_cb)(parent_ctx);
  }
  else if (close_cb)
    (close_cb)(parent_ctx);
}

void GsdmlAttr::activate_cmd_apply()
{
  int sts;

  attrnav->save();

  if (save_cb)
  {
    sts = (save_cb)(parent_ctx);
    if (EVEN(sts))
      message('E', "Error creating modules/channels.");
    else
      attrnav->set_modified(false);
  }
}

void GsdmlAttr::cmd_close_apply_cb(void* ctx, void* data)
{
  GsdmlAttr* attr = (GsdmlAttr*)ctx;
  int sts;

  attr->attrnav->save();

  if (attr->save_cb)
  {
    sts = (attr->save_cb)(attr->parent_ctx);
    if (EVEN(sts))
      attr->message('E', "Error saving profinet runtime data");
    else
      (attr->close_cb)(attr->parent_ctx);
  }
}

void GsdmlAttr::cmd_close_no_cb(void* ctx, void* data)
{
  GsdmlAttr* attr = (GsdmlAttr*)ctx;

  (attr->close_cb)(attr->parent_ctx);
}

/* Activate command cancel */
/* This cancels the configuration asking the user if that's really what he/she wants. */
void GsdmlAttr::activate_cmd_ca()
{
  if (close_cb)
  {
    if (edit_mode && attrnav->is_modified())
    {
      wow->DisplayQuestion((void*)this, "Cancel", "All changes will be lost. Are you sure?", cmd_close_no_cb,
                           [](void* ctx, void* data) { /* NOOP */ }, 0);
    }
    else
      (close_cb)(parent_ctx);
  }
}

GsdmlAttr::~GsdmlAttr()
{
  if (wow)
    delete wow;
}

GsdmlAttr::GsdmlAttr(void* a_parent_ctx, void* a_object, int a_edit_mode)
    : parent_ctx(a_parent_ctx), edit_mode(a_edit_mode), input_open(0), object(a_object), close_cb(0),
      save_cb(0), help_cb(0), client_data(0), recall_idx(-1), value_current_recall(0)
{
}
