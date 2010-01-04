/** 
 * Proview   $Id: co_xhelpnav_gtk.h,v 1.1 2007-01-04 07:51:41 claes Exp $
 * Copyright (C) 2005 SSAB Oxel�sund AB.
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
 * along with the program, if not, write to the Free Software 
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 **/

#ifndef cow_xhelpnav_motif_h
#define cow_xhelpnav_motif_h

/* cow_xhelpnav_motif.h -- Helptext navigator */

#include <gtk/gtk.h>

#ifndef pwr_h
# include "pwr.h"
#endif

#ifndef cow_xhelpnav_h
#include "cow_xhelpnav.h"
#endif

class CoXHelpNavGtk : public CoXHelpNav {
  public:
    CoXHelpNavGtk(
	void *xn_parent_ctx,
	GtkWidget *xn_parent_wid,
	char *xn_name,
	xhelp_eUtility xn_utility,
	GtkWidget **w,
	pwr_tStatus *status);
    ~CoXHelpNavGtk();

    GtkWidget		*parent_wid;
    GtkWidget		*brow_widget;
    GtkWidget		*form_widget;
    GtkWidget		*toplevel;

    void set_inputfocus();
    void pop();
};


#endif


