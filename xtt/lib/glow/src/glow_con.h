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

#ifndef glow_con_h
#define glow_con_h

#include "glow_node.h"
#include "glow_conclass.h"
#include "glow_line.h"
#include "glow_arc.h"
#include "glow_arrow.h"

#define MAX_POINT 8
#define MAX_HVLINE MAX_POINT / 2 + 1

/*! \file glow_con.h
    \brief Contains the GlowCon class. */
/*! \addtogroup Glow */
/*@{*/

//! Element in list of vertical lines.
typedef struct {
  double x; //!< x coordinate of line
  double l_y; //!< y coordinate for lower endpoint of line.
  double u_y; //!< y coordinate for upper endpoint of line.
  int dest; //!< Line for destination point.
} con_tVertLines;

//! Element i list of horizontal lines.
typedef struct {
  double y; //!< y coordinate of line.
  double l_x; //!< x coordinate for left endpoint of line.
  double u_x; //!< x coordinate for right endpoint of line.
  int dest; //!< Line for destination point.
} con_tHorizLines;

//! Class for a connection between two nodes.
/*! A connection is drawn between a source node and a destination node. The node
  objects contains
  connection points which gives the start end end point for the connection.
*/
class GlowCon : public GlowArrayElem {
public:
  //! Constructor.
  /*!
    \param glow_ctx	Glow context.
    \param name		Object name.
    \param con_class	Connection class.
    \param source	Source node.
    \param dest		Destination node.
    \param source_cp	Source connection point number.
    \param dest_cp	Destination connection point number.
    \param nodraw	Don't draw the object now.
    \param point_num	Number of points i x_vect and y_vect.
    \param x_vect	Array of x coordinates for points in the connection.
    \param y_vect	Array of y coordinates for points in the connection.
    \param cborder	Draw with border.
    \param cshadow	Draw width shadow.
  */
  GlowCon(GrowCtx* glow_ctx, const char* name, GlowConClass* con_class,
      GlowNode* source, GlowNode* dest, int source_cp, int dest_cp,
      int nodraw = 0, int point_num = 0, double* x_vect = 0, double* y_vect = 0,
      int cborder = 0, int cshadow = 0);

  //! Destructor.
  ~GlowCon();

  //! Noargs constructor.
  GlowCon(){}

  //! Copyconstructor with new source and destination nodes.
  /*!
    \param c		Connection to copy.
    \param source	Source node.
    \param dest		Destination node.
  */
  GlowCon(const GlowCon& c, GlowNode* source, GlowNode* dest);

  friend std::ostream& operator<<(std::ostream& o, const GlowCon c);

  void zoom();
  void nav_zoom();
  void get_borders(
      double* x1_right, double* x1_left, double* y1_high, double* y1_low){}
  void get_con_borders();
  int event_handler(GlowWind* w, glow_eEvent event, int x, int y);
  int event_handler(
      GlowWind* w, glow_eEvent event, int x, int y, double fx, double fy)
  {
    return event_handler(w, event, x, y);
  }

  //! Save the content of the object to file.
  /*!
    \param fp	Ouput file.
    \param mode	Save as graph or subgraph.
  */
  void save(std::ofstream& fp, glow_eSaveMode mode);

