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

#include <stdlib.h>

#include "co_cdh.h"
#include "co_dcli.h"
#include "co_string.h"
#include "co_time.h"

#include "rt_gdh.h"

#include "ge_msg.h"
#include "ge_dyn.h"

#include "xtt_ssaboxclasses.h"

typedef struct {
  pwr_tClassId classid;
  int (*func)(Graph*, pwr_sAttrRef*);
} graph_sObjectFunction;

static int graph_object_dx(Graph* graph, pwr_sAttrRef* attrref);
static int graph_object_PlcThread(Graph* graph, pwr_sAttrRef* attrref);
static int graph_object_collect_build(Graph* graph, pwr_sAttrRef* attrref);

static graph_sObjectFunction graph_object_functions[]
    = { { pwr_cClass_Di, &graph_object_dx },
        { pwr_cClass_Do, &graph_object_dx },
        { pwr_cClass_PlcThread, &graph_object_PlcThread }, { 0, 0 } };

graph_sLocalDb* Graph::localdb_add(const char* name, int type)
{
  graph_sLocalDb* item_p;

  item_p = (graph_sLocalDb*)calloc(1, sizeof(graph_sLocalDb));
  strncpy(item_p->name, name, sizeof(item_p->name));
  item_p->name[sizeof(item_p->name) - 1] = 0;
  item_p->type = type;
  item_p->next = local_db;
  local_db = item_p;

  return item_p;
}

int Graph::localdb_find(const char* name, graph_sLocalDb** item)
{
  graph_sLocalDb* item_p;

  for (item_p = local_db; item_p; item_p = item_p->next) {
    if (streq(item_p->name, name)) {
      *item = item_p;
      return 1;
    }
  }
  return 0;
}

int Graph::localdb_set_value(char* name, void* value, int size)
{
  graph_sLocalDb* item_p;

  for (item_p = local_db; item_p; item_p = item_p->next) {
    if (streq(item_p->name, name)) {
      memcpy(item_p->value, value, size);
      return 1;
    }
  }
  return 0;
}

int Graph::localdb_toggle_value(char* name)
{
  graph_sLocalDb* item_p;

  for (item_p = local_db; item_p; item_p = item_p->next) {
    if (streq(item_p->name, name)) {
      *(pwr_tBoolean*)&item_p->value = !*(pwr_tBoolean*)&item_p->value;
      return 1;
    }
  }
  return 0;
}

void Graph::localdb_free()
{
  graph_sLocalDb *item_p, *next_item_p;

  for (item_p = local_db; item_p;) {
    next_item_p = item_p->next;
    free(item_p);
    item_p = next_item_p;
  }
}

void* Graph::localdb_ref_or_create(const char* name, int type)
{
  graph_sLocalDb* item_p;

  if (localdb_find(name, &item_p))
    return (void*)item_p->value;

  item_p = localdb_add(name, type);
  return (void*)item_p->value;
}

int Graph::init_object_graph(int mode)
{
  char classname[120];
  pwr_tClassId classid;
  char* s;
  int sts;
  int i;
  int is_type = 0;
  pwr_sAttrRef attrref;

  if (mode == 0) {
    if (streq(filename, "_none_.pwg")) {
      if (streq(object_name[0], "collect")) {
        sts = graph_object_collect_build(this, 0);
        return sts;
      }
    }
    return 1;
  }
  if (streq(filename, "_none_.pwg")) {
    if (streq(object_name[0], "collect"))
      return 1;
  }

  // Get class from filename
  if ((s = strrchr(filename, '/')) || (s = strrchr(filename, '>'))
      || (s = strrchr(filename, ']')) || (s = strrchr(filename, ':'))) {
    if (str_StartsWith(s + 1, "pwr_t_")) {
      is_type = 1;
      strcpy(classname, s + 7);
    } else if (str_StartsWith(s + 1, "pwr_c_"))
      strcpy(classname, s + 7);
    else
      strcpy(classname, s + 1);
  } else
    strcpy(classname, filename);
  if ((s = strrchr(classname, '.')))
    *s = 0;

  if (is_type) {
    sts = gdh_NameToAttrref(pwr_cNObjid, object_name[0], &attrref);
    if (EVEN(sts))
      return sts;

    // Types are removed
    return 0;

  } else {
    sts = gdh_ClassNameToId(classname, &classid);
    if (EVEN(sts))
      return sts;

    sts = gdh_NameToAttrref(pwr_cNObjid, object_name[0], &attrref);
    if (EVEN(sts))
      return sts;

    for (i = 0; graph_object_functions[i].classid; i++) {
      if (classid == graph_object_functions[i].classid) {
        sts = (graph_object_functions[i].func)(this, &attrref);
        return sts;
      }
    }
  }
  return 0;
}

