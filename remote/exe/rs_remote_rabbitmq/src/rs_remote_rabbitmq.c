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

/* rs_remote_rabbitmq.c Remote transport process with rabbitmq */

/*_Include files_________________________________________________________*/

#if defined PWRE_CONF_RABBITMQ

#include <amqp.h>
#include <amqp_framing.h>
#include <amqp_tcp_socket.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "pwr_baseclasses.h"
#include "pwr_class.h"
#include "pwr_remoteclasses.h"
#include "pwr_systemclasses.h"

#include "co_string.h"
#include "co_time.h"
#include "co_cdh.h"

#include "rt_aproc.h"
#include "rt_errh.h"
#include "rt_gdh.h"
#include "rt_pwr_msg.h"
#include "rs_remote_msg.h"

#include "remote.h"
#include "remote_remtrans_utils.h"

#define TIME_INCR 0.02
#define debug 0
#define remote_cMsgClass 204

typedef struct {
  amqp_connection_state_t conn;
  amqp_socket_t* socket;
  amqp_channel_t channel;
  pwr_sClass_RemnodeRabbitMQ* op;
  int is_producer;
  int is_consumer;
} rabbit_sCtx, *rabbit_tCtx;

typedef struct {
  unsigned int msg_size;
  unsigned short int msg_id[2];
} rabbit_header;

typedef enum {
  rabbit_mOpt_KeepAll = 1,
  rabbit_mOpt_MsgOrder = 2
} rabbit_mOpt;

static rabbit_tCtx ctx = 0;
static remnode_item rn;
static remtrans_item *rcv_remtrans = 0;
static int rcv_remtrans_locking = 0;
static pwr_sClass_RemnodeRabbitMQ* rn_rmq;

/*************************************************************************
**************************************************************************
*
* RemoteSleep
*
**************************************************************************
**************************************************************************/

void RemoteSleep(float time)
{
  struct timespec rqtp, rmtp;

  rqtp.tv_sec = 0;
  rqtp.tv_nsec = (long int)(time * 1000000000);
  nanosleep(&rqtp, &rmtp);
  return;
}

void rmq_close(int destroy)
{
  if (ctx->channel) {
    amqp_channel_close(ctx->conn, ctx->channel, AMQP_REPLY_SUCCESS);
    ctx->channel = 0;
  }
  if (ctx->socket) {
    amqp_connection_close(ctx->conn, AMQP_REPLY_SUCCESS);
    ctx->socket = 0;
  }
  if (destroy) {
    amqp_destroy_connection(ctx->conn);
    ctx->conn = 0;
  }
}

