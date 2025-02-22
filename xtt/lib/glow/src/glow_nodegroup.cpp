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

#include <string.h>

#include <iostream>

#include "glow_nodegroup.h"
#include "glow_growctx.h"
#include "glow_grownode.h"
#include "glow_msg.h"

GlowNodeGroup::GlowNodeGroup(
    GrowCtx* glow_ctx, const char* name, GlowArray& array)
    : GlowNodeClass(glow_ctx, name, glow_eNodeGroup_Common)
{
  a.copy_from_common_objects(array);
}

GlowNodeGroup::GlowNodeGroup(GrowCtx* glow_ctx, const char* name)
    : GlowNodeClass(glow_ctx, name, glow_eNodeGroup_Common)
{
}

GlowNodeGroup::GlowNodeGroup(const GlowNodeGroup& nc)
    : GlowNodeClass((GlowNodeClass&)nc)
{
  // Get unique name
  sprintf(n_name, "Grp%d_", ((GrowCtx*)ctx)->objectname_cnt++);
}

GlowNodeGroup::~GlowNodeGroup()
{
}

void GlowNodeGroup::ungroup(GlowTransform* t)
{
  GlowArrayElem *parent, *pp;
  a.set_transform(t);

  for (int i = 0; i < a.size(); i++) {
    parent = a[i]->get_parent();
    if (parent)
      pp = parent->get_parent();
    else {
      pp = 0;
      a[i]->set_parent(0);
    }
    if (pp && pp->type() == glow_eObjectType_GrowLayer)
      ((GrowLayer*)pp)->insert(a[i]);
    else
      ctx->insert(a[i]);
    if (a[i]->type() == glow_eObjectType_GrowNode
        || a[i]->type() == glow_eObjectType_GrowGroup)
      ((GrowNode*)a[i])->ungroup();
  }
  a.clear();
}

void GlowNodeGroup::save(std::ofstream& fp, glow_eSaveMode mode)
{
  fp << int(glow_eSave_NodeGroup) << '\n';
  fp << int(glow_eSave_NodeGroup_nodeclass_part) << '\n';
  saved = 0;
  GlowNodeClass::save(fp, mode);
  fp << int(glow_eSave_End) << '\n';
}

void GlowNodeGroup::open(std::ifstream& fp)
{
  int type = 0;
  int end_found = 0;
  char dummy[40];

  for (;;) {
    if (!fp.good()) {
      fp.clear();
      fp.getline(dummy, sizeof(dummy));
      printf("** Read error GlowNodeGroup: \"%d %s\"\n", type, dummy);
    }

    fp >> type;
    switch (type) {
    case glow_eSave_NodeGroup:
      break;
    case glow_eSave_NodeGroup_nodeclass_part:
      GlowNodeClass::open(fp);
      break;
    case glow_eSave_End:
      end_found = 1;
      break;
    default:
      std::cout << "GrowGroup:open syntax error\n";
      fp.getline(dummy, sizeof(dummy));
    }
    if (end_found)
      break;
  }
}
