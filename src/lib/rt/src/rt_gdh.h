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

#ifndef rt_gdh_h
#define rt_gdh_h

/* rt_gdh.h
   This include file defines the global datastructures and
   data entities in GDH. Also, the GDH entry points are defined.  */

#if defined __cplusplus
extern "C" {
#endif

/*! \file rt_gdh.h
    \brief Include file for \ref GDH.
*/

/*
 *@example gdh_examples.c
 */

/** \addtogroup GDH */
/** @{*/

#include "rt_errh.h"

typedef pwr_tSubid gdh_tSubid;
typedef pwr_tSubid SUBID;
typedef pwr_tDlid gdh_tDlid;
typedef pwr_tDlid DLID;

/** \defgroup DS Gdh Data Structures
 *  @{
 */

/**
 * gdh_RefObjectInfoList parameter structure.
 */
typedef struct {
  pwr_tAName fullname; /**< Name of object or parameter */
  void* adrs; /**< Address of requested info */
  unsigned int bufsize; /**< Requested buffer size */
} gdh_sObjRef;

typedef gdh_sObjRef OBJREF_STRUCT;

/**
 * Link states
 */
typedef enum {
  gdh_eLinkState_Down, /**< Down. No connection */
  gdh_eLinkState_Istrt, /**< Start state I */
  gdh_eLinkState_Astrt, /**< Start state A */
  gdh_eLinkState_Up /**< Running. Now we're talking... */
} gdh_eLinkState;

/**
 * Node info
 */
typedef struct {
  pwr_tNodeId nodidx; /**< Node index (!= qcom qix #) */
  pwr_tUInt32 nix; /**< Network address */
  char nodename[32]; /**< Ascii name of node (nul-terminated) */
  /**< zero-length means empty slot */
  pwr_tObjid objid; /**< Node object for this node */
  gdh_eLinkState linkstate; /**< Nethandler down/istrt/astrt/up */

  pwr_tUInt32 upcnt; /**< # of times up */
  pwr_tTime timeup; /**< Most recent time link came up */
  pwr_tTime timedown; /**< Most recent time link went down */

} gdh_sNodeInfo;

/**
 * Volume info
 */
typedef struct {
  pwr_tBoolean isCached; /**< Volume is cached */
  pwr_tBoolean isLoaded; /**< Volume is loaded */
  pwr_tBoolean isMounted; /**< Volume is mounted */
  pwr_tTime time; /**< Version */
  char name[32]; /**< Ascii name of volume (null-terminated) */
  pwr_tCid cid; /**< Class of volume */
  pwr_tNid nid; /**< Node index */

} gdh_sVolumeInfo;

/**
 * Class info
 */
typedef struct {
  pwr_eEditor Editor;
  pwr_mClassDef Flags; /**< Class flags */
  pwr_eMethod Method;
  pwr_ePopEditorEnum PopEditor;
} gdh_sClassInfo;

/**
 * Attribute flags
 */
typedef enum {
  gdh_mAttrDef_Shadowed = 1 << 0, /**< Attribute is shadowed */
  gdh_mAttrDef_Super = 1 << 1 /**< Super class attribute */
} gdh_mAttrDef;

/**
 * Attribute info
 */
typedef struct {
  pwr_tObjName attrName; /**< Attribute name */
  unsigned long attrLevel; /**< Attribute level */
  pwr_eClass attrClass; /**< Attribute class */
  unsigned long flags; /**< Attribute flags */
  pwr_uParDef* attr; /**< Pointer to attribute object */

} gdh_sAttrDef;

/**
 * Enum value info
 */
typedef struct {
  pwr_tObjName Name; /**< Value name */
  pwr_sValue* Value; /**< Pointer to value object */

} gdh_sValueDef;

/**
 * Mask bit info
 */
typedef struct {
  pwr_tObjName Name; /**< Value name */
  pwr_sBit* Bit; /**< Pointer to bit object */

} gdh_sBitDef;

/** @} */

/* GDH entrypoints (as function prototypes).  */

/**
 * \defgroup GDHFC Gdh Functions
 * @{
 */

#define gdh_ClassNameToNumber gdh_ClassNameToId

pwr_tStatus gdh_ArefANameToAref(
    pwr_sAttrRef* arp, const char* aname, pwr_sAttrRef* oarp);

pwr_tStatus gdh_ArefDisabled(pwr_sAttrRef* arp, pwr_tDisableAttr* disabled);

pwr_tStatus gdh_AttrArefToObjectAref(pwr_sAttrRef* arp, pwr_sAttrRef* oarp);

pwr_tStatus gdh_AttrrefToName(pwr_sAttrRef* attributeReference,
    char* nameBuffer, unsigned int sizeOfNameBuffer, pwr_tBitMask nameType);

pwr_tStatus gdh_AttrRefToPointer(pwr_sAttrRef* arp, void** p);

pwr_tStatus gdh_AttrStringToValue(int type_id, char* value_str,
    void* buffer_ptr, int buff_size, int attr_size);

pwr_tStatus gdh_AttrValueToString(pwr_eType type_id, pwr_tTid tid,
    void* value_ptr, char* str, int size, int* len, char* format);

pwr_tStatus gdh_ClassAttrrefToAttr(pwr_tClassId classid,
    pwr_sAttrRef* attributeReference, char* nameBuffer, int sizeOfNameBuffer);

pwr_tStatus gdh_ClassAttrToAttrref(pwr_tClassId classid,
    const char* attributeName, pwr_sAttrRef* attributeReference);

pwr_tStatus gdh_ClassNameToId(const char* className, pwr_tClassId* classid);

pwr_tStatus gdh_CreateObject(char* objectName, pwr_tClassId classid,
    unsigned int sizeOfObjectData, pwr_tObjid* objectId, pwr_tObjid internal1,
    pwr_tBitMask internal2, pwr_tObjid internal3);

pwr_tStatus gdh_DeleteObject(pwr_tObjid objectId);

pwr_tStatus gdh_DeleteObjectTree(pwr_tObjid objectId);

pwr_tStatus gdh_DLRefObjectInfoAttrref(
    pwr_sAttrRef* addressOfAttributeReference, void** objectData,
    pwr_tDlid* directLinkId);

pwr_tStatus gdh_DLUnrefObjectInfo(pwr_tDlid directLinkId);

void gdh_DLUnrefObjectInfoAll(void);

pwr_tStatus gdh_FReadObject(char* filename, pwr_tAttrRef* arp);

pwr_tStatus gdh_FWriteObjectR(
    FILE* fp, char* ap, char* aname, pwr_tAttrRef* arp, pwr_tCid cid);

pwr_tStatus gdh_FWriteObject(char* filename, pwr_tAttrRef* arp);

pwr_tStatus gdh_GetAlarmInfo(pwr_tObjid object, pwr_tUInt32* alarmLevel,
    pwr_tUInt32* maxAlarmLevel, pwr_tUInt32* alarmBlockLevel,
    pwr_tUInt32* maxAlarmBlockLevel, pwr_tUInt32* alarmVisibility);

pwr_tStatus gdh_GetAttributeCharAttrref(pwr_sAttrRef* attributeReference,
    pwr_tTypeId* attributeType, unsigned int* attributeSize,
    unsigned int* attributeOffset, unsigned int* attributeDimension);

pwr_tStatus gdh_GetAttributeFlags(pwr_sAttrRef* arp, unsigned int* flags);

pwr_tStatus gdh_GetAttributeCharacteristics(char* name, pwr_tTypeId* tid,
    pwr_tUInt32* size, pwr_tUInt32* offs, pwr_tUInt32* elem);

pwr_tStatus gdh_GetAttrRefTid(pwr_sAttrRef* arp, pwr_tTid* tid);

pwr_tStatus gdh_GetChild(pwr_tObjid object, pwr_tObjid* firstChild);

pwr_tStatus gdh_GetClassList(pwr_tClassId classid, pwr_tObjid* object);

pwr_tStatus gdh_GetClassListAttrRef(pwr_tClassId cid, pwr_sAttrRef* arp);

pwr_tStatus gdh_GetDynamicAttrSize(
    pwr_tObjid oid, char* name, pwr_tUInt32* size);

pwr_tStatus gdh_GetEnumValueDef(pwr_tTid tid, gdh_sValueDef** vd, int* rows);

pwr_tStatus gdh_GetLocalParent(pwr_tObjid object, pwr_tObjid* parent);

pwr_tStatus gdh_GetMaskBitDef(pwr_tTid tid, gdh_sBitDef** bd, int* rows);

pwr_tStatus gdh_GetNextAttrRef(
    pwr_tClassId cid, pwr_sAttrRef* arp, pwr_sAttrRef* new_arp);

pwr_tStatus gdh_GetNextObject(pwr_tObjid object, pwr_tObjid* nextObject);

pwr_tStatus gdh_GetNextObjectAttrRef(
    pwr_tClassId cid, /**< The class identity. */
    pwr_sAttrRef* arp, /**< The attribute reference. */
    pwr_sAttrRef* new_arp /**< Receives the attribute reference */
    );

pwr_tStatus gdh_GetNextSibling(pwr_tObjid object, pwr_tObjid* nextSibling);

pwr_tStatus gdh_GetNextVolume(pwr_tVid pvid, pwr_tVid* vid);

pwr_tStatus gdh_GetNodeIndex(pwr_tNodeId* nodeIndex);

pwr_tStatus gdh_GetNodeInfo(pwr_tNodeId nodidx, gdh_sNodeInfo* ip);

pwr_tStatus gdh_GetNodeObject(pwr_tNodeId nodeIndex, pwr_tObjid* object);

pwr_tStatus gdh_GetClassInfo(pwr_tCid cid, gdh_sClassInfo *info);

pwr_tStatus gdh_GetObjectClass(pwr_tObjid object, pwr_tClassId* classid);

pwr_tStatus gdh_GetObjectClassList(pwr_tCid cid, /**< The class identity. */
    pwr_tOid oid, /**< Host object. */
    pwr_sAttrRef* arp /**< Receives the attribute reference. */
    );

pwr_tStatus gdh_GetObjectDLCount(pwr_tObjid object, pwr_tUInt32* count);

pwr_tStatus gdh_GetObjectInfo(
    const char* name, pwr_tAddress bufp, pwr_tUInt32 bufsize);

pwr_tStatus gdh_GetObjectInfoAttrref(
    pwr_sAttrRef* attributeReference, void* buffer, unsigned int sizeOfBuffer);

pwr_tStatus gdh_GetObjectLocation(pwr_tObjid object, pwr_tBoolean* isLocal);

pwr_tStatus gdh_GetObjectNodeIndex(pwr_tObjid object, pwr_tNodeId* nodeIndex);

pwr_tStatus gdh_GetObjectSize(pwr_tObjid oid, pwr_tUInt32* size);

pwr_tStatus gdh_GetParent(pwr_tObjid object, pwr_tObjid* parent);

pwr_tStatus gdh_GetPreviousObject(
    pwr_tObjid object, pwr_tObjid* previousObject);

pwr_tStatus gdh_GetPreviousSibling(
    pwr_tObjid object, pwr_tObjid* previousSibling);

pwr_tStatus gdh_GetRootList(pwr_tObjid* object);

pwr_tStatus gdh_GetSecurityInfo(pwr_sSecurity* security);

pwr_tStatus gdh_GetVolumeInfo(pwr_tVid vid, gdh_sVolumeInfo* info);

pwr_tStatus gdh_GetVolumeList(pwr_tVid* vid);

pwr_tStatus gdh_GetRootVolume(pwr_tVid* vid);

pwr_tStatus gdh_SearchFile(pwr_tOid oid, char* dir, char* pattern,
    pwr_tString40* filelist[], int* filecnt);

pwr_tStatus gdh_GetSubscriptionOldness(pwr_tSubid subid, pwr_tBoolean* isOld,
    pwr_tTime* lastUpdate, pwr_tStatus* lastStatus);

pwr_tStatus gdh_GetSuperClass(pwr_tCid cid, pwr_tCid* supercid, pwr_tObjid oid);

pwr_tStatus gdh_Init(const char* name);

pwr_tBoolean gdh_IsInitialized();

pwr_tStatus gdh_MountObjidToPointer(pwr_tObjid object, void** objectData);

pwr_tStatus gdh_MoveObject(pwr_tObjid objectId, pwr_tObjid newParentId);

pwr_tStatus gdh_NameToAttrref(pwr_tObjid parent, const char* attributeName,
    pwr_sAttrRef* attributeReference);

pwr_tStatus gdh_NameToObjid(const char* objectName, pwr_tObjid* objid);

pwr_tStatus gdh_NameToPointer(const char* objectName, void** objectData);

pwr_tStatus gdh_NethandlerRunning(void);

pwr_tStatus gdh_ObjidToName(
    pwr_tObjid oid, char* namebuf, pwr_tUInt32 size, pwr_tBitMask nametype);

pwr_tStatus gdh_ObjidToPointer(pwr_tObjid object, void** objectData);

pwr_tStatus gdh_RefObjectInfo(char* attributeName, void** objectData,
    pwr_tSubid* subid, unsigned int sizeOfObjectData);

pwr_tStatus gdh_RefObjectInfoList(
    unsigned int nEntry, gdh_sObjRef* objectReference, pwr_tSubid* subid);

pwr_tStatus gdh_RenameObject(pwr_tObjid objectId, char* newObjectName);

pwr_tStatus gdh_SetAlarmBlockLevel(
    pwr_tObjid object, pwr_tUInt32 alarmBlockLevel);

pwr_tStatus gdh_SetAlarmLevel(pwr_tObjid object, pwr_tUInt32 alarmLevel);

pwr_tStatus gdh_SetObjectInfo(
    const char* attributeName, void* buffer, unsigned int sizeOfBuffer);

pwr_tStatus gdh_SetObjectInfoAttrref(
    pwr_sAttrRef* attributeReference, void* buffer, unsigned int sizeOfBuffer);

pwr_tStatus gdh_SubAssociateBuffer(
    pwr_tSubid subid, void** buffer, unsigned int sizeOfBuffer);

pwr_tStatus gdh_SubData(
    pwr_tSubid subid, void* buffer, unsigned int sizeOfBuffer);

pwr_tStatus gdh_SubRefObjectInfoAttrref(
    pwr_sAttrRef* attributeReference, pwr_tSubid* subid);

pwr_tStatus gdh_SubRefObjectInfoList(unsigned int entryCount, void* object[],
    pwr_tBoolean isAttrref[], pwr_tSubid subid[]);

pwr_tStatus gdh_SubRefObjectInfoName(char* attributeName, pwr_tSubid* subid);

pwr_tStatus gdh_SubSize(pwr_tSubid subid, unsigned int* size);

pwr_tStatus gdh_SetSubscriptionDefaults(
    pwr_tInt32 defaultUpdateTime, pwr_tInt32 defaultTimeOut);

pwr_tStatus gdh_SubUnrefObjectInfo(pwr_tSubid subid);

void gdh_SubUnrefObjectInfoAll(void);

pwr_tStatus gdh_SubUnrefObjectInfoList(unsigned int nEntry, pwr_tSubid* subid);

pwr_tStatus gdh_UnrefObjectInfo(pwr_tSubid subid);

pwr_tStatus gdh_UnrefObjectInfoAll(void);

pwr_tStatus gdh_VolumeIdToName(pwr_tVid vid, char* name, int size);

/*
 * Translation between Rtdb reference and job context virtual address formats.
 */

void gdh_StoreRtdbPointer(unsigned long* rtdbReference, void* virtualAddress);

void* gdh_TranslateRtdbPointer(unsigned long rtdbReference);

pwr_tStatus gdh_GetObjectBodyDef(
    pwr_tCid cid, gdh_sAttrDef** bodydef, int* rows, pwr_tOid oid);

/* Thread safe functions for times and strings */
void gdh_GetTimeDL(pwr_tTime* atp, pwr_tTime* time);
void gdh_SetTimeDL(pwr_tTime* atp, pwr_tTime* time);
void gdh_GetDeltaTimeDL(pwr_tDeltaTime* dtp, pwr_tDeltaTime* time);
void gdh_SetDeltaTimeDL(pwr_tDeltaTime* dtp, pwr_tDeltaTime* time);
void gdh_GetStrDL(char* sp, char* str, int size);
void gdh_SetStrDL(char* sp, const char* str, int size);
pwr_tStatus gdh_GetObjectInfoTime(const char* name, pwr_tTime* time);
pwr_tStatus gdh_SetObjectInfoTime(const char* name, pwr_tTime* time);
pwr_tStatus gdh_GetObjectInfoDeltaTime(const char* name, pwr_tDeltaTime* time);
pwr_tStatus gdh_SetObjectInfoDeltaTime(const char* name, pwr_tDeltaTime* time);
pwr_tStatus gdh_GetObjectInfoStr(const char* name, char* str, int size);
pwr_tStatus gdh_SetObjectInfoStr(const char* name, const char* str, int size);
/** @} */

void gdh_InitialLoadDone(pwr_tObjid systemobject, pwr_tObjid nodeobject);

pwr_tStatus gdh_IsAlias(pwr_tObjid object, pwr_tBoolean* isAlias);

pwr_tStatus gdh_IsMountClean(pwr_tObjid object, pwr_tBoolean* isMountClean);

/*
 * Exclusive mode
 */

void gdh_ExclusiveModeOn(void);

void gdh_ExclusiveModeOff(void);

pwr_tStatus gdh_GetTrueObjectBodyDef(
    pwr_tCid cid, gdh_sAttrDef** bodydef, int* rows);

pwr_tStatus gdh_GetAttrRefAdef(pwr_sAttrRef* arp, gdh_sAttrDef* attrdef);

pwr_tStatus gdh_SetObjectReadOnly(pwr_tOid oid);

/* Undocumented functions. For internal use only.  */

pwr_tStatus gdh_MDAttribute(pwr_tClassId classid,
    pwr_sAttrRef* attributeReference, char* attributeName,
    pwr_tTypeId* attributeType, unsigned int* attributeSize,
    unsigned int* attributeOffset, unsigned int* attributeDimension);

pwr_tStatus gdh_SetCache(
    pwr_tUInt32 activation_level, pwr_tUInt32 trimmed_level);

void gdh_RegisterLogFunction(void (*func)(char*, void*, unsigned int));

pwr_tStatus gdh_GetSubClassList(pwr_tCid cid, pwr_tCid* subcid);

pwr_tStatus gdh_GetNextSubClass(
    pwr_tCid cid, pwr_tCid psubcid, pwr_tCid* subcid);

pwr_tStatus gdh_GetGlobalClassList(int cidcnt, pwr_tCid* cid, int attrobjects,
    pwr_tAttrRef* classlist[], int* listcnt);

pwr_tStatus gdh_GetLocalClassList(int cidcnt, pwr_tCid* cid, int attrobjects,
    pwr_tAttrRef* classlist[], int* listcnt);

pwr_tStatus gdh_CheckLocalObject(pwr_tOid oid);
pwr_tStatus gdh_TidToType(pwr_tTid tid, pwr_eType *type);
pwr_tStatus gdh_MountDynClients(void);

/** @}*/

#if defined __cplusplus
}
#endif
#endif