//
// Object graph for Di, Do and Dv
//

typedef struct {
  pwr_tCid cid;
  pwr_tBoolean* conv_p;
  pwr_tBoolean* inv_p;
  pwr_tBoolean* test_p;
  pwr_tSubid conv_subid;
  pwr_tSubid inv_subid;
  pwr_tSubid test_subid;
  pwr_tBoolean* local_conv_p;
  pwr_tBoolean* local_inv_p;
  pwr_tBoolean* local_test_p;
  pwr_tMask mask;
} graph_sObjectDx;

static void graph_object_dx_scan(Graph* graph)
{
  graph_sObjectDx* od = (graph_sObjectDx*)graph->graph_object_data;

  if (od->mask) {
    if (od->local_conv_p && od->conv_p)
      *od->local_conv_p = *od->conv_p & od->mask ? 1 : 0;
    if (od->local_inv_p && od->inv_p)
      *od->local_inv_p = *od->inv_p & od->mask ? 1 : 0;
    if (od->local_test_p && od->test_p)
      *od->local_test_p = *od->test_p & od->mask ? 1 : 0;
  } else {
    if (od->local_conv_p && od->conv_p)
      *od->local_conv_p = *od->conv_p;
    if (od->local_inv_p && od->inv_p)
      *od->local_inv_p = *od->inv_p;
    if (od->local_test_p && od->test_p)
      *od->local_test_p = *od->test_p;
  }
}

static void graph_object_dx_close(Graph* graph)
{
  graph_sObjectDx* od = (graph_sObjectDx*)graph->graph_object_data;

  if (od->local_conv_p && od->conv_p)
    gdh_UnrefObjectInfo(od->conv_subid);
  if (od->local_inv_p && od->inv_p)
    gdh_UnrefObjectInfo(od->inv_subid);
  if (od->local_conv_p && od->test_p)
    gdh_UnrefObjectInfo(od->test_subid);

  free(graph->graph_object_data);
}

