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
#include <string.h>

#include <iostream>

#include "glow_growannot.h"
#include "glow_draw.h"
#include "glow_grownode.h"

static char stars[] = "********************************************************"
                      "***********************";

void GrowAnnot::save(std::ofstream& fp, glow_eSaveMode mode)
{
  if (mode == glow_eSaveMode_SubGraph)
    GlowAnnot::save(fp, mode);
  else {
    fp << int(glow_eSave_GrowAnnot) << '\n';
    fp << int(glow_eSave_GrowAnnot_annot_part) << '\n';
    GlowAnnot::save(fp, mode);
    fp << int(glow_eSave_GrowAnnot_trf) << '\n';
    trf.save(fp, mode);
    fp << int(glow_eSave_GrowAnnot_adjustment) << FSPACE << int(adjustment)
       << '\n';
    fp << int(glow_eSave_End) << '\n';
  }
}

void GrowAnnot::open(std::ifstream& fp)
{
  int type = 0;
  int end_found = 0;
  char dummy[40];
  int tmp;

  for (;;) {
    if (!fp.good()) {
      fp.clear();
      fp.getline(dummy, sizeof(dummy));
      printf("** Read error GrowAnnot: \"%d %s\"\n", type, dummy);
    }

    fp >> type;
    switch (type) {
    case glow_eSave_GrowAnnot:
      break;
    case glow_eSave_GrowAnnot_annot_part:
      GlowAnnot::open(fp);
      break;
    case glow_eSave_GrowAnnot_trf:
      trf.open(fp);
      break;
    case glow_eSave_GrowAnnot_adjustment:
      fp >> tmp;
      adjustment = (glow_eAdjustment)tmp;
      break;
    case glow_eSave_End:
      end_found = 1;
      break;
    default:
      std::cout << "GrowAnnot:open syntax error\n";
      fp.getline(dummy, sizeof(dummy));
    }
    if (end_found)
      break;
  }
}

