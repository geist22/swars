/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file huddrwlstm.c
 *     Making drawlists for the HUD over 3D engine.
 * @par Purpose:
 *     Implements functions for filling drawlists.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     19 Apr 2022 - 12 May 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "huddrwlstm.h"

#include "bfbox.h"
#include "bfscreen.h"
#include "bfsprite.h"
#include "bfgentab.h"
#include <assert.h>

#include "app_sprite.h"

/******************************************************************************/
#pragma pack(1)


#pragma pack()
/******************************************************************************/

void enlist_hud_draw_box(short px, short py, short width, short height, TbPixel colour)
{
    //TODO enlist instead of drawing directly
    LbDrawBox(px, py, width, height, colour);
}

void enlist_hud_draw_sprite(short px, short py, struct TbSprite *p_spr, short brig)
{
    if (brig < 0)
        brig = 0;
    if (brig > 63)
        brig = 63;

    //TODO enlist instead of drawing directly
    if ((lbDisplay.DrawFlags & (Lb_SPRITE_TRANSPAR4|Lb_SPRITE_TRANSPAR8)) != 0)
    {
        low_trans_grey_brightness = brig;
        ApSpriteDrawLowTransGreyRemap(px, py, p_spr,
          &pixmap.fade_table[0 * PALETTE_8b_COLORS]);
    }
    else if (brig != 32)
    {
        LbSpriteDrawRemap(px, py, p_spr, &pixmap.fade_table[brig * PALETTE_8b_COLORS]);
    }
    else
    {
        LbSpriteDraw(px, py, p_spr);
    }
}

void enlist_hud_draw_sprite_scaled(short px, short py, struct TbSprite *p_spr,
  short dest_width, short dest_height, short brig)
{
    if (brig < 0)
        brig = 0;
    if (brig > 63)
        brig = 63;

    //TODO enlist instead of drawing directly
    if ((lbDisplay.DrawFlags & (Lb_SPRITE_TRANSPAR4|Lb_SPRITE_TRANSPAR8)) != 0)
    {
        low_trans_grey_brightness = brig;
        ApSpriteDrawScaledLowTransGreyRemap(px, py, p_spr, dest_width, dest_height,
          &pixmap.fade_table[0 * PALETTE_8b_COLORS]);
    }
    else if (brig != 32)
    {
        LbSpriteDrawScaledRemap(px, py, p_spr, dest_width, dest_height,
          &pixmap.fade_table[brig * PALETTE_8b_COLORS]);
    }
    else
    {
        LbSpriteDrawScaled(px, py, p_spr, dest_width, dest_height);
    }
}

/******************************************************************************/
