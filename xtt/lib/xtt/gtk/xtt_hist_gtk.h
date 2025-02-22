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

#ifndef xtt_hist_gtk_h
#define xtt_hist_gtk_h

/* xtt_hist_gtk.h -- Historical event window in xtt */

#if defined PWRE_CONF_LIBDB

#include "xtt_hist.h"

class HistGtk : public Hist {
public:
  HistGtk(void* hist_parent_ctx, GtkWidget* hist_parent_wid, char* hist_name,
      pwr_tAttrRef* arp, pwr_tStatus* status);
  ~HistGtk();

  GtkWidget* parent_wid;
  GtkWidget* parent_wid_hist;
  GtkWidget* toplevel_hist;
  GtkWidget* toplevel_search;
  GtkWidget* form_hist;
  GtkWidget* hist_widget;
  GtkWidget* start_time_help_lbl_w;
  GtkWidget* start_time_entry_w;
  GtkWidget* stop_time_entry_w;
  GtkWidget* event_text_entry_w;
  GtkWidget* event_name_entry_w;
  GtkWidget* alarm_toggle_w;
  GtkWidget* info_toggle_w;
  GtkWidget* infosuccess_toggle_w;
  GtkWidget* mnt_alarm_toggle_w;
  GtkWidget* sys_alarm_toggle_w;
  GtkWidget* user_alarm1_toggle_w;
  GtkWidget* user_alarm2_toggle_w;
  GtkWidget* user_alarm3_toggle_w;
  GtkWidget* user_alarm4_toggle_w;
  GtkWidget* ack_toggle_w;
  GtkWidget* ret_toggle_w;
  GtkWidget* prioA_toggle_w;
  GtkWidget* prioB_toggle_w;
  GtkWidget* prioC_toggle_w;
  GtkWidget* prioD_toggle_w;
  GtkWidget* nrofevents_string_lbl_w;
  GtkWidget* search_string_lbl_w;
  GtkWidget* search_string2_lbl_w;
  GtkWidget* search_string3_lbl_w;
  GtkWidget* search_string4_lbl_w;
  GtkWidget* search_vbox;

  void set_num_of_events(int nrOfEvents);
  void set_search_string(
      const char* s1, const char* s2, const char* s3, const char* s4);
  void SetListTime(pwr_tTime StartTime, pwr_tTime StopTime, int Sensitive);
  void insert_eventname(const char* name);

  static gboolean action_inputfocus(
      GtkWidget* w, GdkEvent* event, gpointer data);
  static void activate_exit(GtkWidget* w, gpointer data);
  static void activate_print(GtkWidget* w, gpointer data);
  static void activate_export(GtkWidget* w, gpointer data);
  static void activate_analyse(GtkWidget* w, gpointer data);
  static void activate_zoom_in(GtkWidget* w, gpointer data);
  static void activate_zoom_out(GtkWidget* w, gpointer data);
  static void activate_zoom_reset(GtkWidget* w, gpointer data);
  static void activate_hidesearch(GtkWidget* w, gpointer data);
  static void activate_hide_search(GtkWidget* w, gpointer data);
  static void activate_open_plc(GtkWidget* w, gpointer data);
  static void activate_stat(GtkWidget* w, gpointer data);
  static void activate_display_in_xnav(GtkWidget* w, gpointer data);
  static void activate_disp_hundredth(GtkWidget* w, gpointer data);
  static void activate_hide_object(GtkWidget* w, gpointer data);
  static void activate_hide_text(GtkWidget* w, gpointer data);
  static void activate_help(GtkWidget* w, gpointer data);
  static void activate_helpevent(GtkWidget* w, gpointer data);
  static void create_form(GtkWidget* w, gpointer data);
  static void ok_btn(GtkWidget* w, gpointer data);
  static void activate_sea_time_combo(GtkWidget* w, gpointer data);
  static void cancel_cb(GtkWidget* w, gpointer data);
};

#else
// Dummy for other platforms then OS_LINUX
#include "xtt_hist.h"

class HistGtk : public Hist {
public:
  HistGtk(void* hist_parent_ctx, GtkWidget* hist_parent_wid, char* hist_name,
      pwr_tAttrRef* arp, pwr_tStatus* status)
      : Hist(hist_parent_ctx, hist_name, arp, status)
  {
  }
  ~HistGtk()
  {
  }
};

#endif

#endif