static int graph_object_dx(Graph* graph, pwr_sAttrRef* arp)
{
  int sts;
  graph_sObjectDx* od;
  pwr_tAttrRef aref, chanaref;
  pwr_tAName aname;
  pwr_tCid card_cid;

  od = (graph_sObjectDx*)calloc(1, sizeof(graph_sObjectDx));
  graph->graph_object_data = (void*)od;
  graph->graph_object_close = graph_object_dx_close;

  sts = gdh_GetAttrRefTid(arp, &od->cid);
  if (EVEN(sts))
    return sts;

  // Get channel object
  sts = gdh_ArefANameToAref(arp, "SigChanCon", &aref);
  if (EVEN(sts)) {
    // Dv object, register scan function and return with success
    graph->graph_object_scan = graph_object_dx_scan;
    return 1;
  }

  sts = gdh_GetObjectInfoAttrref(&aref, &chanaref, sizeof(chanaref));
  if (EVEN(sts))
    return sts;

  od->local_conv_p = (pwr_tBoolean*)graph->localdb_ref_or_create(
      "ConversionOn", pwr_eType_Boolean);
  od->local_inv_p = (pwr_tBoolean*)graph->localdb_ref_or_create(
      "InvertOn", pwr_eType_Boolean);
  od->local_test_p = (pwr_tBoolean*)graph->localdb_ref_or_create(
      "TestOn", pwr_eType_Boolean);

  // Get card object
  if (chanaref.Flags.b.ObjectAttr) {
    sts = gdh_GetObjectClass(chanaref.Objid, &card_cid);
    if (EVEN(sts))
      return sts;
  } else
    card_cid = 0;

  switch (card_cid) {
  case pwr_cClass_Ssab_DI32D: {
    pwr_tAName card_name;

    unsigned int chan_idx
        = (chanaref.Offset - pwr_AlignLW(sizeof(pwr_sClass_Ssab_BaseDiCard)))
        / pwr_AlignLW(sizeof(pwr_sClass_ChanDi));

    sts = gdh_ObjidToName(
        chanaref.Objid, card_name, sizeof(card_name), cdh_mNName);
    if (EVEN(sts))
      return sts;

    if (chan_idx < 16) {
      strcpy(aname, card_name);
      strcat(aname, ".ConvMask1");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->conv_p,
          &od->conv_subid, sizeof(pwr_tBoolean), 0, true);

      strcpy(aname, card_name);
      strcat(aname, ".InvMask1");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->inv_p,
          &od->inv_subid, sizeof(pwr_tBoolean), 0, true);

      od->mask = 1 << chan_idx;
    } else if (chan_idx < 32) {
      strcpy(aname, card_name);
      strcat(aname, ".ConvMask2");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->conv_p,
          &od->conv_subid, sizeof(pwr_tBoolean), 0, true);

      strcpy(aname, card_name);
      strcat(aname, ".InvMask2");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->inv_p,
          &od->inv_subid, sizeof(pwr_tBoolean), 0, true);

      od->mask = 1 << (chan_idx - 16);
    } else
      return 0;

    break;
  }
  case pwr_cClass_Ssab_DO32DKS:
  case pwr_cClass_Ssab_DO32DKS_Stall: {
    pwr_tAName card_name;
    unsigned int chan_idx
        = (chanaref.Offset - pwr_AlignLW(sizeof(pwr_sClass_Ssab_BaseDoCard)))
        / pwr_AlignLW(sizeof(pwr_sClass_ChanDo));

    sts = gdh_ObjidToName(
        chanaref.Objid, card_name, sizeof(card_name), cdh_mNName);
    if (EVEN(sts))
      return sts;

    if (chan_idx < 16) {
      strcpy(aname, card_name);
      strcat(aname, ".TestMask1");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->test_p,
          &od->test_subid, sizeof(pwr_tBoolean), 0, true);

      strcpy(aname, card_name);
      strcat(aname, ".InvMask1");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->inv_p,
          &od->inv_subid, sizeof(pwr_tBoolean), 0, true);

      od->mask = 1 << chan_idx;
    } else if (chan_idx < 32) {
      strcpy(aname, card_name);
      strcat(aname, ".TestMask2");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->test_p,
          &od->test_subid, sizeof(pwr_tBoolean), 0, true);

      strcpy(aname, card_name);
      strcat(aname, ".InvMask2");

      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->inv_p,
          &od->inv_subid, sizeof(pwr_tBoolean), 0, true);

      od->mask = 1 << (chan_idx - 16);
    } else
      return 0;

    if (od->local_conv_p)
      *od->local_conv_p = 1;

    break;
  }
  default: {
    pwr_tAName chan_name;

    sts = gdh_AttrrefToName(
        &chanaref, chan_name, sizeof(chan_name), cdh_mNName);
    if (ODD(sts)) {
      if (od->cid == pwr_cClass_Di) {
        strcpy(aname, chan_name);
        strcat(aname, ".ConversionOn");
        graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->conv_p,
            &od->conv_subid, sizeof(pwr_tBoolean), 0, true);
      }

      strcpy(aname, chan_name);
      strcat(aname, ".InvertOn");
      graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->inv_p,
          &od->inv_subid, sizeof(pwr_tBoolean), 0, true);

      if (od->cid == pwr_cClass_Do) {
        strcpy(aname, chan_name);
        strcat(aname, ".TestOn");
        graph->ref_object_info(glow_eCycle_Slow, aname, (void**)&od->test_p,
            &od->test_subid, sizeof(pwr_tBoolean), 0, true);

        if (od->local_conv_p)
          *od->local_conv_p = 1;
      }
    }
  }
  }

  // Register scan function
  graph->graph_object_scan = graph_object_dx_scan;
  return 1;
}

int Graph::set_button_command(const char* button_name, const char* cmd)
{
  int sts;
  grow_tObject object;

  // Add command to open channel graph
  sts = grow_FindObjectByName(grow->ctx, button_name, &object);
  if (EVEN(sts))
    return sts;

  GeDyn* dyn;
  grow_GetUserData(object, (void**)&dyn);
  dyn->set_command(cmd);

  return 1;
}

