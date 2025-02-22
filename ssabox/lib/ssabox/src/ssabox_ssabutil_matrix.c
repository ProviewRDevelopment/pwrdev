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

/*************************************************************************
*
* 	PROGRAM		rs_ssabutil_matrix
*
*       Modifierad
*		96 01 26	CS	Skapad
*
*	Funktion:
*		Interpolation i tabeller.
*
**************************************************************************/

/*_Include filer_________________________________________________________*/

#include <stdlib.h>

#include "pwr.h"
#include "co_math.h"

#include "ssabox_ssabutil.h"
#include "rs_sutl_msg.h"

/*_Globala variabler______________________________________________________*/

/*_Local proceduer________________________________________________________*/

/* Globala procedurer_____________________________________________________*/

/*************************************************************************
*
* Name:		ssab_curve
*
* Typ		int
*
* Typ		Parameter	IOGF	Beskrivning
* float		x		I	x-v�rde.
* float*	y		O	interpolerat y-v�rde.
* float*	table		I	tabell.
* int		size		I	antal punkter i tabellen (n).
*
* Beskrivning:
*		Interpolerar i en tabell av float. Tabellen ska vara
*		av formatet
*			float	some_table[n][2] = {
*				{  x1,	y1},
*				{  x2,	y2},
*				{  x3,	y3},
*				...
*				{  xn,	yn}};
*
*
**************************************************************************/

int ssab_curve(float x, float* y, float* table, int size)
{
  int x_idx;
  int x_found;
  float* ptr;
  float x1, x2, y1, y2;

#define TABLE_Y(ix) (*(table + 2 * (ix)-1))
#define TABLE_X(ix) (*(table + 2 * (ix)-2))

  /* Get the x point */
  ptr = table;
  x_found = 0;
  for (x_idx = 0; x_idx < size; x_idx++) {
    if (*ptr > x) {
      x_found = 1;
      break;
    }
    ptr += 2;
  }

  /* Interpolate */
  if (!x_found) {
    /* Take the very last point */
    *y = TABLE_Y(size);
  } else if (x_idx == 0) {
    /* Take the first point */
    *y = TABLE_Y(1);
  } else {
    y1 = TABLE_Y(x_idx);
    y2 = TABLE_Y(x_idx + 1);
    x1 = TABLE_X(x_idx);
    x2 = TABLE_X(x_idx + 1);
    *y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
  }
  return SUTL__SUCCESS;
}

/*************************************************************************
*
* Name:		ssab_curve_2d
*
* Typ		int
*
* Typ		Parameter	IOGF	Beskrivning
* float		x		I	x-v�rde.
* float		y		I	y-v�rde.
* float*	z		O	interpolerat z-v�rde.
* float*	table		I	tabell.
* int		x_size		I	antal rader med x-v�rden (n) i tabellen.
* int		y_size		I	antal kolumner med y-v�rden (m) i
*					tabellen.
*
* Beskrivning:
*		Interpolerar i en tv�dimensionell matris av float.
*		F�rsta i raden i matrisen ska inneh�lla x-v�rden, f�rsta
*		kolumnen y-v�rden. �vriga element inneh�ller z-v�rden som
*		ges av x-v�rdet f�r raden och y-v�rden f�r kolumnen.
*		Element [0][0] anv�nds ej.
*
*		Tabellen ska vara av formatet
*
*			float	temp_tjl_table[n+1][m+1] = {
*				{   0, 	y1,  y2,  y3, ...,  ym},
*				{  x1, z11, z12, z13, ..., z1m},
*				{  x2, z21, z22, z23, ..., z2m},
*				{  x3, z31, z32, z33, ..., z3m},
*					...
*				{  xn, zn1, zn2, zn3, ..., znm}};
*
**************************************************************************/

