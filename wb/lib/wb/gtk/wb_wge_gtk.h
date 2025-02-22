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

#ifndef wb_wge_gtk_h
#define wb_wge_gtk_h

#include "wb_wge.h"

#include "cow_wow_gtk.h"

class WGeGtk : public WGe {
public:
  GtkWidget* parent_wid;
  GtkWidget* grow_widget;
  GtkWidget* form_widget;
  GtkWidget* toplevel;
  GtkWidget* graph_form;
  GtkWidget* nav_shell;
  GtkWidget* nav_widget;
  GtkWidget* menu_widget;
  GtkWidget* value_input;
  GtkWidget* value_dialog;
  GtkWidget* confirm_widget;
  GtkWidget* confirm_label;
  GtkWidget* message_dia_widget;
  GtkWidget* message_dia_label;
  CoWowFocusTimerGtk focustimer;

  void pop();
  void set_size(int width, int height);
  void set_subwindow_release();
  void create_confirm_dialog();

  WGeGtk(GtkWidget* parent_wid, void* parent_ctx, char* name, char* filename,
      int scrollbar, int menu, int navigator, int width, int height, int x,
      int y, char* object_name, int modal);
  ~WGeGtk();

  static void enable_set_focus(WGeGtk* ge);
  static void disable_set_focus(WGeGtk* ge, int time);
  static gboolean action_inputfocus(
      GtkWidget* w, GdkEvent* event, gpointer data);
  static void change_value_cb(void* ge_ctx, void* value_object, char* text);
  static void confirm_cb(void* ge_ctx, void* confirm_object, char* text);
  static void message_dialog_cb(void* ge_ctx, const char* text);
  static void activate_value_input(GtkWidget* w, gpointer data);
  static void activate_confirm_ok(GtkWidget* w, gpointer data);
  static void activate_confirm_cancel(GtkWidget* w, gpointer data);
  static void activate_exit(GtkWidget* w, gpointer data);
  static void activate_zoom_in(GtkWidget* w, gpointer data);
  static void activate_zoom_out(GtkWidget* w, gpointer data);
  static void activate_zoom_reset(GtkWidget* w, gpointer data);
  static void activate_help(GtkWidget* w, gpointer data);
  static void create_graph_form(GtkWidget* w, gpointer data);
  static void create_message_dia(GtkWidget* w, gpointer data);
  static void create_menu(GtkWidget* w, gpointer data);
  static void create_value_input(GtkWidget* w, gpointer data);
  static void action_resize(
      GtkWidget* w, GtkAllocation* allocation, gpointer data);
};

#endif
