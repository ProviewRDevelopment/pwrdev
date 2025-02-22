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

/* wb_c_ai.c -- work bench methods of the Ai class. */

#include "pwr_baseclasses.h"

#include "co_dcli.h"
#include "co_string.h"

#include "wb_pwrs.h"
#include "wb_pwrb_msg.h"
#include "wb_session.h"
#include "wb_wsx.h"

/*----------------------------------------------------------------------------*\
  Syntax check.
\*----------------------------------------------------------------------------*/

static pwr_tStatus SyntaxCheck(
    ldh_tSesContext Session, pwr_tAttrRef Object, /* current object */
    int* ErrorCount, /* accumulated error count */
    int* WarningCount /* accumulated waring count */
    )
{
  wb_session* sp = (wb_session*)Session;
  pwr_tString80 str;

  wb_object o = sp->object(Object.Objid);
  wb_object p = o.parent();
  if (!(!p || p.oid().oix == 0))
    wsx_error_msg_str(
        Session, "Not on top level", Object, 'E', ErrorCount, WarningCount);

  if (Object.Objid.vid != ldh_cDirectoryVolume)
    wsx_error_msg_str(Session, "Not a DirectoryVolume", Object, 'E', ErrorCount,
        WarningCount);

  // Check SystemName
  wb_attribute a = sp->attribute(Object.Objid, "SysBody", "SystemName");
  if (!a)
    return a.sts();

  a.value(&str);
  if (!a)
    return a.sts();

  str_trim(str, str);
  if (streq(str, ""))
    wsx_error_msg_str(Session, "SystemName is missing", Object, 'E', ErrorCount,
        WarningCount);

  // Check SystemGroup
  a = sp->attribute(Object.Objid, "SysBody", "SystemGroup");
  if (!a)
    return a.sts();

  a.value(&str);
  if (!a)
    return a.sts();

  str_trim(str, str);
  if (streq(str, ""))
    wsx_error_msg_str(Session, "SystemGroup is missing", Object, 'E',
        ErrorCount, WarningCount);

  return PWRB__SUCCESS;
}

/*----------------------------------------------------------------------------*\
  Every method to be exported to the workbench should be registred here.
\*----------------------------------------------------------------------------*/

pwr_dExport pwr_BindMethods($System)
    = { pwr_BindMethod(SyntaxCheck), pwr_NullMethod };