void GrowAnnot::draw(GlowWind* w, GlowTransform* t, int highlight, int hot,
    void* node, void* colornode, void *transpnode)
{
  int x1, y1;

  if (!(display_level & ctx->display_level))
    return;
  if (w == &ctx->navw) {
    if (ctx->no_nav)
      return;
    hot = 0;
  }

  if (!((GlowNode*)node)->annotv[number])
    return;

  glow_eDrawType color;
  int rot;
  double offset_x = 0;
  double offset_y = 0;
  double trf_scale = trf.vertical_scale(t);
  int idx = int(
      trf_scale * w->zoom_factor_y / w->base_zoom_factor * (text_size + 4) - 4);
  double tsize = trf_scale * w->zoom_factor_y / w->base_zoom_factor
      * (8 + 2 * text_size);
  if (idx < 0)
    return;
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);

  double transp = 0;  
  if (colornode)
    transp = ((GrowNode*)colornode)->transparency;
  if (transpnode && ((GrowNode*)transpnode)->transparency > transp)
    transp = ((GrowNode*)transpnode)->transparency;

  glow_eFont lfont;
  glow_eDrawType ldraw_type;

  if (node && ((GrowNode*)node)->annot_scrollingtext == number) {
    offset_x = ((GrowNode*)node)->annot_offset_x;
    offset_y = ((GrowNode*)node)->annot_offset_y;
    if (((GrowNode*)node)->annot_scrollingtext != -1)
      ctx->gdraw->set_clip_rectangle(w, 
	  int(((GrowNode*)node)->x_left * w->zoom_factor_x + 0.5) - w->offset_x,
	  int(((GrowNode*)node)->y_low * w->zoom_factor_y + 0.5) - w->offset_y,
	  int(((GrowNode*)node)->x_right * w->zoom_factor_x + 0.5) - w->offset_x + 1,
	  int(((GrowNode*)node)->y_high * w->zoom_factor_y + 0.5) - w->offset_y + 1);
  }

  if (node && ((GrowNode*)node)->text_font != glow_eFont_No) {
    lfont = ((GrowNode*)node)->text_font;
    ldraw_type = ((GrowNode*)node)->text_type;
  } else {
    lfont = font;
    ldraw_type = draw_type;
  }

  if (!t) {
    x1 = int((trf.x(p.x, p.y) + offset_x) * w->zoom_factor_x) - w->offset_x;
    y1 = int((trf.y(p.x, p.y) + offset_y) * w->zoom_factor_y) - w->offset_y;
    rot = (int)trf.rot();
  } else {
    x1 = int((trf.x(t, p.x, p.y) + offset_x) * w->zoom_factor_x) - w->offset_x;
    y1 = int((trf.y(t, p.x, p.y) + offset_y) * w->zoom_factor_y) - w->offset_y;
    rot = (int)trf.rot(t);
  }
  rot = rot < 0 ? rot % 360 + 360 : rot % 360;

  switch (annot_type) {
  case glow_eAnnotType_OneLine: {
    int width = 0, height = 0, descent = 0;
    char* textp;
    int text_len;

    color = ((GrowCtx*)ctx)
                ->get_drawtype(color_drawtype, glow_eDrawType_LineHighlight,
                    highlight, (GrowNode*)colornode, 2);

    if (protect) {
      text_len
          = MIN(strlen(((GlowNode*)node)->annotv[number]), sizeof(stars) - 2);
      textp = &stars[sizeof(stars) - 1 - text_len];
    } else {
      textp = ((GlowNode*)node)->annotv[number];
      text_len = strlen(((GlowNode*)node)->annotv[number]);
    }

    if (((rot < 45 || rot >= 315)
            && (((GlowNode*)node)->annotv_inputmode[number]
                   && ((GrowNode*)node)->input_selected))
        || (!(rot < 45 || rot >= 315)) || adjustment == glow_eAdjustment_Right
        || adjustment == glow_eAdjustment_Center)
      ctx->gdraw->get_text_extent(textp, text_len, ldraw_type, idx, lfont,
          &width, &height, &descent, tsize, 0);

    switch (adjustment) {
    case glow_eAdjustment_Left:
      break;
    case glow_eAdjustment_Right:
      x1 -= width;
      break;
    case glow_eAdjustment_Center:
      x1 -= width / 2;
      break;
    }

    if (rot < 45 || rot >= 315) {
      if (((GlowNode*)node)->annotv_inputmode[number]
          && ((GrowNode*)node)->input_selected) {
        ctx->gdraw->fill_rect(w, x1, y1 - height + descent, width, height,
            glow_eDrawType_MediumGray);
      }
    } else {
      // Text is rotated, adjust the coordinates
      if (adjustment == glow_eAdjustment_Center) {
        // Only center adjustment supports text rotation
        if (45 <= rot && rot < 135) {
          x1 += width / 2;
          y1 += width / 2;
        } else if (135 <= rot && rot < 225) {
          y1 += height - descent;
        } else if (225 <= rot && rot < 315) {
          x1 += width / 2 - height + descent;
          y1 -= width / 2 - height + descent;
        } else {
          x1 -= width;
        }
      } else {
        if (45 <= rot && rot < 135) {
          y1 += height - descent;
        } else if (135 <= rot && rot < 225) {
          x1 -= width;
          y1 += height - descent;
        } else {
          x1 -= width;
        }
        rot = 0;
      }
    }

    ctx->gdraw->text(w, x1, y1, textp, text_len, ldraw_type, color, idx,
	highlight, 0, lfont, tsize, rot, transp);

    if (((GlowNode*)node)->annotv_inputmode[number])
      ctx->gdraw->text_cursor(w, x1, y1, textp, text_len, ldraw_type, color,
          idx, highlight, ((GrowNode*)node)->input_position, lfont, tsize);
    break;
  }
  case glow_eAnnotType_MultiLine: {
    int z_width, z_height, z_descent;
    int len = 0;
    int line_cnt = 0;
    char* line = ((GlowNode*)node)->annotv[number];
    char* s;
    color = ((GrowCtx*)ctx)
                ->get_drawtype(color_drawtype, glow_eDrawType_LineHighlight,
                    highlight, (GrowNode*)colornode, 2);

    ctx->gdraw->get_text_extent("", 0, ldraw_type, idx, lfont, &z_width,
        &z_height, &z_descent, tsize, 0);
    for (s = ((GlowNode*)node)->annotv[number]; *s; s++) {
      if (*s == 10) {
        if (len) {
          *s = 0;
          ctx->gdraw->text(w, x1, y1 + line_cnt * z_height, line, len,
	      ldraw_type, color, idx, highlight, 0, lfont, tsize, 0, transp);
          *s = 10;
        }
        len = 0;
        line = s + 1;
        line_cnt++;
      } else
        len++;
    }
    if (len)
      ctx->gdraw->text(w, x1, y1 + line_cnt * z_height, line, len, ldraw_type,
	  color, idx, highlight, 0, lfont, tsize, 0, transp);
    break;
  }
  }
  if (node && ((GrowNode*)node)->annot_scrollingtext == number &&
      ((GrowNode*)node)->annot_scrollingtext != -1) {
    ctx->gdraw->reset_clip_rectangle(w);
  }
}

