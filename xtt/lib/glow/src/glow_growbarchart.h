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

#ifndef glow_growbarchart_h
#define glow_growbarchart_h

#include "glow_growrect.h"

/*! \file glow_growbarchart.h
    \brief Contains the GrowBarChart class. */
/*! \addtogroup Glow */
/*@{*/

#define BARCHART_MAX_BARSEGMENTS 12
#define BARCHART_MAX_BARS 200

//! Class for drawing a barchart object.
/*! A GrowBarChart object is an object that displays a barchart chart.

  The GrowBarChart class contains function for drawing the object, and handle
  events when the
  object is clicked on, moved etc.
*/
class GrowBarChart : public GrowRect {
public:
  //! Constuctor
  /*!
    \param glow_ctx 	The glow context.
    \param name		Name (max 31 char).
    \param x		x coordinate for first corner.
    \param y		y coordinate for first corner.
    \param w		x coordinate for second corner.
    \param h		y coordinate for second corner.
    \param border_d_type Border color.
    \param line_w	Linewidth of border.
    \param nodraw	Don't draw the object now.
  */
  GrowBarChart(GrowCtx* glow_ctx, const char* name, double x = 0, double y = 0,
      double w = 0, double h = 0,
      glow_eDrawType border_d_type = glow_eDrawType_Line, int line_w = 1,
      int display_border = 1, int display_shadow = 0,
      glow_eDrawType fill_d_type = glow_eDrawType_Line, int nodraw = 0);

  //! Destructor
  /*! Remove the object from context, and erase it from the screen.
   */
  ~GrowBarChart();

  //! Save the content of the object to file.
  /*!
    \param fp	Ouput file.
    \param mode	Not used.
  */
  void save(std::ofstream& fp, glow_eSaveMode mode);

  //! Read the content of the object from file.
  /*!
    \param fp	Input file.
  */
  void open(std::ifstream& fp);

  //! Scan trace
  /*! Calls the trace scan callback for the object.
   */
  int trace_scan();

  //! Init trace
  /*! Calls the trace connect callback for the object.
   */
  int trace_init();

  //! Close trace
  /*! Calls the trace disconnect callback for the object.
   */
  void trace_close();

  //! Draw the objects if any part is inside the drawing area.
  /*!
    \param ll_x		Lower left x coordinate of drawing area.
    \param ll_y		Lower left y coordinate of drawing area.
    \param ur_x		Upper right x coordinate of drawing area.
    \param ur_y		Upper right y coordinate of drawing area.
  */
  void draw(GlowWind* w, int ll_x, int ll_y, int ur_x, int ur_y);

  //! Draw the objects if any part is inside the drawing area, and extends the
  //! drawing area.
  /*!
    \param ll_x		Lower left x coordinate of drawing area.
    \param ll_y		Lower left y coordinate of drawing area.
    \param ur_x		Upper right x coordinate of drawing area.
    \param ur_y		Upper right y coordinate of drawing area.

    If some part of object is inside the drawing area, and also outside the
    drawing area,
    the drawingarea is extended so it contains the whole objects.
  */
  void draw(GlowWind* w, int* ll_x, int* ll_y, int* ur_x, int* ur_y);

  //! Set object highlight.
  /*!
    \param on	If 1, set highlight. If 0, reset highlight.
  */
  void set_highlight(int on);

  //! Get the object type
  /*!
    \return The type of the object.
  */
  glow_eObjectType type()
  {
    return glow_eObjectType_GrowBarChart;
  }

  int bars; //!< Number of bars.
  int barsegments; //!< Number of bar parts.
  double min_value; //!< Range mininum value
  double max_value; //!< Range maximum value
  int vertical_lines; //!< Number of vertical lines
  int horizontal_lines; //!< Number of horizontal lines
  glow_eDrawType line_color; //!< Color of vertical and horizontal lines
  glow_eDrawType bar_color[BARCHART_MAX_BARSEGMENTS]; //!< Bar color.
  float bar_values[BARCHART_MAX_BARSEGMENTS][BARCHART_MAX_BARS]; //!< Bar size
  GlowTraceData trace; //!< Obsolete

  //! Draw the object.
  /*!
    \param t		Transform of parent node. Can be zero.
    \param highlight	Draw with highlight colors.
    \param hot		Draw as hot, with larger line width.
    \param node		Parent node. Can be zero.
    \param colornode	The node that controls the color of the object. Can be
    zero.

    The object is drawn with border, fill and shadow. If t is not zero, the
    current tranform is
    multiplied with the parentnodes transform, to give the appropriate
    coordinates for the drawing.
  */
  void draw(GlowWind* w, GlowTransform* t, int highlight, int hot, void* node,
      void* colornode, void *transpnode);

  //! Redraw the area inside the objects border.
  void draw();

  //! Moves object to alignment line or point.
  /*!
    \param x	x coordinate of alignment point.
    \param y	y coordinate of alignment point.
    \param direction Type of alignment.
  */
  void align(double x, double y, glow_eAlignDirection direction);

  void set_conf(int bar_num, int barsegment_num, double min_val, double max_val,
      int vert_lines, int horiz_lines, glow_eDrawType lcolor,
      glow_eDrawType* color);
  void get_conf(int* bars, int* barsegments, double* min_val, double* max_val);
  void set_values(float* values1, float* values2, float* values3,
      float* values4, float* values5, float* values6, float* values7,
      float* values8, float* values9, float* values10, float* values11,
      float* values12);

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
  void export_javabean(GlowTransform* t, void* node, glow_eExportPass pass,
      int* shape_cnt, int node_cnt, int in_nc, std::ofstream& fp);

  //! Set configuration values for the barchart.
  void set_conf(double max_val, double min_val, int no_of_lines, int long_quot,
      int value_quot, double rot, const char* format);

  //! Conversion between different versions of Glow
  /*!
    \param version	Version to convert to.
  */
  void convert(glow_eConvert version);
};

/*@}*/
#endif
