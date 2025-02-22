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

/* rt_neth_acp.c -- helps net handler.

   The nethandler submitts work that cannot be done
   in the context of the neth to this program. Normally
   transactions that causes cache fetch operations.  */

#include <stdlib.h>
#include <string.h>

#include "rt_qcom_msg.h"
#include "rt_gdh_msg.h"
#include "rt_gdh.h"
#include "rt_vol.h"
#include "rt_cvolc.h"
#include "rt_sanc.h"
#include "rt_subc.h"
#include "rt_pwr_msg.h"
#include "rt_ini_event.h"

static void event(qcom_sGet* get);
static void init(qcom_sQid* qid);
static void lockMountServers(gdb_sNode* np);
static gdb_sNode* node(net_sMessage* mp);
static void nodeUp(net_sNodeUp* mp);
static void* receive(qcom_sQid* qid, qcom_sGet* get);

int main(int argc, char** argv)
{
  pwr_tStatus sts;
  qcom_sGet get;
  net_sNotify* notify;
  net_sMessage* mp;
  gdb_sNode* np;
  qcom_sQid qid = qcom_cNQid;

  errh_Init("pwr_nacp", errh_eAnix_neth_acp);
  errh_SetStatus(PWR__SRVSTARTUP);

  init(&qid);
  errh_SetStatus(PWR__SRUN);

  for (;;) {
    mp = receive(&qid, &get);

    np = node(mp);
    if (np == NULL) {
      errh_Error("sender %u.%u, type %u.%u, size %u, reply %u.%u",
          get.sender.nid, get.sender.aix, get.type.b, get.type.s, get.size,
          get.reply.nid, get.reply.qix);
      continue;
    }

    switch ((int)get.type.s) {
    case net_eMsg_nodeUp:
      nodeUp((net_sNodeUp*)mp);
      break;
    case net_eMsg_createObject:
      gdb_ScopeLock
      {
        subc_ActivateList(&gdbroot->no_node->subc_lh, pwr_cNObjid);
      }
      gdb_ScopeUnlock;
      break;

    case net_eMsg_deleteObject:
      notify = (net_sNotify*)mp;
      gdb_ScopeLock
      {
        subc_ActivateList(&np->subc_lh, notify->oid);
      }
      gdb_ScopeUnlock;
      break;

    case net_eMsg_moveObject:
    case net_eMsg_renameObject:
      gdb_ScopeLock
      {
        subc_ActivateList(&np->subc_lh, pwr_cNObjid);
        subc_ActivateList(&gdbroot->no_node->subc_lh, pwr_cNObjid);
      }
      gdb_ScopeUnlock;
      break;

    default:
      errh_Error("Unexpected subtype %d received from %d.%d %X", get.type.s,
          get.reply.qix, get.reply.nid, get.pid);
    }

    qcom_Free(&sts, mp);
  }
}

/* Initiate qcom, gdh and subscriptions.  */

