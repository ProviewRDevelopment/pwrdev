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

/* xtt_lognav.cpp -- Display test info */

#include <stdlib.h>

#include "pwr_baseclasses.h"
#include "co_cdh.h"
#include "co_dcli.h"
#include "co_string.h"
#include "co_time.h"

#include "flow_msg.h"

#include "xtt_lognav.h"

/*
#define LOGNAV__INPUT_SYNTAX 2
#define LOGNAV__OBJNOTFOUND 4
#define LOGNAV__STRINGTOLONG 6
#define LOGNAV__ITEM_NOCREA 8
*/
#define LOGNAV__SUCCESS 1

void LogNav::message(char sev, const char* text)
{
  (message_cb)(parent_ctx, sev, text);
}

void LogNav::print(char* filename)
{
  brow_Print(brow->ctx, filename);
}

//
//  Free pixmaps
//
void LogNavBrow::free_pixmaps()
{
  brow_FreeAnnotPixmap(ctx, pixmap_leaf);
  brow_FreeAnnotPixmap(ctx, pixmap_map);
  brow_FreeAnnotPixmap(ctx, pixmap_openmap);
}

//
//  Create pixmaps for leaf, closed map and open map
//
void LogNavBrow::allocate_pixmaps()
{
  brow_LoadPBM(ctx, "xnav_bitmap_leaf", &pixmap_leaf);
  brow_LoadPBM(ctx, "xnav_bitmap_map", &pixmap_map);
  brow_LoadPBM(ctx, "xnav_bitmap_openmap", &pixmap_openmap);
}

//
// Create the navigator widget
//
LogNav::LogNav(void* xn_parent_ctx, LogNav_hier *xn_tree, pwr_tStatus* status)
  : parent_ctx(xn_parent_ctx), tree(xn_tree),
    message_cb(NULL)
{
  *status = 1;
}

//
//  Delete a nav context
//
LogNav::~LogNav()
{
}

LogNavBrow::~LogNavBrow()
{
  free_pixmaps();
}