void Graph::trend_scan(graph_sObjectTrend* td)
{
  // Reconfigure bar and trend if limits are changed
  if (td->pres_max_limit_p && td->pres_min_limit_p
      && (!feqf(*td->pres_max_limit_p, td->pres_max_limit_old)
             || !feqf(*td->pres_min_limit_p, td->pres_min_limit_old))) {
    if (!feqf(*td->pres_max_limit_p, *td->pres_min_limit_p)) {
      if (td->bar_object)
        grow_SetBarRange(td->bar_object, double(*td->pres_min_limit_p),
            double(*td->pres_max_limit_p));
      if (td->slider_object) {
        GeDyn* dyn;
        grow_SetSliderRange(td->slider_object, double(*td->pres_min_limit_p),
            double(*td->pres_max_limit_p));
        grow_GetUserData(td->slider_object, (void**)&dyn);
        dyn->update();
      }
      grow_SetTrendRangeY(td->trend_object, 0, double(*td->pres_min_limit_p),
          double(*td->pres_max_limit_p));
    }
    td->pres_min_limit_old = *td->pres_min_limit_p;
    td->pres_max_limit_old = *td->pres_max_limit_p;
  }

  // Reconfigure new scantime
  if (td->scan_time_p && !feqf(*td->scan_time_p, td->old_scan_time)) {
    if (scan_time > *td->scan_time_p / 200) {
      scan_time = *td->scan_time_p / 200;
      animation_scan_time = *td->scan_time_p / 200;
    }
    grow_SetTrendScanTime(td->trend_object, double(*td->scan_time_p / 200));
    td->old_scan_time = *td->scan_time_p;
    *td->data_scan_time_p = double(*td->scan_time_p) / 200;
  }

  if (td->hold_button_p && *td->hold_button_p) {
    *td->hold_p = !*td->hold_p;
    *td->hold_button_p = 0;
    if (*td->hold_p && td->hold_button_object) {
      grow_SetObjectColorTone(td->hold_button_object, glow_eDrawTone_Yellow);
      //      grow_SetAnnotation( td->hold_button_object, 1, "   Go", 6);
    } else {
      grow_ResetObjectColorTone(td->hold_button_object);
      //      grow_SetAnnotation( td->hold_button_object, 1, "   Hold", 8);
    }
  }

  if (td->slider_button_p && *td->slider_button_p) {
    *td->slider_disable_p = !*td->slider_disable_p;
    *td->slider_button_p = 0;
    if (!*td->slider_disable_p && td->slider_button_object)
      grow_SetObjectColorTone(td->slider_button_object, glow_eDrawTone_Yellow);
    else
      grow_ResetObjectColorTone(td->slider_button_object);
  }
}

