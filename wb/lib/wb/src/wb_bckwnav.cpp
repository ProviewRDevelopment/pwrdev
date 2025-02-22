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

/* wb_bckwnav.cpp -- Backupfile display window */

#include "pwr_baseclasses.h"

#include "co_string.h"
#include "co_time.h"

#include "wb_bckwnav.h"
#include "wb_ldh_msg.h"

//
//  Free pixmaps
//
void WbBckWNavBrow::free_pixmaps()
{
  brow_FreeAnnotPixmap(ctx, pixmap_save);
  brow_FreeAnnotPixmap(ctx, pixmap_build);
  brow_FreeAnnotPixmap(ctx, pixmap_package);
  brow_FreeAnnotPixmap(ctx, pixmap_copy);
  brow_FreeAnnotPixmap(ctx, pixmap_export);
  brow_FreeAnnotPixmap(ctx, pixmap_clone);
}

//
//  Create pixmaps for leaf, closed map and open map
//
void WbBckWNavBrow::allocate_pixmaps()
{
  brow_LoadPBM(ctx, "xnav_bitmap_save", &pixmap_save);
  brow_LoadPBM(ctx, "xnav_bitmap_build", &pixmap_build);
  brow_LoadPBM(ctx, "xnav_bitmap_package", &pixmap_package);
  brow_LoadPBM(ctx, "xnav_bitmap_copy", &pixmap_copy);
  brow_LoadPBM(ctx, "xnav_bitmap_export", &pixmap_export);
  brow_LoadPBM(ctx, "xnav_bitmap_clone", &pixmap_clone);
}

