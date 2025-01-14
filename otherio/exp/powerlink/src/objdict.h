//-------------------------------
//  OD for a simple DS401 slave
//-------------------------------

#define EPL_OBD_DEFINE_MACRO
#include "EplObdMacro.h"
#undef EPL_OBD_DEFINE_MACRO

EPL_OBD_BEGIN()

EPL_OBD_BEGIN_PART_GENERIC()

#include "../Generic/objdict_1000-13ff.h"

// Object 1400h: PDO_RxCommParam_00h_REC
EPL_OBD_BEGIN_INDEX_RAM(0x1400, 0x03, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1400, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0x02)
EPL_OBD_SUBINDEX_RAM_VAR(0x1400, 0x01, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NodeID_U8, 0x00)
EPL_OBD_SUBINDEX_RAM_VAR(0x1400, 0x02, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, MappingVersion_U8, 0x00)
EPL_OBD_END_INDEX(0x1400)

// Object 1401h: PDO_RxCommParam_01h_REC
EPL_OBD_BEGIN_INDEX_RAM(0x1401, 0x03, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1401, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0x02)
EPL_OBD_SUBINDEX_RAM_VAR(0x1401, 0x01, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NodeID_U8, 0x00)
EPL_OBD_SUBINDEX_RAM_VAR(0x1401, 0x02, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, MappingVersion_U8, 0x00)
EPL_OBD_END_INDEX(0x1401)

// Object 1402h: PDO_RxCommParam_02h_REC
EPL_OBD_BEGIN_INDEX_RAM(0x1402, 0x03, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1402, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0x02)
EPL_OBD_SUBINDEX_RAM_VAR(0x1402, 0x01, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NodeID_U8, 0x00)
EPL_OBD_SUBINDEX_RAM_VAR(0x1402, 0x02, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, MappingVersion_U8, 0x00)
EPL_OBD_END_INDEX(0x1402)

// Object 1600h: PDO_RxMappParam_00h_AU64
EPL_OBD_BEGIN_INDEX_RAM(0x1600, 0x1A, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x00, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NumberOfEntries, 0x00)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x01, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x02, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x03, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x04, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x05, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x06, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x07, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x08, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x09, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x0A, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x0B, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x0C, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x0D, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x0E, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x0F, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x10, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x11, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x12, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x13, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x14, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x15, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x16, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x17, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x18, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1600, 0x19, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_END_INDEX(0x1600)

// Object 1601h: PDO_RxMappParam_01h_AU64
EPL_OBD_BEGIN_INDEX_RAM(0x1601, 0x1A, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x00, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NumberOfEntries, 0x00)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x01, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x02, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x03, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x04, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x05, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x06, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x07, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x08, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x09, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x0A, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x0B, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x0C, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x0D, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x0E, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x0F, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x10, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x11, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x12, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x13, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x14, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x15, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x16, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x17, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x18, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1601, 0x19, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_END_INDEX(0x1601)

// Object 1602h: PDO_RxMappParam_02h_AU64
EPL_OBD_BEGIN_INDEX_RAM(0x1602, 0x1A, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x00, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NumberOfEntries, 0x00)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x01, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x02, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x03, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x04, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x05, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x06, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x07, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x08, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x09, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x0A, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x0B, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x0C, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x0D, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x0E, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x0F, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x10, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x11, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x12, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x13, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x14, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x15, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x16, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x17, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x18, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1602, 0x19, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_END_INDEX(0x1602)

// Object 1800h: PDO_TxCommParam_00h_REC
EPL_OBD_BEGIN_INDEX_RAM(0x1800, 0x03, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1800, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0x02)
EPL_OBD_SUBINDEX_RAM_VAR(0x1800, 0x01, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NodeID_U8, 0x00)
EPL_OBD_SUBINDEX_RAM_VAR(0x1800, 0x02, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, MappingVersion_U8, 0x00)
EPL_OBD_END_INDEX(0x1800)

