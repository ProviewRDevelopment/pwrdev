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

/* rt_io_m_mb_tcp_server.c -- io methods for Modbus/TCP Server */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>

#include "co_cdh.h"
#include "pwr_basecomponentclasses.h"
#include "pwr_otherioclasses.h"
#include "pwr_version.h"
#include "rt_io_base.h"
#include "rt_io_bus.h"
#include "rt_thread.h"
#include "rt_io_msg.h"
#include "co_cdh.h"
#include "co_time.h"
#include "rt_mb_msg.h"

#include "rt_io_mb_locals.h"

static char rcv_buffer[65536];
static pwr_tStatus mb_init_channels(io_tCtx ctx, io_sAgent* ap, io_sRack* rp);
static void mb_shift_write(
    unsigned char* in, unsigned char* out, int sh, int quant);
static void mb_shift_read(
    unsigned char* in, unsigned char* out, int sh, int quant);

typedef struct {
  io_sRack* rp;
  int idx;
} mb_sCondata;

static void signal_callback_handler(int signum)
{
  printf("Caught signal SIGPIPE %d\n", signum);
}

static void mb_close_connection(io_sRack* rp, int l_idx)
{
  pwr_sClass_Modbus_TCP_Server* op = (pwr_sClass_Modbus_TCP_Server*)rp->op;
  io_sServerLocal* local = rp->Local;
  pwr_tStatus sts;

  sts = thread_Cancel(&local->connections[l_idx].t);
  close(local->connections[l_idx].c_socket);
  local->connections[l_idx].occupied = 0;
  op->Connections--;
}

