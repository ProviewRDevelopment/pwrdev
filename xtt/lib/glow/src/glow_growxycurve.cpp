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

#include <math.h>
#include <string.h>

#include <iostream>

#include "glow_growxycurve.h"
#include "glow_grownode.h"

GrowXYCurve::GrowXYCurve(GrowCtx* glow_ctx, const char* name, double x,
    double y, double w, double h, glow_eDrawType border_d_type, int line_w,
    glow_mDisplayLevel display_lev, int fill_rect, int display_border,
    glow_eDrawType fill_d_type, int nodraw)
    : GrowTrend(glow_ctx, name, x, y, w, h, border_d_type, line_w, display_lev,
          fill_rect, display_border, fill_d_type, 1)
{
}

void GrowXYCurve::save(std::ofstream& fp, glow_eSaveMode mode)
{
  fp << int(glow_eSave_GrowXYCurve) << '\n';
  fp << int(glow_eSave_GrowXYCurve_trend_part) << '\n';
  GrowTrend::save(fp, mode);
  fp << int(glow_eSave_End) << '\n';
}

//! Read the content of the object from file.
/*!
  \param fp	Input file.
*/
void GrowXYCurve::open(std::ifstream& fp)
{
  int type = 0;
  int end_found = 0;
  char dummy[40];

  for (;;) {
    if (!fp.good()) {
      fp.clear();
      fp.getline(dummy, sizeof(dummy));
      printf("** Read error GrowXYWindow: \"%d %s\"\n", type, dummy);
    }

    fp >> type;
    switch (type) {
    case glow_eSave_GrowXYCurve:
      break;
    case glow_eSave_GrowXYCurve_trend_part:
      GrowTrend::open(fp);
      break;
    case glow_eSave_End:
      end_found = 1;
      break;
    default:
      std::cout << "GrowXYCurve:open syntax error\n";
      fp.getline(dummy, sizeof(dummy));
    }
    if (end_found)
      break;
  }
}

//! Set the range for the specified xy_curve in x direction.
/*!
  \param curve	Number of curve.
  \param min		Min value.
  \param max		Max value.
*/
void GrowXYCurve::set_xy_range_x(int curve, double min, double max)
{
  if (curve > TREND_MAX_CURVES)
    return;

  if (curve == 0) {
    if (display_x_mark1) {
      double mark
          = (x_mark1 - ll.x) * (x_max_value[0] - x_min_value[0]) / (ur.x - ll.x)
          + x_min_value[0];
      x_mark1 = ll.x + (mark - min) / (max - min) * (ur.x - ll.x);
    }
    if (display_x_mark2) {
      double mark
          = (x_mark2 - ll.x) * (x_max_value[0] - x_min_value[0]) / (ur.x - ll.x)
          + x_min_value[0];
      x_mark2 = ll.x + (mark - min) / (max - min) * (ur.x - ll.x);
    }
  }
  x_max_value[curve] = max;
  x_min_value[curve] = min;
}

//! Set the range for the specified xy_curve in x direction.
/*!
  \param curve	Number of curve.
  \param min		Min value.
  \param max		Max value.
*/
void GrowXYCurve::set_xy_range_y(int curve, double min, double max)
{
  if (curve > TREND_MAX_CURVES)
    return;
  if (curve == 0) {
    if (display_y_mark1) {
      double mark = y_min_value[0]
          - (y_mark1 - ur.y) * (y_max_value[0] - y_min_value[0])
              / (ur.y - ll.y);
      y_mark1 = ur.y - (mark - min) / (max - min) * (ur.y - ll.y);
    }
    if (display_y_mark2) {
      double mark = y_min_value[0]
          - (y_mark2 - ur.y) * (y_max_value[0] - y_min_value[0])
              / (ur.y - ll.y);
      y_mark2 = ur.y - (mark - min) / (max - min) * (ur.y - ll.y);
    }
  }
  y_max_value[curve] = max;
  y_min_value[curve] = min;
}

void GrowXYCurve::get_xy_range_x(int curve, double *min, double *max)
{
  *max = x_max_value[curve];
  *min = x_min_value[curve];
}

void GrowXYCurve::get_xy_range_y(int curve, double *min, double *max)
{
  *max = y_max_value[curve];
  *min = y_min_value[curve];
}

void GrowXYCurve::set_xy_noofcurves(int noofcurves)
{
  curve_cnt = noofcurves;
}

void GrowXYCurve::set_xy_curve_color(
    int curve, glow_eDrawType curve_color, glow_eDrawType fill_color)
{
  if (curve > TREND_MAX_CURVES)
    return;
  curve_drawtype[curve] = curve_color;
  curve_fill_drawtype[curve] = fill_color;
}

