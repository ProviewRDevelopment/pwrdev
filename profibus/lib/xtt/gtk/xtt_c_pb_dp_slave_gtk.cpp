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

/* xtt_c_pb_db_slave_gtk.cpp -- xtt methods for Pb_DP_Slave. */

#include "pwr_profibusclasses.h"

#include "co_cdh.h"
#include "rt_xnav_msg.h"

#include "cow_xhelp_gtk.h"

#include "xtt_xnav.h"

#include "cow_pb_gsd_attr_gtk.h"

#include "xtt_c_pb_dp_slave.h"

// Show Configuration
static pwr_tStatus ShowConfiguration(xmenu_sMenuCall* ip)
{
  xtt_slave_sCtx* ctx;
  pwr_tStatus sts;
  int edit_mode = 0;

  sts = xtt_pb_dp_slave_create_ctx(ip->Pointed, ip->EditorContext, &ctx);
  if (EVEN(sts))
    return sts;

  ctx->attr =
      new GsdAttrGtk(CoXHelpGtk::get_widget(), ctx, 0, ctx->gsd, edit_mode);
  ctx->attr->close_cb = xtt_pb_dp_slave_close_cb;
  ctx->attr->save_cb = xtt_pb_dp_slave_save_cb;
  ctx->attr->help_cb = xtt_pb_dp_slave_help_cb;

  return 1;
}

/*----------------------------------------------------------------------------*\
  Every method to be exported to xtt should be registred here.
\*----------------------------------------------------------------------------*/

pwr_dExport pwr_BindXttMethods(Pb_DP_Slave) = {
    pwr_BindXttMethod(ShowConfiguration), pwr_NullMethod};
