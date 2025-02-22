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

#ifndef sev_valuecache_h
#define sev_valuecache_h

#include "co_time.h"
#include "rt_sev_msg.h"

typedef enum {
  sev_eCvType_Point,
  sev_eCvType_Mean,
} sev_eCvType;

typedef struct {
  double val;
  double time;
  double epsilon;
} sev_sCacheValueDouble;

typedef struct {
  pwr_tBoolean val;
  pwr_tTime time;
} sev_sCacheValueBool;

#define VALUECACHE_SIZE 20

class sev_valuecache {
public:
  sev_eCvType m_type;
  void* m_userdata;
  int m_useridx;
  void (*m_write_cb)(void*, int, void*, pwr_tTime*, void*);

  sev_valuecache(sev_eCvType type);
  sev_valuecache(const sev_valuecache& x);
  virtual ~sev_valuecache();
  virtual void add(void* value, pwr_tTime* time, void* thread);
  virtual int evaluate(double maxtime, void* thread);
  virtual void write(int index, void* thread);
  virtual void set_write_cb(
      void (*write_cb)(void*, int, void*, pwr_tTime*, void*), void* userdata,
      int idx);
};

class sev_valuecache_double : public sev_valuecache {
  static const int m_size;
  int m_length;
  int m_first;
  int m_last;
  bool m_inited;
  sev_sCacheValueDouble m_val[VALUECACHE_SIZE];
  sev_sCacheValueDouble m_wval;
  double m_k;
  double m_m;
  double m_deadband;
  double m_deadband_value;
  double m_deadband_time;
  int m_last_opt_write;
  pwr_tTime m_start_time;
  double m_last_k;

public:
  sev_valuecache_double(
      sev_eCvType type, double deadband_value, double deadband_time);
  sev_valuecache_double(const sev_valuecache_double& x);
  ~sev_valuecache_double();
  int length();
  int idx(int index);
  sev_sCacheValueDouble& operator[](const int index);
  sev_sCacheValueDouble& wval();
  void add(void* value, pwr_tTime* time, void* thread);
  int evaluate(double maxtime, void* thread);
  void calculate_k();
  void write(int index, void* thread);
  void calculate_epsilon();
  void calculate_epsilon(int index);
  bool check_deadband(int index);
  bool check_deadband();
  int get_optimal_write();
  double epsilon(int index);
  double get_k();
};

class sev_valuecache_bool : public sev_valuecache {
  bool m_inited;
  sev_sCacheValueBool m_val;
  sev_sCacheValueBool m_wval;

public:
  sev_valuecache_bool(sev_eCvType type);
  sev_valuecache_bool(const sev_valuecache_bool& x);
  ~sev_valuecache_bool();
  sev_sCacheValueBool& wval();
  void add(void* value, pwr_tTime* time, void* thread);
  int evaluate(double maxtime, void* thread);
  void write(int index, void* thread);
};

#endif
