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

#include "glow_colpalctx.h"
#include "glow_colpalapi.h"

extern "C" void colpal_EnableEvent(ColPalCtx* ctx, glow_eEvent event,
    glow_eEventType event_type,
    int (*event_cb)(GlowCtx* ctx, glow_tEvent event))
{
  ctx->enable_event(event, event_type, event_cb);
}

void colpal_DisableEvent(ColPalCtx* ctx, glow_eEvent event)
{
  ctx->disable_event(event);
}

extern "C" void colpal_DisableEventAll(ColPalCtx* ctx)
{
  ctx->disable_event_all();
}

void colpal_GetCtxUserData(colpal_tCtx ctx, void** user_data)
{
  ((GlowCtx*)ctx)->get_user_data(user_data);
}

void colpal_SetCtxUserData(colpal_tCtx ctx, void* user_data)
{
  ((GlowCtx*)ctx)->set_user_data(user_data);
}

void colpal_GetCurrentColors(colpal_tCtx ctx, glow_eDrawType* fill_color,
    glow_eDrawType* border_color, glow_eDrawType* text_color)
{
  *fill_color = ctx->current_fill;
  *border_color = ctx->current_border;
  *text_color = ctx->current_text;
}

void colpal_SetCurrentColors(colpal_tCtx ctx, glow_eDrawType fill_color,
    glow_eDrawType border_color, glow_eDrawType text_color)
{
  ctx->current_fill = fill_color;
  ctx->current_border = border_color;
  ctx->current_text = text_color;
}

void colpal_GetCurrentColorTone(colpal_tCtx ctx, glow_eDrawType* color_tone)
{
  *color_tone = ctx->current_tone;
}

void colpal_SetCurrentColorTone(colpal_tCtx ctx, glow_eDrawType color_tone)
{
  ctx->current_tone = color_tone;
}

colpal_eActive colpal_GetActive(colpal_tCtx ctx)
{
  return ctx->get_active();
}

void colpal_UpdateCustomColors(colpal_tCtx ctx, void* customcolors)
{
  ctx->update_custom_colors((GlowCustomColors*)customcolors);
}