//
// Create nodeclasses
//
void WbBckWNavBrow::create_nodeclasses()
{
  allocate_pixmaps();

  // Create common-class

  brow_CreateNodeClass(ctx, "LogDefault", flow_eNodeGroup_Common, &nc_bck);
  brow_AddAnnotPixmap(nc_bck, 0, 0.2, 0.1, flow_eDrawType_Line, 2, 0);
  brow_AddAnnot(nc_bck, 2.8, 0.6, 0, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_bck, 35, 0.6, 1, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_bck, 45, 0.6, 2, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddFrame(nc_bck, 0, 0, 35, 0.83, flow_eDrawType_LineGray, -1, 1);

  // Create common-class with radiobutton

  brow_CreateNodeClass(ctx, "LogDefault", flow_eNodeGroup_Common, &nc_wbbck);
  brow_AddAnnotPixmap(nc_wbbck, 0, 0.2, 0.1, flow_eDrawType_Line, 2, 0);
  brow_AddRadiobutton(nc_wbbck, 1.4, 0.03, 0.7, 0.7, 0, flow_eDrawType_Line, 1);
  brow_AddAnnot(nc_wbbck, 2.8, 0.6, 0, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_wbbck, 35, 0.6, 1, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddAnnot(nc_wbbck, 45, 0.6, 2, flow_eDrawType_TextHelvetica, 2,
      flow_eAnnotType_OneLine, 0);
  brow_AddFrame(nc_wbbck, 0, 0, 35, 0.83, flow_eDrawType_LineGray, -1, 1);
}

void WbBckWNavBrow::brow_setup()
{
  brow_sAttributes brow_attr;
  unsigned long mask;

  mask = 0;
  mask |= brow_eAttr_indentation;
  brow_attr.indentation = 0.5;
  mask |= brow_eAttr_annotation_space;
  brow_attr.annotation_space = 0.5;
  brow_SetAttributes(ctx, &brow_attr, mask);
  brow_SetCtxUserData(ctx, bckwnav);

  brow_EnableEvent(
      ctx, flow_eEvent_MB1Click, flow_eEventType_CallBack, WbBckWNav::brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_MB1DoubleClick, flow_eEventType_CallBack,
      WbBckWNav::brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_MB3Press, flow_eEventType_CallBack, WbBckWNav::brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_MB3Down, flow_eEventType_CallBack, WbBckWNav::brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_SelectClear, flow_eEventType_CallBack,
      WbBckWNav::brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_ObjectDeleted, flow_eEventType_CallBack,
      WbBckWNav::brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_Up, flow_eEventType_CallBack, WbBckWNav::brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_Down, flow_eEventType_CallBack, WbBckWNav::brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_Key_PF3, flow_eEventType_CallBack, WbBckWNav::brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_Key_PageUp, flow_eEventType_CallBack,
      WbBckWNav::brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_Key_PageDown, flow_eEventType_CallBack,
      WbBckWNav::brow_cb);
  brow_EnableEvent(
      ctx, flow_eEvent_ScrollUp, flow_eEventType_CallBack, WbBckWNav::brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_ScrollDown, flow_eEventType_CallBack,
      WbBckWNav::brow_cb);
  brow_EnableEvent(ctx, flow_eEvent_Radiobutton, flow_eEventType_CallBack,
      WbBckWNav::brow_cb);
}

//
// Backcall routine called at creation of the brow widget
// Enable event, create nodeclasses and insert the root objects.
//
int WbBckWNav::init_brow_cb(FlowCtx* fctx, void* client_data)
{
  WbBckWNav* bckwnav = (WbBckWNav*)client_data;
  BrowCtx* ctx = (BrowCtx*)fctx;

  bckwnav->brow = new WbBckWNavBrow(ctx, (void*)bckwnav);

  bckwnav->brow->brow_setup();
  bckwnav->brow->create_nodeclasses();

  return 1;
}

WbBckWNav::WbBckWNav(void* l_parent_ctx, ldh_tSesContext l_ldhses,
    wb_bck_list* l_list, int l_editmode)
    : parent_ctx(l_parent_ctx), ldhses(l_ldhses), list(l_list),
      editmode(l_editmode)
{
}

//
//  Delete ev
//
WbBckWNav::~WbBckWNav()
{
}

WbBckWNavBrow::~WbBckWNavBrow()
{
  free_pixmaps();
}

//
//  Zoom
//
void WbBckWNav::zoom(double zoom_factor)
{
  brow_Zoom(brow->ctx, zoom_factor);
}

//
//  Return to base zoom factor
//
void WbBckWNav::unzoom()
{
  brow_UnZoom(brow->ctx);
}

//
// Callbacks from brow
//
int WbBckWNav::brow_cb(FlowCtx* ctx, flow_tEvent event)
{
  WbBckWNav* bckwnav;
  ItemBck* item;

  if (event->event == flow_eEvent_ObjectDeleted) {
    brow_GetUserData(event->object.object, (void**)&item);
    delete item;
    return 1;
  }

  brow_GetCtxUserData((BrowCtx*)ctx, (void**)&bckwnav);
  switch (event->event) {
  case flow_eEvent_Key_Up: {
    brow_tNode* node_list;
    int node_count;
    brow_tObject object;
    int sts;

    brow_GetSelectedNodes(bckwnav->brow->ctx, &node_list, &node_count);
    if (!node_count) {
      sts = brow_GetLastVisible(bckwnav->brow->ctx, &object);
      if (EVEN(sts))
        return 1;
    } else {
      if (!brow_IsVisible(
              bckwnav->brow->ctx, node_list[0], flow_eVisible_Partial)) {
        sts = brow_GetLastVisible(bckwnav->brow->ctx, &object);
        if (EVEN(sts))
          return 1;
      } else {
        sts = brow_GetPrevious(bckwnav->brow->ctx, node_list[0], &object);
        if (EVEN(sts)) {
          if (node_count)
            free(node_list);
          return 1;
        }
      }
    }
    brow_SelectClear(bckwnav->brow->ctx);
    brow_SetInverse(object, 1);
    brow_SelectInsert(bckwnav->brow->ctx, object);
    if (!brow_IsVisible(bckwnav->brow->ctx, object, flow_eVisible_Full))
      brow_CenterObject(bckwnav->brow->ctx, object, 0.25);
    if (node_count)
      free(node_list);
    break;
  }
  case flow_eEvent_Key_Down: {
    brow_tNode* node_list;
    int node_count;
    brow_tObject object;
    int sts;

    brow_GetSelectedNodes(bckwnav->brow->ctx, &node_list, &node_count);
    if (!node_count) {
      sts = brow_GetFirstVisible(bckwnav->brow->ctx, &object);
      if (EVEN(sts))
        return 1;
    } else {
      if (!brow_IsVisible(
              bckwnav->brow->ctx, node_list[0], flow_eVisible_Partial)) {
        sts = brow_GetFirstVisible(bckwnav->brow->ctx, &object);
        if (EVEN(sts))
          return 1;
      } else {
        sts = brow_GetNext(bckwnav->brow->ctx, node_list[0], &object);
        if (EVEN(sts)) {
          if (node_count)
            free(node_list);
          return 1;
        }
      }
    }
    brow_SelectClear(bckwnav->brow->ctx);
    brow_SetInverse(object, 1);
    brow_SelectInsert(bckwnav->brow->ctx, object);
    if (!brow_IsVisible(bckwnav->brow->ctx, object, flow_eVisible_Full))
      brow_CenterObject(bckwnav->brow->ctx, object, 0.75);
    if (node_count)
      free(node_list);
    break;
  }
  case flow_eEvent_SelectClear:
    brow_ResetSelectInverse(bckwnav->brow->ctx);
    break;
  case flow_eEvent_MB1Click:
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
        sts = WbBckWNav::brow_cb(ctx, doubleclick_event);
        free((char*)doubleclick_event);
        return sts;
      }

      if (brow_FindSelectedObject(bckwnav->brow->ctx, event->object.object)) {
        brow_SelectClear(bckwnav->brow->ctx);
      } else {
        brow_SelectClear(bckwnav->brow->ctx);
        brow_SetInverse(event->object.object, 1);
        brow_SelectInsert(bckwnav->brow->ctx, event->object.object);
      }
      break;
    default:
      brow_SelectClear(bckwnav->brow->ctx);
    }
    break;
  case flow_eEvent_Key_PageDown: {
    brow_Page(bckwnav->brow->ctx, 0.95);
    break;
  }
  case flow_eEvent_Key_PageUp: {
    brow_Page(bckwnav->brow->ctx, -0.95);
    break;
  }
  case flow_eEvent_ScrollDown: {
    brow_Page(bckwnav->brow->ctx, 0.10);
    break;
  }
  case flow_eEvent_ScrollUp: {
    brow_Page(bckwnav->brow->ctx, -0.10);
    break;
  }
  case flow_eEvent_MB1DoubleClick:
    break;
  case flow_eEvent_Radiobutton: {
    switch (event->object.object_type) {
    case flow_eObjectType_Node:
      brow_GetUserData(event->object.object, (void**)&item);
      switch (item->type) {
      case bckwitem_eItemType_Bck:
        ((ItemBck*)item)->set(!event->radiobutton.value);
        break;
      default:;
      }
      break;
    default:;
    }
    break;
  }
  default:;
  }
  return 1;
}