int ssab_curve_2d(
    float x, float y, float* z, float* table, int x_size, int y_size)
{
  int x_idx, y_idx;
  int x_found, y_found;
  float* ptr;
  float x1, x2, y1, y2, z1, z2, z11, z12, z21, z22;

#define TABLE2D_Z(ix, iy) (*(table + (iy) * (x_size + 1) + (ix)))
#define TABLE2D_X(ix) (*(table + (ix)))
#define TABLE2D_Y(iy) (*(table + (iy) * (x_size + 1)))

  /* Get the x point */
  ptr = table + 1;
  x_found = 0;
  for (x_idx = 0; x_idx < x_size; x_idx++) {
    if (*ptr > x) {
      x_found = 1;
      break;
    }
    ptr++;
  }

  /* Get the y point */
  ptr = table + x_size + 1;
  y_found = 0;
  for (y_idx = 0; y_idx < y_size; y_idx++) {
    if (*ptr > y) {
      y_found = 1;
      break;
    }
    ptr += x_size + 1;
  }

  /* Interpolate */
  if (!x_found && !y_found) {
    /* Take the very last point */
    *z = TABLE2D_Z(x_size, y_size);
  } else if (x_idx == 0 && y_idx == 0) {
    /* Take the first point */
    *z = TABLE2D_Z(1, 1);
  } else if (!x_found && y_idx == 0) {
    *z = TABLE2D_Z(x_size, 1);
  } else if (!y_found && x_idx == 0) {
    *z = TABLE2D_Z(1, y_size);
  } else if (!x_found) {
    z1 = TABLE2D_Z(x_size, y_idx);
    z2 = TABLE2D_Z(x_size, y_idx + 1);
    y1 = TABLE2D_Y(y_idx);
    y2 = TABLE2D_Y(y_idx + 1);
    if (feqf(y2, y1))
      *z = z1;
    else
      *z = z1 + (z2 - z1) * (y - y1) / (y2 - y1);
  } else if (x_idx == 0) {
    z1 = TABLE2D_Z(1, y_idx);
    z2 = TABLE2D_Z(1, y_idx + 1);
    y1 = TABLE2D_Y(y_idx);
    y2 = TABLE2D_Y(y_idx + 1);
    if (feqf(y2, y1))
      *z = z1;
    else
      *z = z1 + (z2 - z1) * (y - y1) / (y2 - y1);
  } else if (y_idx == 0) {
    z1 = TABLE2D_Z(x_idx, 1);
    z2 = TABLE2D_Z(x_idx + 1, 1);
    x1 = TABLE2D_X(x_idx);
    x2 = TABLE2D_X(x_idx + 1);
    if (feqf(x2, x1))
      *z = z1;
    else
      *z = z1 + (z2 - z1) * (x - x1) / (x2 - x1);
  } else if (!y_found) {
    z1 = TABLE2D_Z(x_idx, y_size);
    z2 = TABLE2D_Z(x_idx + 1, y_size);
    x1 = TABLE2D_X(x_idx);
    x2 = TABLE2D_X(x_idx + 1);
    if (feqf(x2, x1))
      *z = z1;
    else
      *z = z1 + (z2 - z1) * (x - x1) / (x2 - x1);
  } else {
    z11 = TABLE2D_Z(x_idx, y_idx);
    z12 = TABLE2D_Z(x_idx + 1, y_idx);
    z21 = TABLE2D_Z(x_idx, y_idx + 1);
    z22 = TABLE2D_Z(x_idx + 1, y_idx + 1);
    y1 = TABLE2D_Y(y_idx);
    y2 = TABLE2D_Y(y_idx + 1);
    x1 = TABLE2D_X(x_idx);
    x2 = TABLE2D_X(x_idx + 1);
    if (feqf(y2, y1)) {
      z1 = z11;
      z2 = z12;
    } else {
      z1 = z11 + (z21 - z11) * (y - y1) / (y2 - y1);
      z2 = z12 + (z22 - z12) * (y - y1) / (y2 - y1);
    }
    if (feqf(x2, x1))
      *z = z1;
    else
      *z = z1 + (z2 - z1) * (x - x1) / (x2 - x1);
  }
  return SUTL__SUCCESS;
}

#ifdef TEST
main()
{
  int sts;
  float temp_tjl_table[6][4] = { /* Tjl */
    { 0, 200, 420, 640 }, /* Anl�pnings Temperaturer */
    { 20, 11, 14, 25 }, { 25, 13, 17.5, 30 }, { 50, 20, 35, 47 },
    { 70, 29, 49, 65 }, { 100, 33, 70, 93 }
  };
  float temp_step1_table[3][2] = { /* Anl�pnings temp,     Steg1 temp */
    { 200, 430 }, { 420, 615 }, { 640, 830 }
  };
  float x, y, z;
  int i;

  for (i = 0; i < 15; i++) {
    if (i == 0) {
      x = 0;
      y = 0;
    }
    if (i == 1) {
      x = 0;
      y = 120;
    }
    if (i == 2) {
      x = 700;
      y = 0;
    }
    if (i == 3) {
      x = 700;
      y = 120;
    }
    if (i == 4) {
      x = 0;
      y = 22.5;
    }
    if (i == 5) {
      x = 700;
      y = 22.5;
    }
    if (i == 6) {
      x = 310;
      y = 0;
    }
    if (i == 7) {
      x = 310;
      y = 120;
    }
    if (i == 8) {
      x = 310;
      y = 22.5;
    }
    if (i == 9) {
      x = 420;
      y = 50;
    }
    if (i == 10) {
      x = 420;
      y = 60;
    }
    if (i == 11) {
      x = 420;
      y = 70;
    }
    if (i == 12) {
      x = 310;
      y = 100;
    }
    if (i == 13) {
      x = 310;
      y = 70;
    }
    if (i == 14) {
      x = 310;
      y = 69.5;
    }
/*
          if  ( i == 0) { x = 	100; 	y = 	0; }
          if  ( i == 1) { x = 	190; 	y = 	120; }
          if  ( i == 2) { x = 	200; 	y = 	0; }
          if  ( i == 3) { x = 	310; 	y = 	120; }
          if  ( i == 4) { x = 	420; 	y = 	22.5; }
          if  ( i == 5) { x = 	500; 	y = 	22.5; }
          if  ( i == 6) { x = 	530; 	y = 	0; }
          if  ( i == 7) { x = 	635; 	y = 	120; }
          if  ( i == 8) { x = 	640; 	y = 	22.5; }
          if  ( i == 9) { x = 	645; 	y = 	50; }
          if  ( i == 10) { x = 	1000; 	y = 	60; }
          if  ( i == 11) { x = 	420; 	y = 	70; }
          if  ( i == 12) { x = 	310; 	y = 	100; }
          if  ( i == 13) { x = 	310; 	y = 	70; }
          if  ( i == 14) { x = 	310; 	y = 	69.5; }
*/
#define SSAB_CURVE_2D(x, y, z, table)                                          \
  ssab_curve_2d(x, y, z, (float*)&table,                                       \
      sizeof(table[0]) / sizeof(table[0][0]) - 1,                              \
      sizeof(table) / sizeof(table[0]) - 1)

#define SSAB_CURVE(x, y, table)                                                \
  ssab_curve(x, y, (float*)&table, sizeof(table) / sizeof(table[0]))

    sts = SSAB_CURVE_2D(x, y, &z, temp_tjl_table);
    printf("x: %7.2f  y: %7.2f   z: %7.2f\n", x, y, z);

    sts = SSAB_CURVE(x, &z, temp_step1_table);
    printf("x: %7.2f  z: %7.2f\n", x, z);
  }
}
#endif
