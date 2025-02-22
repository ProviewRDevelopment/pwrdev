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

#include <stdlib.h>

#include "co_cdh.h"
#include "co_dcli.h"
#include "co_string.h"
#include "co_time.h"

#include "rt_gdh.h"
#include "rt_gdh_msg.h"

#include "ge_graph_gtk.h"

#include "wb_wge_gtk.h"

gboolean WGeGtk::action_inputfocus(GtkWidget* w, GdkEvent* event, gpointer data)
{
  WGeGtk* ge = (WGeGtk*)data;

  if (ge->focustimer.disabled())
    return FALSE;

  if (ge->graph)
    ((Graph*)ge->graph)->set_inputfocus(1);

  ge->focustimer.disable(400);
  return FALSE;
}

void WGeGtk::change_value_cb(void* ge_ctx, void* value_object, char* text)
{
  WGeGtk* ge = (WGeGtk*)ge_ctx;

  if (ge->value_input_open) {
    g_object_set(ge->value_dialog, "visible", FALSE, NULL);
    ge->value_input_open = 0;
    return;
  }

  g_object_set(ge->value_dialog, "visible", TRUE, NULL);

  message(ge, ' ', "");
  gtk_widget_grab_focus(ge->value_input);

  gint pos = 0;
  gtk_editable_delete_text(GTK_EDITABLE(ge->value_input), 0, -1);
  gtk_editable_insert_text(
      GTK_EDITABLE(ge->value_input), text, strlen(text), &pos);
  gtk_editable_set_position(GTK_EDITABLE(ge->value_input), -1);
  gtk_editable_select_region(GTK_EDITABLE(ge->value_input), 0, -1);

  ge->value_input_open = 1;
  ge->current_value_object = value_object;
}

void WGeGtk::confirm_cb(void* ge_ctx, void* confirm_object, char* text)
{
  WGe* ge = (WGe*)ge_ctx;

  if (ge->confirm_open) {
    g_object_set(((WGeGtk*)ge)->confirm_widget, "visible", FALSE, NULL);
    ge->confirm_open = 0;
    return;
  }

  ((WGeGtk*)ge)->create_confirm_dialog();

  message(ge, ' ', "");

  gtk_label_set_text(GTK_LABEL(((WGeGtk*)ge)->confirm_label), text);
  ge->confirm_open = 1;
  ge->current_confirm_object = confirm_object;
}

void WGeGtk::message_dialog_cb(void* ge_ctx, const char* text)
{
  WGe* ge = (WGe*)ge_ctx;

  g_object_set(((WGeGtk*)ge)->message_dia_widget, "visible", TRUE, NULL);

  gtk_label_set_text(GTK_LABEL(((WGeGtk*)ge)->message_dia_label), text);
}

void WGeGtk::activate_value_input(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;
  char* text;

  text = gtk_editable_get_chars(GTK_EDITABLE(w), 0, -1);
  if (ge->value_input_open) {
    ((Graph*)ge->graph)->change_value(ge->current_value_object, text);
    g_object_set(((WGeGtk*)ge)->value_dialog, "visible", FALSE, NULL);
    ge->value_input_open = 0;
  }
  g_free(text);
}

void WGeGtk::activate_confirm_ok(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;

  g_object_set(((WGeGtk*)ge)->confirm_widget, "visible", FALSE, NULL);
  ge->confirm_open = 0;
  ((Graph*)ge->graph)->confirm_ok(ge->current_confirm_object);
}

void WGeGtk::activate_confirm_cancel(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;

  ge->confirm_open = 0;
  g_object_set(((WGeGtk*)ge)->confirm_widget, "visible", FALSE, NULL);
}

void WGeGtk::activate_exit(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;

  if (ge->modal) {
    ge->terminated = 1;
    gtk_main_quit();
  } else
    delete ge;
}

void WGeGtk::activate_zoom_in(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;

  ((Graph*)ge->graph)->zoom(1.2);
}

