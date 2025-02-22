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

#include "pwr_names.h"

#include "co_dcli.h"
#include "co_string.h"
#include "co_syi.h"

#include "rt_load.h"

#include "sev_db.h"
#include "sev_dbms.h"
#include "sev_dbsqlite.h"
#include "sev_dbhdf5.h"

char sev_db::m_orignode[80] = "";
char sev_db::m_systemName[40] = "";

sev_attr::sev_attr() : type(pwr_eType_), size(0), elem(0), ip(0), refid(pwr_cNRefId)
{
  strcpy(aname, "");
  strcpy(unit, "");
}

sev_attr::sev_attr(const sev_attr& x) : type(x.type), size(x.size), elem(x.elem),
					ip(x.ip), refid(x.refid)
{
  strncpy(aname, x.aname, sizeof(aname));
  strncpy(unit, x.unit, sizeof(unit));
}

sev_item::sev_item()
    : deadband_active(0), last_id(0), value_size(0), old_value(0),
      first_storage(1), status(0), logged_status(0), cache(0), idx(0),
      deleted(0), mean_value(0), mean_acc_time(0), variance_acc(0),
      variance_cnt(0)
{
  /*memset( old_value, 0, sizeof(old_value));*/
}

sev_item::sev_item(const sev_item& x)
    : id(x.id), oid(x.oid), creatime(x.creatime), modtime(x.modtime),
      storagetime(x.storagetime), sevid(x.sevid), scantime(x.scantime),
      deadband(x.deadband), options(x.options),
      deadband_active(x.deadband_active), last_id(x.last_id),
      value_size(x.value_size), old_value(x.old_value),
      first_storage(x.first_storage), attrnum(x.attrnum), attr(x.attr),
      status(x.status), logged_status(x.logged_status), cache(0), idx(x.idx),
      deleted(x.deleted), mean_value(x.mean_value),
      mean_acc_time(x.mean_acc_time), variance_cnt(x.variance_cnt)
{
  strncpy(tablename, x.tablename, sizeof(tablename));
  strncpy(oname, x.oname, sizeof(oname));
  strncpy(description, x.description, sizeof(description));
  if (x.cache)
    switch (attr[0].type) {
    case pwr_eType_Float32:
    case pwr_eType_Float64:
    case pwr_eType_Int32:
      cache = new sev_valuecache_double(*(sev_valuecache_double*)x.cache);
      break;
    case pwr_eType_Boolean:
      cache = new sev_valuecache_bool(*(sev_valuecache_bool*)x.cache);
      break;
    default:;
    }
}

sev_item& sev_item::operator=(const sev_item& x)
{
  id = x.id;
  oid = x.oid;
  creatime = x.creatime;
  modtime = x.modtime;
  storagetime = x.storagetime;
  sevid = x.sevid;
  scantime = x.scantime;  
  deadband = x.deadband;
  options = x.options;
  deadband_active = x.deadband_active;
  last_id = x.last_id;
  value_size = x.value_size;
  old_value = x.old_value;
  first_storage = x.first_storage;
  attrnum = x.attrnum;
  attr = x.attr;
  status = x.status;
  logged_status = x.logged_status;
  cache = 0;
  idx = x.idx;
  deleted = x.deleted;
  mean_value = x.mean_value;
  mean_acc_time = x.mean_acc_time;
  variance_cnt = x.variance_cnt;
  strncpy(tablename, x.tablename, sizeof(tablename));
  strncpy(oname, x.oname, sizeof(oname));
  strncpy(description, x.description, sizeof(description));
  if (x.cache)
    switch (attr[0].type) {
    case pwr_eType_Float32:
    case pwr_eType_Float64:
    case pwr_eType_Int32:
      cache = new sev_valuecache_double(*(sev_valuecache_double*)x.cache);
      break;
    case pwr_eType_Boolean:
      cache = new sev_valuecache_bool(*(sev_valuecache_bool*)x.cache);
      break;
    default:;
    }
  return *this;
}

sev_item::~sev_item()
{
  if (cache)
    delete cache;
}

sev_db::sev_db() : m_meanvalue_interval1(0), m_meanvalue_interval2(0)
{
  // strcpy(m_orignode, "");
}

sev_db::~sev_db()
{
}

int sev_db::check_item(pwr_tStatus* sts, pwr_tOid oid, char* oname, char* aname,
    pwr_tDeltaTime storatetime, pwr_eType type, unsigned int size,
    char* description, char* unit, pwr_tFloat32 scantime, pwr_tFloat32 deadband,
    pwr_tMask options, unsigned int* idx)
{
  *sts = 0;
  return 0;
}

