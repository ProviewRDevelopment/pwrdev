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

#include <iostream>

#include "co_dcli.h"
#include "co_string.h"

#include "glow_growwindow.h"
#include "glow_grownode.h"
#include "glow_draw.h"
#include "glow_growscrollbar.h"
#include "glow_exportscript.h"
#include "glow_msg.h"

GrowWindow::GrowWindow(GrowCtx* glow_ctx, const char* name, double x, double y,
    double w, double h, glow_eDrawType border_d_type, int line_w,
    glow_mDisplayLevel display_lev, int nodraw)
    : GrowRect(glow_ctx, name, x, y, w, h, border_d_type, line_w, 0,
          display_lev, 0, 1, 0, glow_eDrawType_Line, nodraw),
      user_data(0), window_ctx(0), vertical_scrollbar(0),
      horizontal_scrollbar(0), scrollbar_width(0.5), v_scrollbar(0),
      h_scrollbar(0), v_value(0), h_value(0), wctx_x0(0), wctx_x1(0),
      wctx_y0(0), wctx_y1(0), scrollbar_color(glow_eDrawType_LightGray),
      scrollbar_bg_color(glow_eDrawType_MediumGray), window_scale(1),
      y_low_offs(0), input_focus(0)
{
  strcpy(file_name, "");
  strcpy(input_file_name, "");
  strcpy(owner, "");

  if (!nodraw)
    draw();
}

GrowWindow::~GrowWindow()
{
  if (!ctx->nodraw)
    draw();

  if (window_ctx) {
    if (window_ctx->trace_started)
      window_ctx->trace_close();
    delete window_ctx;
  }
  if (v_scrollbar)
    delete v_scrollbar;
  if (h_scrollbar)
    delete h_scrollbar;
}

void GrowWindow::save(std::ofstream& fp, glow_eSaveMode mode)
{
  fp << int(glow_eSave_GrowWindow) << '\n';
  fp << int(glow_eSave_GrowWindow_file_name) << FSPACE << file_name << '\n';
  fp << int(glow_eSave_GrowWindow_scrollbar_width) << FSPACE << scrollbar_width
     << '\n';
  fp << int(glow_eSave_GrowWindow_scrollbar_color) << FSPACE << scrollbar_color
     << '\n';
  fp << int(glow_eSave_GrowWindow_scrollbar_bg_color) << FSPACE
     << scrollbar_bg_color << '\n';
  fp << int(glow_eSave_GrowWindow_vertical_scrollbar) << FSPACE
     << vertical_scrollbar << '\n';
  fp << int(glow_eSave_GrowWindow_horizontal_scrollbar) << FSPACE
     << horizontal_scrollbar << '\n';
  fp << int(glow_eSave_GrowWindow_window_scale) << FSPACE << window_scale
     << '\n';
  fp << int(glow_eSave_GrowWindow_owner) << FSPACE << owner << '\n';
  fp << int(glow_eSave_GrowWindow_rect_part) << '\n';
  GrowRect::save(fp, mode);
  if (user_data && ctx->userdata_save_callback) {
    fp << int(glow_eSave_GrowWindow_userdata_cb) << '\n';
    (ctx->userdata_save_callback)(&fp, this, glow_eUserdataCbType_Node);
  }
  fp << int(glow_eSave_End) << '\n';
}

void GrowWindow::open(std::ifstream& fp)
{
  int type = 0;
  int end_found = 0;
  char dummy[40];
  int tmp;

  for (;;) {
    if (!fp.good()) {
      fp.clear();
      fp.getline(dummy, sizeof(dummy));
      printf("** Read error GrowWindow: \"%d %s\"\n", type, dummy);
    }

    fp >> type;
    switch (type) {
    case glow_eSave_GrowWindow:
      break;
    case glow_eSave_GrowWindow_file_name:
      fp >> file_name;
      break;
    case glow_eSave_GrowWindow_scrollbar_width:
      fp >> scrollbar_width;
      break;
    case glow_eSave_GrowWindow_scrollbar_color:
      fp >> tmp;
      scrollbar_color = (glow_eDrawType)tmp;
      break;
    case glow_eSave_GrowWindow_scrollbar_bg_color:
      fp >> tmp;
      scrollbar_bg_color = (glow_eDrawType)tmp;
      break;
    case glow_eSave_GrowWindow_vertical_scrollbar:
      fp >> vertical_scrollbar;
      break;
    case glow_eSave_GrowWindow_horizontal_scrollbar:
      fp >> horizontal_scrollbar;
      break;
    case glow_eSave_GrowWindow_window_scale:
      fp >> window_scale;
      break;
    case glow_eSave_GrowWindow_owner:
      fp.get();
      fp.getline(owner, sizeof(owner));
      break;
    case glow_eSave_GrowWindow_rect_part:
      GrowRect::open(fp);
      break;
    case glow_eSave_GrowWindow_userdata_cb:
      if (ctx->userdata_open_callback)
        (ctx->userdata_open_callback)(&fp, this, glow_eUserdataCbType_Node);
      break;
    case glow_eSave_End:
      end_found = 1;
      break;
    default:
      std::cout << "GrowWindow:open syntax error\n";
      fp.getline(dummy, sizeof(dummy));
    }
    if (end_found)
      break;
  }

  if (!streq(file_name, ""))
    new_ctx();
  configure_scrollbars();
}