int Graph::trend_init(graph_sObjectTrend* td, pwr_sAttrRef* arp)
{
  pwr_tClassId classid;
  pwr_tFloat32 max_limit = 100;
  pwr_tFloat32 min_limit = 0;
  int sts;
  pwr_sAttrRef attrref;
  grow_tObject object;
  int presminlimit_found = 0;
  int presmaxlimit_found = 0;
  double scan_time;

  if (arp && cdh_ObjidIsNotNull(arp->Objid)) {
    sts = gdh_GetAttrRefTid(arp, &classid);
    if (EVEN(sts))
      return sts;

    // Try to find attributes PresMaxLimit and PresMinLimit
    sts = gdh_ArefANameToAref(arp, "PresMaxLimit", &attrref);
    if (ODD(sts)) {
      sts = gdh_GetObjectInfoAttrref(
          &attrref, (void*)&max_limit, sizeof(max_limit));
      if (EVEN(sts))
        return sts;
      presmaxlimit_found = 1;
    }
    sts = gdh_ArefANameToAref(arp, "PresMinLimit", &attrref);
    if (ODD(sts)) {
      sts = gdh_GetObjectInfoAttrref(
          &attrref, (void*)&min_limit, sizeof(min_limit));
      if (EVEN(sts))
        return sts;
      presminlimit_found = 1;
    }
  }
  td->pres_max_limit_old = max_limit;
  td->pres_min_limit_old = min_limit;

  // Configure bar
  sts = grow_FindObjectByName(grow->ctx, "ActualValueBar", &td->bar_object);
  if (ODD(sts)) {
    if (!feqf(min_limit, max_limit))
      grow_SetBarRange(td->bar_object, double(min_limit), double(max_limit));
  }

  // Get pointers to max and min value
  sts = grow_FindObjectByName(grow->ctx, "PresMaxLimit", &object);
  if (ODD(sts)) {
    GeDyn* dyn;
    grow_GetUserData(object, (void**)&dyn);
    td->pres_max_limit_p = (pwr_tFloat32*)dyn->get_p();
    if (!presmaxlimit_found)
      // PresMaxLimit in local database, set value
      *td->pres_max_limit_p = max_limit;
  }

  sts = grow_FindObjectByName(grow->ctx, "PresMinLimit", &object);
  if (ODD(sts)) {
    GeDyn* dyn;
    grow_GetUserData(object, (void**)&dyn);
    td->pres_min_limit_p = (pwr_tFloat32*)dyn->get_p();
    if (!presminlimit_found)
      // PresMinLimit in local database, set value
      *td->pres_min_limit_p = min_limit;
  }

  // Configure trend
  sts = grow_FindObjectByName(grow->ctx, "ActualValueTrend", &td->trend_object);
  if (EVEN(sts))
    return sts;

  if (td->pres_min_limit_p && td->pres_max_limit_p) {
    if (!feqf(min_limit, max_limit))
      grow_SetTrendRangeY(
          td->trend_object, 0, double(min_limit), double(max_limit));
  }

  // Configure slider
  sts = grow_FindObjectByName(
      grow->ctx, "ActualValueSlider", &td->slider_object);
  if (ODD(sts)) {
    if (td->pres_min_limit_p && td->pres_max_limit_p) {
      if (!feqf(min_limit, max_limit))
        grow_SetSliderRange(
            td->slider_object, double(min_limit), double(max_limit));
    }
    GeDyn* dyn;
    grow_GetUserData(td->slider_object, (void**)&dyn);
    td->slider_disable_p = dyn->ref_slider_disabled();
    if (td->slider_disable_p)
      *td->slider_disable_p = 1;
  }

  // Set scantime variable in local database
  grow_GetTrendScanTime(td->trend_object, &scan_time);
  td->scan_time_p
      = (float*)localdb_ref_or_create("ScanTime", pwr_eType_Float32);
  td->old_scan_time = float(scan_time * 200);
  *td->scan_time_p = td->old_scan_time;

  // Get Hold button
  sts = grow_FindObjectByName(grow->ctx, "TrendHold", &td->hold_button_object);
  if (ODD(sts))
    td->hold_button_p
        = (int*)localdb_ref_or_create("TrendHold", pwr_eType_Boolean);

  GeDyn* dyn;
  grow_GetUserData(td->trend_object, (void**)&dyn);
  td->data_scan_time_p = dyn->ref_trend_scantime();
  td->hold_p = dyn->ref_trend_hold();

  sts = grow_FindObjectByName(
      grow->ctx, "SliderDisable", &td->slider_button_object);
  if (ODD(sts))
    td->slider_button_p
        = (int*)localdb_ref_or_create("SliderDisable", pwr_eType_Boolean);

  return 1;
}
//
// Object graph for collect
//

#define MAX_TREND_OBJECTS 100