// Object 1A00h: PDO_TxMappParam_00h_AU64
EPL_OBD_BEGIN_INDEX_RAM(0x1A00, 0x1A, EplPdouCbObdAccess)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x00, kEplObdTypUInt8, kEplObdAccRW,
    tEplObdUnsigned8, NumberOfEntries, 0x0)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x01, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x02, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x03, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x04, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x05, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x06, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x07, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x08, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x09, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0A, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0B, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0C, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0D, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0E, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x0F, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x10, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x11, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x12, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x13, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x14, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x15, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x16, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x17, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x18, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_SUBINDEX_RAM_VAR(0x1A00, 0x19, kEplObdTypUInt64, kEplObdAccRW,
    tEplObdUnsigned64, ObjectMapping, 0x00LL)
EPL_OBD_END_INDEX(0x1A00)

#include "../Generic/objdict_1b00-1fff.h"

EPL_OBD_END_PART()

EPL_OBD_BEGIN_PART_DEVICE()

// DigitalInput_00h_AU8
EPL_OBD_BEGIN_INDEX_RAM(0x6000, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6000, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x01, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x02, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x03, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x04, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x05, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x06, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x07, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x08, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x09, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x0a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x0b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x0c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x0d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x0e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x0f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x10, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x11, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x12, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x13, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x14, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x15, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x16, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x17, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x18, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x19, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x1a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x1b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x1c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x1d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x1e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x1f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x20, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x21, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x22, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x23, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x24, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x25, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x26, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x27, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x28, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x29, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x2a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x2b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x2c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x2d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x2e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x2f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x30, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x31, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x32, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x33, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x34, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x35, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x36, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x37, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x38, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x39, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x3a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x3b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x3c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x3d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x3e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x3f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x40, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x41, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x42, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x43, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x44, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x45, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x46, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x47, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x48, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x49, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x4a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x4b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x4c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x4d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x4e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x4f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x50, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x51, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x52, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x53, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x54, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x55, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x56, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x57, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x58, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x59, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x5a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x5b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x5c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x5d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x5e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x5f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x60, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x61, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x62, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x63, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x64, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x65, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x66, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x67, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x68, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x69, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x6a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x6b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x6c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x6d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x6e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x6f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x70, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x71, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x72, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x73, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x74, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x75, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x76, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x77, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x78, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x79, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x7a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x7b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x7c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x7d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x7e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x7f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x80, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x81, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x82, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x83, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x84, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x85, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x86, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x87, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x88, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x89, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x8a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x8b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x8c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x8d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x8e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x8f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x90, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x91, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x92, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x93, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x94, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x95, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x96, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x97, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x98, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x99, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x9a, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x9b, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x9c, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x9d, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x9e, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0x9f, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa0, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa1, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa2, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa3, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa4, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa5, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa6, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa7, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa8, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xa9, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xaa, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xab, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xac, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xad, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xae, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xaf, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb0, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb1, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb2, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb3, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb4, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb5, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb6, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb7, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb8, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xb9, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xba, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xbb, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xbc, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xbd, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xbe, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xbf, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc0, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc1, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc2, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc3, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc4, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc5, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc6, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc7, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc8, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xc9, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xca, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xcb, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xcc, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xcd, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xce, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xcf, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd0, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd1, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd2, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd3, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd4, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd5, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd6, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd7, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd8, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xd9, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xda, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xdb, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xdc, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xdd, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xde, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xdf, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe0, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe1, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe2, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe3, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe4, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe5, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe6, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe7, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe8, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xe9, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xea, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xeb, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xec, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xed, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xee, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xef, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf0, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf1, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf2, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf3, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf4, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf5, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf6, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf7, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf8, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xf9, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xfa, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xfb, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xfc, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xfd, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6000, 0xfe, kEplObdTypUInt8, kEplObdAccVPR,
    tEplObdUnsigned8, DigitalInput, 0x00)
EPL_OBD_END_INDEX(0x6000)

