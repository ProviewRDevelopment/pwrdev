/* 
 * Proview   Open Source Process Control.
 * Copyright (C) 2005-2016 SSAB EMEA AB.
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

#include <stdlib.h>
#include "glow_std.h"

#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>
#include "glow_keyboardwidget_gtk.h"
#include "glow.h"
#include "glow_ctx.h"
#include "glow_keyboardctx.h"
#include "glow_draw.h"
#include "glow_draw_gtk.h"

typedef struct _KeyboardWidgetGtk      	KeyboardWidgetGtk;
typedef struct _KeyboardWidgetGtkClass	KeyboardWidgetGtkClass;

struct _KeyboardWidgetGtk {
  GtkDrawingArea parent;

  /* Private */
  void		*keyboard_ctx;
  void 		*draw_ctx;
  int		(*init_proc)(GlowCtx *ctx, void *clien_data);
  int		is_navigator;
  void		*client_data;
  GtkWidget	*main_keyboard_widget;
  GtkWidget    	*form;
};

struct _KeyboardWidgetGtkClass {
  GtkDrawingAreaClass parent_class;
};

G_DEFINE_TYPE( KeyboardWidgetGtk, keyboardwidgetgtk, GTK_TYPE_DRAWING_AREA);

static int keyboard_init_proc( GtkWidget *w, GlowCtx *fctx, void *client_data)
{
  KeyboardCtx	*ctx;

  ctx = (KeyboardCtx *) ((KeyboardWidgetGtk *) w)->keyboard_ctx;

  ctx->configure();

  if ( ((KeyboardWidgetGtk *) w)->init_proc)
    return (((KeyboardWidgetGtk *) w)->init_proc)( ctx, client_data);
  else
    return 1;
}

static gboolean keyboardwidgetgtk_expose( GtkWidget *glow, GdkEventExpose *event)
{
  ((GlowDrawGtk *)((KeyboardCtx *)((KeyboardWidgetGtk *)glow)->keyboard_ctx)->gdraw)->event_handler( 
					*(GdkEvent *)event);
  return TRUE;
}

static void keyboardwidgetgtk_destroy( GtkObject *object)
{
  KeyboardWidgetGtk *keyboard = (KeyboardWidgetGtk *)object;

  if ( keyboard->is_navigator && keyboard->keyboard_ctx) {
    ((KeyboardCtx *)keyboard->keyboard_ctx)->no_nav = 1;
  }
  GTK_OBJECT_CLASS( keyboardwidgetgtk_parent_class)->destroy( object);
}


static gboolean keyboardwidgetgtk_event( GtkWidget *glow, GdkEvent *event)
{
  if ( event->type == GDK_MOTION_NOTIFY) {
    GdkEvent *next = gdk_event_peek();
    if ( next && next->type == GDK_MOTION_NOTIFY) {
      gdk_event_free( next);
      return TRUE;
    }
    else if ( next)
      gdk_event_free( next);
  }

  ((GlowDrawGtk *)((KeyboardCtx *)((KeyboardWidgetGtk *)glow)->keyboard_ctx)->gdraw)->event_handler( *event);
  return TRUE;
}