void WGeGtk::activate_zoom_out(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;

  ((Graph*)ge->graph)->zoom(5.0 / 6);
}

void WGeGtk::activate_zoom_reset(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;

  ((Graph*)ge->graph)->unzoom();
}

void WGeGtk::activate_help(GtkWidget* w, gpointer data)
{
  WGe* ge = (WGe*)data;
  char key[80];

  if (ge->help_cb) {
    str_ToLower(key, ge->name);
    (ge->help_cb)(ge, key);
  }
}

void WGeGtk::action_resize(
    GtkWidget* w, GtkAllocation* allocation, gpointer data)
{
  WGe* ge = (WGe*)data;

  if (ge->graph && !ge->scrollbar && !ge->navigator && ge->graph->grow)
    ge->graph->set_default_layout();
}

WGeGtk::~WGeGtk()
{
  if (close_cb)
    (close_cb)((void*)this);
  if (confirm_widget)
    gtk_widget_destroy(confirm_widget);
  if (nav_shell)
    gtk_widget_destroy(nav_shell);
  delete graph;
  gtk_widget_destroy(toplevel);
}

void WGeGtk::set_size(int width, int height)
{
  int default_width;
  int default_height;
  GdkGeometry geometry;

  default_width = width + 20;
  default_height = height + 20;

  gtk_window_resize(GTK_WINDOW(toplevel), default_width, default_height);

  geometry.min_aspect = gdouble(default_width) / default_height * 0.95;
  geometry.max_aspect = gdouble(default_width) / default_height * 1.05;
  gtk_window_set_geometry_hints(
      GTK_WINDOW(toplevel), GTK_WIDGET(toplevel), &geometry, GDK_HINT_ASPECT);

  // if ( !scrollbar && !navigator)
  //  graph->set_default_layout();
}

void WGeGtk::set_subwindow_release()
{
  subwindow_release = 1;
  gtk_main_quit();
}

void WGeGtk::pop()
{
  gtk_window_present(GTK_WINDOW(toplevel));
}

static gint delete_event(GtkWidget* w, GdkEvent* event, gpointer wge)
{
  WGeGtk::activate_exit(w, wge);

  return TRUE;
}

static void destroy_event(GtkWidget* w, gpointer data)
{
}

static gint nav_delete_event(GtkWidget* w, GdkEvent* event, gpointer wge)
{
  return TRUE;
}