int sev_db::add_item(pwr_tStatus* sts, pwr_tOid oid, char* oname, char* aname,
    pwr_tDeltaTime storagetime, pwr_eType type, unsigned int size,
    char* description, char* unit, pwr_tFloat32 scantime, pwr_tFloat32 deadband,
    pwr_tMask options, unsigned int* idx)
{
  *sts = 0;
  return 0;
}

int sev_db::delete_item(pwr_tStatus* sts, pwr_tOid oid, char* aname)
{
  *sts = 0;
  return 0;
}

int sev_db::store_value(pwr_tStatus* sts, void* thread, int item_idx,
    int attr_idx, pwr_tTime time, void* buf, unsigned int size)
{
  *sts = 0;
  return 0;
}

int sev_db::get_values(pwr_tStatus* sts, void* thread, pwr_tOid oid,
    pwr_tMask options, float deadband, char* aname, pwr_eType type,
    unsigned int size, pwr_tFloat32 scantime, pwr_tTime* creatime,
    pwr_tTime* starttime, pwr_tTime* endtime, int maxsize, pwr_tTime** tbuf,
    void** vbuf, unsigned int* bsize)
{
  *sts = 0;
  return 0;
}

int sev_db::get_items(pwr_tStatus* sts)
{
  *sts = 0;
  return 0;
}

int sev_db::delete_old_data(pwr_tStatus* sts, void* thread, char* tablename,
    pwr_tMask options, pwr_tTime limit, pwr_tFloat32 scantime,
    pwr_tFloat32 garbagecycle)
{
  *sts = 0;
  return 0;
}

int sev_db::check_objectitem(pwr_tStatus* sts, char* tablename, pwr_tOid oid,
    char* oname, char* aname, pwr_tDeltaTime storagetime, char* description,
    pwr_tFloat32 scantime, pwr_tFloat32 deadband, pwr_tMask options,
    unsigned int attrnum, sev_sHistAttr* attr, unsigned int* idx)
{
  *sts = 0;
  return 0;
}

int sev_db::add_objectitem(pwr_tStatus* sts, char* tablename, pwr_tOid oid,
    char* oname, char* aname, pwr_tDeltaTime storagetime, char* description,
    pwr_tFloat32 scantime, pwr_tFloat32 deadband, pwr_tMask options,
    unsigned int attrnum, sev_sHistAttr* attr, unsigned int* idx)
{
  *sts = 0;
  return 0;
}

int sev_db::store_objectitem(pwr_tStatus* sts, char* tablename, pwr_tOid oid,
    char* oname, char* aname, pwr_tDeltaTime storagetime, char* description,
    pwr_tFloat32 scantime, pwr_tFloat32 deadband, pwr_tMask options)
{
  return 0;
}

int sev_db::store_event(
    pwr_tStatus* sts, void* thread, int item_idx, sev_event* ep)
{
  *sts = 0;
  return 0;
}

int sev_db::get_item(pwr_tStatus* sts, void* thread, sev_item* item,
    pwr_tOid oid, char* attributename)
{
  *sts = 0;
  return 0;
}

int sev_db::get_objectitem(pwr_tStatus* sts, void* thread, sev_item* item,
    pwr_tOid oid, char* attributename)
{
  *sts = 0;
  return 0;
}

int sev_db::get_objectitems(pwr_tStatus* sts)
{
  *sts = 0;
  return 0;
}

int sev_db::check_objectitemattr(pwr_tStatus* sts, char* tablename,
    pwr_tOid oid, char* aname, char* oname, pwr_eType type, unsigned int size,
    unsigned int* idx)
{
  *sts = 0;
  return 0;
}

int sev_db::delete_old_objectdata(pwr_tStatus* sts, void* thread,
    char* tablename, pwr_tMask options, pwr_tTime limit, pwr_tFloat32 scantime,
    pwr_tFloat32 garbagecycle)
{
  *sts = 0;
  return 0;
}

int sev_db::get_objectvalues(pwr_tStatus* sts, void* thread, sev_item* item,
    unsigned int size, pwr_tTime* starttime, pwr_tTime* endtime, int maxsize,
    pwr_tTime** tbuf, void** vbuf, unsigned int* bsize)
{
  *sts = 0;
  return 0;
}

int sev_db::handle_objectchange(
    pwr_tStatus* sts, char* tablename, unsigned int item_idx, bool newObject)
{
  *sts = 0;
  return 0;
}