static void keyboardwidgetgtk_realize( GtkWidget *widget)
{
  GdkWindowAttr attr;
  gint attr_mask;
  KeyboardWidgetGtk *keyboard;

  g_return_if_fail (widget != NULL);
  g_return_if_fail (IS_KEYBOARDWIDGETGTK( widget));

  GTK_WIDGET_SET_FLAGS( widget, GTK_REALIZED);
  keyboard = KEYBOARDWIDGETGTK( widget);

  attr.x = widget->allocation.x;
  attr.y = widget->allocation.y;
  attr.width = widget->allocation.width;
  attr.height = widget->allocation.height;
  attr.wclass = GDK_INPUT_OUTPUT;
  attr.window_type = GDK_WINDOW_CHILD;
  attr.event_mask = gtk_widget_get_events( widget) |
    GDK_EXPOSURE_MASK | 
    GDK_BUTTON_PRESS_MASK | 
    GDK_BUTTON_RELEASE_MASK | 
    GDK_KEY_PRESS_MASK |
    GDK_POINTER_MOTION_MASK |
    GDK_BUTTON_MOTION_MASK |
    GDK_ENTER_NOTIFY_MASK |
    GDK_LEAVE_NOTIFY_MASK;
  attr.visual = gtk_widget_get_visual( widget);
  attr.colormap = gtk_widget_get_colormap( widget);

  attr_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
  widget->window = gdk_window_new( widget->parent->window, &attr, attr_mask);
  widget->style = gtk_style_attach( widget->style, widget->window);
  gdk_window_set_user_data( widget->window, widget);
  gtk_style_set_background( widget->style, widget->window, GTK_STATE_ACTIVE);

  GTK_WIDGET_SET_FLAGS( widget, GTK_CAN_FOCUS);

  if ( keyboard->is_navigator) {
    if ( !keyboard->keyboard_ctx) {
      KeyboardWidgetGtk *main_keyboard = (KeyboardWidgetGtk *) keyboard->main_keyboard_widget;

      keyboard->keyboard_ctx = main_keyboard->keyboard_ctx;
      keyboard->draw_ctx = main_keyboard->draw_ctx;
      ((GlowDrawGtk *)keyboard->draw_ctx)->init_nav( widget);
    }
  }
  else {
    if ( !keyboard->keyboard_ctx) {
      keyboard->draw_ctx = new GlowDrawGtk( widget, 
					&keyboard->keyboard_ctx, 
					keyboard_init_proc, 
					keyboard->client_data,
					glow_eCtxType_Keyboard);
    }
  }

}

static void keyboardwidgetgtk_class_init( KeyboardWidgetGtkClass *klass)
{
  GtkWidgetClass *widget_class;
  GtkObjectClass *object_class;
  widget_class = GTK_WIDGET_CLASS( klass);
  object_class = GTK_OBJECT_CLASS(klass);
  widget_class->realize = keyboardwidgetgtk_realize;
  widget_class->expose_event = keyboardwidgetgtk_expose;
  widget_class->event = keyboardwidgetgtk_event;
  object_class->destroy = keyboardwidgetgtk_destroy;
}

static void keyboardwidgetgtk_init( KeyboardWidgetGtk *glow)
{
}

GtkWidget *keyboardwidgetgtk_new(
        int (*init_proc)(GlowCtx *ctx, void *client_data),
	void *client_data)
{
  KeyboardWidgetGtk *w;
  w =  (KeyboardWidgetGtk *) g_object_new( KEYBOARDWIDGETGTK_TYPE, NULL);
  w->init_proc = init_proc;
  w->keyboard_ctx = 0;
  w->is_navigator = 0;
  w->client_data = client_data;
  return (GtkWidget *) w;  
}


GtkWidget *keyboardnavwidgetgtk_new( GtkWidget *main_keyboard)
{
  KeyboardWidgetGtk *w;
  w =  (KeyboardWidgetGtk *) g_object_new( KEYBOARDWIDGETGTK_TYPE, NULL);
  w->init_proc = 0;
  w->keyboard_ctx = 0;
  w->is_navigator = 1;
  w->main_keyboard_widget = main_keyboard;
  w->client_data = 0;
  return (GtkWidget *) w;  
}

#if 0
GType keyboardwidgetgtk_get_type(void)
{
  static GType keyboardwidgetgtk_type = 0;

  if ( !keyboardwidgetgtk_type) {
    static const GTypeInfo keyboardwidgetgtk_info = {
      sizeof(KeyboardWidgetGtkClass), NULL, NULL, (GClassInitFunc)keyboardwidgetgtk_class_init,
      NULL, NULL, sizeof(KeyboardWidgetGtk), 1, NULL, NULL};
    
    keyboardwidgetgtk_type = g_type_register_static( G_TYPE_OBJECT, "KeyboardWidgetGtk", &keyboardwidgetgtk_info, 
					   (GTypeFlags)0);  
  }
  return keyboardwidgetgtk_type;
}
#endif