static int graph_object_collect_build(Graph* graph, pwr_sAttrRef* attrref)
{
  pwr_sAttrRef *alist, *ap;
  int *is_attrp, *is_attr;
  int sts;
  char name[120];
  double x1, y1;
  grow_sAttrInfo *grow_info, *grow_info_p;
  int grow_info_cnt;
  int i;
  grow_tObject scantime_button;
  grow_tObject hold_button;
  grow_tObject t1, l1;
  double z_width, z_height, z_descent;
  double name_width = 0;
  double trend_width = 48;
  double trend_height = 1.2;
  double y0 = 2.2;
  double x0 = 2;
  pwr_tTypeId attr_type;
  unsigned int attr_size, attr_offset, attr_dimension;
  GeDyn* dyn;
  char attr_name[120];
  grow_sAttributes grow_attr;
  unsigned long mask;
  int trend_cnt = 0;

  if (!graph->get_current_objects_cb)
    return 0;

  sts = (graph->get_current_objects_cb)(graph->parent_ctx, &alist, &is_attr);
  if (EVEN(sts))
    return sts;

  if (cdh_ObjidIsNull(alist->Objid))
    return 0;

  graph->graph_object_data = 0;
  graph->graph_object_close = 0;

  grow_SetPath(graph->grow->ctx, 1, "pwr_exe:");

  // Set graph attributes

  // Default color theme
  mask = grow_eAttr_color_theme;
  strcpy(grow_attr.color_theme, "$default");
  grow_SetAttributes(graph->grow->ctx, &grow_attr, mask);
  grow_ReadCustomColorFile(graph->grow->ctx, 0);

  grow_SetBackgroundColor(graph->grow->ctx, glow_eDrawType_CustomColor1);

  // Scantime input field
  graph->create_node(NULL, "pwrct_valueinputsmallbg", x0, y0 - 1.3, 4,
      y0 - 1.3 + 1.2, &scantime_button);

  dyn = new GeDyn(graph);
  grow_SetUserData(scantime_button, (void*)dyn);

  dyn->set_dyn(ge_mDynType1_Value, ge_mDynType2_No, ge_mActionType1_ValueInput,
      ge_mActionType2_No);
  dyn->update_elements();
  dyn->set_access((glow_mAccess)65535);
  dyn->set_attribute(scantime_button, "$local.ScanTime##Float32", 0);
  dyn->set_value_input("%3.0f", 2, 10000000);

  // Hold button
  graph->create_node("TrendHold", "pwrct_buttonsmalltoggle",
      x0 + trend_width / 2 - 3. / 2, y0 - 1.4, x0 + trend_width / 2 + 3. / 2,
      y0 - 1.4 + 1.2, &hold_button);
  grow_SetAnnotation(hold_button, 1, "Hold", 4);

  dyn = new GeDyn(graph);
  grow_SetUserData(hold_button, (void*)dyn);

  dyn->set_access((glow_mAccess)65535);
  dyn->set_attribute(hold_button, "$local.TrendHold##Boolean", 0);

  //  Zero text
  grow_CreateGrowText(graph->grow->ctx, "", "0", x0 + trend_width - 0.2,
      y0 - 0.3, glow_eDrawType_TextHelvetica, glow_eDrawType_CustomColor5, 3,
      glow_eFont_LucidaSans, glow_mDisplayLevel_1, NULL, &t1);

  ap = alist;
  is_attrp = is_attr;
  x1 = x0;
  y1 = y0;
  while (cdh_ObjidIsNotNull(ap->Objid)) {
    if (*is_attrp) {
      sts = gdh_AttrrefToName(ap, name, sizeof(name), cdh_mNName);
      if (EVEN(sts))
        return sts;

      sts = gdh_GetAttributeCharacteristics(
          name, &attr_type, &attr_size, &attr_offset, &attr_dimension);
      if (EVEN(sts))
        return sts;

      switch (attr_type) {
      case pwr_eType_Boolean: {
        grow_tObject trend;

        grow_CreateGrowTrend(graph->grow->ctx, "ActualValueTrend", x1, y1,
            trend_width, trend_height, glow_eDrawType_Color37, 0,
            glow_mDisplayLevel_1, 1, 1, glow_eDrawType_Color40, NULL, &trend);
        dyn = new GeDyn(graph);
        dyn->dyn_type1 = ge_mDynType1_Trend;
        dyn->update_dyntype(trend);
        dyn->update_elements();
        grow_SetUserData(trend, (void*)dyn);

        grow_GetObjectAttrInfo(trend, NULL, &grow_info, &grow_info_cnt);

        strcpy(attr_name, name);
        strcat(attr_name, "##Boolean");
        grow_GetUserData(trend, (void**)&dyn);
        strcpy(((GeTrend*)dyn->elements)->attribute1, attr_name);
        strcpy(((GeTrend*)dyn->elements)->timerange_attr,
            "$local.ScanTime##Float32");
        strcpy(
            ((GeTrend*)dyn->elements)->hold_attr, "$local.TrendHold##Boolean");
        grow_info_p = grow_info;
        for (i = 0; i < grow_info_cnt; i++) {
          if (streq(grow_info_p->name, "NoOfPoints"))
            *(int*)grow_info_p->value_p = 200;
          else if (streq(grow_info_p->name, "HorizontalLines"))
            *(int*)grow_info_p->value_p = 0;
          else if (streq(grow_info_p->name, "VerticalLines"))
            *(int*)grow_info_p->value_p = 9;
          else if (streq(grow_info_p->name, "CurveColor1"))
            *(int*)grow_info_p->value_p = glow_eDrawType_CustomColor68;
          else if (streq(grow_info_p->name, "MaxValue1"))
            *(double*)grow_info_p->value_p = 1.2;
          else if (streq(grow_info_p->name, "MinValue1"))
            *(double*)grow_info_p->value_p = -0.1;

          grow_info_p++;
        }
        grow_FreeObjectAttrInfo(grow_info);

        // This will configure the curves
        grow_SetTrendScanTime(trend, 0.5);

        grow_SetObjectOriginalFillColor(trend, glow_eDrawType_CustomColor66);
        grow_SetObjectOriginalBorderColor(trend, glow_eDrawType_CustomColor67);

        grow_GetTextExtent(graph->grow->ctx, name, strlen(name),
            glow_eDrawType_TextHelvetica, 4, glow_eFont_LucidaSans, &z_width,
            &z_height, &z_descent);

        grow_CreateGrowText(graph->grow->ctx, "", name, x1 + trend_width + 1,
            y1 + trend_height / 2 + z_height / 2, glow_eDrawType_TextHelvetica,
            glow_eDrawType_CustomColor5, 4, glow_eFont_LucidaSans,
            glow_mDisplayLevel_1, NULL, &t1);
        if (z_width > name_width)
          name_width = z_width;

        trend_cnt++;
        y1 += trend_height;
        break;
      }
      default:;
      }
      if (trend_cnt >= MAX_TREND_OBJECTS)
        break;
    }

    ap++;
    is_attrp++;
  }
  free(alist);
  free(is_attr);

  // Draw separator lines between name texts
  y1 = y0;
  x1 = x0 + trend_width;
  grow_CreateGrowLine(graph->grow->ctx, "", x0 + trend_width, y1,
      x0 + trend_width + name_width + 2, y1, glow_eDrawType_CustomColor4, 1, 0,
      NULL, &l1);

  for (i = 0; i < trend_cnt; i++) {
    y1 += trend_height;

    grow_CreateGrowLine(graph->grow->ctx, "", x0 + trend_width, y1,
        x0 + trend_width + name_width + 2, y1, glow_eDrawType_CustomColor4, 1,
        0, NULL, &l1);
  }

  // Draw frame
  grow_CreateGrowRect(graph->grow->ctx, "R1", x0 - 1.5, y0 - 2.7,
      trend_width + name_width + 5.5, 1, glow_eDrawType_CustomColor3, 1, 0,
      glow_mDisplayLevel_1, 1, 0, 0, glow_eDrawType_CustomColor3, NULL, &l1);
  grow_CreateGrowRect(graph->grow->ctx, "R2", x0 - 1.5,
      y0 + trend_cnt * trend_height + 0.5, trend_width + name_width + 5.5, 5,
      glow_eDrawType_CustomColor3, 1, 0, glow_mDisplayLevel_1, 1, 0, 0,
      glow_eDrawType_CustomColor3, NULL, &l1);
  grow_CreateGrowRect(graph->grow->ctx, "R3", x0 + trend_width + name_width + 2,
      y0 - 1.7, 2, y0 + trend_cnt * trend_height + 0.9,
      glow_eDrawType_CustomColor3, 1, 0, glow_mDisplayLevel_1, 1, 0, 0,
      glow_eDrawType_CustomColor3, NULL, &l1);
  grow_CreateGrowRect(graph->grow->ctx, "R4", x0 - 1.5, y0 - 1.7, 1,
      y0 + trend_cnt * trend_height + 0.9, glow_eDrawType_CustomColor3, 1, 0,
      glow_mDisplayLevel_1, 1, 0, 0, glow_eDrawType_CustomColor3, NULL, &l1);

  grow_SetLayout(graph->grow->ctx, x0 - 1, y0 - 2.3,
      x0 + trend_width + name_width + 3, y0 + trend_cnt * trend_height + 1.5);

  return 1;
}