void WbBckWNav::show()
{
  if (!list)
    return;

  brow_SetNodraw(brow->ctx);

  for (bck_sItem* ip = list->first(); ip; ip = list->next(ip)) {
    if (!ip->hide)
      new ItemBck(this, ip, 0, flow_eDest_IntoLast);
  }

  brow_ResetNodraw(brow->ctx);
  brow_Redraw(brow->ctx, 0);
}

void WbBckWNav::clear()
{
  brow_DeleteAll(brow->ctx);
}

pwr_tStatus WbBckWNav::transfer_wb()
{
  int sts;
  brow_tNode node;
  int rval;
  ItemBck* item;
  char* anamep;
  int size;
  pwr_tAttrRef aref;
  pwr_tCid cid;
  char* s;
  pwr_tAName aname;

  for (sts = brow_GetFirst(brow->ctx, &node); ODD(sts);
       sts = brow_GetNext(brow->ctx, node, &node)) {
    brow_GetRadiobutton(node, 0, &rval);

    if (rval) {
      brow_GetUserData(node, (void**)&item);

      bck_sItem* ip = item->bck_item;

      sts = ldh_AttrRefToName(
          ldhses, &ip->aref, cdh_mName_volumeStrict, &anamep, &size);
      if (EVEN(sts))
        return sts;

      strncpy(aname, anamep, sizeof(aname));
      if ((s = strrchr(aname, '.')) && streq(s, ".ActualValue")) {
        *s = 0;

        sts = ldh_NameToAttrRef(ldhses, aname, &aref);
        if (EVEN(sts))
          return sts;

        sts = ldh_GetAttrRefTid(ldhses, &aref, &cid);
        if (EVEN(sts))
          return sts;

        switch (cid) {
        case pwr_cClass_Ao:
        case pwr_cClass_Do:
        case pwr_cClass_Io:
        case pwr_cClass_Av:
        case pwr_cClass_Dv:
        case pwr_cClass_Iv:
          // Write InitValue instead of ActualValue
          strcat(aname, ".InitialValue");
          sts = ldh_NameToAttrRef(ldhses, aname, &aref);
          if (EVEN(sts))
            return sts;

          sts = ldh_WriteAttribute(ldhses, &aref, ip->valuep, ip->size);

          break;
        default:
          sts = ldh_WriteAttribute(ldhses, &ip->aref, ip->valuep, ip->size);
        }
      } else
        sts = ldh_WriteAttribute(ldhses, &ip->aref, ip->valuep, ip->size);

      if (ODD(sts)) {
        memcpy(ip->value2p, ip->valuep, ip->size);
        item->update();
      } else
        printf("** ldh_WriteAttribute error, %s\n", anamep);
    }
  }
  return LDH__SUCCESS;
}

