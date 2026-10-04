/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file huddrwlstx.c
 *     Drawlist execution for the HUD over 3D engine.
 * @par Purpose:
 *     Implements functions for executing previously made drawlists,
 *     meaning the actual drawing based on primitives in the list.
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
#include "huddrwlstx.h"

#include <assert.h>
#include "bfanywnd.h"
#include "bfbox.h"
#include "bfgentab.h"
#include "bfscreen.h"
#include "bfsprite.h"
#include "bftext.h"

#include "app_sprite.h"
#include "app_text_ba.h"
#include "app_text_cw.h"
#include "app_text_sf.h"
#include "sprfontut.h"

/******************************************************************************/
#pragma pack(1)


#pragma pack()
/******************************************************************************/

void hud_draw_clipped_text(struct DIHudClippedText *p_diClpText)
{
    LbTextSetWindow(p_diClpText->Rect.X, p_diClpText->Rect.Y,
      p_diClpText->Rect.Width, p_diClpText->Rect.Height);

    lbFontPtr = p_diClpText->pFont;
    lbDisplay.DrawColour = p_diClpText->Col;
    lbDisplay.DrawFlags = Lb_TEXT_ONE_COLOR;
    AppTextDrawLineBrigAdjWthPartsResized(p_diClpText->Shift.X, p_diClpText->Shift.Y,
      p_diClpText->Scale, p_diClpText->Bright, p_diClpText->Text);

    LbTextSetWindow(lbDisplay.GraphicsWindowX, lbDisplay.GraphicsWindowY,
      lbDisplay.GraphicsWindowWidth, lbDisplay.GraphicsWindowHeight);
}

int hud_width_shad_cl_flash_wrapped_text(short px, short py,
  struct TbSprite *p_font, const char *text, ushort drwflags, short units_per_px)
{
    ushort space_bkp;
    int height;

    lbFontPtr = p_font;
    lbDisplay.DrawFlags = drwflags;
    space_bkp = FontSpacingAlter(p_font, 12);
    height = LbTextWrapStringHeightResized(px, py, units_per_px, text);
    FontSpacingRestore(p_font, space_bkp);
    return height;
}

void hud_draw_shad_cl_flash_wrapped_text(struct DIHudWrappedText *p_diWrpText)
{
    ushort space_bkp;

    lbFontPtr = p_diWrpText->pFont;
    lbDisplay.DrawColour = p_diWrpText->Col;
    lbDisplay.DrawFlags = p_diWrpText->DrwFlags;
#if defined(LB_ENABLE_SHADOW_COLOUR)
    lbDisplay.ShadowColour = p_diWrpText->Shade;
#endif
    space_bkp = FontSpacingAlter(p_diWrpText->pFont, 12);
    AppTextDrawShadClFlashResized(p_diWrpText->Rect.X, p_diWrpText->Rect.Y,
      p_diWrpText->Scale, p_diWrpText->Timer, p_diWrpText->Text);
    FontSpacingRestore(p_diWrpText->pFont, space_bkp);
}

void hud_draw_colour_wave_wrapped_text(struct DIHudWrappedText *p_diWrpText)
{
    ushort space_bkp;

    lbFontPtr = p_diWrpText->pFont;
    lbDisplay.DrawColour = p_diWrpText->Col;
    lbDisplay.DrawFlags = p_diWrpText->DrwFlags;
#if defined(LB_ENABLE_SHADOW_COLOUR)
    lbDisplay.ShadowColour = p_diWrpText->Shade;
#endif
    space_bkp = FontSpacingAlter(p_diWrpText->pFont, 12);
    AppTextDrawColourWaveResized(p_diWrpText->Rect.X, p_diWrpText->Rect.Y,
      p_diWrpText->Scale, p_diWrpText->Text);
    FontSpacingRestore(p_diWrpText->pFont, space_bkp);
}

/******************************************************************************/
