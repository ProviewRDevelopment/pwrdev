/*
 * ProviewR   Open Source Process Control.
 * Copyright (C) 2005-2023 SSAB EMEA AB.
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

/* ge_graph_layout.cpp
   This module contains ge layout manager. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "pwr.h"
#include "ge_graph_layout.h"

#define BORDER -1
#define ROW_MAX 25
#define VERT 0
#define HORIZ 1
#define MAX_PRIO 20

typedef struct {
  int idx;
  double size;
  double coord;
} sRowItem;

typedef struct {
  double pref_size;
  double calc_size;
  double calc_coord;
  int fix_size;
} sDirItem;
  
typedef struct {
  sDirItem dir[2];
  int disabled;
  int prio;
} sItem;

typedef struct {
  int msize;
  int row_cnt[2];
  int *row_size[2];
  sRowItem *row_idx[2];
  double wind_size[2];
  double calc_wind_size[2];
  sItem *item;
} sCtx;

static int next(sCtx *ctx, int dir, int idx, int row, ccm_tInt *a_next, ccm_tInt *a_prev)
{
  int orig_row;
  int orig_row_size;
  int sts;

  ctx->row_idx[dir][row * ctx->msize + ctx->row_size[dir][row]].idx = idx;
  ctx->row_size[dir][row]++;
  orig_row = row;
  orig_row_size = ctx->row_size[dir][row];
  if (a_next[idx] == BORDER) {
    return 1;
  } else {
    sts = next(ctx, dir, a_next[idx], row, a_next, a_prev);
    if (EVEN(sts))
      return sts;
  }
  for (int j = 0; j < ctx->msize; j++) {
    if (a_prev[j] == idx && j != a_next[idx]) {
      //printf("New row %d, %d -> %d\n", ctx->row_cnt[dir], idx, j);
      // New row, copy original row
      if (ctx->row_cnt[dir] >= ROW_MAX - 1)
	return 0;
      for (int k = 0; k < orig_row_size; k++)
	ctx->row_idx[dir][ctx->row_cnt[dir] * ctx->msize + k].idx = ctx->row_idx[dir][orig_row * ctx->msize + k].idx;
      ctx->row_size[dir][ctx->row_cnt[dir]] = orig_row_size;
      ctx->row_cnt[dir]++;
      sts = next(ctx, dir, j, ctx->row_cnt[dir] - 1, a_next, a_prev);
      if (EVEN(sts))
	return sts;
    }
  }
  return 1;
}

static void disable(sCtx *ctx, int dir)
{
  // Check if disabled
  for (int i = 0; i < ctx->row_cnt[dir]; i++) {
    double total_size = 0;
    for (int j = 0; j < ctx->row_size[dir][i]; j++) {
      if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled)
	total_size += ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].pref_size;
    }
    while (total_size > ctx->wind_size[dir]) {
      int low_prio = 100;
      int low_prio_idx = -1;

      // Disable item with lowest prio      
      for (int j = 0; j < ctx->row_size[dir][i]; j++) {
	if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled &&
	     ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].prio < low_prio) {
	  low_prio_idx = ctx->row_idx[dir][i * ctx->msize + j].idx;
	  low_prio = ctx->item[low_prio_idx].prio;
	}
      }
      if (low_prio_idx != -1 && low_prio != MAX_PRIO)
	ctx->item[low_prio_idx].disabled = 1;

      total_size = 0;
      for (int j = 0; j < ctx->row_size[dir][i]; j++) {
	if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled)
	  total_size += ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].pref_size;
      }
      if (low_prio == MAX_PRIO)
	break;
    }
  }
}

static void calculate(sCtx *ctx, int dir)
{
  // Calculate window size
  ctx->calc_wind_size[dir] = 0;
  for (int i = 0; i < ctx->row_cnt[dir]; i++) {
    double total_size = 0;
    for (int j = 0; j < ctx->row_size[dir][i]; j++) {
      if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled)
	total_size += ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].pref_size;
    }
    if (total_size > ctx->calc_wind_size[dir])
      ctx->calc_wind_size[dir] = total_size;
  }
  if (ctx->wind_size[dir] > ctx->calc_wind_size[dir])
    ctx->calc_wind_size[dir] = ctx->wind_size[dir];

  for (int i = 0; i < ctx->row_cnt[dir]; i++) {
    double total_size = 0;
    for (int j = 0; j < ctx->row_size[dir][i]; j++) {
      if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled)
	total_size += ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].pref_size;
    }

    if (total_size > 0) {
      // Spread space
      double add_size;
      int cnt = 0;
      for (int j = 0; j < ctx->row_size[dir][i]; j++) {
	if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled &&
	     !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].fix_size)
	  cnt++;
      }
      if (cnt > 0)
	add_size = MAX(0,(ctx->calc_wind_size[dir] - total_size) / cnt);
      for (int j = 0; j < ctx->row_size[dir][i]; j++) {
	if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled) {
	  if (ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].fix_size)
	    ctx->row_idx[dir][i * ctx->msize + j].size = 
	      ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].pref_size;
	  else
	    ctx->row_idx[dir][i * ctx->msize + j].size = 
	      ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].pref_size + add_size;
	}
      }
    }
  }

  // Adjust if size differs
  int adjusted = 1;
  int adjust_cnt = 0;
  while (adjusted && adjust_cnt < 20) {
    adjusted = 0;
    adjust_cnt++;
    for (int k = 0; k < ctx->msize; k++) {
      double last_size = 0;
      int last_rowitem;
      if (!ctx->item[k].disabled) {
	for (int i = 0; i < ctx->row_cnt[dir]; i++) {
	  for (int j = 0; j < ctx->row_size[dir][i]; j++) {
	    if (ctx->row_idx[dir][i * ctx->msize + j].idx == k) {
	      if (last_size == 0) {
		last_rowitem = i * ctx->msize + j;
		last_size = ctx->row_idx[dir][last_rowitem].size;
	      } else {
		if (!(fabs(last_size - ctx->row_idx[dir][i * ctx->msize + j].size) < DBL_EPSILON)) {
		  if (j == ctx->row_size[dir][i] - 1 && j != 0) {
		    // Adjust previous
		    ctx->row_idx[dir][i * ctx->msize + j - 1].size -= last_size - 
		        ctx->row_idx[dir][i * ctx->msize + j].size;
		    ctx->row_idx[dir][i * ctx->msize + j].size = last_size;
		  } else {
		    // Adjust next
		    ctx->row_idx[dir][i * ctx->msize + j + 1].size -= last_size - 
		        ctx->row_idx[dir][i * ctx->msize + j].size;
		    ctx->row_idx[dir][i * ctx->msize + j].size = last_size;
		  }
		  adjusted = 1;
		}
	      }
	      if (ctx->item[k].dir[dir].calc_size < ctx->row_idx[dir][i * ctx->msize + j].size)
		ctx->item[k].dir[dir].calc_size = ctx->row_idx[dir][i * ctx->msize + j].size;
	    }
	  }
	}	
      }
    }
  }
  
  for (int i = 0; i < ctx->row_cnt[dir]; i++) {
    double coord = 0;
    for (int j = 0; j < ctx->row_size[dir][i]; j++) {
      if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled) {
	ctx->row_idx[dir][i * ctx->msize + j].coord = coord;
	if (coord > ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].calc_coord)
	  ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].calc_coord = coord;
	coord += ctx->row_idx[dir][i * ctx->msize + j].size;
      }
    }
  }

#if 0
  printf("%s\n", dir == HORIZ ? "Horizontal" : "Vertical");
  for (int i = 0; i < ctx->row_cnt[dir]; i++) {
    printf("Row %d\n", i);
    for (int j = 0; j < ctx->row_size[dir][i]; j++) {
      if ( !ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].disabled)
	printf("Size %d %g (%g)\n", ctx->row_idx[dir][i * ctx->msize + j].idx, ctx->row_idx[dir][i * ctx->msize + j].size,
	       ctx->item[ctx->row_idx[dir][i * ctx->msize + j].idx].dir[dir].pref_size);
      else
	printf("Size %d disabled\n", ctx->row_idx[dir][i * ctx->msize + j].idx);
    }
  }

  for (int k = 0; k < ctx->msize; k++) {
    if (!ctx->item[k].disabled) {
      printf("Item %d coord %g size %g (%g)\n", k, ctx->item[k].dir[dir].calc_coord, ctx->item[k].dir[dir].calc_size, ctx->item[k].dir[dir].pref_size); 
    }
    else
      printf("Item %d disabled\n", k);
  }
#endif
}


int graph_layout(Graph* graph, int mod_size, float wind_width, float wind_height, 
    ccm_tInt* prio, 
    ccm_tInt* top_neighbour, ccm_tInt* down_neighbour, ccm_tInt* left_neighbour,
    ccm_tInt* right_neighbour, ccm_tFloat* pref_width, ccm_tFloat* pref_height, 
    ccm_tInt* fix_width, ccm_tInt* fix_height, ccm_tFloat *calc_x, ccm_tFloat* calc_y, 
    ccm_tFloat* calc_width, ccm_tFloat* calc_height,
    float* calc_wind_width, float* calc_wind_height)
{
  int i;
  sCtx *ctx;

  // Create context
  ctx = (sCtx *)calloc(1, sizeof(sCtx));
  ctx->row_idx[0] = (sRowItem *)calloc(mod_size, ROW_MAX * sizeof(sRowItem));
  ctx->row_idx[1] = (sRowItem *)calloc(mod_size, ROW_MAX * sizeof(sRowItem));
  ctx->row_size[0] = (int *)calloc(sizeof(int), ROW_MAX);
  ctx->row_size[1] = (int *)calloc(sizeof(int), ROW_MAX);
  ctx->item = (sItem *)calloc(sizeof(sItem), mod_size);

  // Insert data into context
  ctx->msize = mod_size;
  ctx->wind_size[VERT] = wind_height;
  ctx->wind_size[HORIZ] = wind_width;
  for (i = 0; i < ctx->msize; i++) {
    ctx->item[i].dir[VERT].pref_size = pref_height[i];
    ctx->item[i].dir[VERT].fix_size = fix_height[i];
    ctx->item[i].dir[HORIZ].pref_size = pref_width[i];
    ctx->item[i].dir[HORIZ].fix_size = fix_width[i];
    ctx->item[i].prio = prio[i];
  }

  // Create rows
  for (i = 0; i < ctx->msize; i++) {
    if (top_neighbour[i] == BORDER) {
      ctx->row_cnt[VERT]++;
      next(ctx, VERT, i, ctx->row_cnt[VERT] - 1, down_neighbour, top_neighbour);
    }
    if (left_neighbour[i] == BORDER) {
      ctx->row_cnt[HORIZ]++;
      next(ctx, HORIZ, i, ctx->row_cnt[HORIZ] - 1, right_neighbour, left_neighbour);
    }
  }

  // Disable
  if (graph->mode == graph_eMode_Runtime) {  
    disable(ctx, VERT);
    disable(ctx, HORIZ);
  }

  // Calculate module size
  calculate(ctx, VERT);
  calculate(ctx, HORIZ);

#if 0
  for (i = 0; i < ctx->row_cnt[VERT]; i++) {
    for (int j = 0; j < ctx->row_size[VERT][i]; j++)
      printf("%d ", ctx->row_idx[VERT][i * ctx->msize + j].idx);
    printf("\n");
  }
  for (i = 0; i < ctx->row_cnt[HORIZ]; i++) {
    for (int j = 0; j < ctx->row_size[HORIZ][i]; j++)
      printf("%d ", ctx->row_idx[HORIZ][i * ctx->msize + j].idx);
    printf("\n");
  }
#endif

  // Result
  for (i = 0; i < ctx->msize; i++) {
    calc_x[i] = ctx->item[i].dir[HORIZ].calc_coord;
    calc_y[i] = ctx->item[i].dir[VERT].calc_coord;
    calc_width[i] = ctx->item[i].dir[HORIZ].calc_size;
    calc_height[i] = ctx->item[i].dir[VERT].calc_size;
  }
  *calc_wind_width = ctx->calc_wind_size[HORIZ];
  *calc_wind_height = ctx->calc_wind_size[VERT];

  free(ctx->row_idx[0]);
  free(ctx->row_idx[1]);
  free(ctx->row_size[0]);
  free(ctx->row_size[1]);
  free(ctx->item);
  free(ctx);

  return 1;
}