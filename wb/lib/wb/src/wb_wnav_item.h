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

#ifndef wb_wnav_item_h
#define wb_wnav_item_h

#include "wb_wnav.h"

typedef enum {
  wnav_eItemType_Object,
  wnav_eItemType_Menu,
  wnav_eItemType_Command,
  wnav_eItemType_Local,
  wnav_eItemType_Header,
  wnav_eItemType_HeaderLarge,
  wnav_eItemType_Volume,
  wnav_eItemType_Attr,
  wnav_eItemType_AttrInput,
  wnav_eItemType_AttrInputF,
  wnav_eItemType_AttrInputInv,
  wnav_eItemType_AttrOutput,
  wnav_eItemType_AttrArray,
  wnav_eItemType_AttrArrayOutput,
  wnav_eItemType_AttrArrayElem,
  wnav_eItemType_AttrObject,
  wnav_eItemType_Enum,
  wnav_eItemType_Mask,
  wnav_eItemType_ObjectName,
  wnav_eItemType_File,
  wnav_eItemType_Text,
  wnav_eItemType_Crossref,
  wnav_eItemType_DocBlock,
  wnav_eItemType_ObjectModTime,
  wnav_eItemType_EnumObject,
  wnav_eItemType_LocalEnum
} wnav_eItemType;

typedef enum {
  item_eDisplayType_Attr,
  item_eDisplayType_Path
} item_eDisplayType;

typedef enum {
  item_eFileType_Unknown,
  item_eFileType_Script,
  item_eFileType_Graph
} item_eFileType;

class WItem {
public:
  WItem(pwr_tObjid item_objid, int item_is_root);
  virtual ~WItem();
  int open_attributes(WNav* wnav, double x, double y);
  int open_children(WNav* wnav, double x, double y);
  int open_trace(WNav* wnav, double x, double y);
  void close(WNav* wnav, double x, double y);
  virtual pwr_sAttrRef aref();
  wnav_eItemType type;
  pwr_tObjid objid;
  int is_root;
  brow_tNode node;
  pwr_tOName name;
};

class WItemBaseObject : public WItem {
public:
  WItemBaseObject(pwr_tObjid item_objid, int item_is_root);
  virtual ~WItemBaseObject();
  int open_children(WNav* wnav, double x, double y);
  int open_attributes(WNav* wnav, double x, double y);
  int close(WNav* wnav, double x, double y);
  int open_attribute(
      WNav* wnav, double x, double y, char* attr_name, int element);
  int open_crossref(WNav* wnav, double x, double y);
};

class WItemObject : public WItemBaseObject {
public:
  WItemObject(WNav* wnav, pwr_tObjid item_objid, brow_tNode dest,
      flow_eDest dest_code, int item_is_root);
  virtual ~WItemObject();
};

class WItemMenu : public WItem {
public:
  WItemMenu(WNav* wnav, const char* item_name, brow_tNode dest,
      flow_eDest dest_code, wnav_sMenu** item_child_list, int item_is_root);
  virtual ~WItemMenu();
  wnav_sMenu** child_list;
  int open_children(WNav* wnav, double x, double y);
  int close(WNav* wnav, double x, double y);
};

class WItemCommand : public WItem {
public:
  WItemCommand(WNav* wnav, const char* item_name, brow_tNode dest,
      flow_eDest dest_code, char* item_command, int item_is_root,
      flow_sAnnotPixmap* pixmap);
  virtual ~WItemCommand();
  char command[400];
  int open_children(WNav* wnav, double x, double y);
};