  //! Read the content of the object from file.
  /*!
    \param fp	Input file.
  */
  void open(std::ifstream& fp);
  void draw(GlowWind* w, int ll_x, int ll_y, int ur_x, int ur_y);
  void draw(GlowWind* w, int* ll_x, int* ll_y, int* ur_x, int* ur_y);
  void draw();
  void erase(){}
  void move(double delta_x, double delta_y, int grid);
  void move_noerase(int delta_x, int delta_y, int move);
  void reconfigure();
  void store_position(){}
  void restore_position(){}
  void redraw_node_cons(void* node);
  int delete_node_cons(void* node);
  int con_route(double src_x, double src_y, glow_eDirection src_dir,
      double dest_x, double dest_y, glow_eDirection dest_dir);
  int con_route_noobstacle(double src_x, double src_y, glow_eDirection src_dir,
      double dest_x, double dest_y, glow_eDirection dest_dir);
  int con_route_grafcet(glow_eConType con_type, double src_x, double src_y,
      double dest_x, double dest_y);
  void draw_routed_roundcorner(int points, double* x, double* y);
  void draw_routed(int points, double* x, double* y);
  void draw_routed_trans(int points, double* x, double* y);
  void set_highlight(int on);
  int get_highlight()
  {
    return highlight;
  }
  void set_hot(int on);
  void select_region_insert(double ll_x, double ll_y, double ur_x, double ur_y);
  glow_eObjectType type()
  {
    return glow_eObjectType_Con;
  }
  double x_right;
  double x_left;
  double y_high;
  double y_low;
  GlowConClass* cc;
  GlowNode* destination()
  {
    return dest_node;
  }
  GlowNode* source()
  {
    return source_node;
  }
  GlowNode* dest_node;
  GlowNode* source_node;
  int dest_conpoint;
  int source_conpoint;
  glow_eDirection source_direction;
  glow_eDirection dest_direction;
  int p_num;
  int l_num;
  int a_num;
  int arrow_num;
  int ref_num;
  double point_x[MAX_POINT];
  double point_y[MAX_POINT];
  GlowArray line_a;
  GlowArray arc_a;
  GlowArray arrow_a;
  GlowArray ref_a;
  int temporary_ref;
  int source_ref_cnt;
  int dest_ref_cnt;
  int hot;
  int highlight;
  glow_eMoveType movement_type;
  char trace_object[120];
  char trace_attribute[32];
  glow_eTraceType trace_attr_type;
  void* trace_p;
  GlowCon* link;
  int con_route_area(
      double wind_ll_x, double wind_ll_y, double wind_ur_x, double wind_ur_y);
  int find_horiz_line_up(double check_y, double check_l_x, double check_u_x,
      GlowNode* nodelist, GlowNode* next_node, GlowCon* conlist,
      GlowCon* next_con, double wind_ll_x, double wind_ur_x);
  int find_horiz_line_down(double check_y, double check_l_x, double check_u_x,
      GlowNode* nodelist, GlowNode* next_node, GlowCon* conlist,
      GlowCon* next_con, double wind_ll_x, double wind_ur_x);
  int find_vert_line_right(double check_x, double check_l_y, double check_u_y,
      GlowNode* nodelist, GlowNode* next_node, GlowCon* conlist,
      GlowCon* next_con, double wind_ll_y, double wind_ur_y);
  int find_vert_line_left(double check_x, double check_l_y, double check_u_y,
      GlowNode* nodelist, GlowNode* next_node, GlowCon* conlist,
      GlowCon* next_con, double wind_ll_y, double wind_ur_y);
  void find_horiz_line_right_border(double y, double start_x,
      double start_x_con, double* border_x, GlowNode* nodelist,
      GlowCon* conlist);
  void find_horiz_line_left_border(double y, double start_x, double start_x_con,
      double* border_x, GlowNode* nodelist, GlowCon* conlist);
  void find_vert_line_high_border(double x, double start_y, double start_x_con,
      double* border_y, GlowNode* nodelist, GlowCon* conlist);
  void find_vert_line_low_border(double x, double start_y, double start_x_con,
      double* border_y, GlowNode* nodelist, GlowCon* conlist);
  void link_insert(void** start)
  {
    link = *(GlowCon**)start;
    *start = (void*)this;
  }
  int in_area(double ll_x, double ll_y, double ur_x, double ur_y)
  {
    return ((x_left + ctx->draw_delta) < ur_x
        && (x_right + ctx->draw_delta) > ll_x
        && (y_low + ctx->draw_delta) < ur_y
        && (y_high + ctx->draw_delta) > ll_y);
  }
  int in_area_exact(double ll_x, double ll_y, double ur_x, double ur_y)
  {
    return (x_left < ur_x && x_right > ll_x && y_low < ur_y && y_high > ll_y);
  }
  int in_vert_line(double x, double l_y, double u_y)
  {
    return 0;
  }
  int in_horiz_line(double y, double l_x, double u_x)
  {
    return 0;
  }
  int find_horiz_line_next_line(con_tHorizLines* horiz_line);
  int find_vert_line_next_line(con_tVertLines* vert_line);
  int sort_lines(double dest_x, double dest_y, glow_eDirection dest_dir,
      double src_x, double src_y, glow_eDirection src_dir);
  void move_ref(double x1, double y1, double x2, double y2);
  void conpoint_refcon_redraw(void* node, int conpoint);
  void conpoint_refcon_erase(void* node, int conpoint);
  void remove_notify();
  int ideal_line_cnt;
  int current_line_cnt;
  unsigned int loop_cnt;
  void* user_data;
  int border;
  int shadow;

  void set_user_data(void* data)
  {
    user_data = data;
  }
  void get_user_data(void** data)
  {
    *data = user_data;
  }
  int trace_scan();
  int trace_init();
  void trace_close();
  void* get_ctx()
  {
    return this->ctx;
  }
  void get_con_position(double* x_arr[], double* y_arr[], int* num)
  {
    *x_arr = point_x;
    *y_arr = point_y;
    *num = p_num;
  }
  glow_eConGroup get_group()
  {
    return cc->group;
  }
  void set_movement_type(GlowArrayElem** a, int a_size);
  void set_movement_type(glow_eMoveType move_type)
  {
    movement_type = move_type;
  }
  int is_connected_to(GlowNode* node)
  {
    return source_node == node || dest_node == node;
  }
  void change_conclass(GlowConClass* conclass);
  void export_javabean(GlowTransform* t, void* node, glow_eExportPass pass,
      int* shape_cnt, int node_cnt, int in_nc, std::ofstream& fp);
  void convert(glow_eConvert version);
  void set_border(int borderval);
  void set_shadow(int shadowval);
  void con_modified();
  int find_cc(GlowArrayElem* conclass);
};

/*@}*/
#endif