int sev_db::repair_table(pwr_tStatus* sts, char* tablename)
{
  *sts = 0;
  return 0;
}

int sev_db::alter_engine(pwr_tStatus* sts, char* tablename)
{
  *sts = 0;
  return 0;
}

int sev_db::optimize(pwr_tStatus* sts, char* tablename)
{
  *sts = 0;
  return 0;
}

int sev_db::store_stat(sev_sStat* stat)
{
  return 0;
}

int sev_db::begin_transaction(void* thread)
{
  return 0;
}

int sev_db::commit_transaction(void* thread)
{
  return 0;
}

char* sev_db::dbName()
{
  return 0;
}

void* sev_db::new_thread()
{
  return 0;
}

void sev_db::delete_thread(void* thread)
{
}

sev_db* sev_db::open_database(sev_eDbType type, sev_sDbConfig* cnf)
{
  sev_db* db = 0;

  if (type == sev_eDbType_Mysql) {
#if defined PWRE_CONF_MYSQL
    db = sev_dbms::open_database();
#else
    printf("** Release is not built with mysql\n");
#endif
  } else if (type == sev_eDbType_Sqlite) {
#if defined PWRE_CONF_SQLITE3
    db = sev_dbsqlite::open_database();
#else
    printf("** Release is not built with sqlite3\n");
#endif
  } else if (type == sev_eDbType_HDF5) {
#if defined PWRE_CONF_HDF5
    db = sev_dbhdf5::open_database();
#else
    printf("** Release is not built with HDF5\n");
#endif
  }
  if (db)
    db->m_cnf = *cnf;

  return db;
}

int sev_db::get_systemname()
{
  FILE* file;
  pwr_tFileName fname;
  char nodename[80];
  char* bus_str;
  int bus;
  char line[200];
  pwr_tStatus sts;

  if (!streq(m_systemName, ""))
    return 1;

  sev_db::get_orignode(nodename);
  if (streq(nodename, "")) {
    syi_NodeName(&sts, nodename, sizeof(nodename));
    if (EVEN(sts))
      return 0;
  }
  bus_str = getenv("PWR_BUS_ID");
  if (!bus_str)
    return 0;
  if (sscanf(bus_str, "%d", &bus) != 1)
    return 0;

  sprintf(fname, pwr_cNameBoot, load_cDirectory, cdh_Low(nodename), bus);
  dcli_translate_filename(fname, fname);
  file = fopen(fname, "r");
  if (file == 0) {
    printf("In %s row %d:\n", __FILE__, __LINE__);
    printf("** Warning, systemname not found\n");
    return 0;
  }

  if (!dcli_read_line(line, sizeof(line), file))
    return 0;
  if (!dcli_read_line(line, sizeof(line), file))
    return 0;

  strcpy(m_systemName, line);
  return 1;
}

void sev_db::get_item_idx(
    pwr_tStatus* sts, unsigned int* item_idx, pwr_tOid oid, char* attributename)
{
  for (unsigned int i = 0; i < m_items.size(); i++) {
    if (m_items[i].oid.oix == oid.oix && m_items[i].oid.vid == oid.vid
        && (str_NoCaseStrcmp(attributename, m_items[i].attr[0].aname) == 0)) {
      *item_idx = i;
      *sts = SEV__SUCCESS;
      return;
    }
  }
  *sts = SEV__NOSUCHITEM;
}

void sev_db::get_item_idx_by_name(
    pwr_tStatus* sts, unsigned int* item_idx, char* name)
{
  pwr_tAName aname;
  char *s;

  strncpy(aname, name, sizeof(aname));
  s = strchr(aname, '.');
  if (s == 0) {
    *sts = SEV__NOSUCHITEM;
    return;
  }
  *s = 0;
  s++;
	  
  for (unsigned int i = 0; i < m_items.size(); i++) {
    if ((str_NoCaseStrcmp(aname, m_items[i].oname) == 0)
        && (str_NoCaseStrcmp(s, m_items[i].attr[0].aname) == 0)) {
      *item_idx = i;
      *sts = SEV__SUCCESS;
      return;
    }
  }
  *sts = SEV__NOSUCHITEM;
}

int sev_db::get_events(pwr_tStatus *sts, void *thread, pwr_tOid oid,
    pwr_tMask options, pwr_tMask eventtypemask,
    pwr_tMask eventpriomask, char *eventtext, char *eventname,
    pwr_tTime *starttime, pwr_tTime *endtime, unsigned int numevents,
    std::vector<sev_event> &list)
{
  *sts = SEV__NYI;
  return 0;
}

