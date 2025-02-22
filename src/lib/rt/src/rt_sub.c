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

/* rt_sub.c
   This module contains routines to handle subscription.
   Those routines can be called from the GDH API.  */

#include "rt_gdh_msg.h"
#include "rt_hash_msg.h"
#include "co_tree.h"
#include "rt_vol.h"
#include "rt_sub.h"
#include "rt_dl.h"

/* Updates all server buffers that are connected to this object.  */

void sub_UnlinkObject(gdb_sObject* op)
{
  sub_sServer* sp;
  pool_sQlink* sl;

  for (sl = pool_Qsucc(NULL, gdbroot->pool, &gdbroot->db->subs_lh);
       sl != &gdbroot->db->subs_lh; sl = pool_Qsucc(NULL, gdbroot->pool, sl)) {
    sp = pool_Qitem(sl, sub_sServer, subs_ll);
    if (cdh_ObjidIsEqual(sp->aref.Objid, op->g.oid)) {
      sp->data = pool_cNRef;
      sp->sts = GDH__NOSUCHOBJ;

      if (op->u.n.subcount
          > 0) /* Subscriptions on invalid offset will allocate buffer without
                  increasing count */
        op->u.n.subcount--;
    }
  }

  pwr_Assert(op->u.n.subcount == 0);
}
