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

/* wb_c_opplaceweb.cpp -- work bench methods of the OpPlaceWeb class. */

#include "pwr_baseclasses.h"

#include "co_string.h"

#include "wb_pwrs.h"
#include "wb_pwrb_msg.h"
#include "wb_build.h"

static pwr_tStatus Build(ldh_sMenuCall* ip)
{
  wb_build build(*(wb_session*)ip->PointedSession, ip->wnav);

  build.opt = ip->wnav->gbl.build;
  build.opplaceweb(ip->Pointed.Objid);

  if (build.sts() == PWRB__NOBUILT)
    ip->wnav->message('I', "Nothing to build");
  return build.sts();
}

static pwr_tStatus PostCreate(
    ldh_tSesContext Session, pwr_tOid Object, pwr_tOid Father, pwr_tCid Class)
{
  wb_session* sp = (wb_session*)Session;
  wb_object o = sp->object(Object);

  // Find a unique name for FileName
  int idx = 0;
  for (wb_object co = sp->object(pwr_cClass_OpPlaceWeb); co; co = co.next()) {
    pwr_tString80 filename;
    int i;

    if (cdh_ObjidIsEqual(co.oid(), o.oid()))
      continue;

    wb_attribute ca = sp->attribute(co.oid(), "RtBody", "FileName");
    if (!ca)
      return ca.sts();

    ca.value(filename);
    if ((streq(filename, "index.html")) && idx < 1)
      idx = 2;
    else if (sscanf(filename, "index%d.html", &i) != 0) {
      if (idx <= i)
        idx = i + 1;
    }
    if (idx > 0) {
      wb_attribute a = sp->attribute(o.oid(), "RtBody", "FileName");
      if (!a)
        return a.sts();

      sprintf(filename, "index%d.html", idx);
      try {
        sp->writeAttribute(a, filename, sizeof(filename));
      } catch (wb_error& e) {
        return e.sts();
      }
    }
  }

  return PWRB__SUCCESS;
}

pwr_dExport pwr_BindMethods(OpPlaceWeb)
    = { pwr_BindMethod(Build), pwr_BindMethod(PostCreate), pwr_NullMethod };
