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

#ifndef glow_growdashcell_h
#define glow_growdashcell_h

#include "glow_growgroup.h"
#include "glow_growrect.h"

/*! \file glow_growdashcell.h
    \brief Contains the GrowDashCell class. */
/*! \addtogroup Glow */
/*@{*/

//! Class for handling a dashboard cell.
/*! A GrowDashCell object is an object that is built of other object or groups.
  The GrowDashCell class contains function for drawing the object, and handle
  events when the
  object is clicked on, moved etc.
*/
class GrowDashCell : public GrowGroup {
public:
  GrowRect *frame;
  int cell_rows;
  int cell_columns;
  int cell_rows_old;
  int cell_columns_old;

  //! Constuctor
  /*!
    \param glow_ctx 	The glow context.
    \param name		Name (max 31 char).
    \param array	Array with group member objects.
    \param nodraw	Don't draw the object now.
  */
  GrowDashCell(
      GrowCtx* glow_ctx, const char* name, double x, double y, double w, double h, 
      glow_eDrawType border_d_type, int nodraw = 0);

  //! Noargs constructor.
  GrowDashCell(){}

  GrowDashCell(GrowCtx* glow_ctx, const char* name);
  ~GrowDashCell();

  //! Make this object a copy of another image object.
  /*!
    \param n	Object to copy.
  */
  void copy_from(const GrowDashCell& n);

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

  //! Conversion between different versions of Glow
  /*!
    \param version	Version to convert to.
  */
  void convert(glow_eConvert version);

  int order_object(GlowArrayElem* o, GlowArrayElem* dest, glow_eDest code)
  {
    return nc->a.move(o, dest, code);
  }

  void update_attributes();

  void get_node_borders();
  
  void get_borders(GlowTransform* t, double* x1_right, double* x1_left,
      double* y1_high, double* y1_low);

  void draw(GlowWind* w, GlowTransform* t, int highlight, int hot,
      void* node, void* colornode, void *transpnode);

  int local_event_handler(glow_eEvent event, double x, double y);

  int event_handler(GlowWind* w, glow_eEvent event, double fx, double fy);

  int event_handler(GlowWind* w, glow_eEvent event, int x, int y, double fx, double fy);

  void get_info(int *rows, int *columns);

  int trace_init();

  int insert(GlowArrayElem* element);

};

/*@}*/
#endif
