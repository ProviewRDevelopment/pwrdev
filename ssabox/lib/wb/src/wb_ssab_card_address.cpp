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

/* wb_ssab_card_address.cpp -- Calculate address for ssab cards */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wb_pwrs.h"
#include "wb_pwrb_msg.h"
#include "pwr_baseclasses.h"
#include "pwr_basecomponentclasses.h"
#include "pwr_ssaboxclasses.h"
#include "wb_session.h"
#include "wb_ssab_card_address.h"

static bool addressTypeIsEqual(pwr_tCid cid1, pwr_tCid cid2)
{
  pwr_tCid groups[][5] = { { pwr_cClass_Ssab_DO32DKS,
                               pwr_cClass_Ssab_DO32DKS_Stall,
                               pwr_cClass_Do_HVDO32, 0, 0 },
    { pwr_cClass_Ssab_DI32D, pwr_cClass_Di_DIX2, 0, 0, 0 },
    { pwr_cClass_Ssab_CO4uP, pwr_cClass_Co_CO4uP, pwr_cClass_Co_PI24BO, 0, 0 },
    { pwr_cClass_Ssab_AI32uP, pwr_cClass_Ssab_AI16uP, pwr_cClass_Ssab_AI8uP, 0,
        0 },
    { pwr_cClass_Ssab_AO8uP, pwr_cClass_Ssab_AO8uPL, 0, 0, 0 } };

  if (cid1 == cid2)
    return 1;

  unsigned int group;
  for (unsigned int i = 0; i < sizeof(groups) / sizeof(groups[0]); i++) {
    // Check if cid1 is member of any group
    int found = 0;
    for (unsigned int j = 0; j < sizeof(groups[0]) / sizeof(groups[0][0]);
         j++) {
      if (cid1 == groups[i][j]) {
        found = 1;
        group = j;
        break;
      }
    }
    if (found) {
      // Check if cid2 is in the same group
      for (unsigned int j = 0; j < sizeof(groups[0]) / sizeof(groups[0][0]);
           j++) {
        if (cid2 == groups[i][j])
          return 1;
      }
      return 0;
    }
  }
  return 0;
}

pwr_tStatus ssab_SetAddress(wb_session* sp, pwr_tOid oid)
{
  wb_object o = sp->object(oid);

  wb_object parent = o.parent();
  pwr_tUInt32 nyno = 0;
  pwr_tUInt32 lynxno = 0;
  pwr_tUInt32 bitno = 0;
  pwr_tUInt32 offset = 0;

  int no = 1;
  for (wb_object child = parent.first(); child; child = child.after()) {
    if (addressTypeIsEqual(o.cid(), child.cid())) {
      if (child.oid().oix == o.oid().oix)
        break;
      no++;
    }
  }

  switch (o.cid()) {
  case pwr_cClass_Ssab_DO32DKS:
  case pwr_cClass_Ssab_DO32DKS_Stall:
  case pwr_cClass_Do_HVDO32:
    nyno = 0176000 + 04 * (no - 1);
    bitno = (nyno - 0176000) / 2;
    lynxno = 4193280 + 4 * (no - 1);
    break;
  case pwr_cClass_Ssab_DI32D:
  case pwr_cClass_Di_DIX2:
    offset = (no == 17 || no == 18) ? 0300 : 0000;
    nyno = 0176100 + 04 * (no - 1) + offset;
    bitno = (nyno - 0176000) / 2;
    lynxno = 4193344 + 4 * (no - 1) + offset;
    break;
  case pwr_cClass_Ssab_CO4uP:
  case pwr_cClass_Co_CO4uP:
  case pwr_cClass_Co_PI24BO:
    nyno = 0176300 + 020 * (no - 1) + offset;
    bitno = (nyno - 0176000) / 2;
    lynxno = 4193472 + 16 * (no - 1) + offset;
    break;
  case pwr_cClass_Ao_HVAO4:
    nyno = 0176200 + 010 * (no - 1) + offset;
    bitno = (nyno - 0176000) / 2;
    lynxno = 4193416 + 8 * (no - 1) + offset;
    break;
  case pwr_cClass_Ai_HVAI32:
    nyno = 0176400 + 02 * (no - 1) + offset;
    bitno = (nyno - 0176000) / 2;
    lynxno = 4193536 + 2 * (no - 1) + offset;
    break;
  case pwr_cClass_Ssab_AI32uP:
  case pwr_cClass_Ssab_AI16uP:
  case pwr_cClass_Ssab_AI8uP:
    offset = (no == 9 || no == 10) ? 0000 : 02000;
    nyno = 0165000 + 0100 * (no - 1) + offset;
    bitno = (nyno - 0140000) / 64;
    lynxno = 4188672 + 64 * (no - 1) + offset;
    break;
  case pwr_cClass_Ssab_AO8uP:
  case pwr_cClass_Ssab_AO8uPL:
    nyno = 0176200 + 020 * (no - 1) + offset;
    bitno = (nyno - 0174000) / 16;
    lynxno = 4193408 + 16 * (no - 1) + offset;
    break;
  case pwr_cClass_Ssab_PIDuP:
    nyno = 0175400 + 04 * (no - 1) + offset;
    bitno = (nyno - 0174000) / 4;
    lynxno = 4193024 + 4 * (no - 1) + offset;
    break;
  case pwr_cClass_Ssab_AO16uP_Logger:
    nyno = 0175000 + 040 * (no - 1) + offset;
    bitno = (nyno - 0174000) / 4;
    lynxno = 4192768 + 32 * (no - 1) + offset;
    break;
  default:
    return 0;
  }

  pwr_tUInt32 bits = 0;
  pwr_tUInt32 mask;
  for (int i = 0; i < 8; i++) {
    mask = 1 << i;
    if (bitno & mask)
      bits += (int)(pow(10, i) + 0.1);
  }

  wb_attribute a = sp->attribute(o.oid(), "RtBody", "RegAddress");
  if (!a)
    return a.sts();

  try {
    sp->writeAttribute(a, (char*)&lynxno, sizeof(lynxno));
    if (EVEN(sp->sts()))
      return sp->sts();
  } catch (wb_error& e) {
    return e.sts();
  }

  a = sp->attribute(o.oid(), "RtBody", "SwitchSettings");
  if (!a)
    return a.sts();

  try {
    sp->writeAttribute(a, (char*)&bits, sizeof(bits));
    if (EVEN(sp->sts()))
      return sp->sts();
  } catch (wb_error& e) {
    return e.sts();
  }

  return 1;
}