// DigitalOutput_00h_AU8
EPL_OBD_BEGIN_INDEX_RAM(0x6200, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6200, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x01, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x02, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x03, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x04, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x05, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x06, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x07, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x08, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x09, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x0a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x0b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x0c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x0d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x0e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x0f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x10, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x11, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x12, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x13, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x14, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x15, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x16, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x17, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x18, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x19, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x1a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x1b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x1c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x1d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x1e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x1f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x20, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x21, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x22, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x23, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x24, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x25, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x26, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x27, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x28, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x29, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x2a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x2b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x2c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x2d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x2e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x2f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x30, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x31, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x32, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x33, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x34, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x35, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x36, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x37, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x38, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x39, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x3a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x3b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x3c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x3d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x3e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x3f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x40, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x41, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x42, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x43, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x44, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x45, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x46, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x47, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x48, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x49, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x4a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x4b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x4c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x4d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x4e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x4f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x50, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x51, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x52, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x53, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x54, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x55, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x56, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x57, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x58, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x59, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x5a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x5b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x5c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x5d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x5e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x5f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x60, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x61, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x62, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x63, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x64, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x65, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x66, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x67, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x68, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x69, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x6a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x6b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x6c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x6d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x6e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x6f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x70, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x71, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x72, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x73, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x74, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x75, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x76, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x77, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x78, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x79, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x7a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x7b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x7c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x7d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x7e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x7f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x80, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x81, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x82, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x83, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x84, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x85, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x86, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x87, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x88, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x89, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x8a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x8b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x8c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x8d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x8e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x8f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x90, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x91, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x92, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x93, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x94, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x95, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x96, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x97, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x98, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x99, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x9a, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x9b, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x9c, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x9d, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x9e, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0x9f, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa0, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa1, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa2, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa3, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa4, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa5, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa6, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa7, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa8, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xa9, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xaa, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xab, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xac, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xad, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xae, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xaf, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb0, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb1, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb2, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb3, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb4, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb5, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb6, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb7, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb8, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xb9, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xba, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xbb, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xbc, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xbd, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xbe, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xbf, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc0, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc1, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc2, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc3, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc4, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc5, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc6, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc7, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc8, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xc9, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xca, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xcb, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xcc, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xcd, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xce, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xcf, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd0, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd1, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd2, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd3, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd4, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd5, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd6, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd7, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd8, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xd9, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xda, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xdb, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xdc, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xdd, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xde, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xdf, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe0, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe1, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe2, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe3, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe4, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe5, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe6, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe7, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe8, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xe9, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xea, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xeb, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xec, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xed, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xee, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xef, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf0, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf1, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf2, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf3, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf4, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf5, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf6, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf7, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf8, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xf9, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xfa, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xfb, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xfc, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xfd, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6200, 0xfe, kEplObdTypUInt8, kEplObdAccVPRW,
    tEplObdUnsigned8, DigitalOutput, 0x00)
EPL_OBD_END_INDEX(0x6200)

// AnalogueInput_00h_AI8
EPL_OBD_BEGIN_INDEX_RAM(0x6400, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6400, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x01, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x02, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x03, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x04, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x05, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x06, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x07, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x08, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x09, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x0a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x0b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x0c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x0d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x0e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x0f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x10, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x11, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x12, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x13, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x14, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x15, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x16, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x17, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x18, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x19, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x1a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x1b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x1c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x1d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x1e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x1f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x20, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x21, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x22, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x23, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x24, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x25, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x26, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x27, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x28, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x29, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x2a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x2b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x2c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x2d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x2e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x2f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x30, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x31, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x32, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x33, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x34, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x35, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x36, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x37, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x38, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x39, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x3a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x3b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x3c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x3d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x3e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x3f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x40, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x41, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x42, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x43, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x44, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x45, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x46, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x47, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x48, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x49, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x4a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x4b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x4c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x4d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x4e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x4f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x50, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x51, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x52, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x53, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x54, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x55, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x56, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x57, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x58, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x59, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x5a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x5b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x5c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x5d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x5e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x5f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x60, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x61, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x62, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x63, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x64, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x65, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x66, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x67, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x68, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x69, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x6a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x6b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x6c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x6d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x6e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x6f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x70, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x71, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x72, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x73, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x74, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x75, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x76, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x77, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x78, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x79, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x7a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x7b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x7c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x7d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x7e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x7f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x80, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x81, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x82, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x83, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x84, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x85, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x86, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x87, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x88, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x89, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x8a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x8b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x8c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x8d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x8e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x8f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x90, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x91, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x92, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x93, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x94, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x95, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x96, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x97, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x98, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x99, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x9a, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x9b, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x9c, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x9d, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x9e, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0x9f, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa0, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa1, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa2, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa3, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa4, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa5, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa6, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa7, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa8, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xa9, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xaa, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xab, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xac, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xad, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xae, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xaf, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb0, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb1, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb2, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb3, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb4, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb5, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb6, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb7, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb8, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xb9, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xba, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xbb, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xbc, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xbd, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xbe, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xbf, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc0, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc1, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc2, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc3, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc4, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc5, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc6, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc7, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc8, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xc9, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xca, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xcb, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xcc, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xcd, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xce, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xcf, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd0, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd1, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd2, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd3, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd4, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd5, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd6, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd7, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd8, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xd9, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xda, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xdb, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xdc, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xdd, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xde, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xdf, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe0, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe1, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe2, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe3, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe4, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe5, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe6, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe7, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe8, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xe9, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xea, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xeb, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xec, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xed, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xee, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xef, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf0, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf1, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf2, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf3, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf4, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf5, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf6, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf7, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf8, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xf9, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xfa, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xfb, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xfc, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xfd, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6400, 0xfe, kEplObdTypInt8, kEplObdAccVPR,
    tEplObdInteger8, AnalogueInput, 0x00)
