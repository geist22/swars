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

TbBool enlist_hud_draw_box(short px, short py, short width, short height,
  ushort drwflags, short brig, TbPixel colour)
{
    struct DrawItemHud dih;
    struct DrawItemHud *p_di;

    if (brig > PALETTE_FADE_LEVELS-1)
        brig = PALETTE_FADE_LEVELS-1;
    if (brig < 0)
        brig = 0;

    p_di = &dih;

    p_di->U.Box.Rect.X = px;
    p_di->U.Box.Rect.Y = py;
    p_di->U.Box.Rect.Width = width;
    p_di->U.Box.Rect.Height = height;
    p_di->U.Box.DrwFlags = drwflags;
    p_di->U.Box.Bright = brig;
    p_di->U.Box.Col = colour;

    //TODO enlist instead of drawing directly
    hud_draw_box(&p_di->U.Box);
    return true;
}

TbBool enlist_hud_draw_slant_box(short px, short py, short width, short height,
  ushort drwflags, short brig, TbPixel colour)
{
    struct DrawItemHud dih;
    struct DrawItemHud *p_di;

    if (brig > PALETTE_FADE_LEVELS-1)
        brig = PALETTE_FADE_LEVELS-1;
    if (brig < 0)
        brig = 0;

    p_di = &dih;

    p_di->U.Box.Rect.X = px;
    p_di->U.Box.Rect.Y = py;
    p_di->U.Box.Rect.Width = width;
    p_di->U.Box.Rect.Height = height;
    p_di->U.Box.DrwFlags = drwflags;
    p_di->U.Box.Bright = brig;
    p_di->U.Box.Col = colour;

    //TODO enlist instead of drawing directly
    hud_draw_slant_box(&p_di->U.Box);
    return true;
}

TbBool enlist_hud_draw_sprite(short px, short py, struct TbSprite *p_spr,
  ushort drwflags, short brig)
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
    return true;
}

TbBool enlist_hud_draw_sprite_scaled(short px, short py, struct TbSprite *p_spr,
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
    return true;
}

TbBool enlist_hud_draw_clipped_text(short px, short py, short width, short height,
  short shift_x, short shift_y, struct TbSprite *p_font, const char *text,
  short units_per_px, short brig, TbPixel colour)
{
    struct DrawItemHud dih;
    struct DrawItemHud *p_di;

    if (brig > PALETTE_FADE_LEVELS-1)
        brig = PALETTE_FADE_LEVELS-1;
    if (brig < 0)
        brig = 0;

    p_di = &dih;

    p_di->U.ClpText.Rect.X = px;
    p_di->U.ClpText.Rect.Y = py;
    p_di->U.ClpText.Rect.Width = width;
    p_di->U.ClpText.Rect.Height = height;
    p_di->U.ClpText.pFont = p_font;
    p_di->U.ClpText.Text = text;
    p_di->U.ClpText.Shift.X = shift_x;
    p_di->U.ClpText.Shift.Y = shift_y;
    p_di->U.ClpText.Scale = units_per_px;
    p_di->U.ClpText.Bright = brig;
    p_di->U.ClpText.Col = colour;
    p_di->U.ClpText.Shade = 0;

    //TODO enlist instead of drawing directly
    hud_draw_clipped_text(&p_di->U.ClpText);
    return true;
}

int get_width_shad_cl_flash_wrapped_text(short px, short py,
  struct TbSprite *p_font, const char *text, short units_per_px)
{
    ushort drwflags;

    drwflags = Lb_TEXT_ONE_COLOR | Lb_TEXT_HALIGN_LEFT;
    return hud_width_shad_cl_flash_wrapped_text(px, py,
      p_font, text, drwflags, units_per_px);
}

TbBool enlist_hud_draw_shad_cl_flash_wrapped_text(short px, short py,
  short width, short height, struct TbSprite *p_font, const char *text,
  short units_per_px, short timer, TbPixel colour, TbPixel shcolour)
{
    struct DrawItemHud dih;
    struct DrawItemHud *p_di;

    p_di = &dih;

    p_di->U.WrpText.Rect.X = px;
    p_di->U.WrpText.Rect.Y = py;
    p_di->U.WrpText.Rect.Width = width;
    p_di->U.WrpText.Rect.Height = height;
    p_di->U.WrpText.pFont = p_font;
    p_di->U.WrpText.Text = text;
    p_di->U.WrpText.Timer = timer;
    p_di->U.WrpText.DrwFlags = Lb_TEXT_ONE_COLOR | Lb_TEXT_HALIGN_LEFT;
    p_di->U.WrpText.Scale = units_per_px;
    p_di->U.WrpText.Bright = 32;
    p_di->U.WrpText.Col = colour;
    p_di->U.WrpText.Shade = shcolour;

    //TODO enlist instead of drawing directly
    hud_draw_shad_cl_flash_wrapped_text(&p_di->U.WrpText);
    return true;
}

TbBool enlist_hud_draw_colour_wave_wrapped_text(short px, short py,
  short width, short height, struct TbSprite *p_font, const char *text,
  short units_per_px, TbPixel colour, TbPixel shcolour)
{
    struct DrawItemHud dih;
    struct DrawItemHud *p_di;

    p_di = &dih;

    p_di->U.WrpText.Rect.X = px;
    p_di->U.WrpText.Rect.Y = py;
    p_di->U.WrpText.Rect.Width = width;
    p_di->U.WrpText.Rect.Height = height;
    p_di->U.WrpText.pFont = p_font;
    p_di->U.WrpText.Text = text;
    p_di->U.WrpText.Timer = 0;
    p_di->U.WrpText.DrwFlags = Lb_TEXT_ONE_COLOR | Lb_TEXT_HALIGN_LEFT;
    p_di->U.WrpText.Scale = units_per_px;
    p_di->U.WrpText.Bright = 32;
    p_di->U.WrpText.Col = colour;
    p_di->U.WrpText.Shade = shcolour;

    //TODO enlist instead of drawing directly
    hud_draw_colour_wave_wrapped_text(&p_di->U.WrpText);
    return true;
}

/******************************************************************************/