class WItemLocal : public WItem {
public:
  WItemLocal(WNav* wnav, const char* item_name, const char* attr, int attr_type,
      int attr_size, double attr_min_limit, double attr_max_limit,
      void* attr_value_p, brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemLocal();
  int open_children(WNav* wnav, double x, double y);
  void close(WNav* wnav, double x, double y);
  void* value_p;
  char old_value[80];
  int first_scan;
  int type_id;
  int size;
  double min_limit;
  double max_limit;
};

//! Item for a local enum attribute.
class WItemLocalEnum : public WItem {
public:
  WItemLocalEnum(WNav* wnav, char* item_name, int item_num, int item_type_id,
      int item_nochange, void* attr_value_p, brow_tNode dest, flow_eDest dest_code);
  int set_value(WNav* wnav);
  int num;
  int type_id;
  void* value_p;
  int old_value;
  int first_scan;
  int nochange;
};

class WItemText : public WItem {
public:
  WItemText(WNavBrow* brow, const char* item_name, char* text, brow_tNode dest,
      flow_eDest dest_code);
  virtual ~WItemText();
};

class WItemHeader : public WItem {
public:
  WItemHeader(WNavBrow* brow, const char* item_name, const char* title,
      brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemHeader();
};

class WItemHeaderLarge : public WItem {
public:
  WItemHeaderLarge(WNavBrow* brow, const char* item_name, char* title,
      brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemHeaderLarge();
};

class WItemVolume : public WItem {
public:
  WItemVolume(WNav* wnav, pwr_tVolumeId item_volid, brow_tNode dest,
      flow_eDest dest_code);
  virtual ~WItemVolume();
  pwr_tVolumeId volid;
  ldh_tVolContext volctx;
  int open_children(WNav* wnav, double x, double y);
  int close(WNav* wnav, double x, double y);
};

class WItemObjectName : public WItem {
public:
  WItemObjectName(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemObjectName();
  WNavBrow* brow;
  ldh_tSesContext ldhses;

  int open_children(double x, double y);
  int close(double x, double y);
  int update();
  int get_value(char** value); // The value should be freed with free
};

class WItemObjectModTime : public WItem {
public:
  WItemObjectModTime(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemObjectModTime();
  WNavBrow* brow;
  ldh_tSesContext ldhses;

  int update();
};

class WItemDocBlock : public WItem {
public:
  WItemDocBlock(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, char* block, int item_size, brow_tNode dest,
      flow_eDest dest_code);
  virtual ~WItemDocBlock();
  WNavBrow* brow;
  ldh_tSesContext ldhses;

  int update();
  int get_value(char** value); // The value should be freed with free
};

class WItemFile : public WItem {
public:
  WItemFile(WNav* wnav, const char* item_name, char* text, char* file,
      item_eFileType item_filetype, brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemFile();
  int open_children(WNav* wnav, double x, double y);
  char file_name[120];
  item_eFileType file_type;
};

class WItemCrossref : public WItem {
public:
  WItemCrossref(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      char* item_ref_name, char* item_ref_class, int item_write,
      brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemCrossref();
  WNavBrow* brow;
  ldh_tSesContext ldhses;
  char ref_name[32];
  char ref_class[32];
  int write;
};

class WItemBaseAttr : public WItem {
public:
  WItemBaseAttr(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, char* attr_name, int attr_type_id,
      pwr_tTid attr_tid, int attr_size, int attr_flags, char* attr_body);
  virtual ~WItemBaseAttr();
  WNavBrow* brow;
  ldh_tSesContext ldhses;
  int type_id;
  pwr_tTid tid;
  int size;
  int flags;
  pwr_tOName attr;
  char body[20];
  pwr_tClassId classid;