EPL_OBD_END_INDEX(0x6400)

// AnalogueInput_00h_AI16
EPL_OBD_BEGIN_INDEX_RAM(0x6401, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6401, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x01, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x02, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x03, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x04, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x05, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x06, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x07, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x08, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x09, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x0a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x0b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x0c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x0d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x0e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x0f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x10, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x11, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x12, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x13, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x14, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x15, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x16, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x17, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x18, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x19, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x1a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x1b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x1c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x1d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x1e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x1f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x20, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x21, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x22, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x23, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x24, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x25, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x26, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x27, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x28, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x29, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x2a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x2b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x2c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x2d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x2e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x2f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x30, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x31, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x32, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x33, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x34, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x35, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x36, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x37, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x38, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x39, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x3a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x3b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x3c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x3d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x3e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x3f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x40, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x41, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x42, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x43, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x44, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x45, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x46, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x47, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x48, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x49, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x4a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x4b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x4c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x4d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x4e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x4f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x50, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x51, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x52, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x53, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x54, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x55, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x56, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x57, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x58, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x59, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x5a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x5b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x5c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x5d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x5e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x5f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x60, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x61, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x62, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x63, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x64, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x65, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x66, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x67, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x68, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x69, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x6a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x6b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x6c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x6d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x6e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x6f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x70, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x71, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x72, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x73, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x74, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x75, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x76, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x77, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x78, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x79, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x7a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x7b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x7c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x7d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x7e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x7f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x80, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x81, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x82, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x83, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x84, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x85, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x86, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x87, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x88, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x89, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x8a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x8b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x8c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x8d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x8e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x8f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x90, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x91, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x92, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x93, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x94, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x95, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x96, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x97, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x98, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x99, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x9a, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x9b, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x9c, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x9d, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x9e, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0x9f, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa0, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa1, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa2, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa3, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa4, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa5, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa6, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa7, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa8, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xa9, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xaa, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xab, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xac, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xad, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xae, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xaf, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb0, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb1, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb2, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb3, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb4, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb5, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb6, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb7, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb8, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xb9, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xba, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xbb, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xbc, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xbd, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xbe, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xbf, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc0, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc1, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc2, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc3, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc4, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc5, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc6, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc7, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc8, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xc9, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xca, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xcb, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xcc, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xcd, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xce, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xcf, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd0, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd1, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd2, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd3, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd4, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd5, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd6, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd7, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd8, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xd9, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xda, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xdb, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xdc, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xdd, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xde, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xdf, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe0, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe1, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe2, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe3, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe4, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe5, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe6, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe7, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe8, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xe9, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xea, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xeb, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xec, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xed, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xee, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xef, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf0, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf1, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf2, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf3, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf4, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf5, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf6, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf7, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf8, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xf9, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xfa, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xfb, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xfc, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xfd, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6401, 0xfe, kEplObdTypInt16, kEplObdAccVPR,
    tEplObdInteger16, AnalogueInput, 0x0000)