void GrowAnnot::erase_background(
    GlowWind* w, GlowTransform* t, int hot, void* node)
{
  int x1, y1;

  if (!(display_level & ctx->display_level))
    return;

  if (!((GlowNode*)node)->annotv[number])
    return;
  double trf_scale = trf.vertical_scale(t);
  int idx = int(
      trf_scale * w->zoom_factor_y / w->base_zoom_factor * (text_size + 4) - 4);
  double tsize = trf_scale * w->zoom_factor_y / w->base_zoom_factor
      * (8 + 2 * text_size);
  if (idx < 0)
    return;
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);

  glow_eFont lfont;
  glow_eDrawType ldraw_type;

  if (node && ((GrowNode*)node)->text_font != glow_eFont_No) {
    lfont = ((GrowNode*)node)->text_font;
    ldraw_type = ((GrowNode*)node)->text_type;
  } else {
    lfont = font;
    ldraw_type = draw_type;
  }

  if (!t) {
    x1 = int(trf.x(p.x, p.y) * w->zoom_factor_x) - w->offset_x;
    y1 = int(trf.y(p.x, p.y) * w->zoom_factor_y) - w->offset_y;
  } else {
    x1 = int(trf.x(t, p.x, p.y) * w->zoom_factor_x) - w->offset_x;
    y1 = int(trf.y(t, p.x, p.y) * w->zoom_factor_y) - w->offset_y;
  }
  switch (annot_type) {
  case glow_eAnnotType_OneLine: {
    int sts;

    sts = ((GrowNode*)node)->draw_annot_background(t, 0, 0);
    if (ODD(sts)) {
      // There is not any gc for color text...
      //        glow_draw_text( ctx, x1, y1,
      //		((GlowNode *) node)->annotv[number],
      //		strlen(((GlowNode *) node)->annotv[number]), background,
      // idx,
      //		0, 0);
    } else {
      if (!protect)
        ctx->gdraw->text_erase(w, x1, y1, ((GlowNode*)node)->annotv[number],
            strlen(((GlowNode*)node)->annotv[number]), ldraw_type, idx, 0,
            lfont, tsize, 0);
      else {
        int text_len
            = MIN(strlen(((GlowNode*)node)->annotv[number]), sizeof(stars) - 2);
        ctx->gdraw->text_erase(w, x1, y1, &stars[sizeof(stars) - 1 - text_len],
            text_len, ldraw_type, idx, 0, lfont, tsize, 0);
      }
    }
    break;
  }
  case glow_eAnnotType_MultiLine: {
    int z_width, z_height, z_descent;
    int len = 0;
    int line_cnt = 0;
    char* line = ((GlowNode*)node)->annotv[number];
    char* s;
    ctx->gdraw->get_text_extent("", 0, ldraw_type, idx, lfont, &z_width,
        &z_height, &z_descent, tsize, 0);
    for (s = ((GlowNode*)node)->annotv[number]; *s; s++) {
      if (*s == 10) {
        if (len) {
          *s = 0;
          ctx->gdraw->text_erase(w, x1, y1 + line_cnt * z_height, line, len,
              ldraw_type, idx, 0, lfont, tsize, 0);
          *s = 10;
        }
        len = 0;
        line = s + 1;
        line_cnt++;
      } else
        len++;
    }
    if (len)
      ctx->gdraw->text_erase(w, x1, y1 + line_cnt * z_height, line, len,
          ldraw_type, idx, 0, lfont, tsize, 0);
    break;
  }
  }
}

void GrowAnnot::get_borders(GlowTransform* t, double* x_right, double* x_left,
    double* y_high, double* y_low)
{
  double x1, y1;

  if (!t) {
    x1 = trf.x(p.x, p.y);
    y1 = trf.y(p.x, p.y);
  } else {
    x1 = trf.x(t, p.x, p.y);
    y1 = trf.y(t, p.x, p.y);
  }

  if (x1 < *x_left)
    *x_left = x1;
  if (x1 > *x_right)
    *x_right = x1;
  if (y1 < *y_low)
    *y_low = y1;
  if (y1 > *y_high)
    *y_high = y1;
}

