/* 
 * Proview   $Id: co_login_motif.cpp,v 1.3 2008-10-31 12:51:30 claes Exp $
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Mrm/MrmPublic.h>
#include <X11/Intrinsic.h>

#include "co_login_msg.h"
#include "cow_login_motif.h"
#include "co_api.h"
#include "co_dcli.h"

#define	BEEP	    putchar( '\7' );

//
//	Callback from the pushbutton.
//
void CoLoginMotif::activate_ok( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data)
{
  loginctx->activate_ok();
}

//
//	Callback from the pushbutton.
//
void CoLoginMotif::activate_cancel( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data)
{
  loginctx->activate_cancel();
}

void CoLoginMotif::create_label( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data) 
{
  ((CoLoginMotif *)loginctx)->widgets.label = w;
}

void CoLoginMotif::create_adb( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data)
{
  ((CoLoginMotif *)loginctx)->widgets.adb = w;
}

void CoLoginMotif::create_usernamevalue( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data)
{
  ((CoLoginMotif *)loginctx)->widgets.usernamevalue = w;
}

void CoLoginMotif::create_passwordvalue( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data)
{
  ((CoLoginMotif *)loginctx)->widgets.passwordvalue = w;
}

//
//	Callback when value changed.
//
void CoLoginMotif::valchanged_passwordvalue( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data)
{
  char	*value;
  int	sts;
  char	*s;

  if ( ((CoLoginMotif *)loginctx)->widgets.passwordvalue == 0)
    return;

  value = XmTextGetString( ((CoLoginMotif *)loginctx)->widgets.passwordvalue);
  if ( *value == 0)
    return;

  s = strrchr( value, 10);

  if (s == 0) {
    strcat(loginctx->password, value);
    XtFree( value);
    XmTextSetString( ((CoLoginMotif *)loginctx)->widgets.passwordvalue, (char *)"");
    return;
  }
  
  loginctx->message( "");
  sts = loginctx->get_values();
  if ( ODD(sts)) {
    if (loginctx->bc_success != NULL)
      (loginctx->bc_success) ( loginctx->parent_ctx);
    XtFree( value);
    delete loginctx;
    return;
  }
  else {
    loginctx->message( "User not authorized");
    BEEP;
    printf( "User not authorized\n");
    XmTextSetString( ((CoLoginMotif *)loginctx)->widgets.passwordvalue, (char *)"");
    strcpy(loginctx->password, "");

    XtFree( value);
  }
}

//
//	Callback when value changed.
//
void CoLoginMotif::valchanged_usernamevalue( Widget w, CoLogin *loginctx, XmAnyCallbackStruct *data)
{
  char	*value;
  char	*s;

  if ( ((CoLoginMotif *)loginctx)->widgets.usernamevalue == 0)
    return;

  value = XmTextGetString( ((CoLoginMotif *)loginctx)->widgets.usernamevalue);
  if ( *value == 0)
    return;

  s = strrchr( value, 10);

  if (s == 0) 
  {
    XtFree( value);
    return;
  }
  
  loginctx->message( "");
  strcpy( s, s + 1);	
  XmTextSetString( ((CoLoginMotif *)loginctx)->widgets.usernamevalue, value);
  XtFree( value);

  /* Focus password */
  XtSetKeyboardFocus( ((CoLoginMotif *)loginctx)->widgets.toplevel,
    ((CoLoginMotif *)loginctx)->widgets.passwordvalue);
}