EPL_OBD_END_INDEX(0x6401)

// AnalogueInput_00h_AI32
EPL_OBD_BEGIN_INDEX_RAM(0x6402, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6402, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x01, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x02, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x03, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x04, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x05, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x06, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x07, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x08, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x09, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x0a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x0b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x0c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x0d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x0e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x0f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x10, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x11, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x12, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x13, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x14, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x15, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x16, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x17, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x18, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x19, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x1a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x1b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x1c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x1d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x1e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x1f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x20, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x21, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x22, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x23, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x24, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x25, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x26, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x27, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x28, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x29, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x2a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x2b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x2c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x2d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x2e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x2f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x30, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x31, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x32, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x33, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x34, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x35, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x36, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x37, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x38, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x39, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x3a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x3b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x3c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x3d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x3e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x3f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x40, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x41, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x42, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x43, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x44, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x45, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x46, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x47, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x48, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x49, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x4a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x4b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x4c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x4d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x4e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x4f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x50, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x51, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x52, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x53, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x54, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x55, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x56, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x57, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x58, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x59, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x5a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x5b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x5c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x5d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x5e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x5f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x60, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x61, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x62, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x63, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x64, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x65, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x66, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x67, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x68, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x69, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x6a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x6b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x6c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x6d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x6e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x6f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x70, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x71, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x72, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x73, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x74, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x75, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x76, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x77, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x78, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x79, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x7a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x7b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x7c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x7d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x7e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x7f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x80, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x81, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x82, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x83, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x84, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x85, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x86, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x87, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x88, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x89, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x8a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x8b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x8c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x8d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x8e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x8f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x90, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x91, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x92, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x93, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x94, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x95, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x96, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x97, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x98, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x99, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x9a, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x9b, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x9c, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x9d, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x9e, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0x9f, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa0, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa1, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa2, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa3, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa4, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa5, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa6, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa7, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa8, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xa9, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xaa, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xab, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xac, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xad, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xae, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xaf, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb0, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb1, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb2, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb3, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb4, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb5, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb6, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb7, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb8, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xb9, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xba, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xbb, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xbc, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xbd, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xbe, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xbf, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc0, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc1, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc2, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc3, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc4, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc5, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc6, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc7, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc8, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xc9, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xca, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xcb, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xcc, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xcd, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xce, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xcf, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd0, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd1, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd2, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd3, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd4, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd5, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd6, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd7, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd8, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xd9, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xda, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xdb, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xdc, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xdd, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xde, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xdf, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe0, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe1, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe2, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe3, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe4, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe5, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe6, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe7, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe8, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xe9, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xea, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xeb, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xec, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xed, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xee, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xef, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf0, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf1, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf2, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf3, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf4, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf5, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf6, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf7, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf8, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xf9, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xfa, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xfb, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xfc, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xfd, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6402, 0xfe, kEplObdTypInt32, kEplObdAccVPR,
    tEplObdInteger32, AnalogueInput, 0x00000000)
EPL_OBD_END_INDEX(0x6401)