/*************************************************************************
**************************************************************************
*
* Namn : rmq_connect
*
* Typ  : int
*
* Typ		Parameter	       IOGF	Beskrivning
*
* Beskrivning : Connect to RabbitMQ broker.
*
**************************************************************************
**************************************************************************/
int rmq_connect(int msg_order)
{
  int sts;
  amqp_rpc_reply_t rep;
  amqp_channel_open_ok_t* co;

  if (!ctx->conn) {
    ctx->conn = amqp_new_connection();
    // printf( "Connection : %u\n", (unsigned int)ctx->conn);
  }

  if (!ctx->socket) {
    ctx->socket = (amqp_socket_t*)amqp_tcp_socket_new(ctx->conn);
    if (!ctx->socket) {
      errh_Error("Socket error");
      return 0;
    }

    while (1) {
      sts = amqp_socket_open(ctx->socket, ctx->op->Server, ctx->op->Port);
      if (sts) {
        errh_Error("Socket open error %d", sts);
	sleep(10);
      }
      else {
	errh_Info("Socket opened");
	break;
      }
    }
  }

  rep = amqp_login(ctx->conn, "/", 0, 131072, ctx->op->Heartbeat, 
      AMQP_SASL_METHOD_PLAIN, ctx->op->User, ctx->op->Password);
  if (rep.reply_type != AMQP_RESPONSE_NORMAL) {
    if (rep.reply_type == AMQP_RESPONSE_LIBRARY_EXCEPTION) {
      errh_Error("Login failure, not authorized? %d library_error %d %s", rep.reply_type, 
		 rep.library_error, amqp_error_string2(rep.library_error));
    }
    else
      errh_Error("Login failure: %d", rep.reply_type);
    return 0;
  }

  if (!ctx->channel) {
    if (ctx->op->Channel == 0)
      ctx->channel = 1;
    else
      ctx->channel = ctx->op->Channel;

    co = amqp_channel_open(ctx->conn, ctx->channel);
    if (!co) {
      printf("Channel not open\n");
      ctx->channel = 0;
    } else {
      if (debug)
	printf("Channel open %s\n", (char*)co->channel_id.bytes);
    }
  }

  /* Declare send queue */
  if (ctx->is_producer) {
    // 0 passive 0 durable 0 exclusive 0 auto-delete
    amqp_queue_declare_ok_t* qd = amqp_queue_declare(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->SendQueue), 0, ctx->op->Durable, 0, 0,
        amqp_empty_table);
    if (!qd) {
      if (debug)
	printf("SendQueue not declared\n");
    } else {
      if (debug)
	printf("SendQueue %s message cnt %d, consumer cnt %d\n",
            (char*)qd->queue.bytes, qd->message_count, qd->consumer_count);
    }
  }

  /* Declare receive queue */
  if (ctx->is_consumer) {
    // 0 passive 0 durable 0 exclusive 0 auto-delete
    amqp_queue_declare_ok_t* qd = amqp_queue_declare(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->ReceiveQueue), 0, ctx->op->Durable, 0, 0,
        amqp_empty_table);
    if (!qd) {
      if (debug)
	printf("ReceiveQueue not declared\n");
    } else {
      if (debug)
	printf("ReceiveQueue %s message cnt %d, consumer cnt %d\n",
            (char*)qd->queue.bytes, qd->message_count, qd->consumer_count);
    }
  }

  if (ctx->is_producer && !streq(ctx->op->Exchange, ""))
#if AMQP_VERSION_MAJOR == 0 && AMQP_VERSION_MINOR < 6
    amqp_exchange_declare(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->Exchange), amqp_cstring_bytes("fanout"), 0,
        ctx->op->Durable, amqp_empty_table);
#else
    amqp_exchange_declare(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->Exchange), amqp_cstring_bytes("fanout"), 0,
        ctx->op->Durable, 0, 0, amqp_empty_table);
#endif

  if (ctx->is_producer && !streq(ctx->op->Exchange, ""))
    amqp_queue_bind(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->SendQueue),
        amqp_cstring_bytes(ctx->op->Exchange),
        amqp_cstring_bytes("exchange-key"), amqp_empty_table);

  amqp_basic_consume_ok_t* bc;
  // 0 no-local 1 no-ack 0 exclusive
  if (ctx->is_consumer) {
    bc = amqp_basic_consume(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->ReceiveQueue), amqp_empty_bytes, 0,
        !ctx->op->Acknowledge, 0, amqp_empty_table);
    if (!bc)
      errh_Error("Consumer error");
    else {
      if (debug)
	printf("Consumer tag: %s\n", (char*)bc->consumer_tag.bytes);
    }
  }

  if (msg_order) {
    if (!amqp_basic_qos(ctx->conn, ctx->channel, 0, 1, 0))
      errh_Error("amqp_basic_qos error\n");
  }

  return 1;
}

/*************************************************************************
**************************************************************************
*
* Namn : rmq_receive
*
* Typ  : unsigned int
*
* Typ		Parameter	       IOGF	Beskrivning
*
* Beskrivning : Invoked when a RabbitMQ message is received.
*
**************************************************************************
**************************************************************************/