int Graph::create_node(const char* node_name, const char* subgraph_str,
    double x1, double y1, double x2, double y2, grow_tNode* node)
{
  int sts;
  grow_tNodeClass nc;
  double sx, sy;
  double ll_x, ll_y, ur_x, ur_y;
  char name[80];

  sts = grow_FindNodeClassByName(grow->ctx, subgraph_str, &nc);
  if (EVEN(sts)) {
    // Load the subgraph
    grow_OpenSubGraphFromName(grow->ctx, subgraph_str);
  }
  sts = grow_FindNodeClassByName(grow->ctx, subgraph_str, &nc);
  if (EVEN(sts)) {
    message('E', "Unable to open subgraph");
    return GE__SUBGRAPHLOAD;
  }

  if (!node_name)
    sprintf(name, "O%d", grow_GetNextObjectNameNumber(grow->ctx));
  else
    strcpy(name, node_name);

  if (!grow_IsSliderClass(nc))
    grow_CreateGrowNode(grow->ctx, name, nc, x1, y1, NULL, node);
  else
    grow_CreateGrowSlider(grow->ctx, name, nc, x1, y1, NULL, node);

  grow_MoveNode(*node, x1, y1);

  grow_MeasureNode(*node, &ll_x, &ll_y, &ur_x, &ur_y);
  if (!feq(x2, x1))
    sx = (x2 - x1) / (ur_x - ll_x);
  else
    sx = 1;
  if (!feq(y2, y1))
    sy = (y2 - y1) / (ur_y - ll_y);
  else
    sy = 1;
  grow_StoreTransform(*node);
  grow_SetObjectScale(*node, sx, sy, x1, y1, glow_eScaleType_LowerLeft);

  return 1;
}