// AnalogueOutput_00h_AI8
EPL_OBD_BEGIN_INDEX_RAM(0x6410, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6410, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x01, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x02, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x03, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x04, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x05, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x06, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x07, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x08, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x09, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x0a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x0b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x0c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x0d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x0e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x0f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x10, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x11, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x12, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x13, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x14, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x15, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x16, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x17, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x18, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x19, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x1a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x1b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x1c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x1d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x1e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x1f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x20, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x21, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x22, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x23, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x24, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x25, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x26, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x27, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x28, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x29, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x2a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x2b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x2c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x2d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x2e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x2f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x30, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x31, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x32, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x33, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x34, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x35, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x36, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x37, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x38, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x39, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x3a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x3b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x3c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x3d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x3e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x3f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x40, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x41, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x42, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x43, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x44, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x45, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x46, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x47, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x48, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x49, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x4a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x4b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x4c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x4d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x4e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x4f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x50, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x51, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x52, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x53, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x54, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x55, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x56, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x57, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x58, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x59, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x5a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x5b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x5c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x5d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x5e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x5f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x60, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x61, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x62, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x63, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x64, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x65, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x66, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x67, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x68, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x69, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x6a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x6b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x6c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x6d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x6e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x6f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x70, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x71, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x72, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x73, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x74, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x75, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x76, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x77, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x78, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x79, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x7a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x7b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x7c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x7d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x7e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x7f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x80, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x81, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x82, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x83, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x84, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x85, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x86, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x87, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x88, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x89, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x8a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x8b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x8c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x8d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x8e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x8f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x90, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x91, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x92, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x93, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x94, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x95, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x96, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x97, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x98, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x99, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x9a, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x9b, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x9c, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x9d, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x9e, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0x9f, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa0, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa1, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa2, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa3, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa4, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa5, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa6, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa7, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa8, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xa9, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xaa, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xab, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xac, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xad, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xae, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xaf, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb0, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb1, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb2, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb3, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb4, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb5, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb6, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb7, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb8, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xb9, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xba, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xbb, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xbc, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xbd, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xbe, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xbf, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc0, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc1, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc2, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc3, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc4, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc5, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc6, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc7, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc8, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xc9, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xca, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xcb, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xcc, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xcd, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xce, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xcf, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd0, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd1, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd2, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd3, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd4, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd5, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd6, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd7, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd8, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xd9, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xda, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xdb, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xdc, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xdd, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xde, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xdf, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe0, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe1, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe2, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe3, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe4, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe5, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe6, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe7, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe8, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xe9, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xea, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xeb, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xec, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xed, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xee, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xef, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf0, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf1, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf2, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf3, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf4, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf5, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf6, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf7, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf8, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xf9, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xfa, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xfb, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xfc, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xfd, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6410, 0xfe, kEplObdTypInt8, kEplObdAccVPRW,
    tEplObdInteger8, AnalogueOutput, 0x00)
EPL_OBD_END_INDEX(0x6410)

// AnalogueOutput_00h_AI16
EPL_OBD_BEGIN_INDEX_RAM(0x6411, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6411, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x01, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x02, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x03, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x04, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x05, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x06, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x07, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x08, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x09, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x0a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x0b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x0c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x0d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x0e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x0f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x10, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x11, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x12, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x13, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x14, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x15, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x16, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x17, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x18, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x19, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x1a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x1b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x1c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x1d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x1e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x1f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x20, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x21, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x22, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x23, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x24, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x25, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x26, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x27, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x28, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x29, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x2a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x2b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x2c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x2d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x2e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x2f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x30, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x31, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x32, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x33, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x34, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x35, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x36, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x37, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x38, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x39, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x3a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x3b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x3c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x3d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x3e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x3f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x40, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x41, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x42, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x43, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x44, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x45, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x46, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x47, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x48, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x49, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x4a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x4b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x4c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x4d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x4e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x4f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x50, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x51, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x52, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x53, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x54, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x55, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x56, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x57, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x58, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x59, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x5a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x5b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x5c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x5d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x5e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x5f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x60, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x61, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x62, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x63, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x64, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x65, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x66, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x67, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x68, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x69, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x6a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x6b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x6c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x6d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x6e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x6f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x70, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x71, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x72, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x73, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x74, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x75, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x76, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x77, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x78, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x79, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x7a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x7b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x7c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x7d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x7e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x7f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x80, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x81, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x82, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x83, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x84, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x85, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x86, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x87, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x88, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x89, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x8a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x8b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x8c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x8d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x8e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x8f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x90, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x91, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x92, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x93, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x94, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x95, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x96, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x97, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x98, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x99, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x9a, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x9b, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x9c, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x9d, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x9e, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0x9f, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa0, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa1, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa2, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa3, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa4, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa5, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa6, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa7, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa8, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xa9, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xaa, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xab, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xac, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xad, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xae, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xaf, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb0, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb1, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb2, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb3, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb4, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb5, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb6, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb7, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb8, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xb9, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xba, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xbb, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xbc, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xbd, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xbe, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xbf, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc0, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc1, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc2, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc3, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc4, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc5, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc6, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc7, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc8, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xc9, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xca, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xcb, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xcc, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xcd, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xce, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xcf, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd0, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd1, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd2, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd3, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd4, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd5, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd6, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd7, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd8, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xd9, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xda, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xdb, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xdc, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xdd, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xde, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xdf, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe0, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe1, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe2, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe3, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe4, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe5, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe6, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe7, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe8, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xe9, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xea, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xeb, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xec, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xed, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xee, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xef, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf0, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf1, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf2, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf3, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf4, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf5, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf6, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf7, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf8, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xf9, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xfa, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xfb, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xfc, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xfd, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6411, 0xfe, kEplObdTypInt16, kEplObdAccVPRW,
    tEplObdInteger16, AnalogueOutput, 0x0000)
