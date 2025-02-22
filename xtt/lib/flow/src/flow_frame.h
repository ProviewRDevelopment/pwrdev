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

#ifndef flow_frame_h
#define flow_frame_h

#include "flow_rect.h"

class FlowFrame : public FlowRect {
public:
  FlowFrame(FlowCtx* flow_ctx, double x = 0, double y = 0, double w = 0,
      double h = 0, flow_eDrawType d_type = flow_eDrawType_Line, int line_w = 1,
      int fix_line_w = 0)
      : FlowRect(flow_ctx, x, y, w, h, d_type, line_w, fix_line_w){}
  void save(std::ofstream& fp, flow_eSaveMode mode);
  void open(std::ifstream& fp);
  void draw(void* pos, int hightlight, int dimmed, int hot, void* node);
  void erase(void* pos, int hot, void* node);
  void get_borders(double pos_x, double pos_y, double* x_right, double* x_left,
      double* y_high, double* y_low, void* node);
  flow_eObjectType type()
  {
    return flow_eObjectType_Frame;
  }
  int event_handler(void* pos, flow_eEvent event, int x, int y, void* node);
};

#endif