void GrowAnnot::export_javabean(GlowTransform* t, void* node,
    glow_eExportPass pass, int* shape_cnt, int node_cnt, int in_nc,
    std::ofstream& fp)
{
  int x1, y1;
  int bold;

  double trf_scale = trf.vertical_scale(t);
  int idx = int(trf_scale * ctx->mw.zoom_factor_y / ctx->mw.base_zoom_factor
          * (text_size + 4)
      - 4);
  if (idx < 0)
    return;
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);

  if (!t) {
    x1 = int(trf.x(p.x, p.y) * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
    y1 = int(trf.y(p.x, p.y) * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;
  } else {
    x1 = int(trf.x(t, p.x, p.y) * ctx->mw.zoom_factor_x) - ctx->mw.offset_x;
    y1 = int(trf.y(t, p.x, p.y) * ctx->mw.zoom_factor_y) - ctx->mw.offset_y;
  }

  bold = (draw_type == glow_eDrawType_TextHelveticaBold);

  ((GrowCtx*)ctx)
      ->export_jbean->annot(x1, y1, number, draw_type, color_drawtype, bold,
          adjustment, idx, pass, shape_cnt, node_cnt, fp);
  //  (*shape_cnt)++;
}

void GrowAnnot::export_javabean_font(
    GlowTransform* t, void* node, glow_eExportPass pass, std::ofstream& fp)
{
  int bold;
  glow_eDrawType background;

  double trf_scale = trf.vertical_scale(t);
  int idx = int(trf_scale * ctx->mw.zoom_factor_y / ctx->mw.base_zoom_factor
          * (text_size + 4)
      - 4);
  if (idx < 0)
    return;
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);

  glow_eFont lfont;
  glow_eDrawType ldraw_type;

  if (node && ((GrowNode*)node)->text_font != glow_eFont_No) {
    lfont = ((GrowNode*)node)->text_font;
    ldraw_type = ((GrowNode*)node)->text_type;
  } else {
    lfont = font;
    ldraw_type = draw_type;
  }

  bold = (ldraw_type == glow_eDrawType_TextHelveticaBold);

  ((GrowCtx*)ctx)
      ->export_jbean->nc->get_annot_background(NULL, NULL, &background);

  ((GrowCtx*)ctx)
      ->export_jbean->annot_font(
          number, ldraw_type, background, bold, idx, pass, fp);
}

void GrowAnnot::convert(glow_eConvert version)
{
  switch (version) {
  case glow_eConvert_V34: {
    // Conversion of colors
    draw_type = GlowColor::convert(version, draw_type);

    break;
  }
  }
}

void GrowAnnot::get_annotation_info(void* node, int* t_size,
    glow_eDrawType* t_drawtype, glow_eDrawType* t_color, glow_eFont* t_font,
    glow_eAnnotType* t_type)
{
  *t_color = ((GrowCtx*)ctx)
                 ->get_drawtype(color_drawtype, glow_eDrawType_LineHighlight, 0,
                     (GrowNode*)node, 2);
  *t_size = text_size;
  *t_type = annot_type;
  if (node && ((GrowNode*)node)->text_font != glow_eFont_No) {
    *t_font = ((GrowNode*)node)->text_font;
    *t_drawtype = ((GrowNode*)node)->text_type;
  } else {
    *t_drawtype = draw_type;
    *t_font = font;
  }
}

int GrowAnnot::get_text_size(GlowTransform* t, double* tsize)
{
  double trf_scale = trf.vertical_scale(t);
  *tsize = trf_scale * ctx->mw.zoom_factor_y / ctx->mw.base_zoom_factor
      * (8 + 2 * text_size);

  return 1;
}

void GrowAnnot::get_text_extent(
    GlowTransform* t, void* node, double* width, double* height)
{
  if (!((GlowNode*)node)->annotv[number]) {
    *width = 0;
    *height = 0;
    return;
  }
  int z_width, z_height, descent;
  double trf_scale = trf.vertical_scale(t);
  int idx = int(trf_scale * ctx->mw.zoom_factor_y / ctx->mw.base_zoom_factor
          * (text_size + 4)
      - 4);
  double tsize = trf_scale * ctx->mw.zoom_factor_y / ctx->mw.base_zoom_factor
      * (8 + 2 * text_size);
  if (idx < 0)
    return;
  idx = MIN(idx, DRAW_TYPE_SIZE - 1);

  char* textp = ((GlowNode*)node)->annotv[number];
  int text_len = strlen(((GlowNode*)node)->annotv[number]);

  ctx->gdraw->get_text_extent(textp, text_len, draw_type, idx, font, &z_width,
      &z_height, &descent, tsize, 0);

  *width = (double)z_width / ctx->mw.zoom_factor_x;
  *height = (double)z_height / ctx->mw.zoom_factor_y;
}