unsigned int rmq_receive()
{
  pwr_tStatus sts;
  int search_remtrans = 0;
  remtrans_item* remtrans;
  amqp_rpc_reply_t ret;
  amqp_envelope_t envelope;
  struct timeval t = {0, 0};
  rabbit_header header;
  int msg_received = 0;
  int restart = 0;

  if (rcv_remtrans && 
      rcv_remtrans->objp->Address[2] & rabbit_mOpt_KeepAll &&
      rcv_remtrans->objp->DataValid)
    return 1;
  if (rcv_remtrans_locking) {
    rcv_remtrans = 0;
    rcv_remtrans_locking = 0;
  }  

  amqp_maybe_release_buffers(ctx->conn);
  ret = amqp_consume_message(ctx->conn, &envelope, &t, 0);
  switch (ret.reply_type) {
  case AMQP_RESPONSE_NORMAL: {
    break;
  }
  case AMQP_RESPONSE_NONE:
    return REM__SUCCESS;
  case AMQP_RESPONSE_SERVER_EXCEPTION:
    return REM__EXCEPTION;
  case AMQP_RESPONSE_LIBRARY_EXCEPTION:
    switch (ret.library_error) {
    case AMQP_STATUS_TIMEOUT: {
      amqp_destroy_envelope(&envelope);
      return REM__TIMEOUT;
    }
    case AMQP_STATUS_UNEXPECTED_STATE: {
      amqp_frame_t frame;

      sts = amqp_simple_wait_frame_noblock(ctx->conn, &frame, &t);
      if (sts == AMQP_STATUS_TIMEOUT) {
        printf("Wait frame timeout\n");
        return REM__EXCEPTION;
      } else if (sts == AMQP_STATUS_OK) {
        if (frame.frame_type == AMQP_FRAME_METHOD) {
          switch (frame.payload.method.id) {
          case AMQP_BASIC_ACK_METHOD:
            errh_Error("Exception: Basic ack method called");
	    return REM__EXCEPTION;
          case AMQP_BASIC_RETURN_METHOD:
            errh_Error("Exception: Basic return method called");
	    return REM__EXCEPTION;
          case AMQP_CHANNEL_CLOSE_METHOD:
	    restart = 1;
            errh_Error("Exception: Channel close method called");
            break;
          case AMQP_CONNECTION_CLOSE_METHOD:
	    restart = 1;
            errh_Error("Exception: Connection close method called");
            break;
          default:;
          }
        }
      } else
        return REM__EXCEPTION;
      break;
    }
    case AMQP_STATUS_SOCKET_ERROR:
      errh_Error("Exception: Socket error");
      restart = 1;
      break;
    case AMQP_STATUS_CONNECTION_CLOSED:
      errh_Error("Exception: Connection closed");
      restart = 1;
      break;
    case AMQP_STATUS_TCP_ERROR:
      errh_Error("Exception: TCP error");
      return REM__EXCEPTION;
    }
    if (restart) {
      // Reconnect...
      rmq_close(1);
      exit(0);
    }
    return REM__EXCEPTION;
  default:
    errh_Error("Unknown Reply type: %d", ret.reply_type);
  }

  if (debug)
    printf("Received message %d\n", (int)envelope.message.body.len);

  if (envelope.message.body.len > 0 && rn_rmq->DisableHeader) {
    /* Header disabled, take the first receive remtrans object */

    remtrans = rn.remtrans;
    search_remtrans = 1;

    while (remtrans && search_remtrans) {
      /* Match? */
      if (remtrans->objp->Direction == REMTRANS_IN) {
        search_remtrans = false;
        sts = RemTrans_Receive(remtrans, (char*)envelope.message.body.bytes,
            envelope.message.body.len);
        msg_received = 1;
      }
      remtrans = (remtrans_item*)remtrans->next;
    }
    if (search_remtrans) {
      rn_rmq->ErrCount++;
      errh_Info("RabbitMQ Receive no remtrans %s", rn_rmq->ReceiveQueue);
    }
  } else if (envelope.message.body.len >= sizeof(rabbit_header)) {
    memcpy(&header, envelope.message.body.bytes, sizeof(rabbit_header));

    /* Convert the header to host byte order */
    header.msg_size = ntohs(header.msg_size);
    header.msg_id[0] = ntohs(header.msg_id[0]);
    header.msg_id[1] = ntohs(header.msg_id[1]);

    search_remtrans = 1;
    remtrans = rn.remtrans;
    while (remtrans && search_remtrans) {
      if (remtrans->objp->Address[0] == header.msg_id[0]
          && remtrans->objp->Address[1] == header.msg_id[1]
          && remtrans->objp->Direction == REMTRANS_IN) {
	if (remtrans->objp->Address[2] & rabbit_mOpt_KeepAll && 
	    remtrans->objp->DataValid) {
	  /* Not ready, requeue the message */
	  amqp_basic_nack(ctx->conn, ctx->channel, envelope.delivery_tag, 0, 1);
	  if (!rcv_remtrans && !rcv_remtrans_locking) {
	    rcv_remtrans_locking = 1;
	    rcv_remtrans = remtrans;
	  }
	  return 1;
	}
        search_remtrans = false;
        sts = RemTrans_Receive(remtrans,
            (char*)envelope.message.body.bytes + sizeof(rabbit_header),
            envelope.message.body.len);
        if (sts != STATUS_OK && sts != STATUS_BUFF)
          errh_Error("Error from RemTrans_Receive, queue %s, status %d",
              rn_rmq->ReceiveQueue, sts, 0);
        msg_received = 1;
        break;
      }
      remtrans = (remtrans_item*)remtrans->next;
    }
    if (search_remtrans) {
      rn_rmq->ErrCount++;
      msg_received = 1;
      errh_Info("No remtrans for received message, queue %s, class %d, type %d",
          rn_rmq->ReceiveQueue, header.msg_id[0], header.msg_id[1]);
    }
  }

  if (ctx->op->Acknowledge) {
    if (msg_received)
      amqp_basic_ack(ctx->conn, ctx->channel, envelope.delivery_tag, 0);
    else
      /* Requeue the message */
      amqp_basic_nack(ctx->conn, ctx->channel, envelope.delivery_tag, 0, 1);
  }
  amqp_destroy_envelope(&envelope);

  return sts;
}