WGeGtk::WGeGtk(GtkWidget* wge_parent_wid, void* wge_parent_ctx, char* wge_name,
    char* wge_filename, int wge_scrollbar, int wge_menu, int wge_navigator,
    int wge_width, int wge_height, int x, int y, char* object_name,
    int wge_modal = 0)
    : WGe(wge_parent_ctx, wge_name, wge_filename, wge_scrollbar, wge_menu,
          wge_navigator, wge_width, wge_height, x, y, object_name, wge_modal),
      parent_wid(wge_parent_wid), nav_shell(0), value_dialog(0),
      confirm_widget(0)
{
  int window_width = 600;
  int window_height = 500;
  GdkGeometry geometry;
  pwr_tStatus sts;
  GtkMenuBar* menu_bar = NULL;
  char title[300];

  if (wge_width != 0 && wge_height != 0) {
    window_width = wge_width;
    window_height = wge_height;
  }
  str_StrncpyCutOff(title, name, sizeof(title), 1);

  // Gtk
  toplevel = (GtkWidget*)g_object_new(GTK_TYPE_WINDOW, "default-height",
      window_height, "default-width", window_width, "title", title, NULL);

  CoWowGtk::SetWindowIcon(toplevel);

  geometry.min_aspect = gdouble(window_width) / window_height * 0.95;
  geometry.max_aspect = gdouble(window_width) / window_height * 1.05;
  gtk_window_set_geometry_hints(
      GTK_WINDOW(toplevel), GTK_WIDGET(toplevel), &geometry, GDK_HINT_ASPECT);

  if (!(x == 0 && y == 0)) {
    // Set position...
  }

  g_signal_connect(toplevel, "delete_event", G_CALLBACK(delete_event), this);
  g_signal_connect(toplevel, "destroy", G_CALLBACK(destroy_event), this);
  g_signal_connect(
      toplevel, "focus-in-event", G_CALLBACK(action_inputfocus), this);

  if (wge_menu) {
    GtkAccelGroup* accel_g
        = (GtkAccelGroup*)g_object_new(GTK_TYPE_ACCEL_GROUP, NULL);
    gtk_window_add_accel_group(GTK_WINDOW(toplevel), accel_g);

    menu_bar = (GtkMenuBar*)g_object_new(GTK_TYPE_MENU_BAR, NULL);

    // File Entry
    GtkWidget* file_close = gtk_menu_item_new_with_mnemonic("_Close");
    g_signal_connect(file_close, "activate", G_CALLBACK(activate_exit), this);
    gtk_widget_add_accelerator(file_close, "activate", accel_g, 'w',
	GdkModifierType(GDK_CONTROL_MASK), GTK_ACCEL_VISIBLE);

    GtkMenu* file_menu = (GtkMenu*)g_object_new(GTK_TYPE_MENU, NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), file_close);

    GtkWidget* file = gtk_menu_item_new_with_mnemonic("_File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), GTK_WIDGET(file_menu));

    // View menu
    GtkWidget* view_zoom_in = gtk_menu_item_new_with_mnemonic("Zoom _in");
    g_signal_connect(view_zoom_in, "activate", G_CALLBACK(activate_zoom_in), this);
    gtk_widget_add_accelerator(view_zoom_in, "activate", accel_g, 'i',
	GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

    GtkWidget* view_zoom_out = gtk_menu_item_new_with_mnemonic("Zoom _out");
    g_signal_connect(view_zoom_out, "activate", G_CALLBACK(activate_zoom_out), this);
    gtk_widget_add_accelerator(view_zoom_out, "activate", accel_g, 'o',
        GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

    GtkWidget* view_zoom_reset = gtk_menu_item_new_with_mnemonic("Zoom _reset");
    g_signal_connect(view_zoom_reset, "activate", G_CALLBACK(activate_zoom_reset), this);

    GtkMenu* view_menu = (GtkMenu*)g_object_new(GTK_TYPE_MENU, NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(view_menu), view_zoom_in);
    gtk_menu_shell_append(GTK_MENU_SHELL(view_menu), view_zoom_out);
    gtk_menu_shell_append(GTK_MENU_SHELL(view_menu), view_zoom_reset);

    GtkWidget* view = gtk_menu_item_new_with_mnemonic("_View");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), view);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(view), GTK_WIDGET(view_menu));

    // Menu Help
    GtkWidget* help_help = gtk_menu_item_new_with_mnemonic("_Help");
    g_signal_connect(help_help, "activate", G_CALLBACK(activate_help), this);
    gtk_widget_add_accelerator(help_help, "activate", accel_g, 'h',
	GdkModifierType(GDK_CONTROL_MASK), GTK_ACCEL_VISIBLE);

    GtkMenu* help_menu = (GtkMenu*)g_object_new(GTK_TYPE_MENU, NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), help_help);

    GtkWidget* help = gtk_menu_item_new_with_mnemonic("_Help");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), GTK_WIDGET(help_menu));
  }

  graph_form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  graph = new GraphGtk(this, graph_form, "Plant", &grow_widget, &sts,
      "pwrp_exe:", graph_eMode_Runtime, scrollbar, 1, object_name, 0, 0);
  ((Graph*)graph)->message_cb = &message;
  ((Graph*)graph)->close_cb = &graph_close_cb;
  ((Graph*)graph)->init_cb = &graph_init_cb;
  ((Graph*)graph)->change_value_cb = &change_value_cb;
  ((Graph*)graph)->confirm_cb = &confirm_cb;
  ((Graph*)graph)->message_dialog_cb = &message_dialog_cb;
  ((Graph*)graph)->command_cb = &wge_command_cb;
  ((Graph*)graph)->is_authorized_cb = &wge_is_authorized_cb;

  // g_signal_connect( graph_form, "check_resize", G_CALLBACK(action_resize),
  // this);
  g_signal_connect(((GraphGtk*)graph)->grow_widget, "size_allocate",
      G_CALLBACK(action_resize), this);

  if (wge_menu)
    gtk_box_pack_start(
        GTK_BOX(graph_form), GTK_WIDGET(menu_bar), FALSE, FALSE, 0);
  gtk_box_pack_start(
      GTK_BOX(graph_form), GTK_WIDGET(grow_widget), TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(toplevel), graph_form);

  gtk_widget_show_all(toplevel);

  if (navigator) {
    // Create navigator popup
    nav_shell = (GtkWidget*)g_object_new(GTK_TYPE_WINDOW, "default-height", 200,
        "default-width", 200, "title", "Navigator", NULL);
    g_signal_connect(
        nav_shell, "delete_event", G_CALLBACK(nav_delete_event), this);

    ((GraphGtk*)graph)->create_navigator(nav_shell);
    gtk_container_add(GTK_CONTAINER(nav_shell), ((GraphGtk*)graph)->nav_widget);

    gtk_widget_show_all(nav_shell);
    ((Graph*)graph)->set_nav_background_color();
  }
}

