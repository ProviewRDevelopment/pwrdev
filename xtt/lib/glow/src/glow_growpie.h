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

#ifndef glow_growpie_h
#define glow_growpie_h

#include "glow_growarc.h"

/*! \file glow_growpie.h
    \brief Contains the GrowPie class. */
/*! \addtogroup Glow */
/*@{*/

#define PIE_MAX_SECTORS 12

//! Class for drawing a pie object.
/*! A GrowPie object is an object that displays a pie chart.

  The GrowPie class contains function for drawing the object, and handle events
  when the
  object is clicked on, moved etc.
*/
class GrowPie : public GrowArc {
public:
  //! Constuctor
  /*!
    \param glow_ctx 	The glow context.
    \param name		Name (max 31 char).
    \param x1		x coordinate for first corner.
    \param y1		y coordinate for first corner.
    \param x2		x coordinate for second corner.
    \param y2		y coordinate for second corner.
    \param border_d_type Border color.
    \param line_w	Linewidth of border.
    \param nodraw	Don't draw the object now.
  */
  GrowPie(GrowCtx* glow_ctx, const char* name, double x1 = 0, double y1 = 0,
      double x2 = 0, double y2 = 0, int ang1 = 0, int ang2 = 0,
      glow_eDrawType border_d_type = glow_eDrawType_Line, int line_w = 1,
      int display_border = 1, int display_shadow = 0,
      glow_eDrawType fill_d_type = glow_eDrawType_Line, int nodraw = 0);

  //! Destructor
  /*! Remove the object from context, and erase it from the screen.
   */
  ~GrowPie();

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
    return glow_eObjectType_GrowPie;
  }

  int sectors; //!< Number of sectors.
  double min_value; //!< Range mininum value
  double max_value; //!< Range maximum value
  glow_eDrawType sector_color[PIE_MAX_SECTORS]; //!< Sector color.
  double sector_size[PIE_MAX_SECTORS]; //!< Sector size in range 0-1.
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

  void set_conf(
      int sectors, double min_val, double max_val, glow_eDrawType* color);
  void get_conf(int* sectors, double* min_val, double* max_val);
  void set_values(double* values);

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

  //! Set configuration values for the pie.
  void set_conf(double max_val, double min_val, int no_of_lines, int long_quot,
      int value_quot, double rot, const char* format);

  int export_script(GlowExportScript* es, void* o, void* m);

  //! Conversion between different versions of Glow
  /*!
    \param version	Version to convert to.
  */
  void convert(glow_eConvert version);
};

/*@}*/
#endif