static void* mb_receive(void* data)
{
  io_sRack* rp = ((mb_sCondata*)data)->rp;
  int l_idx = ((mb_sCondata*)data)->idx;
  io_sServerLocal* local = rp->Local;
  int c_socket = local->connections[l_idx].c_socket;
  pwr_sClass_Modbus_TCP_Server* op = (pwr_sClass_Modbus_TCP_Server*)rp->op;
  ssize_t data_size;
  rec_buf* rb;
  unsigned char fc;
  unsigned char exception_code;
  ssize_t ssts;
  int size_of_msg;

  free(data);
  op->Connections++;

  while (1) {
    size_of_msg = 0;

    data_size = recv(c_socket, rcv_buffer, sizeof(rec_buf), 0);
    if (data_size < 0) {
      op->ErrorCount++;
      continue;
    }
    if (data_size == 0) {
      /* Disconnected */
      op->Connections--;
      close(c_socket);
      local->connections[l_idx].occupied = 0;
      errh_Error("Connection lost for IO modbus tcp server %s, %d", rp->Name,
          c_socket);
      return 0;
    }
    if (op->DisableServer)
      continue;

    while (data_size > 0) {
      if (data_size < sizeof(mbap_header))
        break;

      op->RX_packets++;

      rb = (rec_buf*)&rcv_buffer[size_of_msg];

      if (rb->head.length == 0)
        break;

      size_of_msg += ntohs(rb->head.length) + 6;
      data_size -= ntohs(rb->head.length) + 6;

      fc = (unsigned char)*rb->buf;

      time_GetTime(&local->connections[l_idx].last_req_time);
      exception_code = 0;

      switch (fc) {
      case pwr_eModbus_FCEnum_ReadInputRegisters:
      case pwr_eModbus_FCEnum_ReadHoldingRegisters: {
        io_sCard* cardp;
        io_sServerModuleLocal* local_card = NULL;
        pwr_sClass_Modbus_TCP_ServerModule* mp = NULL;
        read_req* rmsg = (read_req*)rb;
        rsp_read msg;
        int found;

        short addr = ntohs(rmsg->addr);
        short quant = ntohs(rmsg->quant);
        unsigned char unit_id = rmsg->head.unit_id;

        if (quant < 1 || quant >= 0x07d0) {
          exception_code = 3;
          break;
        }

        /* Check the address */
        found = 0;
        for (cardp = rp->cardlist; cardp; cardp = cardp->next) {
          mp = (pwr_sClass_Modbus_TCP_ServerModule*)cardp->op;
          if (mp->UnitId == unit_id) {
            local_card = cardp->Local;
            found = 1;
            break;
          }
        }

        if (!found) {
          exception_code = 2;
          break;
        }

        addr -= mp->ReadRegAddress;

        if (addr < 0 || addr + quant * 2 > local_card->output_size) {
          exception_code = 2;
          break;
        }

        msg.fc = fc;
        msg.bc = quant * 2;
        msg.head.trans_id = rmsg->head.trans_id;
        // msg.head.length = htons( sizeof(msg) - 6);
        msg.head.length = htons(sizeof(msg) - sizeof(msg.buf) + quant * 2 - 6);
        msg.head.unit_id = rmsg->head.unit_id;
        msg.head.proto_id = rmsg->head.proto_id;

        thread_MutexLock(&local->mutex);
        memcpy(msg.buf, (char*)local_card->output_area + addr, quant * 2);
        thread_MutexUnlock(&local->mutex);

        ssts = send(c_socket, &msg, ntohs(msg.head.length) + 6, MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;

        break;
      }
      case pwr_eModbus_FCEnum_ReadCoils:
      case pwr_eModbus_FCEnum_ReadDiscreteInputs: {
        io_sCard* cardp;
        io_sServerModuleLocal* local_card = NULL;
        pwr_sClass_Modbus_TCP_ServerModule* mp;
        read_req* rmsg = (read_req*)rb;
        rsp_read msg;
        int found;
        unsigned char mask;
        unsigned int bytes;
        int i;
        int offs;

        short addr = ntohs(rmsg->addr);
        short quant = ntohs(rmsg->quant);
        unsigned char unit_id = rmsg->head.unit_id;

        if (quant < 1 || quant >= 0x07d0) {
          exception_code = 3;
          break;
        }

        /* Check the address */
        found = 0;
        for (cardp = rp->cardlist; cardp; cardp = cardp->next) {
          mp = (pwr_sClass_Modbus_TCP_ServerModule*)cardp->op;
          if (mp->UnitId == unit_id) {
            local_card = cardp->Local;
            found = 1;
            break;
          }
        }

        if (!found) {
          exception_code = 2;
          break;
        }

        addr -= mp->ReadDigAddress;

        offs = addr / 8;
        bytes = (addr + quant) / 8 + (((addr + quant) % 8 == 0) ? 0 : 1) - offs;

        if (addr < 0
            || offs + bytes + local_card->do_offset > local_card->output_size
            || offs + bytes > local_card->do_size) {
          exception_code = 2;
          break;
        }

        memset(&msg, 0, sizeof(msg));
        msg.fc = fc;
        msg.bc = bytes;
        msg.head.trans_id = rmsg->head.trans_id;
        // msg.head.length = htons( sizeof(msg) - 6);
        msg.head.length = htons(sizeof(msg) - sizeof(msg.buf) + bytes - 6);
        msg.head.unit_id = rmsg->head.unit_id;
        msg.head.proto_id = rmsg->head.proto_id;

        thread_MutexLock(&local->mutex);
        if (addr % 8 == 0) {
          memcpy(msg.buf,
              (char*)local_card->output_area + local_card->do_offset + addr / 8,
              bytes);

          mask = 0;
          for (i = 0; i < quant % 8; i++)
            mask |= 1 << i;

          if (quant % 8 != 0) {
            unsigned char* b = (unsigned char*)msg.buf;
            b[bytes - 1] &= mask;
          }
        } else {
          mb_shift_read((unsigned char*)local_card->output_area
                  + local_card->do_offset + addr / 8,
              (unsigned char*)msg.buf, addr % 8, quant);
        }
        thread_MutexUnlock(&local->mutex);

        ssts = send(c_socket, &msg, ntohs(msg.head.length) + 6, MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;

        break;
      }
      case pwr_eModbus_FCEnum_WriteSingleRegister: {
        io_sCard* cardp;
        io_sServerModuleLocal* local_card = NULL;
        pwr_sClass_Modbus_TCP_ServerModule* mp = NULL;
        write_single_req* rmsg = (write_single_req*)rb;
        rsp_single_write msg;
        int found;

        short addr = ntohs(rmsg->addr);
        unsigned char unit_id = rmsg->head.unit_id;

        /* Check the address */
        found = 0;
        for (cardp = rp->cardlist; cardp; cardp = cardp->next) {
          mp = (pwr_sClass_Modbus_TCP_ServerModule*)cardp->op;
          if (mp->UnitId == unit_id) {
            local_card = cardp->Local;
            found = 1;
            break;
          }
        }

        if (!found) {
          exception_code = 2;
          break;
        }

        addr -= mp->WriteRegAddress;

        if (addr < 0 || addr + 2 > local_card->input_size) {
          exception_code = 2;
          break;
        }

        thread_MutexLock(&local->mutex);
        memcpy((char*)local_card->input_area + addr, &rmsg->value, 2);
        thread_MutexUnlock(&local->mutex);

        msg.fc = fc;
        msg.addr = rmsg->addr;
        msg.value = rmsg->value;
        msg.head.trans_id = rmsg->head.trans_id;
        msg.head.length = htons(sizeof(msg) - 6);
        msg.head.unit_id = rmsg->head.unit_id;
        msg.head.proto_id = rmsg->head.proto_id;

        ssts = send(c_socket, &msg, sizeof(msg), MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;

        break;
      }
      case pwr_eModbus_FCEnum_WriteMultipleRegisters: {
        io_sCard* cardp;
        io_sServerModuleLocal* local_card = NULL;
        pwr_sClass_Modbus_TCP_ServerModule* mp = NULL;
        write_reg_req* rmsg = (write_reg_req*)rb;
        rsp_write msg;
        int found;

        short addr = ntohs(rmsg->addr);
        short quant = ntohs(rmsg->quant);
        unsigned char unit_id = rmsg->head.unit_id;

        if (quant < 1 || quant >= 0x07d0) {
          exception_code = 3;
          break;
        }

        /* Check the address */
        found = 0;
        for (cardp = rp->cardlist; cardp; cardp = cardp->next) {
          mp = (pwr_sClass_Modbus_TCP_ServerModule*)cardp->op;
          if (mp->UnitId == unit_id) {
            local_card = cardp->Local;
            found = 1;
            break;
          }
        }

        if (!found) {
          exception_code = 2;
          break;
        }

        addr -= mp->WriteRegAddress;

        if (addr < 0 || addr + quant * 2 > local_card->input_size) {
          exception_code = 2;
          break;
        }

        thread_MutexLock(&local->mutex);
        memcpy((char*)local_card->input_area + addr, rmsg->reg, quant * 2);
        thread_MutexUnlock(&local->mutex);

        msg.fc = fc;
        msg.addr = rmsg->addr;
        msg.quant = rmsg->quant;
        msg.head.trans_id = rmsg->head.trans_id;
        msg.head.length = htons(sizeof(msg) - 6);
        msg.head.unit_id = rmsg->head.unit_id;
        msg.head.proto_id = rmsg->head.proto_id;

        ssts = send(c_socket, &msg, sizeof(msg), MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;

        break;
      }
      case pwr_eModbus_FCEnum_WriteSingleCoil: {
        io_sCard* cardp;
        io_sServerModuleLocal* local_card = NULL;
        pwr_sClass_Modbus_TCP_ServerModule* mp;
        write_single_req* rmsg = (write_single_req*)rb;
        rsp_single_write msg;
        int found;
        unsigned char mask;
        int offs;

        short addr = ntohs(rmsg->addr);
        unsigned short value = ntohs(rmsg->value);
        unsigned char unit_id = rmsg->head.unit_id;

        /* Check the address */
        found = 0;
        for (cardp = rp->cardlist; cardp; cardp = cardp->next) {
          mp = (pwr_sClass_Modbus_TCP_ServerModule*)cardp->op;
          if (mp->UnitId == unit_id) {
            local_card = cardp->Local;
            found = 1;
            break;
          }
        }

        if (!found) {
          exception_code = 2;
          break;
        }

        addr -= mp->WriteDigAddress;

        offs = addr / 8;

        if (addr < 0 || offs + local_card->di_offset >= local_card->input_size
            || offs >= local_card->di_size) {
          exception_code = 2;
          break;
        }

        mask = 1 << (addr % 8);
        if (value == 0xFF00 || value == 0) {
          thread_MutexLock(&local->mutex);
          if (value == 0xFF00)
            *((char*)local_card->input_area + local_card->di_offset + offs)
                |= mask;
          else
            *((char*)local_card->input_area + local_card->di_offset + offs)
                &= ~mask;
          thread_MutexUnlock(&local->mutex);
        }
        msg.fc = fc;
        msg.addr = rmsg->addr;
        msg.value = rmsg->value;
        msg.head.trans_id = rmsg->head.trans_id;
        msg.head.length = htons(sizeof(msg) - 6);
        msg.head.unit_id = rmsg->head.unit_id;
        msg.head.proto_id = rmsg->head.proto_id;

        ssts = send(c_socket, &msg, sizeof(msg), MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;

        break;
      }
      case pwr_eModbus_FCEnum_WriteMultipleCoils: {
        io_sCard* cardp;
        io_sServerModuleLocal* local_card = NULL;
        pwr_sClass_Modbus_TCP_ServerModule* mp;
        write_reg_req* rmsg = (write_reg_req*)rb;
        rsp_write msg;
        int found;
        unsigned char mask;
        unsigned int bytes;
        int i;
        int offs;

        short addr = ntohs(rmsg->addr);
        short quant = ntohs(rmsg->quant);
        unsigned char unit_id = rmsg->head.unit_id;

        if (quant < 1 || quant >= 0x07d0) {
          exception_code = 3;
          break;
        }

        /* Check the address */
        found = 0;
        for (cardp = rp->cardlist; cardp; cardp = cardp->next) {
          mp = (pwr_sClass_Modbus_TCP_ServerModule*)cardp->op;
          if (mp->UnitId == unit_id) {
            local_card = cardp->Local;
            found = 1;
            break;
          }
        }

        if (!found) {
          exception_code = 2;
          break;
        }
        addr -= mp->WriteDigAddress;

        offs = addr / 8;
        bytes = (addr + quant) / 8 + (((addr + quant) % 8 == 0) ? 0 : 1) - offs;

        if (addr < 0
            || offs + bytes + local_card->di_offset > local_card->input_size
            || offs + bytes > local_card->di_size) {
          exception_code = 2;
          break;
        }

        thread_MutexLock(&local->mutex);
        if (addr % 8 == 0) {
          if (quant % 8 != 0) {
            mask = 0;
            for (i = 0; i < quant % 8; i++)
              mask |= 1 << i;

            memcpy((char*)local_card->input_area + local_card->di_offset
                    + addr / 8,
                rmsg->reg, bytes - 1);
            *((char*)local_card->input_area + local_card->di_offset + addr / 8
                + bytes - 1)
                &= ~mask;
            *((char*)local_card->input_area + local_card->di_offset + addr / 8
                + bytes - 1)
                |= *((char*)rmsg->reg + bytes - 1) & mask;
          } else
            memcpy((char*)local_card->input_area + local_card->di_offset
                    + addr / 8,
                rmsg->reg, bytes);
        } else {
          mb_shift_write((unsigned char*)rmsg->reg,
              (unsigned char*)local_card->input_area + local_card->di_offset
                  + addr / 8,
              addr % 8, quant);
        }
        thread_MutexUnlock(&local->mutex);

        msg.fc = fc;
        msg.addr = rmsg->addr;
        msg.quant = rmsg->quant;
        msg.head.trans_id = rmsg->head.trans_id;
        msg.head.length = htons(sizeof(msg) - 6);
        msg.head.unit_id = rmsg->head.unit_id;
        msg.head.proto_id = rmsg->head.proto_id;

        ssts = send(c_socket, &msg, sizeof(msg), MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;

        break;
      }
      case 43: {
        /* Encapsulated Interface Transport, Read Device Identification */
        read_dev_id_req* rmsg = (read_dev_id_req*)rb;
        rsp_dev_id msg;
        int i;
        int len;

        if (rmsg->mei_type != 0x2b) {
          exception_code = 1;
          break;
        }

        if (rmsg->id_code != 1) {
          exception_code = 1;
          break;
        }

        if (rmsg->object_id != 0) {
          exception_code = 1;
          break;
        }

        msg.fc = rmsg->fc;
        msg.mei_type = rmsg->mei_type;
        msg.id_code = rmsg->id_code;
        msg.conformity_level = 1;
        msg.more_follows = 0;
        msg.next_object_id = 0;
        msg.number_of_objects = 3;

        i = 0;

        /* Vendor name */
        msg.list[i++] = 0;
        len = strlen("Proview");
        msg.list[i++] = len;
        strncpy((char*)&msg.list[i], "Proview", len);
        i += len;

        /* Product code */
        msg.list[i++] = 0;
        len = strlen("-");
        msg.list[i++] = len;
        strncpy((char*)&msg.list[i], "-", len);
        i += len;

        /* Major Minor Revision */
        msg.list[i++] = 0;
        len = strlen(pwrv_cPwrVersionStr);
        msg.list[i++] = len;
        strncpy((char*)&msg.list[i], pwrv_cPwrVersionStr, len);
        i += len;

        msg.head.trans_id = rmsg->head.trans_id;
        msg.head.length = htons(sizeof(msg) - sizeof(msg.list) + i - 6);
        msg.head.unit_id = rmsg->head.unit_id;
        msg.head.proto_id = rmsg->head.proto_id;

        ssts = send(c_socket, &msg, ntohs(msg.head.length) + 6, MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;

        break;
      }
      default:
        exception_code = 1;
      }

      if (exception_code) {
        rsp_fault rsp_f;

        rsp_f.fc = fc + 0x80;
        rsp_f.ec = exception_code;
        rsp_f.head.trans_id = rb->head.trans_id;
        rsp_f.head.length = htons(sizeof(rsp_f) - 6);
        rsp_f.head.unit_id = rb->head.unit_id;

        ssts = send(c_socket, &rsp_f, sizeof(rsp_f), MSG_DONTWAIT);
        if (ssts < 0) {
          op->Connections--;
          close(c_socket);
          local->connections[l_idx].occupied = 0;
          errh_Error("Connection lost for IO modbus tcp server %s, %d",
              rp->Name, c_socket);
          return 0;
        }
        op->TX_packets++;
      }
    }
  }
}

static void* mb_connect(void* arg)
{
  io_sRack* rp = (io_sRack*)arg;
  io_sServerLocal* local = rp->Local;
  int sts;
  pwr_sClass_Modbus_TCP_Server* op;
  struct sockaddr_in r_addr;
  socklen_t r_addr_len;
  int c_socket;
  mb_sCondata* condata;
  int idx = 0;
  int found;
  int i;

  op = (pwr_sClass_Modbus_TCP_Server*)rp->op;

  while (1) {
    /* Wait for client connect request */
    r_addr_len = sizeof(r_addr);

    c_socket = accept(local->s, (struct sockaddr*)&r_addr, &r_addr_len);
    if (c_socket < 0) {
      errh_Error(
          "Error accept IO modbus tcp server %s, %d", rp->Name, local->s);
      continue;
    }
    if (op->DisableServer)
      continue;

    errh_Info("Connection accepted for IO modbus tcp server %s, %d", rp->Name,
        c_socket);

    /* Close other connections to this address */
    for (i = 0; i < MB_MAX_CONNECTIONS; i++) {
      if (local->connections[i].occupied
          && r_addr_len == local->connections[i].addrlen
          && r_addr.sin_family == local->connections[i].addr.sin_family
          && memcmp(&r_addr.sin_addr, &local->connections[i].addr.sin_addr,
                 sizeof(r_addr.sin_addr))
              == 0) {
        mb_close_connection(rp, i);
      }
    }

    /* Find next empty in connection list */
    found = 0;
    for (i = 0; i < MB_MAX_CONNECTIONS; i++) {
      if (!local->connections[i].occupied) {
        found = 1;
        idx = i;
        break;
      }
    }

    if (!found) {
      /* Remove the oldest connection */
      int oldest_idx = 0;

      for (i = 1; i < MB_MAX_CONNECTIONS; i++) {
        if (time_Acomp(&local->connections[i].last_req_time,
                &local->connections[oldest_idx].last_req_time)
            < 0)
          oldest_idx = i;
      }
      mb_close_connection(rp, oldest_idx);
      errh_Info(
          "Connection closed, IO modbus tcp server %s, %d", rp->Name, local->s);
      idx = oldest_idx;
    }

    local->connections[idx].c_socket = c_socket;
    local->connections[idx].occupied = 1;
    time_GetTime(&local->connections[idx].last_req_time);
    local->connections[idx].addrlen = r_addr_len;
    memcpy(&local->connections[idx].addr, &r_addr, r_addr_len);

    /* Create a thread for this connection */
    condata = (mb_sCondata*)malloc(sizeof(mb_sCondata));
    condata->rp = rp;
    condata->idx = idx;

    sts = thread_Create(
        &local->connections[idx].t, 0, mb_receive, (void*)condata);
    if (EVEN(sts)) {
      local->connections[idx].occupied = 0;
      errh_Error("Error creating thread IO modbus tcp server %s, %d", rp->Name,
          local->s);
      free(condata);
      continue;
    }
  }
  return NULL;
}

/*----------------------------------------------------------------------------*\
   Init method for the Modbus/TCP server
\*----------------------------------------------------------------------------*/

static pwr_tStatus IoRackInit(io_tCtx ctx, io_sAgent* ap, io_sRack* rp)
{
  io_sServerLocal* local;
  pthread_t thread;
  pwr_tOName name;
  pwr_tStatus sts;
  pwr_sClass_Modbus_TCP_Server* op;
  int i;
  unsigned short port;
  io_sCard 	*cardp;

  // Ignore SIGPIPE signal
  signal(SIGPIPE, signal_callback_handler);

  op = (pwr_sClass_Modbus_TCP_Server*)rp->op;
  op->Connections = 0;

  port = op->Port == 0 ? 502 : op->Port;

  sts = gdh_ObjidToName(rp->Objid, (char*)&name, sizeof(name), cdh_mNName);
  errh_Info("Init of Modbus TCP Server %s", name);

  rp->Local = calloc(1, sizeof(io_sServerLocal));
  local = rp->Local;

  if (op->DisableServer)
    return IO__SUCCESS;

  for ( cardp = rp->cardlist; cardp; cardp = cardp->next)
    io_bus_card_area_size( ctx, cardp, &local->inputs_size, &local->outputs_size);

  local->inputs = calloc(1, local->inputs_size);
  local->outputs = calloc(1, local->output_size);

  /* Create socket, store in local struct */
  uid_t ruid;
  ruid = getuid();
  //printf("ruid: %d\n", ruid);

  local->s = socket(AF_INET, SOCK_STREAM, 0);
  if (local->s < 0) {
    errh_Error("Error creating socket for IO modbus tcp server %s, %d",
        rp->Name, local->s);
    return 0;
  }

  local->loc_addr.sin_family = AF_INET;
  local->loc_addr.sin_port = htons(port);
  for (i = 0; i < 10; i++) {
    sts = bind(
        local->s, (struct sockaddr*)&local->loc_addr, sizeof(local->loc_addr));
    if (sts == 0)
      break;
    perror("Modbus TCP Bind socket failure, retrying... ");
    sleep(10);
  }
  if (sts != 0) {
    printf("Modbus TCP Bind socket failure, exiting");
    errh_Error("Error bind socket to port for IO modbus tcp server %s, %d",
        rp->Name, local->s);
    return 0;
  }

  errh_Info("Modbus TCP Server bind to port %d, %s", port, name);

  sts = listen(local->s, 16);

  sts = thread_MutexInit(&local->mutex);
  if (EVEN(sts))
    return sts;

  /* Create a thread that listens for connections */
  sts = pthread_create(&thread, NULL, mb_connect, (void*)rp);
  if (sts != 0)
    return sts;

  sts = mb_init_channels(ctx, ap, rp);
  if (EVEN(sts))
    return sts;

  op->Status = MB__NORMAL;

  return IO__SUCCESS;
}

static pwr_tStatus mb_init_channels(io_tCtx ctx, io_sAgent* ap, io_sRack* rp)
{
  io_sServerModuleLocal* local_card;
  io_sCard* cardp;
  io_sServerLocal* local;
  pwr_sClass_Modbus_TCP_Server* op;
  char name[196];
  pwr_tStatus sts;
  io_sChannel* chanp;
  int i;

  sts = gdh_ObjidToName(rp->Objid, (char*)&name, sizeof(name), cdh_mNName);

  op = (pwr_sClass_Modbus_TCP_Server*)rp->op;

  local = rp->Local;

  /* Create socket, store in local struct */

  /* Do configuration check and initialize modules. */

  cardp = rp->cardlist;

  unsigned int input_area_offset = 0;
  unsigned int output_area_offset = 0;
  unsigned int input_area_chansize = 0;
  unsigned int output_area_chansize = 0;
  unsigned int card_input_area_offset = 0;
  unsigned int card_output_area_offset = 0;

  while(cardp) {
    local_card = calloc(1, sizeof(*local_card));
    cardp->Local = local_card;

    card_input_area_offset += input_area_offset + input_area_chansize;
    card_output_area_offset += output_area_offset + output_area_chansize;
    input_area_offset = 0;
    output_area_offset = 0;
    input_area_chansize = 0;
    output_area_chansize = 0;

    local_card->input_area = (char *)local->inputs + card_input_area_offset;
    local_card->output_area = (char *)local->outputs + card_output_area_offset;


    io_bus_card_init( ctx, cardp, &input_area_offset, &input_area_chansize,
		      &output_area_offset, &output_area_chansize,
		      pwr_eByteOrderingEnum_BigEndian, io_eAlignment_Packed);

    for (i = 0; i < cardp->ChanListSize; i++) {
      chanp = &cardp->chanlist[i];
      switch (chanp->ChanClass) {
      case pwr_cClass_ChanDi: {
	pwr_sClass_ChanDi *chan_di = (pwr_sClass_ChanDi *) chanp->cop;

	if (local_card->di_size == 0)
	  local_card->di_offset = chanp->offset;
	if (chan_di->Number == 0 || local_card->di_size == 0)
	  local_card->di_size += GetChanSize(chan_di->Representation);

	break;
      }
      case pwr_cClass_ChanDo: {
	pwr_sClass_ChanDo *chan_do = (pwr_sClass_ChanDo *) chanp->cop;

	if (local_card->do_size == 0)
	  local_card->do_offset = chanp->offset;
	if (chan_do->Number == 0 || local_card->do_size == 0)
	  local_card->do_size += GetChanSize(chan_do->Representation);

	break;
      }
      case pwr_cClass_ChanD: {
	pwr_sClass_ChanD *chan_d = (pwr_sClass_ChanD *) chanp->cop;
	if ( chan_d->Type == pwr_eDChanTypeEnum_Di) {
	  if (local_card->di_size == 0)
	    local_card->di_offset = chanp->offset;
	  if (chan_d->Number == 0 || local_card->di_size == 0)
	    local_card->di_size += GetChanSize(chan_d->Representation);
	}
	else {
	  if (local_card->do_size == 0)
	    local_card->do_offset = chanp->offset;
	  if (chan_d->Number == 0 || local_card->do_size == 0)
	    local_card->do_size += GetChanSize(chan_d->Representation);
	}
	break;
      }
      }
    }

    local_card->input_size = input_area_offset + input_area_chansize;
    local_card->output_size = output_area_offset + output_area_chansize;

    cardp = cardp->next;
  }

  local->input_size = card_input_area_offset + input_area_offset + input_area_chansize;
  local->output_size = card_output_area_offset + output_area_offset + output_area_chansize;


  return IO__SUCCESS;
}

static void mb_shift_write(
    unsigned char* in, unsigned char* out, int sh, int quant)
{
  int i;

  if (sh + quant <= 8) {
    unsigned char mask = 0;
    for (i = sh; i < sh + quant; i++)
      mask |= 1 << i;
    out[0] &= ~mask;
    out[0] |= mask & (in[0] << sh);
    return;
  }

  for (i = 0; i < (quant + sh) / 8; i++) {
    if (i == 0) {
      unsigned char mask = ~0;
      mask = mask << sh;

      out[0] &= ~mask;
      out[0] |= mask & (in[0] << sh);
    } else {
      out[i] = in[i] << sh;
      out[i] |= in[i - 1] >> (8 - sh);
    }
  }
  if ((quant + sh) % 8 != 0) {
    unsigned char mask = ~0;
    mask = mask << ((quant + sh) % 8);
    mask = ~mask;

    out[i] &= ~mask;
    out[i] |= mask & (in[i] << sh);
    out[i] |= mask & (in[i - 1] >> (8 - sh));
  }
}

void mb_shift_read(unsigned char* in, unsigned char* out, int sh, int quant)
{
  int i;

  if (sh + quant <= 8) {
    unsigned char mask = ~0;
    mask = mask >> (8 - quant);

    out[0] = mask & (in[0] >> sh);
    return;
  }

  for (i = 0; i < quant / 8; i++) {
    out[i] = in[i] >> sh;
    out[i] |= in[i + 1] << (8 - sh);
  }

  out[i] = in[i] >> sh;
  if ((quant + sh) / 8 > quant / 8)
    out[i] |= in[i + 1] << (8 - sh);

  if (quant % 8 != 0) {
    unsigned char mask = ~0;
    mask = mask >> (8 - (quant % 8));
    out[i] &= mask;
  }
}

/*----------------------------------------------------------------------------*\
   Read method for the Modbus TCP server
\*----------------------------------------------------------------------------*/
static pwr_tStatus IoRackRead(io_tCtx ctx, io_sAgent* ap, io_sRack* rp)
{
  io_sServerLocal *local = rp->Local;
  pwr_sClass_Modbus_TCP_Server *op = (pwr_sClass_Modbus_TCP_Server *) rp->op;

  /* For display */
  memcpy( op->Inputs, local->inputs, MIN(sizeof(op->Inputs), local->inputs_size));
  return IO__SUCCESS;
}

/*----------------------------------------------------------------------------*\
   Write method for the Modbus_TCP server
\*----------------------------------------------------------------------------*/
static pwr_tStatus IoRackWrite(io_tCtx ctx, io_sAgent* ap, io_sRack* rp)
{
  io_sServerLocal *local = rp->Local;
  pwr_sClass_Modbus_TCP_Server *op = (pwr_sClass_Modbus_TCP_Server *) rp->op;

  /* For display */
  memcpy( op->Outputs, local->outputs, MIN(sizeof(op->Outputs), local->outputs_size));
  return IO__SUCCESS;
}

/*----------------------------------------------------------------------------*\

\*----------------------------------------------------------------------------*/
static pwr_tStatus IoRackClose(io_tCtx ctx, io_sAgent* ap, io_sRack* rp)
{
  io_sServerLocal* local = rp->Local;
  int i;

  for (i = 1; i < MB_MAX_CONNECTIONS; i++) {
    if (local->connections[i].occupied)
      mb_close_connection(rp, i);
  }

  close(local->s);

  return IO__SUCCESS;
}

/*----------------------------------------------------------------------------*\
  Every method to be exported to the workbench should be registred here.
\*----------------------------------------------------------------------------*/

pwr_dExport pwr_BindIoMethods(Modbus_TCP_Server)
    = { pwr_BindIoMethod(IoRackInit), pwr_BindIoMethod(IoRackRead),
        pwr_BindIoMethod(IoRackWrite), pwr_BindIoMethod(IoRackClose),
        pwr_NullMethod };
