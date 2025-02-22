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

#ifndef xtt_xattone_gtk_h
#define xtt_xattone_gtk_h

/* xtt_xattone_gtk.h -- Single attribute editor */

#include "xtt_xattone.h"

#include "cow_wow_gtk.h"

class XAttOneGtk : public XAttOne {
public:
  XAttOneGtk(GtkWidget* xa_parent_wid, void* xa_parent_ctx,
      pwr_sAttrRef* xa_objar, char* xa_title, unsigned int xa_priv,
      int* xa_sts);
  ~XAttOneGtk();

  GtkWidget* parent_wid;
  GtkWidget* form_widget;
  GtkWidget* toplevel;
  GtkWidget* msg_label;
  GtkWidget* cmd_prompt;
  GtkWidget* cmd_label;
  GtkWidget* cmd_input;
  GtkWidget* cmd_scrolledinput;
  GtkWidget* cmd_scrolledtextview;
  GtkWidget* cmd_scrolled_ok;
  GtkWidget* cmd_scrolled_ap;
  GtkWidget* cmd_scrolled_ca;
  GtkTextBuffer* cmd_scrolled_buffer;
  static CoWowRecall value_recall;
  CoWowEntryGtk* cmd_entry;

  void message(char severity, const char* message);
  void set_prompt(char* prompt);
  int change_value(int set_focus);
  int open_changevalue(char* name);
  void change_value_close();
  void pop();
  void swap(int mode);
  int set_value();

  static void activate_exit(GtkWidget* w, gpointer data);
  static void activate_help(GtkWidget* w, gpointer data);
  static gboolean action_inputfocus(
      GtkWidget* w, GdkEvent* event, gpointer data);
  static void valchanged_cmd_input(GtkWidget* w, gpointer data);
  static void activate_cmd_input(GtkWidget* w, gpointer data);
  static void activate_cmd_scrolled_ok(GtkWidget* w, gpointer data);
  static void activate_cmd_scrolled_ap(GtkWidget* w, gpointer data);
  static void activate_cmd_scrolled_ca(GtkWidget* w, gpointer data);
};

#endif