/*************************************************************************
**************************************************************************
*
* Namn : rmq_send
*
* Typ  : unsigned int
*
* Typ		Parameter	       IOGF	Beskrivning
*
* Beskrivning : Sends a RabbitMQ message to remote node
*
**************************************************************************
**************************************************************************/

unsigned int rmq_send(remnode_item* remnode, pwr_sClass_RemTrans* remtrans,
    char* buf, int buf_size)
{
  int sts;
  amqp_basic_properties_t prop;
  amqp_bytes_t msg;
  char* tmpbuf;
  unsigned int tmpbuf_size;

  if (rn_rmq->DisableHeader) {
    msg.bytes = buf;
    msg.len = buf_size;
  } else {
    tmpbuf_size = sizeof(rabbit_header) + buf_size;
    tmpbuf = malloc(tmpbuf_size);
    memcpy(tmpbuf + sizeof(rabbit_header), buf, buf_size);

    ((rabbit_header*)tmpbuf)->msg_size = htons(tmpbuf_size);
    ((rabbit_header*)tmpbuf)->msg_id[0] = htons(remtrans->Address[0]);
    ((rabbit_header*)tmpbuf)->msg_id[1] = htons(remtrans->Address[1]);

    msg.bytes = tmpbuf;
    msg.len = tmpbuf_size;
  }

  if ( remtrans->Address[3] == 2)
    prop.delivery_mode = 2;
  else
    prop.delivery_mode = 1;
  prop._flags = AMQP_BASIC_DELIVERY_MODE_FLAG;

  // 0 mandatory 0 immediate
  if (!streq(ctx->op->Exchange, ""))
    sts = amqp_basic_publish(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->Exchange), amqp_cstring_bytes(""), 0, 0,
        &prop, msg);
  else
    sts = amqp_basic_publish(ctx->conn, ctx->channel,
        amqp_cstring_bytes(ctx->op->Exchange),
        amqp_cstring_bytes(ctx->op->SendQueue), 0, 0, &prop, msg);
  if (sts) {
    remtrans->ErrCount++;
    errh_Error("Send failed, queue %s, RabbitMQ status %d",
        rn_rmq->SendQueue, sts, 0);
    if (debug)
      printf("Send failed sts:%d\n", (int)sts);
  }
  if (!rn_rmq->DisableHeader)
    free(tmpbuf);

  return STATUS_OK;
}

/*************************************************************************
**************************************************************************
*
* Main
*
**************************************************************************
**************************************************************************/