//
// Callbacks from brow
//
static int lognav_brow_cb(FlowCtx* ctx, flow_tEvent event)
{
  LogNav* lognav;
  ItemBase* item;

  if (event->event == flow_eEvent_ObjectDeleted) {
    brow_GetUserData(event->object.object, (void**)&item);
    delete item;
    return 1;
  }

  brow_GetCtxUserData((BrowCtx*)ctx, (void**)&lognav);

  lognav->message(' ', "");
  switch (event->event) {
  case flow_eEvent_Key_PageDown: {
    brow_Page(lognav->brow->ctx, 0.8);
    break;
  }
  case flow_eEvent_Key_PageUp: {
    brow_Page(lognav->brow->ctx, -0.8);
    break;
  }
  case flow_eEvent_ScrollDown: {
    brow_Page(lognav->brow->ctx, 0.1);
    break;
  }
  case flow_eEvent_ScrollUp: {
    brow_Page(lognav->brow->ctx, -0.1);
    break;
  }
  case flow_eEvent_Key_Up: {
    brow_tNode* node_list;
    int node_count;
    brow_tObject object;
    int sts;

    brow_GetSelectedNodes(lognav->brow->ctx, &node_list, &node_count);
    if (!node_count) {
      sts = brow_GetLastVisible(lognav->brow->ctx, &object);
      if (EVEN(sts))
        return 1;
    } else {
      if (!brow_IsVisible(
              lognav->brow->ctx, node_list[0], flow_eVisible_Partial)) {
        sts = brow_GetLastVisible(lognav->brow->ctx, &object);
        if (EVEN(sts))
          return 1;
      } else {
        sts = brow_GetPrevious(lognav->brow->ctx, node_list[0], &object);
        if (EVEN(sts)) {
          if (node_count)
            free(node_list);
          return 1;
        }
      }
    }
    brow_SelectClear(lognav->brow->ctx);
    brow_SetInverse(object, 1);
    brow_SelectInsert(lognav->brow->ctx, object);
    if (!brow_IsVisible(lognav->brow->ctx, object, flow_eVisible_Full))
      brow_CenterObject(lognav->brow->ctx, object, 0.25);
    if (node_count)
      free(node_list);
    break;
  }
  case flow_eEvent_Key_Down: {
    brow_tNode* node_list;
    int node_count;
    brow_tObject object;
    int sts;

    brow_GetSelectedNodes(lognav->brow->ctx, &node_list, &node_count);
    if (!node_count) {
      sts = brow_GetFirstVisible(lognav->brow->ctx, &object);
      if (EVEN(sts))
        return 1;
    } else {
      if (!brow_IsVisible(
              lognav->brow->ctx, node_list[0], flow_eVisible_Partial)) {
        sts = brow_GetFirstVisible(lognav->brow->ctx, &object);
        if (EVEN(sts))
          return 1;
      } else {
        sts = brow_GetNext(lognav->brow->ctx, node_list[0], &object);
        if (EVEN(sts)) {
          if (node_count)
            free(node_list);
          return 1;
        }
      }
    }
    brow_SelectClear(lognav->brow->ctx);
    brow_SetInverse(object, 1);
    brow_SelectInsert(lognav->brow->ctx, object);
    if (!brow_IsVisible(lognav->brow->ctx, object, flow_eVisible_Full))
      brow_CenterObject(lognav->brow->ctx, object, 0.75);
    if (node_count)
      free(node_list);
    break;
  }
  case flow_eEvent_SelectClear:
    brow_ResetSelectInverse(lognav->brow->ctx);
    break;
  case flow_eEvent_MB1Click: {
    // Select
    double ll_x, ll_y, ur_x, ur_y;
    int sts;

    switch (event->object.object_type) {
    case flow_eObjectType_Node:
      brow_MeasureNode(event->object.object, &ll_x, &ll_y, &ur_x, &ur_y);
      if (event->object.x < ll_x + 1.0) {
        // Simulate doubleclick
        flow_tEvent doubleclick_event;

        doubleclick_event = (flow_tEvent)calloc(1, sizeof(*doubleclick_event));
        memcpy(doubleclick_event, event, sizeof(*doubleclick_event));
        doubleclick_event->event = flow_eEvent_MB1DoubleClick;
        sts = lognav_brow_cb(ctx, doubleclick_event);
        free((char*)doubleclick_event);
        return sts;
      }

      if (brow_FindSelectedObject(lognav->brow->ctx, event->object.object)) {
        brow_SelectClear(lognav->brow->ctx);
      } else {
        brow_SelectClear(lognav->brow->ctx);
        brow_SetInverse(event->object.object, 1);
        brow_SelectInsert(lognav->brow->ctx, event->object.object);
      }
      break;
    default:
      brow_SelectClear(lognav->brow->ctx);
    }
    break;
  }
  case flow_eEvent_Key_Left: {
    brow_tNode* node_list;
    int node_count;
    brow_tObject object;
    int sts;

    brow_GetSelectedNodes(lognav->brow->ctx, &node_list, &node_count);
    if (!node_count)
      return 1;

    if (brow_IsOpen(node_list[0]))
      // Close this node
      object = node_list[0];
    else {
      // Close parent
      sts = brow_GetParent(lognav->brow->ctx, node_list[0], &object);
      if (EVEN(sts)) {
        free(node_list);
        return 1;
      }
    }
    brow_GetUserData(object, (void**)&item);
    item->close(lognav, 0, 0);

    brow_SelectClear(lognav->brow->ctx);
    brow_SetInverse(object, 1);
    brow_SelectInsert(lognav->brow->ctx, object);
    if (!brow_IsVisible(lognav->brow->ctx, object, flow_eVisible_Full))
      brow_CenterObject(lognav->brow->ctx, object, 0.25);
    free(node_list);
    break;
  }
  case flow_eEvent_Key_Right: {
    brow_tNode* node_list;
    int node_count;

    brow_GetSelectedNodes(lognav->brow->ctx, &node_list, &node_count);
    if (!node_count)
      return 1;

    brow_GetUserData(node_list[0], (void**)&item);
    switch (item->type) {
    case lognav_eItemType_Hier:
      ((ItemHier*)item)->open_children(lognav, 0, 0);
      break;
    case lognav_eItemType_Entry:
      ((ItemEntry*)item)->open_children(lognav, 0, 0);
      break;
    default:;
    }
  }
  case flow_eEvent_MB1DoubleClick:
    switch (event->object.object_type) {
    case flow_eObjectType_Node:
      brow_GetUserData(event->object.object, (void**)&item);
      switch (item->type) {
      case lognav_eItemType_Hier:
        ((ItemHier*)item)
            ->open_children(lognav, event->object.x, event->object.y);
      case lognav_eItemType_Entry:
        ((ItemEntry*)item)
            ->open_children(lognav, event->object.x, event->object.y);
        break;
      default:;
      }
      break;
    default:;
    }
    break;
  default:;
  }
  return 1;
}