void GrowWindow::draw(GlowWind* w, int ll_x, int ll_y, int ur_x, int ur_y)
{
  int tmp;

  if (ll_x > ur_x) {
    /* Shift */
    tmp = ll_x;
    ll_x = ur_x;
    ur_x = tmp;
  }
  if (ll_y > ur_y) {
    /* Shift */
    tmp = ll_y;
    ll_y = ur_y;
    ur_y = tmp;
  }

  if (x_right * w->zoom_factor_x - w->offset_x >= ll_x
      && x_left * w->zoom_factor_x - w->offset_x <= ur_x
      && y_high * w->zoom_factor_y - w->offset_y >= ll_y
      && y_low * w->zoom_factor_y - w->offset_y <= ur_y) {
    draw(w, (GlowTransform*)NULL, highlight, hot, NULL, NULL, NULL);
  }
}

void GrowWindow::draw(GlowWind* w, int* ll_x, int* ll_y, int* ur_x, int* ur_y)
{
  int tmp;
  int obj_ur_x = int(x_right * w->zoom_factor_x) - w->offset_x;
  int obj_ll_x = int(x_left * w->zoom_factor_x) - w->offset_x;
  int obj_ur_y = int(y_high * w->zoom_factor_y) - w->offset_y;
  int obj_ll_y = int(y_low * w->zoom_factor_y) - w->offset_y;

  if (*ll_x > *ur_x) {
    /* Shift */
    tmp = *ll_x;
    *ll_x = *ur_x;
    *ur_x = tmp;
  }
  if (*ll_y > *ur_y) {
    /* Shift */
    tmp = *ll_y;
    *ll_y = *ur_y;
    *ur_y = tmp;
  }

  if (obj_ur_x >= *ll_x && obj_ll_x <= *ur_x && obj_ur_y >= *ll_y
      && obj_ll_y <= *ur_y) {
    draw(w, (GlowTransform*)NULL, highlight, hot, NULL, NULL, NULL);

    // Increase the redraw area
    if (obj_ur_x > *ur_x)
      *ur_x = obj_ur_x;
    if (obj_ur_y > *ur_y)
      *ur_y = obj_ur_y;
    if (obj_ll_x < *ll_x)
      *ll_x = obj_ll_x;
    if (obj_ll_y < *ll_y)
      *ll_y = obj_ll_y;
  }
}

void GrowWindow::set_highlight(int on)
{
  highlight = on;
  draw();
}