int main(int argc, char* argv[])
{
  remtrans_item* remtrans;
  unsigned char id[32];
  unsigned char pname[80];
  pwr_tStatus sts;
  int i;
  float time_since_scan = 0.0;
  int msg_order = 0;

  /* Read arg number 2, should be id for this instance and id is our queue
   * number */

  if (argc >= 2)
    strncpy((char*)id, argv[1], sizeof(id));
  else
    strcpy((char*)id, "0");

  /* Build process name with id */

  sprintf((char*)pname, "rs_remrabbitmq_%s", id);

  /* Init of errh */

  errh_Init((char*)pname, errh_eAnix_remote);
  errh_SetStatus(PWR__SRVSTARTUP);

  /* Init of gdh */
  if (debug)
    printf("Before gdh_init\n");
  sts = gdh_Init((char*)pname);
  if (EVEN(sts)) {
    errh_Fatal("gdh_Init, %m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }

  /* Arg number 3 should be my remnodes objid in string representation,
     read it, convert to real objid and store in remnode_item */

  sts = 0;
  if (argc >= 3)
    sts = cdh_StringToObjid(argv[2], &rn.objid);
  if (EVEN(sts)) {
    errh_Fatal("cdh_StringToObjid, %m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }

  /* Get pointer to RemnodeRabbitMQ object and store locally */
  sts = gdh_ObjidToPointer(rn.objid, (pwr_tAddress*)&rn_rmq);
  if (EVEN(sts)) {
    errh_Fatal("cdh_ObjidToPointer, %m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }

  if (streq(rn_rmq->ReceiveQueue, "")
      && streq(rn_rmq->SendQueue, "")) {
    errh_Fatal(
        "Process terminated, neither send or receive queue configured, %s", id);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }

  /* Create context */
  ctx = calloc(1, sizeof(*ctx));
  ctx->op = rn_rmq;
  if (!streq(rn_rmq->ReceiveQueue, ""))
    ctx->is_consumer = 1;
  if (!streq(rn_rmq->SendQueue, ""))
    ctx->is_producer = 1;

  /* Initialize some internal data and make standard remtrans init */

  rn.next = NULL;
  rn.local = NULL; // We dont use local structure since we only have one remnode
  rn_rmq->ErrCount = 0;
  if (debug)
    printf("Before remtrans_init\n");

  sts = RemTrans_Init(&rn);

  if (EVEN(sts)) {
    errh_Fatal("RemTrans_Init, %m", sts);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }

  /* Store remtrans objects objid in remnode_qcom object */
  remtrans = rn.remtrans;
  i = 0;
  while (remtrans) {
    rn_rmq->RemTransObjects[i++] = remtrans->objid;
    if (i >= (int)(sizeof(rn_rmq->RemTransObjects)
                 / sizeof(rn_rmq->RemTransObjects[0])))
      break;
    remtrans = (remtrans_item*)remtrans->next;
  }

  /* Find single receive remtrans */
  remtrans = rn.remtrans;
  i = 0;
  while (remtrans) {
    if (remtrans->objp->Direction == REMTRANS_IN) {
      rcv_remtrans = remtrans;
      i++;
      if (rn_rmq->DisableHeader)
	break;
      if (remtrans->objp->Address[2] & rabbit_mOpt_MsgOrder)
	msg_order = 1;
    }
    remtrans = (remtrans_item*)remtrans->next;
  }
  if (i != 1)
    rcv_remtrans = 0;

  /* Connect to rabbitmq broker */
  sts = rmq_connect(msg_order);
  if (EVEN(sts)) {
    rmq_close(1);
    errh_Fatal("Process terminated, unable to connect to RabbitMQ, %s", id);
    errh_SetStatus(PWR__SRVTERM);
    exit(sts);
  }

  /* Set running status */

  errh_SetStatus(PWR__SRUN);

  /* Set (re)start time in remnode object */

  time_GetTime(&rn_rmq->RestartTime);

  /* Loop forever */

  while (!doomsday) {
    if (rn_rmq->Disable == 1) {
      errh_Fatal("Disabled, exiting");
      errh_SetStatus(PWR__SRVTERM);
      exit(0);
    }
    aproc_TimeStamp(TIME_INCR, 5);

    sts = rmq_receive();
    RemoteSleep(TIME_INCR);

    time_since_scan += TIME_INCR;
    if (time_since_scan >= rn_rmq->ScanTime) {
      if (ctx->is_producer)
        sts = RemTrans_Cyclic(&rn, &rmq_send);
      time_since_scan = 0.0;
    }
  }
}

#else
#include <stdio.h>
int main()
{
  printf("Remote RabbitMq not built for this release\n");
  return 0;
}
#endif
