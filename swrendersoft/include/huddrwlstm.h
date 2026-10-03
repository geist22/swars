/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file huddrwlstm.h
 *     Header file for huddrwlstm.c.
 * @par Purpose:
 *     Making drawlists for the HUD over 3D engine.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     19 Apr 2022 - 12 May 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef HUDDRWLSTM_H
#define HUDDRWLSTM_H

#include "bftypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
#pragma pack(1)

 struct TbSprite;

#pragma pack()
/******************************************************************************/

void enlist_hud_draw_box(short px, short py, short width, short height,
  ushort drwflags, TbPixel colour);

void enlist_hud_draw_sprite(short px, short py, struct TbSprite *p_spr,
  ushort drwflags, short brig);

void enlist_hud_draw_sprite_scaled(short px, short py, struct TbSprite *p_spr,
  short dest_width, short dest_height, ushort drwflags, short brig);

void enlist_hud_draw_clipped_text(short px, short py, short width, short height,
  short shift_x, short shift_y, struct TbSprite *p_font, const char *text,
  short units_per_px, short brig, TbPixel colour);

/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