void GrowWindow::draw(GlowWind* w, GlowTransform* t, int highlight, int hot,
    void* node, void* colornode, void *transpnode)
{
  if (w == &ctx->navw) {
    draw_brief(w, t, highlight, hot, node, colornode);
    return;
  }

  if (!(display_level & ctx->display_level))
    return;
  int idx;
  glow_eDrawType drawtype;

  idx = int(w->zoom_factor_y / w->base_zoom_factor * line_width - 1);
  idx += hot;
  idx = MAX(0, idx);
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);
  int ll_x, ll_y, ur_x, ur_y;
  double dx1, dy1, dx2, dy2;

  if (!t) {
    dx1 = trf.x(ll.x, ll.y);
    dy1 = trf.y(ll.x, ll.y);
    dx2 = trf.x(ur.x, ur.y);
    dy2 = trf.y(ur.x, ur.y);
  } else {
    dx1 = trf.x(t, ll.x, ll.y);
    dy1 = trf.y(t, ll.x, ll.y);
    dx2 = trf.x(t, ur.x, ur.y);
    dy2 = trf.y(t, ur.x, ur.y);
  }
  dx1 = MIN(dx1, dx2);
  dx2 = MAX(dx1, dx2);
  dy1 = MIN(dy1, dy2);
  dy2 = MAX(dy1, dy2);

  if (v_scrollbar) {
    if (!h_scrollbar)
      v_scrollbar->set_position(dx2 - scrollbar_width, dy1 + y_low_offs,
          scrollbar_width, dy2 - (dy1 + y_low_offs));
    else
      v_scrollbar->set_position(dx2 - scrollbar_width, dy1 + y_low_offs,
          scrollbar_width, dy2 - (dy1 + y_low_offs) - scrollbar_width);
    v_scrollbar->draw(w, 0, 0, 0, 0, 0, 0);
  }
  if (h_scrollbar) {
    if (!v_scrollbar)
      h_scrollbar->set_position(
          dx1, dy2 - scrollbar_width, dx2 - dx1, scrollbar_width);
    else
      h_scrollbar->set_position(dx1, dy2 - scrollbar_width,
          dx2 - dx1 - scrollbar_width, scrollbar_width);
    h_scrollbar->draw(w, 0, 0, 0, 0, 0, 0);
  }
  ll_x = int(dx1 * w->zoom_factor_x) - w->offset_x;
  ll_y = int((dy1 + y_low_offs) * w->zoom_factor_y) - w->offset_y;

  if (window_ctx) {
    ur_x = int((dx2 - vertical_scrollbar * scrollbar_width) * w->zoom_factor_x)
        - w->offset_x;
    ur_y
        = int((dy2 - horizontal_scrollbar * scrollbar_width) * w->zoom_factor_y)
        - w->offset_y;

    window_ctx->mw.window_width = int((x_right - x_left) * w->zoom_factor_x);
    window_ctx->mw.window_height = int((y_high - y_low) * w->zoom_factor_y);
    window_ctx->mw.subwindow_x = int(x_left * w->zoom_factor_x - w->offset_x);
    window_ctx->mw.subwindow_y = int(y_low * w->zoom_factor_y - w->offset_y);
    window_ctx->mw.offset_x = -ll_x + int(h_value * w->zoom_factor_x);
    window_ctx->mw.offset_y = -ll_y + int(v_value * w->zoom_factor_y);
    window_ctx->mw.zoom_factor_x
        = window_ctx->mw.subwindow_scale * w->zoom_factor_x;
    window_ctx->mw.zoom_factor_y
        = window_ctx->mw.subwindow_scale * w->zoom_factor_y;

    ctx->gdraw->push_customcolors(window_ctx->customcolors);
#if 0
    if (fill)
      ctx->gdraw->fill_rect(
          w, ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, fill_drawtype);
#endif
    ctx->gdraw->push_background(fill_drawtype);
    window_ctx->draw_invalidated(&window_ctx->mw, ll_x, ll_y, ur_x, ur_y);
    ctx->gdraw->pop_background();
    ctx->gdraw->pop_customcolors();
  }

  ur_x = int(dx2 * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
  ur_y = int(dy2 * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;

  drawtype = ctx->get_drawtype(draw_type, glow_eDrawType_LineHighlight,
      highlight, (GrowNode*)colornode, 0);
  ctx->gdraw->rect(w, ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, drawtype, idx, 0);
}

void GrowWindow::draw_brief(GlowWind* w, GlowTransform* t, int highlight,
    int hot, void* node, void* colornode)
{
  if (!(display_level & ctx->display_level))
    return;
  glow_eDrawType drawtype;
  int idx;
  idx = int(w->zoom_factor_y / w->base_zoom_factor * line_width - 1);

  idx = MAX(0, idx);
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);
  int x1, y1, x2, y2, ll_x, ll_y, ur_x, ur_y;

  if (!t) {
    x1 = int(trf.x(ll.x, ll.y) * w->zoom_factor_x) - w->offset_x;
    y1 = int(trf.y(ll.x, ll.y) * w->zoom_factor_y) - w->offset_y;
    x2 = int(trf.x(ur.x, ur.y) * w->zoom_factor_x) - w->offset_x;
    y2 = int(trf.y(ur.x, ur.y) * w->zoom_factor_y) - w->offset_y;
  } else {
    x1 = int(trf.x(t, ll.x, ll.y) * w->zoom_factor_x) - w->offset_x;
    y1 = int(trf.y(t, ll.x, ll.y) * w->zoom_factor_y) - w->offset_y;
    x2 = int(trf.x(t, ur.x, ur.y) * w->zoom_factor_x) - w->offset_x;
    y2 = int(trf.y(t, ur.x, ur.y) * w->zoom_factor_y) - w->offset_y;
  }
  ll_x = MIN(x1, x2);
  ur_x = MAX(x1, x2);
  ll_y = MIN(y1, y2);
  ur_y = MAX(y1, y2);

  if (window_ctx && fill)
    ctx->gdraw->fill_rect(
        w, ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, fill_drawtype);

  drawtype = ctx->get_drawtype(draw_type, glow_eDrawType_LineHighlight,
      highlight, (GrowNode*)colornode, 0);
  ctx->gdraw->rect(w, ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, drawtype, idx, 0);
}