//
// Object graph for PlcThread
//

typedef struct {
  pwr_tFloat32* set_max_show_p;
  pwr_tFloat32* set_min_show_p;
  pwr_tFloat32 set_max_show_old;
  pwr_tFloat32 set_min_show_old;
  grow_tObject set_bar_object;
  grow_tObject set_trend_object;
  grow_tObject hold_button_object;
  float* scan_time_p;
  float old_scan_time;
  double* data_set_scan_time_p;
  int* hold_button_p;
  int* hold_set_p;
} graph_sObjectPlcThread;

static void graph_object_PlcThread_scan(Graph* graph)
{
  graph_sObjectPlcThread* od
      = (graph_sObjectPlcThread*)graph->graph_object_data;

  // Reconfigure bar and trend if limits are changed
  if (od->set_max_show_p && od->set_min_show_p
      && (!feqf(*od->set_max_show_p, od->set_max_show_old)
             || !feqf(*od->set_min_show_p, od->set_min_show_old))) {
    if (!feqf(*od->set_max_show_p, *od->set_min_show_p)) {
      grow_SetBarRange(od->set_bar_object, double(*od->set_min_show_p),
          double(*od->set_max_show_p));
      grow_SetTrendRangeY(od->set_trend_object, 0, double(*od->set_min_show_p),
          double(*od->set_max_show_p));
      grow_SetTrendRangeY(od->set_trend_object, 1, double(*od->set_min_show_p),
          double(*od->set_max_show_p));
    }
    od->set_min_show_old = *od->set_min_show_p;
    od->set_max_show_old = *od->set_max_show_p;
  }
}

static void graph_object_PlcThread_close(Graph* graph)
{
  free(graph->graph_object_data);
}

static int graph_object_PlcThread(Graph* graph, pwr_sAttrRef* arp)
{
  pwr_sAttrRef attrref;
  int sts;
  graph_sObjectPlcThread* od;
  pwr_tClassId classid;
  pwr_tFloat32 max_limit = 1;
  pwr_tFloat32 min_limit = 0;
  pwr_tObjid objid = arp->Objid;

  od = (graph_sObjectPlcThread*)calloc(1, sizeof(graph_sObjectPlcThread));
  graph->graph_object_data = (void*)od;
  graph->graph_object_close = graph_object_PlcThread_close;

  sts = gdh_GetObjectClass(objid, &classid);
  if (EVEN(sts))
    return sts;

  // Get value for ScanTime
  sts = gdh_ClassAttrToAttrref(classid, ".ScanTime", &attrref);
  if (EVEN(sts))
    return sts;

  attrref.Objid = objid;
  sts = gdh_GetObjectInfoAttrref(
      &attrref, (void*)&max_limit, sizeof(max_limit));
  if (EVEN(sts))
    return sts;

  max_limit = max_limit * 2;

  od->set_max_show_old = max_limit;
  od->set_min_show_old = min_limit;

  // Configure ProcVal and SetVal bar
  sts = grow_FindObjectByName(
      graph->grow->ctx, "ActualScanTimeBar", &od->set_bar_object);
  if (EVEN(sts))
    return sts;

  if (!feqf(min_limit, max_limit))
    grow_SetBarRange(od->set_bar_object, double(min_limit), double(max_limit));

  // Get pointers to max and min value
  od->set_max_show_p
      = (float*)graph->localdb_ref_or_create("MaxShow", pwr_eType_Float32);
  *od->set_max_show_p = od->set_max_show_old;

  od->set_min_show_p
      = (float*)graph->localdb_ref_or_create("MinShow", pwr_eType_Float32);
  *od->set_min_show_p = od->set_min_show_old;

  // Configure SetVal  trend
  sts = grow_FindObjectByName(
      graph->grow->ctx, "ActualScanTimeTrend", &od->set_trend_object);
  if (EVEN(sts))
    return sts;

  if (!feqf(min_limit, max_limit)) {
    grow_SetTrendRangeY(
        od->set_trend_object, 0, double(min_limit), double(max_limit));
    grow_SetTrendRangeY(
        od->set_trend_object, 1, double(min_limit), double(max_limit));
  }

  // Register scan function
  graph->graph_object_scan = graph_object_PlcThread_scan;

  return 1;
}
