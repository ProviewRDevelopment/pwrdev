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

#ifndef cow_tree_gtk_h
#define cow_tree_gtk_h

#include "cow_tree.h"
#include "cow_treenav.h"
#include "cow_wow_gtk.h"

/* cow_tree.h -- Tree viewer */

class CoWowRecall;
class CoWowEntryGtk;
class CowTreeNavGtk;

class CowTreeGtk : public CowTree {
public:
  CowTreeGtk(GtkWidget* a_parent_wid, void* a_parent_ctx, const char* title,
      pwr_tAttrRef* itemlist, int item_cnt, unsigned int options,
      pwr_tStatus (*get_object_info)(
          void*, pwr_tAttrRef*, char*, int, char*, char*, int),
      pwr_tStatus (*get_node_info)(void*, char*, char*, int),
      pwr_tStatus (*action)(void*, pwr_tAttrRef*));
  GtkWidget* parent_wid;
  GtkWidget* brow_widget;
  GtkWidget* form_widget;
  GtkWidget* toplevel;
  GtkWidget* msg_label;
  GtkWidget* button_ok;
  GtkWidget* button_apply;
  GtkWidget* button_cancel;
  GtkWidget* pane;

  void message(char severity, const char* message);
  void pop();

  static void activate_print(GtkWidget* w, gpointer data);
  static void activate_close(GtkWidget* w, gpointer data);
  static void activate_tree_layout(GtkWidget* w, gpointer data);
  static void activate_list_layout(GtkWidget* w, gpointer data);
  static void activate_zoom_in(GtkWidget* w, gpointer data);
  static void activate_zoom_out(GtkWidget* w, gpointer data);
  static void activate_zoom_reset(GtkWidget* w, gpointer data);
  static void activate_help(GtkWidget* w, gpointer data);
  static void activate_button_ok(GtkWidget* w, gpointer data);
  static void activate_button_apply(GtkWidget* w, gpointer data);
  static void activate_button_cancel(GtkWidget* w, gpointer data);

  ~CowTreeGtk();
};

#endif