static void init(qcom_sQid* myQid)
{
  pwr_tStatus sts;

  sts = gdh_Init("pwr_nacp");
  if (EVEN(sts)) {
    errh_Fatal("gdh_Init, %m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }

#if defined OS_CYGWIN
  qcom_sQattr qAttr;
  qcom_sQid qid = qcom_cQnacp;

  qAttr.type = qcom_eQtype_private;
  qAttr.quota = 100;
  if (!qcom_CreateQ(&sts, &qid, &qAttr, "nacp")) {
    errh_Error("Failed to create QCOM que\n%m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }
#else
  if (!qcom_AttachQ(&sts, &qcom_cQnacp)) {
    errh_Fatal("qcom_AttachQ, %m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }
#endif
  *myQid = qcom_cQnacp;

  if (!qcom_Bind(&sts, myQid, &qcom_cQini)) {
    errh_Fatal("qcom_Bind, %m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(-1);
  }

  /* Activate all subscriptions that were requested before we started!  */

  gdb_ScopeLock
  {
    gdbroot->db->neth_acp = *myQid;
    subc_ActivateList(&gdbroot->my_node->subc_lh, pwr_cNObjid);
    subc_ActivateList(&gdbroot->no_node->subc_lh, pwr_cNObjid);
  }
  gdb_ScopeUnlock;
}

/* Receive a message.  */

static void* receive(qcom_sQid* qid, qcom_sGet* get)
{
  pwr_tStatus sts;
  void* mp;

  for (;;) {
    get->data = NULL;
    /* Loop until receiving a valid message.  */
    mp = qcom_Get(&sts, &qcom_cQnacp, get, qcom_cTmoEternal);
    if (mp == NULL) {
      errh_Error("qcom_Get, %m", sts);
      continue;
    }

    if (get->type.b == qcom_eBtype_event) {
      event(get);
      qcom_Free(&sts, mp);
      continue;
    }

    else if (get->type.b != net_cMsgClass) {
      errh_Error("Received bad message, type: <%d>, subtype: <%d>", get->type.b,
          get->type.s);
      qcom_Free(&sts, mp);
      continue;
    }

    return mp;
  }
}

static void event(qcom_sGet* get)
{
  qcom_sEvent* ep = (qcom_sEvent*)get->data;
  ini_mEvent new_event;

  if (get->type.s != qcom_cIini)
    return;

  new_event.m = ep->mask;
  if (new_event.b.terminate) {
    exit(0);
  }
}

/* Check message node identity and return pointer to node.  */

static gdb_sNode* node(net_sMessage* mp)
{
  pwr_tStatus sts;
  gdb_sNode* np;

  if (mp->nid == pwr_cNNodeId) {
    errh_Error("Message from pwr_cNNodeId received");
    return NULL;
  }

  gdb_ScopeLock
  {
    np = hash_Search(&sts, gdbroot->nid_ht, &mp->nid);
  }
  gdb_ScopeUnlock;

  if (np == NULL) {
    errh_Error("Message about unknown node: (%s) received\n",
        cdh_NodeIdToString(NULL, mp->nid, 0, 0));
    return NULL;
  }

  return np;
}

/* A node is up.

   Get object headers for all mount servers
   and lock them in the cache cache.

   Reactivate subscriptions.  */

static void nodeUp(net_sNodeUp* mp)
{
  pwr_tStatus sts;
  gdb_sNode* np;

  np = hash_Search(&sts, gdbroot->nid_ht, &mp->nid);
  if (np == NULL) {
    errh_Error("Message about unknown node: (%s) received\n",
        cdh_NodeIdToString(NULL, mp->nid, 0, 0));
    return;
  }
  errh_Info("Up, link to node %s (%s)", np->name,
      cdh_NodeIdToString(NULL, mp->nid, 0, 0));

  gdb_ScopeLock
  {
    lockMountServers(np);
    subc_ActivateList(&np->subc_lh, pwr_cNObjid);
    subc_ActivateList(&gdbroot->no_node->subc_lh, pwr_cNObjid);
    sanc_SubscribeMountServers(&sts, np);
  }
  gdb_ScopeUnlock;
}

/* Get the object header of all mount servers and lock them in cache.  */

static void lockMountServers(gdb_sNode* np)
{
  pwr_tStatus sts;
  pool_sQlink* msl;
  pool_sQlink* vl;
  gdb_sVolume* vp;
  gdb_sMountServer* msp;
  gdb_sObject* op;

  gdb_AssumeLocked;

  for (vl = pool_Qsucc(NULL, gdbroot->pool, &np->own_lh); vl != &np->own_lh;
       vl = pool_Qsucc(NULL, gdbroot->pool, vl)) {
    vp = pool_Qitem(vl, gdb_sVolume, l.own_ll);

    if (vl->self == vl->flink) {
      /* Connection lost and volume removed from own list */
      errh_Error("Volume not owned any more, %s", vp->g.name.orig);
      return;
    }
    if (!vp->l.flags.b.isConnected) {
      /* !!! Todo !!! How do we make this known ?  */
      errh_Error("Volume not connected, %s", vp->g.name.orig);
      continue;
    }

    for (msl = pool_Qsucc(NULL, gdbroot->pool, &vp->l.volms_lh);
         msl != &vp->l.volms_lh; msl = pool_Qsucc(NULL, gdbroot->pool, msl)) {
      msp = pool_Qitem(msl, gdb_sMountServer, volms_ll);
      op = hash_Search(&sts, gdbroot->oid_ht, &msp->oid);
      if (op == NULL) {
        op = cvolc_OidToObject(
            &sts, vp, msp->oid, vol_mTrans_none, cvol_eHint_none);
        if (op == NULL) {
          errh_Error("Can't fetch the mount server's object, %s",
              cdh_ObjidToString(msp->oid, 0));
          /* !!! Todo !!! How do we make this error known ?  */
          continue;
        }
      }
      msp->msor = pool_ItemReference(NULL, gdbroot->pool, op);
      op->l.flags.b.isMountServer = 1;
      if (msp->nodms_ll.self == msp->nodms_ll.flink
          && msp->nodms_ll.self == msp->nodms_ll.blink)
        pool_QinsertPred(NULL, gdbroot->pool, &msp->nodms_ll, &np->nodms_lh);

      /* if (0)
        errh_Info("Locking object %s", op->g.f.name.orig); */
      cvolc_LockObject(&sts, op);
    }
  }
}