//
// Create nodeclasses
//
void LogNavBrow::create_nodeclasses()
{
  allocate_pixmaps();

  // Create red class

  brow_CreateNodeClass(
      ctx, "Red", flow_eNodeGroup_Common, &nc_red);
  brow_AddAnnotPixmap(nc_red, 0, 0.2, 0.1, flow_eDrawType_Line, 2, 0);
  brow_AddFilledRect(nc_red, 1.05, 0.05, 0.6, 0.6, flow_eDrawType_LineRed);
  brow_AddRect(nc_red, 1.05, 0.05, 0.6, 0.6, flow_eDrawType_Line, 0, 0);
  brow_AddAnnot(nc_red, 2, 0.6, 0, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_red, 9.5, 0.6, 1, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 1);
  brow_AddFrame(nc_red, 0, 0, 20, 0.83, flow_eDrawType_LineGray, -1, 1);

  // Create green class

  brow_CreateNodeClass(
      ctx, "Green", flow_eNodeGroup_Common, &nc_green);
  brow_AddAnnotPixmap(nc_green, 0, 0.2, 0.1, flow_eDrawType_Line, 2, 0);
  brow_AddFilledRect(nc_green, 1.05, 0.05, 0.6, 0.6, flow_eDrawType_Green);
  brow_AddRect(nc_green, 1.05, 0.05, 0.6, 0.6, flow_eDrawType_Line, 0, 0);
  brow_AddAnnot(nc_green, 2, 0.6, 0, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_green, 9.5, 0.6, 1, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 1);
  brow_AddFrame(nc_green, 0, 0, 20, 0.83, flow_eDrawType_LineGray, -1, 1);

  // Create yellow class

  brow_CreateNodeClass(
      ctx, "Yellow", flow_eNodeGroup_Common, &nc_yellow);
  brow_AddAnnotPixmap(nc_yellow, 0, 0.2, 0.1, flow_eDrawType_Line, 2, 0);
  brow_AddFilledRect(nc_yellow, 1.05, 0.05, 0.6, 0.6, flow_eDrawType_Yellow);
  brow_AddRect(nc_yellow, 1.05, 0.05, 0.6, 0.6, flow_eDrawType_Line, 0, 0);
  brow_AddAnnot(nc_yellow, 2, 0.6, 0, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_yellow, 9.5, 0.6, 1, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 1);
  brow_AddFrame(nc_yellow, 0, 0, 20, 0.83, flow_eDrawType_LineGray, -1, 1);

  // Create white class

  brow_CreateNodeClass(
      ctx, "White", flow_eNodeGroup_Common, &nc_white);
  brow_AddAnnotPixmap(nc_white, 0, 0.2, 0.1, flow_eDrawType_Line, 2, 0);
  brow_AddRect(nc_white, 1.05, 0.05, 0.6, 0.6, flow_eDrawType_Line, 0, 0);
  brow_AddAnnot(nc_white, 2, 0.6, 0, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_white, 9.5, 0.6, 1, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 1);
  brow_AddFrame(nc_white, 0, 0, 20, 0.83, flow_eDrawType_LineGray, -1, 1);

  // Create without mark

  brow_CreateNodeClass(
      ctx, "NoMark", flow_eNodeGroup_Common, &nc_nomark);
  brow_AddAnnotPixmap(nc_nomark, 0, 0.2, 0.1, flow_eDrawType_Line, 2, 0);
  brow_AddAnnot(nc_nomark, 2, 0.6, 0, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_nomark, 9.5, 0.6, 1, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 1);
  brow_AddFrame(nc_nomark, 0, 0, 20, 0.83, flow_eDrawType_LineGray, -1, 1);

}

int LogNav::create_items()
{
  brow_SetNodraw(brow->ctx);

  for (int i = 0; i < tree->child.size(); i++) {
    new ItemHier(this, &tree->child[i], NULL, flow_eDest_IntoLast);
  }
  brow_ResetNodraw(brow->ctx);
  brow_Redraw(brow->ctx, 0);
  return LOGNAV__SUCCESS;
}

