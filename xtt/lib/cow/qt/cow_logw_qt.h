/**
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

#ifndef cow_logw_qt_h
#define cow_logw_qt_h

/* cow_logw_qt.h -- History log window */

#ifndef cow_logw_h
#include "cow_logw.h"
#endif

#include "cow_wow_qt.h"

class CoLogWQtWidget;

class CoLogWQt : public CoLogW {
public:
  CoLogWQt(void* msg_parent_ctx, QWidget* msg_parent_wid, const char* msg_name,
      int l_show_item, pwr_tStatus* status);

  QWidget* nav_widget;
  CoWowFocusTimerQt focustimer;
  CoWowFocusTimerQt maptimer;

  void print();

private:
  CoLogWQtWidget* toplevel;
};

class CoLogWQtWidget : public QWidget {
  Q_OBJECT

public:
  CoLogWQtWidget(CoLogWQt* parent_ctx, QWidget* parent)
      : QWidget(), logw(parent_ctx)
  {
  }

protected:
  void focusInEvent(QFocusEvent* event);
  void closeEvent(QCloseEvent* event);

public slots:
  void activate_print();
  void activate_zoom_in();
  void activate_zoom_out();
  void activate_zoom_reset();
  void activate_help();

private:
  CoLogWQt* logw;
};

#endif