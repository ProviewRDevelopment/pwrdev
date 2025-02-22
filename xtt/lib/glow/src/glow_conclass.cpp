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

#include "glow_msg.h"

#include <string.h>

#include <iostream>

#include "glow_conclass.h"

GlowConClass::GlowConClass(GrowCtx* glow_ctx, const char* name,
    glow_eConType contype, glow_eCorner cornertype, glow_eDrawType d_type,
    int line_w, double arrow_w, double arrow_l, double round_corner_amnt,
    glow_eConGroup grp)
    : GlowArrayElem(glow_ctx), zero(glow_ctx, 0, 0), con_type(contype),
      corner(cornertype), draw_type(d_type), line_width(line_w),
      arrow_width(arrow_w), arrow_length(arrow_l),
      round_corner_amount(round_corner_amnt), group(grp)
{
  strcpy(n_name, name);
  zero.nav_zoom();
  zero.print_zoom();
}

void GlowConClass::save(std::ofstream& fp, glow_eSaveMode mode)
{
  if ((mode == glow_eSaveMode_Trace && group != glow_eConGroup_Trace)
      || (mode == glow_eSaveMode_Edit && group == glow_eConGroup_Trace))
    return;
  fp << int(glow_eSave_ConClass) << '\n';
  fp << int(glow_eSave_ConClass_cc_name) << FSPACE << n_name << '\n';
  fp << int(glow_eSave_ConClass_con_type) << FSPACE << int(con_type) << '\n';
  fp << int(glow_eSave_ConClass_corner) << FSPACE << int(corner) << '\n';
  fp << int(glow_eSave_ConClass_draw_type) << FSPACE << int(draw_type) << '\n';
  fp << int(glow_eSave_ConClass_line_width) << FSPACE << line_width << '\n';
  fp << int(glow_eSave_ConClass_arrow_width) << FSPACE << arrow_width << '\n';
  fp << int(glow_eSave_ConClass_arrow_length) << FSPACE << arrow_length << '\n';
  fp << int(glow_eSave_ConClass_round_corner_amount) << FSPACE
     << round_corner_amount << '\n';
  fp << int(glow_eSave_ConClass_group) << FSPACE << int(group) << '\n';
  fp << int(glow_eSave_End) << '\n';
}

void GlowConClass::open(std::ifstream& fp)
{
  int type = 0;
  int end_found = 0;
  char dummy[40];
  int tmp;

  for (;;) {
    if (!fp.good()) {
      fp.clear();
      fp.getline(dummy, sizeof(dummy));
      printf("** Read error GlowConClass: \"%d %s\"\n", type, dummy);
    }

    fp >> type;
    switch (type) {
    case glow_eSave_ConClass:
      break;
    case glow_eSave_ConClass_cc_name:
      fp.get();
      fp.getline(n_name, sizeof(n_name));
      break;
    case glow_eSave_ConClass_con_type:
      fp >> tmp;
      con_type = (glow_eConType)tmp;
      break;
    case glow_eSave_ConClass_corner:
      fp >> tmp;
      corner = (glow_eCorner)tmp;
      break;
    case glow_eSave_ConClass_draw_type:
      fp >> tmp;
      draw_type = (glow_eDrawType)tmp;
      break;
    case glow_eSave_ConClass_line_width:
      fp >> line_width;
      break;
    case glow_eSave_ConClass_arrow_width:
      fp >> arrow_width;
      break;
    case glow_eSave_ConClass_arrow_length:
      fp >> arrow_length;
      break;
    case glow_eSave_ConClass_round_corner_amount:
      fp >> round_corner_amount;
      break;
    case glow_eSave_ConClass_group:
      fp >> tmp;
      group = (glow_eConGroup)tmp;
      break;
    case glow_eSave_End:
      end_found = 1;
      break;
    default:
      std::cout << "GlowConClass:open syntax error\n";
      fp.getline(dummy, sizeof(dummy));
    }
    if (end_found)
      break;
  }
}

void GlowConClass::convert(glow_eConvert version)
{
  switch (version) {
  case glow_eConvert_V34: {
    // Conversion of colors
    draw_type = GlowColor::convert(version, draw_type);

    break;
  }
  }
}

std::ostream& operator<<(std::ostream& o, const GlowConClass cc)
{
  o << "ConClass: " << cc.n_name;
  return o;
}
