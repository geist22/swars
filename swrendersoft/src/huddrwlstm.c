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

#include <assert.h>
#include "bfanywnd.h"
#include "bfbox.h"
#include "bfgentab.h"
#include "bfscreen.h"
#include "bfsprite.h"
#include "bftext.h"

#include "app_sprite.h"
#include "app_text_ba.h"
#include "huddrwlstx.h"

/******************************************************************************/
#pragma pack(1)


#pragma pack()
/******************************************************************************/

void enlist_hud_draw_box(short px, short py, short width, short height, ushort drwflags, TbPixel colour)
{
    //TODO enlist instead of drawing directly
    lbDisplay.DrawFlags = drwflags;

    LbDrawBox(px, py, width, height, colour);
}

void enlist_hud_draw_sprite(short px, short py, struct TbSprite *p_spr, ushort drwflags, short brig)
{
    if (brig > PALETTE_FADE_LEVELS-1)
        brig = PALETTE_FADE_LEVELS-1;
    if (brig < 0)
        brig = 0;

    //TODO enlist instead of drawing directly
    lbDisplay.DrawFlags = drwflags;

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
  short dest_width, short dest_height, ushort drwflags, short brig)
{
    if (brig > PALETTE_FADE_LEVELS-1)
        brig = PALETTE_FADE_LEVELS-1;
    if (brig < 0)
        brig = 0;

    //TODO enlist instead of drawing directly
    lbDisplay.DrawFlags = drwflags;

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

void enlist_hud_draw_clipped_text(short px, short py, short width, short height,
  short shift_x, short shift_y, struct TbSprite *p_font, const char *text,
  short units_per_px, short brig, TbPixel colour)
{
    if (brig > PALETTE_FADE_LEVELS-1)
        brig = PALETTE_FADE_LEVELS-1;
    if (brig < 0)
        brig = 0;

    //TODO enlist instead of drawing directly
    LbTextSetWindow(px, py, width, height);

    lbFontPtr = p_font;
    lbDisplay.DrawColour = colour;
    lbDisplay.DrawFlags = Lb_TEXT_ONE_COLOR;
    AppTextDrawLineBrigAdjWthPartsResized(shift_x, shift_y, units_per_px, brig, text);

    LbTextSetWindow(lbDisplay.GraphicsWindowX, lbDisplay.GraphicsWindowY,
      lbDisplay.GraphicsWindowWidth, lbDisplay.GraphicsWindowHeight);
}

/** Enlist drawing line-wrapped text with shadow colour flash effect.
 */
void enlist_hud_draw_shad_cl_flash_wrapped_text(short px, short py,
  short width, short height, struct TbSprite *p_font, const char *text,
  short units_per_px, short timer, TbPixel colour, TbPixel shcolour)
{
    //TODO enlist instead of drawing directly
}

/******************************************************************************/