EPL_OBD_END_INDEX(0x6411)

// AnalogueOutput_00h_AI32
EPL_OBD_BEGIN_INDEX_RAM(0x6412, 0xff, NULL)
EPL_OBD_SUBINDEX_RAM_VAR(0x6412, 0x00, kEplObdTypUInt8, kEplObdAccConst,
    tEplObdUnsigned8, NumberOfEntries, 0xfe)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x01, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x02, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x03, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x04, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x05, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x06, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x07, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x08, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x09, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x0a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x0b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x0c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x0d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x0e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x0f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x10, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x11, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x12, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x13, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x14, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x15, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x16, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x17, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x18, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x19, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x1a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x1b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x1c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x1d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x1e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x1f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x20, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x21, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x22, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x23, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x24, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x25, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x26, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x27, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x28, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x29, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x2a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x2b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x2c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x2d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x2e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x2f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x30, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x31, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x32, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x33, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x34, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x35, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x36, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x37, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x38, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x39, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x3a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x3b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x3c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x3d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x3e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x3f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x40, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x41, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x42, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x43, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x44, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x45, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x46, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x47, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x48, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x49, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x4a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x4b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x4c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x4d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x4e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x4f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x50, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x51, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x52, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x53, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x54, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x55, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x56, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x57, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x58, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x59, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x5a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x5b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x5c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x5d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x5e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x5f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x60, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x61, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x62, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x63, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x64, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x65, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x66, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x67, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x68, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x69, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x6a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x6b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x6c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x6d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x6e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x6f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x70, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x71, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x72, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x73, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x74, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x75, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x76, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x77, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x78, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x79, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x7a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x7b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x7c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x7d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x7e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x7f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x80, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x81, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x82, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x83, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x84, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x85, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x86, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x87, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x88, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x89, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x8a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x8b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x8c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x8d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x8e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x8f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x90, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x91, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x92, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x93, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x94, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x95, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x96, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x97, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x98, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x99, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x9a, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x9b, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x9c, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x9d, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x9e, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0x9f, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa0, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa1, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa2, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa3, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa4, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa5, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa6, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa7, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa8, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xa9, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xaa, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xab, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xac, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xad, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xae, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xaf, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb0, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb1, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb2, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb3, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb4, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb5, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb6, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb7, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb8, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xb9, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xba, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xbb, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xbc, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xbd, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xbe, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xbf, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc0, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc1, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc2, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc3, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc4, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc5, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc6, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc7, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc8, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xc9, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xca, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xcb, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xcc, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xcd, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xce, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xcf, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd0, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd1, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd2, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd3, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd4, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd5, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd6, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd7, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd8, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xd9, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xda, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xdb, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xdc, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xdd, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xde, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xdf, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe0, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe1, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe2, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe3, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe4, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe5, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe6, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe7, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe8, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xe9, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xea, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xeb, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xec, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xed, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xee, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xef, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf0, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf1, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf2, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf3, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf4, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf5, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf6, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf7, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf8, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xf9, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xfa, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xfb, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xfc, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xfd, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_SUBINDEX_RAM_USERDEF(0x6412, 0xfe, kEplObdTypInt32, kEplObdAccVPRW,
    tEplObdInteger32, AnalogueOutput, 0x00000000)
EPL_OBD_END_INDEX(0x6412)

EPL_OBD_END_PART()

EPL_OBD_END()

#define EPL_OBD_UNDEFINE_MACRO
#include "EplObdMacro.h"
#undef EPL_OBD_UNDEFINE_MACRO