  virtual pwr_sAttrRef aref();
  int get_value(char** value); // The value should be freed with free
  int update()
  {
    return 1;
  }
};

class WItemAttr : public WItemBaseAttr {
public:
  WItemAttr(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_type_id, pwr_tTid attr_tid, int attr_size,
      int attr_flags, char* attr_body, int fullname);
  virtual ~WItemAttr();
  int open_children(double x, double y);
  int close(double x, double y);
  int update();
};

class WItemAttrInput : public WItemBaseAttr {
public:
  WItemAttrInput(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_type_id, pwr_tTid attr_tid, int attr_size,
      int attr_flags, char* attr_body, int attr_input_num);
  virtual ~WItemAttrInput();
  int update();
  int set_mask(int radio_button, int value);
  unsigned int mask;
};

class WItemAttrInputF : public WItemBaseAttr {
public:
  WItemAttrInputF(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_type_id, pwr_tTid attr_tid, int attr_size,
      int attr_flags, char* attr_body, int attr_input_num);
  virtual ~WItemAttrInputF();
  int update();
  int set_mask(int radio_button, int value);
  unsigned int mask;
};

class WItemAttrInputInv : public WItemBaseAttr {
public:
  WItemAttrInputInv(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_type_id, pwr_tTid attr_tid, int attr_size,
      int attr_flags, char* attr_body, int attr_input_num);
  virtual ~WItemAttrInputInv();
  int update();
  int set_mask(int radio_button, int value);
  unsigned int mask;
};

class WItemAttrOutput : public WItemBaseAttr {
public:
  WItemAttrOutput(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_type_id, pwr_tTid attr_tid, int attr_size,
      int attr_flags, char* attr_body, int attr_output_num);
  virtual ~WItemAttrOutput();
  int update();
  int set_mask(int radio_button, int value);
  unsigned int mask;
};

class WItemAttrArray : public WItemBaseAttr {
public:
  int elements;
  WItemAttrArray(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_elements, int attr_type_id, pwr_tTid attr_tid,
      int attr_size, int attr_flags, char* attr_body, int fullname);
  virtual ~WItemAttrArray();
  int open_children(double x, double y)
  {
    return 1;
  }
  int open_attributes(double x, double y);
  int close(double x, double y);
};

class WItemAttrArrayOutput : public WItemBaseAttr {
public:
  int elements;
  unsigned int mask;
  WItemAttrArrayOutput(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_elements, int attr_type_id, pwr_tTid attr_tid,
      int attr_size, int attr_flags, char* attr_body, int attr_output_num);
  virtual ~WItemAttrArrayOutput();
  int open_children(double x, double y)
  {
    return 1;
  }
  int open_attributes(double x, double y);
  int close(double x, double y);
  int update();
  int set_mask(int radio_button, int value);
};

class WItemAttrArrayElem : public WItemBaseAttr {
public:
  int element;
  int offset;
  WItemAttrArrayElem(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_element, int attr_type_id, pwr_tTid attr_tid,
      int attr_size, int attr_offset, int attr_flags, char* attr_body);
  virtual ~WItemAttrArrayElem();
  int open_children(double x, double y);
  int close(double x, double y);
  int update();
  int get_value(char** value);
};

class WItemAttrObject : public WItemBaseAttr {
public:
  bool is_elem;
  int idx;

  WItemAttrObject(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, brow_tNode dest, flow_eDest dest_code,
      char* attr_name, int attr_type_id, int attr_size, bool attr_is_elem,
      int attr_idx, int attr_flags, char* attr_body, int fullname);
  virtual ~WItemAttrObject();
  int open_children(double x, double y)
  {
    return 1;
  }
  int open_attributes(double x, double y);
  int open_crossref(WNav* wnav, double x, double y);
  int close(double x, double y);
};

class WItemEnum : public WItemBaseAttr {
public:
  WItemEnum(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, char* attr_enum_name, char* attr_name,
      int attr_type_id, pwr_tTid attr_tid, int attr_size, int attr_flags,
      char* attr_body, unsigned int item_num, int item_is_element,
      int item_element, brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemEnum();
  char enum_name[80];
  unsigned int num;
  int is_element;
  int element;

  int update();
  int set();
};

class WItemMask : public WItemBaseAttr {
public:
  WItemMask(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, char* attr_mask_name, char* attr_name,
      int attr_type_id, pwr_tTid attr_tid, int attr_size, int attr_flags,
      char* attr_body, unsigned int item_mask, int item_is_element,
      int item_element, brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemMask();
  char mask_name[40];
  unsigned int mask;
  int is_element;
  int element;

  int update();
  int set(int set_value);
};

class WItemEnumObject : public WItemBaseAttr {
public:
  WItemEnumObject(WNavBrow* item_brow, ldh_tSesContext item_ldhses,
      pwr_tObjid item_objid, char* attr_enum_name, char* attr_name,
      int attr_type_id, pwr_tTid attr_tid, int attr_size, int attr_flags,
      char* attr_body, void* item_enum_value, int item_is_element,
      int item_element, int item_idx, brow_tNode dest, flow_eDest dest_code);
  virtual ~WItemEnumObject();
  pwr_tOName enum_name;
  pwr_tAttrRef enum_aref;
  pwr_tString80 enum_string;
  int is_element;
  int element;

  int update();
  int set();
};

#endif
