/* 
 * Proview   Open Source Process Control.
 * Copyright (C) 2005-2017 SSAB EMEA AB.
 *
 * This file is part of Proview.
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
 * along with Proview. If not, see <http://www.gnu.org/licenses/>
 *
 * Linking Proview statically or dynamically with other modules is
 * making a combined work based on Proview. Thus, the terms and 
 * conditions of the GNU General Public License cover the whole 
 * combination.
 *
 * In addition, as a special exception, the copyright holders of
 * Proview give you permission to, from the build function in the
 * Proview Configurator, combine Proview with modules generated by the
 * Proview PLC Editor to a PLC program, regardless of the license
 * terms of these modules. You may copy and distribute the resulting
 * combined work under the terms of your choice, provided that every 
 * copy of the combined work is accompanied by a complete copy of 
 * the source code of Proview (the version used to produce the 
 * combined work), being distributed under the terms of the GNU 
 * General Public License plus this exception.
 **/

#ifndef wb_wrev_h
#define wb_wrev_h

/* wb_wrev.h -- Revision window */

#ifndef pwr_h
# include "pwr.h"
#endif

#ifndef wb_utility_h
# include "wb_utility.h"
#endif

#ifndef wb_ldh_h
# include "wb_ldh.h"
#endif

#ifndef wb_revision_h
# include "wb_wrevnav.h"
#endif

class WRevNav;
class CoWow;

class WRev {
  public:
    WRev(  void *wa_parent_ctx, ldh_tSession wa_ldhses);
    virtual ~WRev();
    void 	*parent_ctx;
    ldh_tSession ldhses;
    char 	name[80];
    WRevNav	*wrevnav;
    void	(*close_cb) ( void *);
    int		(*command_cb) ( void *, char *);
    void 	(*india_ok_cb)( WRev *, char *, char *);
    wb_eUtility	utility;
    CoWow	*wow;
    int		dialog_count;

    void activate_store();
    void activate_restore();
    void activate_delete();
    void activate_build();
    void activate_zoom_in();
    void activate_zoom_out();
    void activate_zoom_reset();
    void next_name( char *name);

    virtual void message( char severity, const char *message) {}
    virtual void pop() {}
    virtual void set_clock_cursor() {}
    virtual void reset_cursor() {}
    virtual void flush() {}
    virtual void open_input_dialog( const char *text1, const char *text2, const char *title,
				    const char *init_text1, const char *init_text2,
				    void (*ok_cb)( WRev *, char *, char *)) {}

    static void message_cb( void *wrev, char severity, const char *message);
    static void set_clock_cursor_cb( void *wrev);
    static void reset_cursor_cb( void *wrev);
    static int rev_command_cb( void *ctx, char *cmd);
    static void restore_cancel( void *ctx, void *data);
    static void restore_ok( void *ctx, void *data);
    static void delete_cancel( void *ctx, void *data);
    static void delete_ok( void *ctx, void *data);
    static void store_ok_cb( WRev *wrev, char *text1, char *text2);
};

#endif






