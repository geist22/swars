/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file engintext.c
 *     Drawing text on screen within the game engine.
 * @par Purpose:
 *     Implement functions for drawing text over the 3D world.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     19 Apr 2022 - 27 Aug 2023
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "engintext.h"

#include "bfanywnd.h"
#include "bfmemut.h"
#include "bftext.h"
#include "bfscreen.h"
#include "bfsprite.h"

#include "app_text_cw.h"
#include "app_text_sf.h"
#include "engincolour.h"
#include "enginprops.h"
#include "huddrwlstm.h"
#include "sprfontut.h"

#include "game_sprts.h"
#include "hud_panel.h"
#include "mydraw.h"
#include "swlog.h"
/******************************************************************************/

short FontOnscreenMessageTextScale(struct TbSprite *font)
{
    int tx_height;
    int units_per_px;

    lbFontPtr = small_font;
    tx_height = my_char_height('A');
    // For window width=320, expect text height=5; so that should
    // produce unscaled sprite, which is 16 units per px.
    units_per_px = (lbDisplay.GraphicsWindowWidth * 5 / tx_height)  / (320 / 16);
    // Do not allow any scale, only n * 50%
    units_per_px = (units_per_px + 4) & ~0x07;

    return units_per_px;
}


TbBool AppTextDrawMissionStatus(int posx, int posy, const char *text,
  TbPixel colour, TbPixel shcolour)
{
    short units_per_px;
    int width, height;

    units_per_px = FontOnscreenMessageTextScale(small_font);
    width = lbTextJustifyWindow.x + lbTextJustifyWindow.width - posx;
    height = lbTextJustifyWindow.y + lbTextJustifyWindow.height - posy;

    return enlist_hud_draw_colour_wave_wrapped_text(posx, posy, width, height,
      small_font, text, units_per_px, colour, shcolour);
}

TbBool AppTextDrawMissionChatMessage(int posx, int posy, int width, int height,
  TbPixel colour, int timer, const char *text)
{
    short units_per_px;

    units_per_px = FontOnscreenMessageTextScale(small_font);

    return enlist_hud_draw_shad_cl_flash_wrapped_text(posx, posy, width, height,
      small_font, text, units_per_px, timer,
      colour, colour_lookup[ColLU_GREYLT]);
}

int AppTextHeightMissionChatMessage(int posx, int posy, const char *text)
{
    short units_per_px;

    units_per_px = FontOnscreenMessageTextScale(small_font);

    return get_width_shad_cl_flash_wrapped_text(posx, posy,
      small_font, text, units_per_px);
}

/******************************************************************************/