void LogNavBrow::brow_setup()
{
  brow_sAttributes brow_attr;
  unsigned long mask;

  mask = 0;
  mask |= brow_eAttr_indentation;
  brow_attr.indentation = 0.5;
  mask |= brow_eAttr_annotation_space;
  brow_attr.annotation_space = 0.5;
  brow_SetAttributes(ctx, &brow_attr, mask);
  brow_SetCtxUserData(ctx, lognav);

  brow_EnableEvent(
      ctx, flow_eEvent_MB1Click, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_MB1DoubleClick, flow_eEventType_CallBack,
      lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_SelectClear, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_ObjectDeleted, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_Up, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_Down, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_Right, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_Left, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_PF3, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Radiobutton, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_PageUp, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_PageDown, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_ScrollUp, flow_eEventType_CallBack, lognav_brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_ScrollDown, flow_eEventType_CallBack, lognav_brow_cb);
}

//
// Backcall routine called at creation of the brow widget
// Enable event, create nodeclasses and insert the root objects.
//
int LogNav::init_brow_cb(FlowCtx* fctx, void* client_data)
{
  LogNav* lognav = (LogNav*)client_data;
  BrowCtx* ctx = (BrowCtx*)fctx;

  lognav->brow = new LogNavBrow(ctx, (void*)lognav);

  lognav->brow->brow_setup();
  lognav->brow->create_nodeclasses();

  // Create the root items
  lognav->create_items();

  if (lognav->command_cb) {
    pwr_tCmd cmd = "@$HOME/test_xtt_setup";
    lognav->command_cb(lognav->parent_ctx, cmd);
  }

  return 1;
}

int LogNav::get_select(ItemBase** item)
{
  brow_tNode* node_list;
  int node_count;

  brow_GetSelectedNodes(brow->ctx, &node_list, &node_count);

  if (!node_count)
    return 0;

  brow_GetUserData(node_list[0], (void**)item);
  return 1;
}

//
//  Get zoom
//
void LogNav::get_zoom(double* zoom_factor)
{
  brow_GetZoom(brow->ctx, zoom_factor);
}

//
//  Zoom
//
void LogNav::zoom(double zoom_factor)
{
  brow_Zoom(brow->ctx, zoom_factor);
}

//
//  Return to base zoom factor
//
void LogNav::unzoom()
{
  brow_UnZoom(brow->ctx);
}

ItemBase::ItemBase(lognav_eItemType t) : type(t)
{
}

ItemBase::~ItemBase()
{
}

int ItemBase::close(LogNav* lognav, double x, double y)
{
  return 1;
}

ItemHier ::ItemHier (LogNav* lognav, LogNav_hier* xitem,
    brow_tNode dest, flow_eDest dest_code)
    : ItemBase(lognav_eItemType_Hier), item(xitem)
{
  brow_tNodeClass nc;

  type = lognav_eItemType_Hier;

  switch (item->severity) {
  case lognav_eSeverity_Fatal:
  case lognav_eSeverity_Error:
  case lognav_eSeverity_DetailError:
    nc = lognav->brow->nc_red;
    break;
  case lognav_eSeverity_Warning:
  case lognav_eSeverity_DetailWarning:
    nc = lognav->brow->nc_yellow;
    break;
  case lognav_eSeverity_Info:
  case lognav_eSeverity_Success:
  case lognav_eSeverity_No:
  case lognav_eSeverity_Detail:
    nc = lognav->brow->nc_nomark;
    break;
  }
  brow_CreateNode(lognav->brow->ctx, "HierItem", nc, dest,
      dest_code, (void*)this, 1, &node);

  if (item->child.size() == 0)
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_leaf);
  else
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_map);

  brow_SetAnnotation(node, 0, item->text, strlen(item->text));
}

int ItemHier::open_children(LogNav* lognav, double x, double y)
{
  double node_x, node_y;

  brow_GetNodePosition(node, &node_x, &node_y);

  if (brow_IsOpen(node)) {
    // Close
    brow_SetNodraw(lognav->brow->ctx);
    brow_CloseNode(lognav->brow->ctx, node);
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_map);
    brow_ResetOpen(node, lognav_mOpen_All);
    brow_ResetNodraw(lognav->brow->ctx);
    brow_Redraw(lognav->brow->ctx, node_y);
  } else {

    brow_SetNodraw(lognav->brow->ctx);

    for (int i = 0; i < item->child.size(); i++) {
      if (item->child[i].type == lognav_eItemType_Hier)
	new ItemHier(lognav, &item->child[i], node, flow_eDest_IntoLast);
      else
	new ItemEntry(lognav, &item->child[i], node, flow_eDest_IntoLast);
    }
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_openmap);
    brow_SetOpen(node, lognav_mOpen_Children);
    brow_ResetNodraw(lognav->brow->ctx);
    brow_Redraw(lognav->brow->ctx, node_y);
  }
  return 1;
}