static gint confirm_delete_event(GtkWidget* w, GdkEvent* event, gpointer wge)
{
  g_object_set(((WGeGtk*)wge)->confirm_widget, "visible", FALSE, NULL);
  return TRUE;
}

void WGeGtk::create_confirm_dialog()
{
  if (confirm_widget) {
    g_object_set(confirm_widget, "visible", TRUE, NULL);
    return;
  }

  // Create a confirm window
  confirm_widget = (GtkWidget*)g_object_new(GTK_TYPE_WINDOW, "default-height",
      150, "default-width", 400, "title", "Confirm", NULL);
  g_signal_connect(
      confirm_widget, "delete_event", G_CALLBACK(confirm_delete_event), this);
  confirm_label = gtk_label_new("");

  pwr_tFileName fname;
  dcli_translate_filename(fname, "$pwr_exe/xtt_question.png");
  GtkWidget* confirm_image = gtk_image_new_from_file(fname);

  GtkWidget* confirm_ok = gtk_button_new_with_label("Yes");
  gtk_widget_set_size_request(confirm_ok, 70, 25);
  g_signal_connect(
      confirm_ok, "clicked", G_CALLBACK(activate_confirm_ok), this);

  GtkWidget* confirm_cancel = gtk_button_new_with_label("No");
  gtk_widget_set_size_request(confirm_cancel, 70, 25);
  g_signal_connect(
      confirm_cancel, "clicked", G_CALLBACK(activate_confirm_cancel), this);

  GtkWidget* confirm_hboxtext = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(
      GTK_BOX(confirm_hboxtext), confirm_image, FALSE, FALSE, 15);
  gtk_box_pack_start(GTK_BOX(confirm_hboxtext), confirm_label, TRUE, TRUE, 15);

  GtkWidget* confirm_hboxbuttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 40);
  gtk_box_pack_start(GTK_BOX(confirm_hboxbuttons), confirm_ok, FALSE, FALSE, 0);
  gtk_box_pack_end(
      GTK_BOX(confirm_hboxbuttons), confirm_cancel, FALSE, FALSE, 0);

  GtkWidget* confirm_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(confirm_vbox), confirm_hboxtext, TRUE, TRUE, 30);
  gtk_box_pack_start(
      GTK_BOX(confirm_vbox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL), FALSE, FALSE, 0);
  gtk_box_pack_end(
      GTK_BOX(confirm_vbox), confirm_hboxbuttons, FALSE, FALSE, 15);
  gtk_container_add(GTK_CONTAINER(confirm_widget), confirm_vbox);
  gtk_widget_show_all(confirm_widget);
}
