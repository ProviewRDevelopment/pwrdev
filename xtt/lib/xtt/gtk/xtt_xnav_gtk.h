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

#ifndef xtt_xnav_gtk_h
#define xtt_xnav_gtk_h

/* xtt_xnav_gtk.h -- Simple navigator */

#include "xtt_xnav.h"

class XNavGtk : public XNav {
public:
  XNavGtk(void* xn_parent_ctx, GtkWidget* xn_parent_wid, const char* xn_name,
      GtkWidget** w, xnav_sStartMenu* root_menu, char* xn_opplace_name,
      int xn_op_close_button, pwr_tStatus* status);
  ~XNavGtk();

  void set_inputfocus();
  void pop();
  void set_transient(void* basewidget);
  void create_popup_menu(pwr_sAttrRef attrref, xmenu_eItemType item_type,
      xmenu_mUtility caller, unsigned int priv, char* arg, int x, int y);
  RtTrace* plctrace_new(pwr_tOid oid, pwr_tStatus* sts);
  XAtt* xatt_new(pwr_tAttrRef* arp, int advanced_user, pwr_tStatus* sts);
  XCrr* xcrr_new(pwr_tAttrRef* arp, int advanced_user, pwr_tStatus* sts);
  XColWind* xcolwind_new(pwr_tAttrRef* ar_list, char* title, int advanced_user,
      int type, pwr_tStatus* sts);
  Ev* ev_new(char* eve_name, char* ala_name, char* blk_name, pwr_tObjid ev_user,
      int display_ala, int display_eve, int display_blk, int display_return,
      int display_ack, int ev_beep, pwr_tMask ev_pop_mask, int ev_eventname_seg,
      pwr_tStatus* status);
  Hist* hist_new(char* title, pwr_tAttrRef* arp, pwr_tStatus* sts);
  Block* block_new(
      pwr_tAttrRef* arp, char* name, unsigned int priv, pwr_tStatus* sts);
  Op* op_new(char* opplace, pwr_tStatus* sts);
  XttTrend* xtttrend_new(char* name, pwr_tAttrRef* objar,
      pwr_tAttrRef* plotgroup, int width, int height, unsigned int options,
      int color_theme, void* basewidget, pwr_tStatus* sts);
  XttSevHist* xttsevhist_new(char* name, pwr_tOid* oidv, pwr_tOName* anamev,
      pwr_tOName* onamev, bool* sevhistobjectv, sevcli_tCtx scctx,
      char* filename, int width, int height, unsigned int options,
      int color_theme, time_ePeriod time_range, void* basewidget,
      pwr_tStatus* sts);
  XttTCurve* xtttcurve_new(char* name, pwr_tAttrRef* arefv, int width,
      int height, unsigned int options, int color_theme, void* basewidget,
      pwr_tStatus* sts);
  XttFast* xttfast_new(char* name, pwr_tAttrRef* objar, int width, int height,
      unsigned int options, char* filename, int color_theme, void* basewidget,
      pwr_tStatus* sts);
  XAttOne* xattone_new(
      pwr_tAttrRef* objar, char* title, unsigned int priv, pwr_tStatus* sts);
  CLog* clog_new(const char* name, pwr_tStatus* sts);
  XttGe* xnav_ge_new(const char* name, const char* filename, int scrollbar,
      int menu, int navigator, int width, int height, int x, int y,
      double scan_time, const char* object_name, int use_default_access,
      unsigned int access, unsigned int options, void* basewidget,
      double* borders, int color_theme, int dashboard,
      int (*xg_command_cb)(void*, char*, char*, char*, void*),
      int (*xg_get_current_objects_cb)(void*, pwr_sAttrRef**, int**),
      int (*xg_is_authorized_cb)(void*, unsigned int),
      void (*xg_keyboard_cb)(void*, void*, int, int));
  XttMultiView* multiview_new(const char* name, pwr_tAttrRef* aref, int width,
      int height, int x, int y, unsigned int options, void* basewidget,
      int color_theme, pwr_tStatus* sts,
      int (*command_cb)(void*, char*, char*, char*, void*),
      int (*get_current_objects_cb)(void*, pwr_sAttrRef**, int**),
      int (*is_authorized_cb)(void*, unsigned int),
      void (*keyboard_cb)(void*, void*, int, int));
  XttStream* stream_new(const char* name, const char* uri, int width,
      int height, int x, int y, double scan_time, unsigned int options,
      int embedded, pwr_tAttrRef* arp, pwr_tStatus* sts);
  GeCurve* gecurve_new(char* name, char* filename, GeCurveData* data,
      int pos_right, unsigned int options, int color_theme, void* basewidget);
  XttFileview* fileview_new(pwr_tOid oid, char* title, char* dir, char* pattern,
      int type, char* target_attr, char* trigger_attr, char* filetype);
  CoLogin* login_new(const char* wl_name, const char* wl_groupname,
      void (*wl_bc_success)(void*), void (*wl_bc_cancel)(void*),
      void* basewidget, pwr_tStatus* status);
  XttKeyboard* keyboard_new(const char* name, keyboard_eKeymap keymap,
      keyboard_eType type, int color_theme, pwr_tStatus* status);
  XttOTree* tree_new(const char* title, pwr_tAttrRef* itemlist, int itemcnt,
      unsigned int options, pwr_tStatus (*action_cb)(void*, pwr_tAttrRef*));
  void bell(int time);
  void get_popup_menu(pwr_sAttrRef attrref, xmenu_eItemType item_type,
      xmenu_mUtility caller, unsigned int priv, char* arg, int x, int y);
  void set_clock_cursor();
  void reset_cursor();
  int confirm_dialog(char* title, char* text);
  static void menu_position_func(
      GtkMenu* menu, gint* x, gint* y, gboolean* push_in, gpointer data);
  static GtkWidget* build_menu(GtkWidget* Parent, int MenuType,
      const char* MenuTitle, void* MenuUserData,
      void (*Callback)(GtkWidget*, gpointer), void* CallbackData,
      xmenu_sMenuItem* Items, int* idx);
  static void popup_button_cb(GtkWidget* w, gpointer data);

  GtkWidget* parent_wid;
  GtkWidget* brow_widget;
  GtkWidget* form_widget;
  GtkWidget* toplevel;
  int popupmenu_x;
  int popupmenu_y;
  GdkCursor* clock_cursor;
};

#endif
