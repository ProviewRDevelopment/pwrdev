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

#ifndef co_user_h
#define co_user_h

/* ge_user.h -- User authorization */

#include <fstream>

#include "pwr.h"

#if defined __cplusplus
extern "C" {
#endif

#define user_cFilename "pwra_db:pwr_user2.dat"
#define user_cVersion "V2.0.0"
#define user_cNId ((pwr_tOix)(~0))
#define FSPACE " "

typedef enum {
  user_eData_GeUser = 1,
  user_eData_System = 2,
  user_eData_User = 3,
  user_eData_End = 99,
  user_eData_GeUserVersion = 100,
  user_eData_GeNextId = 101,
  user_eData_SystemName = 200,
  user_eData_SystemLevel = 201,
  user_eData_SystemAttributes = 202,
  user_eData_SystemId = 203,
  user_eData_SystemDescription = 204,
  user_eData_UserName = 300,
  user_eData_UserPassword = 301,
  user_eData_UserPrivilege = 302,
  user_eData_UserId = 303,
  user_eData_UserDescription = 304,
  user_eData_UserFullName = 305,
  user_eData_UserPhone = 306,
  user_eData_UserEmail = 307,
  user_eData_UserSms = 308
} user_eData;

typedef enum { user_mSystemAttr_UserInherit = 1 } user_mSystemAttr;

class SystemName {
public:
  SystemName(const char* system_name);
  char pathname[80];
  char segname[10][40];
  int segments;

  int parse();
  SystemName* parent();
  char* name()
  {
    return pathname;
  }
  char* segment(int idx)
  {
    return segname[idx];
  }
};

class UserList;
class GeUser;

class SystemList {
  friend class GeUser;
  friend class UserList;

public:
  SystemList(pwr_tOix sl_id, const char* sl_name, int sl_level,
      unsigned int sl_attributes, char* sl_descr);

private:
  pwr_tObjName name;
  int level;
  pwr_tMask attributes;
  pwr_tOix id;
  pwr_tString80 description;
  SystemList* next;
  SystemList* childlist;
  UserList* userlist;

public:
  int load(std::ifstream& fp);
  void save(std::ofstream& fp);
  void print(int brief);
  void print_all(int brief);
  void* find_user(char* name);
  int add_user(pwr_tOix ident, char* user, char* password, pwr_tMask priv,
      char* fullname, char* descr, char* phone, char* email, char* sms);
  int add_system(
      pwr_tOix ident, SystemName* name, pwr_tMask attributes, char* descr);
  int load_system(std::ifstream& fp);
  int load_user(std::ifstream& fp);
  SystemList* find_system(SystemName* name);
  int remove_user(char* user);
  int remove_system(SystemList* sys);
  void modify(pwr_tMask attributes, char* description);
  void get_data(pwr_tMask* attributes, pwr_tOix* id, char* description);
  SystemList* first_system()
  {
    return childlist;
  }
  SystemList* next_system()
  {
    return next;
  }
  UserList* first_user()
  {
    return userlist;
  }
  char* get_name()
  {
    return name;
  }
  unsigned long get_attributes()
  {
    return attributes;
  }
  ~SystemList();
};

class UserList {
  friend class SystemList;
  friend class GeUser;

public:
  UserList(pwr_tOix ul_id, const char* ul_name, const char* ul_password,
      pwr_tMask ul_priv, const char* ul_fullname, const char* ul_description,
      const char* ul_email, const char* ul_phone, const char* ul_sms);

private:
  pwr_tObjName name;
  char password[40];
  pwr_tMask priv;
  pwr_tOix id;
  pwr_tString80 fullname;
  pwr_tString80 description;
  pwr_tString80 email;
  pwr_tString40 phone;
  pwr_tString40 sms;
  UserList* next;

  unsigned int icrypt(unsigned int i);
  unsigned int idecrypt(unsigned int i);

public:
  int load(std::ifstream& fp);
  void save(std::ofstream& fp);
  void print(int brief);
  void print_all(int brief);
  void modify(char* password, pwr_tMask priv, char* fullname, char* description,
      char* email, char* phone, char* sms);
  int check_password(char* password);
  void get_data(char* password, pwr_tMask* priv, pwr_tOix* id, char* fullname,
      char* description, char* email, char* phone, char* sms);
  UserList* next_user()
  {
    return next;
  }
  char* get_name()
  {
    return name;
  }
  void get_sms(char* s, int size);
  void get_email(char* s, int size);
  unsigned long get_priv()
  {
    return priv;
  }
  static char* pwcrypt(const char* str);
};

class GeUser {
  friend class SystemList;
  friend class UserList;

public:
  GeUser();
  ~GeUser();

private:
  SystemList* root;
  char version[20];
  char fname[256];
  pwr_tOix next_id;

  bool get_system_name_child(SystemList* s, SystemList* system, char* name);
  SystemList* get_system_child(SystemList* system, UserList* user);

public:
  int load(char* filename);
  void clear();
  int save()
  {
    return save(fname);
  }
  int save(char* filename);
  int load_system(std::ifstream& fp);
  void print(int brief);
  void print_all(int brief);
  SystemList* find_system(SystemName* name);
  int add_system(char* name, unsigned int attributes, char* description,
      pwr_tOix id = user_cNId);
  int add_user(char* system, char* user, char* password, unsigned int priv,
      char* fullname, char* description, char* email, char* phone, char* sms,
      pwr_tOix id = user_cNId);
  int remove_user(char* system, char* user);
  int modify_user(char* system, char* user, char* password, unsigned int priv,
      char* fullname, char* description, char* email, char* phone, char* sms);
  int get_user_data(char* system, char* user, char* password, pwr_tMask* priv,
      pwr_tOix* id, char* fullname, char* description, char* email, char* phone,
      char* sms);
  int modify_system(char* system, unsigned int attributes, char* description);
  int get_system_data(const char* system, pwr_tMask* attributes, pwr_tOix* id,
      char* description);
  int remove_system(char* name);
  int get_user(const char* system, const char* user, const char* password,
      unsigned int* priv);
  int get_user_priv(const char* system, const char* user, unsigned int* priv);
  char* get_status(int sts);
  SystemList* root_system()
  {
    return root;
  }
  SystemList* get_system(UserList* user);
  bool get_system_name(SystemList* system, char* name);
  pwr_tOix get_next_id()
  {
    return next_id++;
  }
  static void priv_to_string(unsigned int priv, char* str, int size);
  static void rt_priv_to_string(unsigned int priv, char* str, int size);
  static void dev_priv_to_string(unsigned int priv, char* str, int size);
};

#if defined __cplusplus
}
#endif
#endif