void GrowXYCurve::set_xy_data(
    double* y_data, double* x_data, int curve_idx, int data_points)
{
  glow_eDrawType dt, dt_fill;
  int points;
  int cpoints;
  glow_sPoint* pointarray;
  glow_sPoint* point_p;
  int i, j, idx;

  if (curve_idx > TREND_MAX_CURVES)
    return;

  no_of_points = MAX(2, no_of_points);
  points = cpoints = MIN(no_of_points, data_points);
  if (fill_curve)
    cpoints += 2;

  curve_width = MIN(DRAW_TYPE_SIZE, MAX(1, curve_width));

  pointarray = (glow_sPoint*)calloc(cpoints, sizeof(glow_sPoint));
  point_p = pointarray;
  j = curve_idx;
  for (i = 0, idx = 0; i < cpoints; i++, idx++) {
    if (!fill_curve) {
      idx = i;
      if (!feq(y_max_value[j], y_min_value[j]))
        point_p->y = ur.y
            - (y_data[idx] - y_min_value[j]) / (y_max_value[j] - y_min_value[j])
                * (ur.y - ll.y);

      point_p->y = MAX(ll.y, MIN(point_p->y, ur.y));

      if (!feq(x_max_value[j], x_min_value[j]))
        point_p->x = ll.x
            + (x_data[idx] - x_min_value[j]) / (x_max_value[j] - x_min_value[j])
                * (ur.x - ll.x);

      point_p->x = MAX(ll.x, MIN(point_p->x, ur.x));
    } else {
      if (i == 0) {
        if (!feq(x_max_value[j], x_min_value[j]))
          point_p->x = ll.x
              + (x_data[idx] - x_min_value[j])
                  / (x_max_value[j] - x_min_value[j]) * (ur.x - ll.x);

        point_p->x = MAX(ll.x, MIN(point_p->x, ur.x));
        point_p->y = ur.y;
        idx--;
      } else if (i == cpoints - 1) {
        if (!feq(x_max_value[j], x_min_value[j]))
          point_p->x = ll.x
              + (x_data[idx - 1] - x_min_value[j])
                  / (x_max_value[j] - x_min_value[j]) * (ur.x - ll.x);

        point_p->x = MAX(ll.x, MIN(point_p->x, ur.x));
        point_p->y = ur.y;
      } else {
        if (!feq(y_max_value[j], y_min_value[j]))
          point_p->y = ur.y
              - (y_data[idx] - y_min_value[j])
                  / (y_max_value[j] - y_min_value[j]) * (ur.y - ll.y);

        point_p->y = MAX(ll.y, MIN(point_p->y, ur.y));

        if (!feq(x_max_value[j], x_min_value[j]))
          point_p->x = ll.x
              + (x_data[idx] - x_min_value[j])
                  / (x_max_value[j] - x_min_value[j]) * (ur.x - ll.x);

        point_p->x = MAX(ll.x, MIN(point_p->x, ur.x));
      }
    }
    point_p++;
  }

  ctx->nodraw++;
  if (curve[j])
    delete curve[j];
  ctx->nodraw--;

  if (curve_drawtype[j] != glow_eDrawType_Inherit)
    dt = curve_drawtype[j];
  else
    dt = draw_type;

  if (curve_fill_drawtype[j] != glow_eDrawType_Inherit)
    dt_fill = curve_fill_drawtype[j];
  else
    dt_fill = draw_type;

  ctx->nodraw++;
  curve[j] = new GrowPolyLine(ctx, "", pointarray, cpoints, dt, curve_width, 0,
      fill_curve, 1, 0, dt_fill, 0, 1);
  ctx->nodraw--;
  free((char*)pointarray);
  draw();
}

//! Export the object as a javabean.
/*!
  \param t		Transform of parent node. Can be zero.
  \param node		Parent node. Can be zero.
  \param pass		Export pass.
  \param shape_cnt	Current index in a shape std::vector.
  \param node_cnt	Counter used for javabean name. Not used for this kind
  of
  object.
  \param in_nc	Member of a nodeclass. Not used for this kind of object.
  \param fp		Output file.

  The object is transformed to the current zoom factor, and GlowExportJBean is
  used to generate
  java code for the bean.
*/
void GrowXYCurve::export_javabean(GlowTransform* t, void* node,
    glow_eExportPass pass, int* shape_cnt, int node_cnt, int in_nc,
    std::ofstream& fp)
{
  double x1, y1, x2, y2, ll_x, ll_y, ur_x, ur_y;
  double rotation;

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

  if (t)
    rotation = (trf.rot(t) / 360 - floor(trf.rot(t) / 360)) * 360;
  else
    rotation = (trf.rot() / 360 - floor(trf.rot() / 360)) * 360;

  ((GrowCtx*)ctx)
      ->export_jbean->xycurve(ll_x, ll_y, ur_x, ur_y, draw_type, fill_drawtype,
          fill, border, curve_width, no_of_points, horizontal_lines,
          vertical_lines, line_width, rotation, pass, shape_cnt, node_cnt, fp);
}

int GrowXYCurve::get_java_name(char* name)
{
  strcpy(name, "jopXYCurve");
  return 1;
}
