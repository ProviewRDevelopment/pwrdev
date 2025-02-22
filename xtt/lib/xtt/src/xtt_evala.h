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

#ifndef xtt_evala_h
#define xtt_evala_h

/* xtt_evala.h -- Alarm window in xtt */

#ifndef xtt_evlist
#include "xtt_evlist.h"
#endif

class CoWow;
class XttMethodToolbar;

class EvAla {
public:
  EvAla(void* ev_parent_ctx, char* ala_name, pwr_tObjid ev_user,
      int ev_eventname_seg, int ev_width, int ev_height, int ev_x, int ev_y,
      pwr_tObjid ev_view, unsigned int ev_options, pwr_tStatus* status);
  virtual ~EvAla();

  void* parent_ctx;
  char name[80];
  pwr_tObjid user;
  int eventname_seg;
  int width;
  int height;
  int x;
  int y;
  pwr_tObjid view;
  unsigned int options;
  void (*start_trace_cb)(void*, pwr_tObjid, char*);
  void (*display_in_xnav_cb)(void*, pwr_tAttrRef*);
  void (*help_cb)(void*, const char*);
  void (*popup_menu_cb)(
      void*, pwr_tAttrRef, unsigned long, unsigned long, char*, int x, int y);
  int (*sound_cb)(void*, pwr_tAttrRef*);
  void (*pop_cb)(void*);
  int (*is_authorized_cb)(void*, unsigned int);
  int (*acknowledge_cb)(void*, mh_sEventId*);
  char* (*name_to_alias_cb)(void*, char*);
  void (*copy_list_cb)(void*, EvList*);
  void (*close_cb)(void*, EvAla*);
  EvList* ala;
  int ala_displayed;
  int ala_size;
  CoWow* wow;
  XttMethodToolbar* ala_methodtoolbar;
  XttMethodToolbar* ala_sup_methodtoolbar;
  int list_copied;

  virtual void map_ala()
  {
  }
  virtual void unmap_ala()
  {
  }
  virtual void set_title_ala(char* title)
  {
  }

  int is_mapped_ala()
  {
    return ala_displayed;
  }
  pwr_tStatus set_view(pwr_tOid view);
  void view_shift();
  void update();
  pwr_tStatus mh_ack(mh_sAck* MsgP);
  pwr_tStatus mh_return(mh_sReturn* MsgP);
  pwr_tStatus mh_alarm(mh_sMessage* MsgP);
  pwr_tStatus mh_cancel(mh_sReturn* MsgP);
  pwr_tStatus mh_info(mh_sMessage* MsgP);
  pwr_tStatus mh_clear_alarmlist(pwr_tNodeIndex nix);
  void init();

  void ala_activate_print();
  void ala_activate_ack_last();
  void ala_activate_help();
  void ala_activate_helpevent();

  void ala_activate_ack_all();
  void ack_last_prio(unsigned long type, unsigned long prio);
  void ack_all();
  void ack(mh_sEventId* id)
  {
    ala->ack(id);
  }
  int get_last_not_acked_prio(
      mh_sEventId** id, unsigned long type, unsigned long prio);
  int event_delete(mh_sEventId* id);

  static void ala_display_in_xnav_cb(void* ctx, pwr_tAttrRef* arp);
  static void ala_start_trace_cb(void* ctx, pwr_tObjid objid, char* name);
  static void ala_popup_menu_cb(void* ctx, pwr_tAttrRef attrref,
      unsigned long item_type, unsigned long utility, char* arg, int x, int y);
  static int ala_sound_cb(void* ctx, pwr_tAttrRef* attrref);
  static void ala_selection_changed_cb(void* ctx);
  static char* ala_name_to_alias_cb(void* ctx, char* name);
  static void ala_init_cb(void* ctx);
  static void help_event_cb(void* ctx, void* item);
};

#endif