int GrowWindow::trace_scan()
{
  int sts;

  if (trace.p && ctx->trace_scan_func) {
    sts = ctx->trace_scan_func((void*)this, trace.p);
    if (sts == GLOW__TERMINATED || sts == GLOW__SUBTERMINATED
        || sts == GLOW__SWAPTERMINATED)
      return sts;
  }

  if (window_ctx) {
    int ur_x = int((x_right - vertical_scrollbar * scrollbar_width)
                   * ctx->mw.zoom_factor_x)
        - ctx->mw.offset_x;
    int ll_x = int(x_left * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
    int ur_y = int((y_high - horizontal_scrollbar * scrollbar_width)
                   * ctx->mw.zoom_factor_y)
        - ctx->mw.offset_y;
    int ll_y
        = int((y_low + y_low_offs) * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;

    ctx->gdraw->set_clip_rectangle(&ctx->mw, ll_x, ll_y, ur_x, ur_y);

    if (ctx->trace_ctrl_func)
      (ctx->trace_ctrl_func)(glow_eTraceCtrl_CtxPop, window_ctx);

    sts = window_ctx->trace_scan();
    if (sts == GLOW__TERMINATED)
      return sts;
    else if (sts == GLOW__SUBTERMINATED || sts == GLOW__SWAPTERMINATED) {
      if (ctx->trace_ctrl_func)
        (ctx->trace_ctrl_func)(glow_eTraceCtrl_CtxPush, ctx);
      ctx->gdraw->reset_clip_rectangle(&ctx->mw);
      return sts;
    }
    if (ctx->trace_ctrl_func)
      (ctx->trace_ctrl_func)(glow_eTraceCtrl_CtxPush, window_ctx);

    ctx->gdraw->reset_clip_rectangle(&ctx->mw);
  }
  return 1;
}

int GrowWindow::trace_init()
{
  int sts = 1;

  // sts = ctx->trace_connect_func( (void *) this, &trace);

  if (window_ctx) {
    double dx1, dy1, dx2, dy2;

    ctx->set_nodraw();
    configure_scrollbars();
    ctx->reset_nodraw();

    dx1 = trf.x(ll.x, ll.y);
    dy1 = trf.y(ll.x, ll.y);
    dx2 = trf.x(ur.x, ur.y);
    dy2 = trf.y(ur.x, ur.y);
    dx1 = MIN(dx1, dx2);
    dx2 = MAX(dx1, dx2);
    dy1 = MIN(dy1, dy2);
    dy2 = MAX(dy1, dy2);

    int ll_x = int(dx1 * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
    int ll_y
        = int((dy1 + y_low_offs) * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;

    window_ctx->mw.offset_x = -ll_x + int(h_value * ctx->mw.zoom_factor_x);
    window_ctx->mw.offset_y = -ll_y + int(v_value * ctx->mw.zoom_factor_y);

    memcpy(window_ctx->event_callback, ctx->event_callback,
        sizeof(ctx->event_callback));
    window_ctx->event_move_node = ctx->event_move_node;
    window_ctx->trace_init(ctx->trace_connect_func, ctx->trace_disconnect_func,
        ctx->trace_scan_func, ctx->trace_ctrl_func);
  }

  return sts;
}

void GrowWindow::trace_close()
{
  if (trace.p)
    ctx->trace_disconnect_func((void*)this);

  if (window_ctx)
    window_ctx->trace_close();
}

void GrowWindow::draw()
{
  ctx->draw(&ctx->mw,
      x_left * ctx->mw.zoom_factor_x - ctx->mw.offset_x - DRAW_MP,
      y_low * ctx->mw.zoom_factor_y - ctx->mw.offset_y - DRAW_MP,
      x_right * ctx->mw.zoom_factor_x - ctx->mw.offset_x + DRAW_MP,
      y_high * ctx->mw.zoom_factor_y - ctx->mw.offset_y + DRAW_MP);
  ctx->draw(&ctx->navw, x_left * ctx->navw.zoom_factor_x - ctx->mw.offset_x - 1,
      y_low * ctx->navw.zoom_factor_y - ctx->mw.offset_y - 1,
      x_right * ctx->navw.zoom_factor_x - ctx->mw.offset_x + 1,
      y_high * ctx->navw.zoom_factor_y - ctx->mw.offset_y + 1);
}

void GrowWindow::align(double x, double y, glow_eAlignDirection direction)
{
  double dx, dy;

  ctx->set_defered_redraw();
  draw();
  switch (direction) {
  case glow_eAlignDirection_CenterVert:
    dx = x - (x_right + x_left) / 2;
    dy = 0;
    break;
  case glow_eAlignDirection_CenterHoriz:
    dx = 0;
    dy = y - (y_high + y_low) / 2;
    break;
  case glow_eAlignDirection_CenterCenter:
    dx = x - (x_right + x_left) / 2;
    dy = y - (y_high + y_low) / 2;
    break;
  case glow_eAlignDirection_Right:
    dx = x - x_right;
    dy = 0;
    break;
  case glow_eAlignDirection_Left:
    dx = x - x_left;
    dy = 0;
    break;
  case glow_eAlignDirection_Up:
    dx = 0;
    dy = y - y_high;
    break;
  case glow_eAlignDirection_Down:
    dx = 0;
    dy = y - y_low;
    break;
  }
  trf.move(dx, dy);
  x_right += dx;
  x_left += dx;
  y_high += dy;
  y_low += dy;

  draw();
  ctx->redraw_defered();
}

void GrowWindow::export_javabean(GlowTransform* t, void* node,
    glow_eExportPass pass, int* shape_cnt, int node_cnt, int in_nc,
    std::ofstream& fp)
{
  double x1, y1, x2, y2, ll_x, ll_y, ur_x, ur_y;

  if (!t) {
    x1 = trf.x(ll.x, ll.y) * ctx->mw.zoom_factor_x - ctx->mw.offset_x;
    y1 = trf.y(ll.x, ll.y) * ctx->mw.zoom_factor_y - ctx->mw.offset_y;
    x2 = trf.x(ur.x, ur.y) * ctx->mw.zoom_factor_x - ctx->mw.offset_x;
    y2 = trf.y(ur.x, ur.y) * ctx->mw.zoom_factor_y - ctx->mw.offset_y;
  } else {
    x1 = trf.x(t, ll.x, ll.y) * ctx->mw.zoom_factor_x - ctx->mw.offset_x;
    y1 = trf.y(t, ll.x, ll.y) * ctx->mw.zoom_factor_y - ctx->mw.offset_y;
    x2 = trf.x(t, ur.x, ur.y) * ctx->mw.zoom_factor_x - ctx->mw.offset_x;
    y2 = trf.y(t, ur.x, ur.y) * ctx->mw.zoom_factor_y - ctx->mw.offset_y;
  }

  ll_x = MIN(x1, x2);
  ur_x = MAX(x1, x2);
  ll_y = MIN(y1, y2);
  ur_y = MAX(y1, y2);

  ctx->export_jbean->window(ll_x, ll_y, ur_x, ur_y, file_name,
      vertical_scrollbar, horizontal_scrollbar, owner, pass, shape_cnt,
      node_cnt, fp);
}

void GrowWindow::convert(glow_eConvert version)
{
  switch (version) {
  case glow_eConvert_V34: {
    // Conversion of colors
  }
  }
}

int GrowWindow::event_handler(
    GlowWind* w, glow_eEvent event, int x, int y, double fx, double fy)
{
  int sts, v_sts, h_sts;

  switch (event) {
  case glow_eEvent_Key_Right:
  case glow_eEvent_Key_Left:
  case glow_eEvent_Key_Up:
  case glow_eEvent_Key_Down:
  case glow_eEvent_Key_BackSpace:
  case glow_eEvent_Key_Return:
  case glow_eEvent_Key_Tab:
  case glow_eEvent_Key_ShiftTab:
  case glow_eEvent_Key_Escape:
  case glow_eEvent_Key_Ascii:
    if (input_focus) {
      window_ctx->event_handler(event, 0, 0, x, 0);
      if (!window_ctx->inputfocus_object) {
        ctx->register_inputfocus(this, 0);
        input_focus = 0;
      }
      return 1;
    } else
      return 0;
  case glow_eEvent_ScrollUp:
    if (!ctx->trace_started)
      return 0;
    if (v_scrollbar) {
      double rx, ry;

      // Convert koordinates to local koordinates
      trf.reverse(fx, fy, &rx, &ry);
      sts = local_event_handler(event, rx, ry);
      if (sts) {
        v_value -= (wctx_y1 - wctx_y0) * window_scale / 50;
        if (v_value < wctx_y0 * window_scale)
          v_value = wctx_y0 * window_scale;
        draw();
        v_scrollbar->set_value(v_value, y_high - (y_low + y_low_offs)
                - scrollbar_width * horizontal_scrollbar);
        return 1;
      } else
        return 0;
    }
    break;
  case glow_eEvent_ScrollDown:
    if (!ctx->trace_started)
      return 0;
    if (v_scrollbar) {
      double rx, ry;

      // Convert koordinates to local koordinates
      trf.reverse(fx, fy, &rx, &ry);
      sts = local_event_handler(event, rx, ry);
      if (sts) {
        v_value += (wctx_y1 - wctx_y0) * window_scale / 50;
        if (v_value > wctx_y1 * window_scale
                - ((y_high - (y_low + y_low_offs)
                      - scrollbar_width * horizontal_scrollbar)))
          v_value = wctx_y1 * window_scale
              - ((y_high - (y_low + y_low_offs)
                    - scrollbar_width * horizontal_scrollbar));
        draw();
        v_scrollbar->set_value(v_value, y_high - (y_low + y_low_offs)
                - scrollbar_width * horizontal_scrollbar);
        return 1;
      } else
        return 0;
    }
    break;
  default:;
  }

  v_sts = h_sts = 0;
  if (v_scrollbar)
    v_sts = v_scrollbar->event_handler(w, event, x, y, fx, fy);
  if (h_scrollbar)
    h_sts = h_scrollbar->event_handler(w, event, x, y, fx, fy);
  if (v_sts || h_sts) {
    if (event == ctx->event_move_node)
      return 0;
    return 1;
  }

  sts = GrowRect::event_handler(w, event, x, y, fx, fy);
  if (ctx->trace_started && ctx->callback_object == this) {
    // Disable event callback for this object, let the window ctx handle it
    ctx->callback_object = 0;
    ctx->callback_object_type = glow_eObjectType_NoObject;
  }
  if (!ctx->trace_started) {
    if (event == glow_eEvent_ButtonMotion)
      return 0;
  }

  if (ctx->hot_mode == glow_eHotMode_TraceAction) {
    double rx, ry;

    // Convert koordinates to local koordinates
    trf.reverse(fx, fy, &rx, &ry);
    sts = local_event_handler(event, rx, ry);
  }

  if (window_ctx && sts) {
    if (!ctx->trace_started)
      return sts;

    int ur_x = int((x_right - vertical_scrollbar * scrollbar_width)
                   * ctx->mw.zoom_factor_x)
        - ctx->mw.offset_x;
    int ll_x = int(x_left * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
    int ur_y = int((y_high - horizontal_scrollbar * scrollbar_width)
                   * ctx->mw.zoom_factor_y)
        - ctx->mw.offset_y;
    int ll_y
        = int((y_low + y_low_offs) * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;

    ctx->gdraw->push_customcolors(window_ctx->customcolors);
    ctx->gdraw->set_clip_rectangle(&ctx->mw, ll_x, ll_y, ur_x, ur_y);

    // Set callback to redraw the background
    window_ctx->redraw_callback = redraw_cb;
    window_ctx->redraw_data = (void*)this;

    sts = window_ctx->event_handler(event, x, y, 0, 0);
    if (sts == GLOW__TERMINATED)
      return sts;
    else if (sts == GLOW__SUBTERMINATED || sts == GLOW__SWAPTERMINATED) {
      // ctx->gdraw->pop_customcolors();
      ctx->gdraw->reset_clip_rectangle(&ctx->mw);
      return 1;
    }

    window_ctx->redraw_callback = 0;
    window_ctx->redraw_data = 0;
    ctx->gdraw->reset_clip_rectangle(&ctx->mw);
    ctx->gdraw->pop_customcolors();

    if (window_ctx->inputfocus_object && !input_focus) {
      ctx->register_inputfocus(this, 1);
      input_focus = 1;
    } else if (!window_ctx->inputfocus_object && input_focus) {
      ctx->register_inputfocus(this, 0);
      input_focus = 0;
    }

    // if ( window_ctx->callback_object)
    //  ctx->register_callback_object( window_ctx->callback_object_type,
    //  window_ctx->callback_object);
  }
  return sts;
}

void GrowWindow::set_input_focus(int focus, glow_eEvent event)
{
  if (focus && !input_focus) {
    input_focus = 1;
    ctx->register_inputfocus(this, 1);

    if (event == glow_eEvent_InputFocusInit)
      window_ctx->inputfocus_init_event();
  } else if (!focus && input_focus) {
    if (window_ctx->inputfocus_object)
      window_ctx->inputfocus_object->set_input_focus(0, event);
    input_focus = 0;
    ctx->register_inputfocus(this, 0);
  }
}

int GrowWindow::update_attributes()
{
  int sts = 0;

  if (!streq(input_file_name, file_name)
      || (window_ctx && !streq(window_ctx->owner, owner))) {
    int ur_x = int(x_right * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
    int ll_x = int(x_left * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
    int ur_y = int(y_high * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;
    int ll_y = int(y_low * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;
    ctx->gdraw->set_clip_rectangle(&ctx->mw, ll_x, ll_y, ur_x, ur_y);

    if (window_ctx) {
      if (window_ctx->trace_started)
        window_ctx->trace_close();
      delete window_ctx;
      fill_drawtype = original_fill_drawtype = glow_eDrawType_Inherit;
      fill = 0;
    }
    strcpy(file_name, input_file_name);
    new_ctx(true);
    sts = 1;

    ctx->gdraw->reset_clip_rectangle(&ctx->mw);
  } else if (window_ctx) {
    window_ctx->mw.subwindow_scale = window_scale;
    window_ctx->mw.zoom_factor_x = window_ctx->mw.zoom_factor_y
        = window_ctx->mw.subwindow_scale * ctx->mw.zoom_factor_x;
    window_ctx->a.zoom();
  }

  configure_scrollbars();

  if (v_scrollbar)
    v_scrollbar->set_colors(scrollbar_bg_color, scrollbar_color);
  if (h_scrollbar)
    h_scrollbar->set_colors(scrollbar_bg_color, scrollbar_color);
  return sts;
}

void GrowWindow::set_transform_from_stored(GlowTransform* t)
{
  GrowRect::set_transform_from_stored(t);
  configure_scrollbars();
}

void GrowWindow::configure_scrollbars()
{
  double x0, y0, width, height;

  if (vertical_scrollbar && !v_scrollbar) {
    x0 = x_right - scrollbar_width;
    y0 = y_low + y_low_offs;
    width = scrollbar_width;
    if (horizontal_scrollbar)
      height = y_high - (y_low + y_low_offs) - scrollbar_width;
    else
      height = y_high - (y_low + y_low_offs);

    v_scrollbar = new GrowScrollBar(ctx, "vScrollbar", x0, y0, width, height,
        glow_eDir_Vertical, glow_eDrawType_Line, 1, display_level,
        scrollbar_bg_color, scrollbar_color, 1);
    v_scrollbar->register_value_changed_cb((void*)this, &v_value_changed_cb);
    if (window_ctx) {
      v_scrollbar->set_value(wctx_y0 * window_ctx->mw.subwindow_scale, y_high
              - (y_low + y_low_offs) - scrollbar_width * horizontal_scrollbar);
      v_scrollbar->set_range(
          wctx_y0 * window_ctx->mw.subwindow_scale, wctx_y1 * window_scale);
      v_value = wctx_y0 * window_ctx->mw.subwindow_scale;
    }
    v_scrollbar->set_shadow(shadow);
  } else if (!vertical_scrollbar && v_scrollbar) {
    delete v_scrollbar;
    v_scrollbar = 0;
    if (window_ctx)
      v_value = wctx_y0 * window_ctx->mw.subwindow_scale;
  } else if (v_scrollbar) {
    // Reconfigure range and length
    if (window_ctx) {
      v_scrollbar->set_value(wctx_y0 * window_ctx->mw.subwindow_scale, y_high
              - (y_low + y_low_offs) - scrollbar_width * horizontal_scrollbar);
      v_value = wctx_y0 * window_ctx->mw.subwindow_scale;
      v_scrollbar->set_range(wctx_y0 * window_ctx->mw.subwindow_scale,
          wctx_y1 * window_ctx->mw.subwindow_scale);
    }
    v_scrollbar->set_shadow(shadow);
  } else {
    if (window_ctx)
      v_value = wctx_y0 * window_ctx->mw.subwindow_scale;
  }

  if (horizontal_scrollbar && !h_scrollbar) {
    x0 = x_left;
    y0 = y_high - scrollbar_width;
    height = scrollbar_width;
    if (vertical_scrollbar)
      width = x_right - x_left - scrollbar_width;
    else
      width = x_right - x_left;

    h_scrollbar = new GrowScrollBar(ctx, "vScrollbar", x0, y0, width, height,
        glow_eDir_Horizontal, glow_eDrawType_Line, 1, display_level,
        scrollbar_bg_color, scrollbar_color, 1);
    h_scrollbar->register_value_changed_cb((void*)this, &h_value_changed_cb);
    if (window_ctx) {
      h_scrollbar->set_value(wctx_x0 * window_ctx->mw.subwindow_scale,
          x_right - x_left - scrollbar_width * vertical_scrollbar);
      h_scrollbar->set_range(wctx_x0 * window_ctx->mw.subwindow_scale,
          wctx_x1 * window_ctx->mw.subwindow_scale);
      h_value = wctx_x0 * window_ctx->mw.subwindow_scale;
    }
    h_scrollbar->set_shadow(shadow);
  } else if (!horizontal_scrollbar && h_scrollbar) {
    delete h_scrollbar;
    h_scrollbar = 0;
    if (window_ctx)
      h_value = wctx_x0 * window_ctx->mw.subwindow_scale;
  } else if (h_scrollbar) {
    // Reconfigure lenght and range
    if (window_ctx) {
      h_scrollbar->set_value(wctx_x0 * window_ctx->mw.subwindow_scale,
          x_right - x_left - scrollbar_width * vertical_scrollbar);
      h_value = wctx_x0 * window_ctx->mw.subwindow_scale;
      h_scrollbar->set_range(wctx_x0 * window_ctx->mw.subwindow_scale,
          wctx_x1 * window_ctx->mw.subwindow_scale);
    }
    h_scrollbar->set_shadow(shadow);
  } else {
    if (window_ctx)
      h_value = wctx_x0 * window_ctx->mw.subwindow_scale;
  }
}

void GrowWindow::v_value_changed_cb(void* o, double value)
{
  GrowWindow* gw = (GrowWindow*)o;

  gw->v_value = value;
  gw->draw();
}

void GrowWindow::h_value_changed_cb(void* o, double value)
{
  GrowWindow* gw = (GrowWindow*)o;

  gw->h_value = value;
  gw->draw();
}

void GrowWindow::new_ctx(bool is_updating_attributes)
{
  char fname[200];
  int sts;
  char* s;
  bool copied;
  int no_file = streq(file_name, "_no_") ? 1 : 0; // No initial graph

  for (int i = 0; i < ctx->path_cnt; i++) {

    if (strchr(file_name, '/') == 0) {
      if (file_name[0] == '@') {
	strcpy(fname, "@");
	strcat(fname, ctx->path[i]);
	strcat(fname, &file_name[1]);
      }
      else {
	strcpy(fname, ctx->path[i]);
	strcat(fname, file_name);
      }
    } else
      strcpy(fname, file_name);
    if (!strchr(fname, '.')) {
      if (fname[0] == '@')
	strcat(fname, ".ge_com");
      else
	strcat(fname, ".pwg");
    }
    dcli_translate_filename(fname, fname);
    if (check_file(fname))
      break;
  }

  window_ctx
      = new GrowCtx("WindowComponent", ctx->mw.zoom_factor_x * window_scale);
  window_ctx->gdraw = ctx->gdraw;
  window_ctx->is_subwindow = 1;
  window_ctx->mw.window = ctx->mw.window;
  window_ctx->navw.window = ctx->navw.window;
  window_ctx->userdata_save_callback = ctx->userdata_save_callback;
  window_ctx->userdata_open_callback = ctx->userdata_open_callback;
  window_ctx->userdata_copy_callback = ctx->userdata_copy_callback;
  window_ctx->user_data = ctx->user_data;
  window_ctx->hot_mode = ctx->hot_mode;
  window_ctx->path_cnt = ctx->path_cnt;
  memcpy(window_ctx->path, ctx->path, sizeof(window_ctx->path));
  window_ctx->default_hot_mode = ctx->default_hot_mode;
  window_ctx->is_component = 1;
  memcpy(window_ctx->event_callback, ctx->event_callback,
      sizeof(ctx->event_callback));
  window_ctx->event_move_node = ctx->event_move_node;
  //window_ctx->background_disabled = 1;

  copied = false;
  for (int i = 0; i < 4; i++) {
    if ((s = strstr(owner, "$object"))) {
      if (!streq(ctx->owner, "")) {
        int len = s - owner;
        strncpy(window_ctx->owner, owner, len);
        window_ctx->owner[len] = 0;
        strcat(window_ctx->owner, ctx->owner);
        strcat(window_ctx->owner, s + 7);
        copied = true;
      }
    } else
      break;
  }
  if (!copied)
    strcpy(window_ctx->owner, owner);
  window_ctx->customcolors = ctx->gdraw->create_customcolors();
  
  if (is_updating_attributes)
    ctx->gdraw->push_customcolors(window_ctx->customcolors);

  if (!no_file) {
    if (fname[0] == '@') {
      if (ctx->scriptexec_callback)
	(ctx->scriptexec_callback)(window_ctx, fname);
    }
    else {
      window_ctx->set_nodraw();
      sts = window_ctx->open(fname, glow_eSaveMode_Edit);
      window_ctx->reset_nodraw();
      if (EVEN(sts))
	printf("** Unable to open graph %s\n", fname);
    }
  }

  strcpy(input_file_name, file_name);
  if (window_ctx->background_color != glow_eDrawType_Inherit) {
    fill_drawtype = original_fill_drawtype = window_ctx->background_color;
    fill = 1;
  }
  if (!feq(window_ctx->x0, window_ctx->x1)
      && !feq(window_ctx->y0, window_ctx->y1)) {
    wctx_x0 = window_ctx->x0;
    wctx_x1 = window_ctx->x1;
    wctx_y0 = window_ctx->y0;
    wctx_y1 = window_ctx->y1;
  } else {
    wctx_x0 = window_ctx->x_left;
    wctx_x1 = window_ctx->x_right;
    wctx_y0 = window_ctx->y_low;
    wctx_y1 = window_ctx->y_high;
  }
  window_ctx->mw.window_width = int((x_right - x_left) * ctx->mw.zoom_factor_x);
  window_ctx->mw.window_height = int((y_high - y_low) * ctx->mw.zoom_factor_y);
  window_ctx->mw.subwindow_x
      = int(x_left * ctx->mw.zoom_factor_x - ctx->mw.offset_x);
  window_ctx->mw.subwindow_y
      = int(y_low * ctx->mw.zoom_factor_y - ctx->mw.offset_y);
  window_ctx->mw.subwindow_scale = ctx->mw.subwindow_scale * window_scale;
  window_ctx->mw.zoom_factor_x = window_ctx->mw.zoom_factor_y
      = ctx->mw.zoom_factor_x * window_ctx->mw.subwindow_scale;
  window_ctx->move_restriction = glow_eMoveRestriction_Disable;
  window_ctx->a.zoom();

  if (is_updating_attributes)
    ctx->gdraw->pop_customcolors();

  if (ctx->trace_started) {
    trace_init();
    trace_scan();
  }

  // if ( input_focus)
  ctx->inputfocus_object = this;
  window_ctx->inputfocus_init_event();
}

void GrowWindow::redraw_cb(void* o)
{
  GrowWindow* gw = (GrowWindow*)o;

  gw->draw_background();
}

void GrowWindow::draw_background()
{
  if (!(display_level & ctx->display_level))
    return;
  int idx;
  glow_eDrawType drawtype;

  idx = int(ctx->mw.zoom_factor_y / ctx->mw.base_zoom_factor * line_width - 1);
  idx += hot;
  idx = MAX(0, idx);
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);
  int ll_x, ll_y, ur_x, ur_y;
  double dx1, dy1, dx2, dy2;

  dx1 = trf.x(ll.x, ll.y);
  dy1 = trf.y(ll.x, ll.y);
  dx2 = trf.x(ur.x, ur.y);
  dy2 = trf.y(ur.x, ur.y);

  dx1 = MIN(dx1, dx2);
  dx2 = MAX(dx1, dx2);
  dy1 = MIN(dy1, dy2);
  dy2 = MAX(dy1, dy2);

  if (v_scrollbar)
    v_scrollbar->draw(&ctx->mw, 0, 0, 0, 0, 0, 0);
  if (h_scrollbar)
    h_scrollbar->draw(&ctx->mw, 0, 0, 0, 0, 0, 0);

  ll_x = int(dx1 * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
  ll_y = int((dy1 + y_low_offs) * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;

  if (window_ctx) {
    ur_x = int((dx2 - vertical_scrollbar * scrollbar_width)
               * ctx->mw.zoom_factor_x)
        - ctx->mw.offset_x;
    ur_y = int((dy2 - horizontal_scrollbar * scrollbar_width)
               * ctx->mw.zoom_factor_y)
        - ctx->mw.offset_y;

    if (fill)
      ctx->gdraw->fill_rect(
          &ctx->mw, ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, fill_drawtype);
  }

  ur_x = int(dx2 * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
  ur_y = int(dy2 * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;

  drawtype = ctx->get_drawtype(
      draw_type, glow_eDrawType_LineHighlight, highlight, 0, 0);
  ctx->gdraw->rect(
      &ctx->mw, ll_x, ll_y, ur_x - ll_x, ur_y - ll_y, drawtype, idx, 0);
}

void GrowWindow::zoom()
{
  GrowRect::zoom();
  if (window_ctx)
    window_ctx->a.zoom();
}

int GrowWindow::get_background_object_limits(GlowTransform* t,
    glow_eTraceType type, double x, double y, GlowArrayElem** background,
    double* min, double* max, glow_eDirection* direction)
{
  if (window_ctx)
    return window_ctx->get_background_object_limits(
        type, x, y, background, min, max, direction);
  return 0;
}

int GrowWindow::set_source(char* source, char* new_owner)
{
  int clip_removed = 0;
  int sts;

  if (ctx->gdraw->clip_level(&ctx->mw)) {
    // Remove any clip
    ctx->gdraw->reset_clip_rectangle(&ctx->mw);
    clip_removed = 1;
  }

  strcpy(input_file_name, source);
  if (new_owner)
    strncpy(owner, new_owner, sizeof(owner));
  sts = update_attributes();

  window_ctx->gdraw->push_customcolors(window_ctx->customcolors);
  draw();
  window_ctx->gdraw->pop_customcolors();

  if (clip_removed)
    // Set a clip to match the previous reset
    ctx->gdraw->set_clip_rectangle(
        &ctx->mw, 0, 0, ctx->mw.window_width, ctx->mw.window_height);

  return sts;
}

int GrowWindow::export_script(GlowExportScript* es, void* o, void* m)
{
  return es->window(this, o, m);
}