//
// Constructor
//
CoLoginMotif::CoLoginMotif( void		*wl_parent_ctx,
			  Widget       	wl_parent_wid,
			  const char   	*wl_name,
			  const char   	*wl_groupname,
			  void		(* wl_bc_success)( void *),
			  void		(* wl_bc_cancel)( void *),
			  pwr_tStatus  	*status) :
  CoLogin(wl_parent_ctx,wl_name,wl_groupname,wl_bc_success,wl_bc_cancel,status),
  parent_wid(wl_parent_wid)
{
  Arg	args[20];
  int	sts;
  int 	i;
  /* DRM database hierarchy related variables */
  MrmHierarchy s_DRMh;
  MrmType dclass;
  char		uid_filename[200] = {"pwr_exe:wb_login.uid"};
  char		*uid_filename_p = uid_filename;


  static MrmRegisterArg	reglist[] = {
  /* First the context variable */
  {(char *) "login_ctx", 0 },

  /* Callbacks for the controlled login widget */
  {(char *) "login_create_adb",(caddr_t)create_adb},
  {(char *) "login_create_label",(caddr_t)create_label},
  {(char *) "login_create_usernamevalue",(caddr_t)create_usernamevalue},
  {(char *) "login_create_passwordvalue",(caddr_t)create_passwordvalue},
  {(char *) "login_valchanged_usernamevalue",(caddr_t)valchanged_usernamevalue},
  {(char *) "login_valchanged_passwordvalue",(caddr_t)valchanged_passwordvalue},
  {(char *) "login_activate_ok",(caddr_t)activate_ok},
  {(char *) "login_activate_cancel",(caddr_t)activate_cancel},
  };

  static int	reglist_num = (sizeof reglist / sizeof reglist[0]);

  sts = dcli_translate_filename( uid_filename, uid_filename);
  if ( EVEN(sts))
  {
    printf( "** pwr_exe is not defined\n");
    exit(0);
  }

/*
 * Now start the module creation
 */

  /* Save the context structure in the widget */
  XtSetArg (args[0], XmNuserData, (XtPointer) this);

  /*
   * Create a new widget
   * Open the UID files (the output of the UIL compiler) in the hierarchy
   * Register the items DRM needs to bind for us.
   * Create a new widget
   * Close the hierarchy
   * Compile the additional button translations and augment and add actions
   */ 
  sts = MrmOpenHierarchy( 1, &uid_filename_p, NULL, &s_DRMh);
  if (sts != MrmSUCCESS) printf("can't open hierarchy\n");

  reglist[0].value = (caddr_t) this;

  MrmRegisterNames(reglist, reglist_num);

  i=0;
  XtSetArg(args[i],XmNiconName,name);  i++;
  
  /* Save the id of the top in the context */ 
  widgets.toplevel = XtCreatePopupShell (
    "login", topLevelShellWidgetClass, parent_wid, args, i);

  /* the positioning of a top level can only be define after the creation
   *   of the widget . So i do it now: 
   *  use the parameters received x and y 
   */

  i=0;
  XtSetArg(args[i],XmNx,100);i++;
  XtSetArg(args[i],XmNy,100);i++;
  XtSetArg(args[i],XtNallowShellResize,TRUE), i++;

  XtSetValues( widgets.toplevel  ,args,i);

  /* now that we have a top level we can get the main window */
  sts = MrmFetchWidgetOverride(s_DRMh, (char *)"login_window",
    widgets.toplevel, name, args, 1, 
    &widgets.login_window, &dclass);

  if (sts != MrmSUCCESS) printf("can't fetch utedit widget\n");

  XtManageChild(widgets.login_window);

  /* SG 09.02.91 a top level should always be realized ! */
  XtPopup( widgets.toplevel, XtGrabNone );

  MrmCloseHierarchy(s_DRMh);

  *status = 1;
}

//
// Destructor
//
CoLoginMotif::~CoLoginMotif()
{
  /* Destroy the widget */
  XtDestroyWidget( widgets.toplevel) ;
}

//
//	Get values in username and password.
//
pwr_tStatus CoLoginMotif::get_values()
{
  char	passwd[40];
  char	username[40];
  char	*value;
  pwr_tStatus	sts;

  /* Get UserName */
  value = XmTextGetString( widgets.usernamevalue);
  strcpy(username, value);
  XtFree( value);

  /* Get Password */
  strcpy(passwd, password);

  sts = user_check( groupname, username, passwd);
  if ( EVEN(sts))
    return sts;

  return LOGIN__SUCCESS;
}

//
//	Displays a message in the login window.
//
void CoLoginMotif::message( const char *new_label)
{
  Arg	args[2];

  XtSetArg(args[0], XmNlabelString, 
	  XmStringCreateLtoR( (char *)new_label , (char *)"ISO8859-1"));
  XtSetValues( widgets.label, args, 1);
}
