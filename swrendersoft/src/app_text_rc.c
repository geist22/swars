/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file app_text_rc.c
 *     Functions for drawing text on graphical screen, per-application mod.
 * @par Purpose:
 *     Allows drawing rich text (with format tags for changing colur).
 * @par Comment:
 *     This is a modification of `gtext.c` from bflibrary.
 * @author   Tomasz Lis
 * @date     12 Nov 2008 - 02 Oct 2026
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include <stdio.h>
#include <limits.h>
#include "bftext.h"

#include "app_text_rc.h"

#include "bfconfig.h"
#include "bfgentab.h"
#include "bfsprite.h"
#include "bfscreen.h"
#include "bffont.h"
#include "bfmath.h"
#include "bfmemory.h"
#include "bfanywnd.h"

#include "engincolour.h"
#include "privrdlog.h"
/******************************************************************************/

TbBool AppTextDrawLineRichWthParts(int posx, int posy,
  TbPixel def_colour, ubyte bri, const char *text)
{
    const ubyte *str;
    int x, y;
    TbPixel sel_c1;

    y = posy;
    x = posx;
    str = (const ubyte *)text;
    sel_c1 = def_colour;

    while (*str != '\0')
    {
        const struct TbSprite *p_spr;
        ubyte ch;
        TbPixel col;

        if (*str == '\1') {
          str++;
          sel_c1 = *str;
        } else {
          ch = *str;
          col = pixmap.fade_table[bri * PALETTE_8b_COLORS + sel_c1];
          p_spr = LbFontCharSprite(lbFontPtr, ch);
          LbSpriteDrawOneColour(x, y, p_spr, col);
          x += p_spr->SWidth;
        }
        str++;
    }
    return true;
}

TbBool AppTextDrawLineRichWthPartsResized(int posx, int posy,
  int units_per_px, TbPixel def_colour, ubyte bri, const char *text)
{
    const ubyte *str;
    int x, y;
    TbPixel sel_c1;

    y = posy;
    x = posx;
    str = (const ubyte *)text;
    sel_c1 = def_colour;

    while (*str != '\0')
    {
        const struct TbSprite *p_spr;
        int chr_width, chr_height;
        ubyte ch;
        TbPixel col;

        if (*str == '\1') {
          str++;
          sel_c1 = *str;
        } else {
          ch = *str;
          col = pixmap.fade_table[bri * PALETTE_8b_COLORS + sel_c1];
          p_spr = LbFontCharSprite(lbFontPtr, ch);
          chr_width = p_spr->SWidth * units_per_px >> 4;
          chr_height = p_spr->SHeight * units_per_px >> 4;
          LbSpriteDrawScaledOneColour(x, y, p_spr, chr_width, chr_height, col);
          x += chr_width;
        }
        str++;
    }
    return true;
}

/******************************************************************************/