pwr_tStatus WbBckWNav::filter(char* hierarchy)
{
  pwr_tStatus sts;
  pwr_tOid oid;
  pwr_tOid p;
  int found;

  sts = ldh_NameToObjid(ldhses, &oid, hierarchy);
  if (EVEN(sts))
    return sts;

  for (bck_sItem* ip = list->first(); ip; ip = list->next(ip)) {
    sts = 1;
    found = 0;
    for (p = ip->aref.Objid; ODD(sts); sts = ldh_GetParent(ldhses, p, &p)) {
      if (cdh_ObjidIsEqual(p, oid)) {
        found = 1;
        break;
      }
    }
    ip->hide = !found;
  }

  clear();
  show();

  return LDH__SUCCESS;
}

void WbBckWNav::check_all()
{
  int sts;
  brow_tNode node;

  for (sts = brow_GetFirst(brow->ctx, &node); ODD(sts);
       sts = brow_GetNext(brow->ctx, node, &node))
    brow_SetRadiobutton(node, 0, 1);
}

void WbBckWNav::check_clear()
{
  int sts;
  brow_tNode node;

  for (sts = brow_GetFirst(brow->ctx, &node); ODD(sts);
       sts = brow_GetNext(brow->ctx, node, &node))
    brow_SetRadiobutton(node, 0, 0);
}

ItemBck::ItemBck(WbBckWNav* item_bckwnav, bck_sItem* item_bck_item,
    brow_tNode dest, flow_eDest dest_code)
    : bckwnav(item_bckwnav), bck_item(item_bck_item)
{
  char str[1024];
  char* anamep;
  int size;
  pwr_tStatus sts;

  type = bckwitem_eItemType_Bck;

  sts = ldh_AttrRefToName(
      bckwnav->ldhses, &bck_item->aref, cdh_mName_volumeStrict, &anamep, &size);
  if (EVEN(sts))
    return;

  sts = ldh_GetAttrRefType(bckwnav->ldhses, &bck_item->aref, &atype);
  if (EVEN(sts))
    return;

  sts = cdh_AttrValueToString(atype, bck_item->valuep, str, sizeof(str));
  if (EVEN(sts))
    strcpy(str, "-");

  if (bckwnav->editmode && bckwnav->list->type() == bck_eType_WbDiff)
    brow_CreateNode(bckwnav->brow->ctx, (char*)"Bck", bckwnav->brow->nc_wbbck,
        dest, dest_code, (void*)this, 1, &node);
  else
    brow_CreateNode(bckwnav->brow->ctx, (char*)"Bck", bckwnav->brow->nc_bck,
        dest, dest_code, (void*)this, 1, &node);

  int annot = 0;
  brow_SetAnnotation(node, annot++, anamep, strlen(anamep));
  brow_SetAnnotation(node, annot++, str, strlen(str));

  if (bck_item->value2p) {
    sts = cdh_AttrValueToString(atype, bck_item->value2p, str, sizeof(str));
    if (EVEN(sts))
      strcpy(str, "-");

    brow_SetAnnotation(node, annot++, str, strlen(str));
  }

  brow_SetAnnotPixmap(node, 0, bckwnav->brow->pixmap_save);
}

ItemBck::~ItemBck()
{
}

void ItemBck::update()
{
  char str[1024];
  pwr_tStatus sts;

  sts = cdh_AttrValueToString(atype, bck_item->valuep, str, sizeof(str));
  if (EVEN(sts))
    strcpy(str, "-");

  brow_SetAnnotation(node, 1, str, strlen(str));

  if (bck_item->value2p) {
    sts = cdh_AttrValueToString(atype, bck_item->value2p, str, sizeof(str));
    if (EVEN(sts))
      strcpy(str, "-");

    brow_SetAnnotation(node, 2, str, strlen(str));
  }
}

void ItemBck::set(int value)
{
  brow_SetRadiobutton(node, 0, value);
}