int ItemHier::close(LogNav* lognav, double x, double y)
{
  double node_x, node_y;

  brow_GetNodePosition(node, &node_x, &node_y);

  if (brow_IsOpen(node)) {
    // Close
    brow_SetNodraw(lognav->brow->ctx);
    brow_CloseNode(lognav->brow->ctx, node);
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_map);
    brow_ResetOpen(node, lognav_mOpen_All);
    brow_ResetNodraw(lognav->brow->ctx);
    brow_Redraw(lognav->brow->ctx, node_y);
  }
  return 1;
}

ItemEntry ::ItemEntry (LogNav* lognav, LogNav_hier* xitem,
    brow_tNode dest, flow_eDest dest_code)
    : ItemBase(lognav_eItemType_Hier), item(xitem)
{
  char timstr[40];
  brow_tNodeClass nc;

  type = lognav_eItemType_Entry;

  switch (item->severity) {
  case lognav_eSeverity_Fatal:
  case lognav_eSeverity_Error:
  case lognav_eSeverity_DetailError:
    nc = lognav->brow->nc_red;
    break;
  case lognav_eSeverity_Warning:
  case lognav_eSeverity_DetailWarning:
    nc = lognav->brow->nc_yellow;
    break;
  case lognav_eSeverity_Info:
  case lognav_eSeverity_Success:
  case lognav_eSeverity_No:
  case lognav_eSeverity_Detail:
    nc = lognav->brow->nc_nomark;
    break;
  }
  
  brow_CreateNode(lognav->brow->ctx, "EntryItem", nc, dest,
      dest_code, (void*)this, 1, &node);

  if (item->child.size() == 0)
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_leaf);
  else
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_map);

  time_AtoAscii(&item->time, time_eFormat_DateAndTime, timstr, sizeof(timstr));
  brow_SetAnnotation(node, 0, timstr, strlen(timstr));
  brow_SetAnnotation(node, 1, item->text, strlen(item->text));
}

int ItemEntry::open_children(LogNav* lognav, double x, double y)
{
  double node_x, node_y;
  if (item->child.size() == 0)
    return 1;

  brow_GetNodePosition(node, &node_x, &node_y);

  if (brow_IsOpen(node)) {
    // Close
    brow_SetNodraw(lognav->brow->ctx);
    brow_CloseNode(lognav->brow->ctx, node);
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_map);
    brow_ResetOpen(node, lognav_mOpen_All);
    brow_ResetNodraw(lognav->brow->ctx);
    brow_Redraw(lognav->brow->ctx, node_y);
  } else {

    brow_SetNodraw(lognav->brow->ctx);

    for (int i = 0; i < item->child.size(); i++) {
      if (item->child[i].type == lognav_eItemType_Hier)
	new ItemHier(lognav, &item->child[i], node, flow_eDest_IntoLast);
      else
	new ItemEntry(lognav, &item->child[i], node, flow_eDest_IntoLast);
    }
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_openmap);
    brow_SetOpen(node, lognav_mOpen_Children);
    brow_ResetNodraw(lognav->brow->ctx);
    brow_Redraw(lognav->brow->ctx, node_y);
  }
  return 1;
}

int ItemEntry::close(LogNav* lognav, double x, double y)
{
  double node_x, node_y;

  brow_GetNodePosition(node, &node_x, &node_y);

  if (brow_IsOpen(node)) {
    // Close
    brow_SetNodraw(lognav->brow->ctx);
    brow_CloseNode(lognav->brow->ctx, node);
    brow_SetAnnotPixmap(node, 0, lognav->brow->pixmap_map);
    brow_ResetOpen(node, lognav_mOpen_All);
    brow_ResetNodraw(lognav->brow->ctx);
    brow_Redraw(lognav->brow->ctx, node_y);
  }
  return 1;
}

