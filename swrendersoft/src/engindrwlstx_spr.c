/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file engindrwlstx_spr.c
 *     Drawlists execution for the 3D engine, sprite related items.
 * @par Purpose:
 *     Implements functions for executing previously made drawlists,
 *     meaning the actual drawing based on primitives in the list.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     22 Apr 2024 - 12 May 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "engindrwlstx.h"

#include <assert.h>

#include "bfgentab.h"
#include "bfsprite.h"
#include "insspr.h"

#include "engindrwlstm.h"
#include "enginzoom.h"
#include "frame_sprani.h"
#include "swlog.h"
/******************************************************************************/
extern long dword_176CE0;
extern long dword_176CE4;
extern long dword_176CE8;
extern long dword_176CEC;
extern long dword_176CF0;
extern long dword_176CF4;

extern short word_1A5834;
extern short word_1A5836;

extern long unkn1_pos_x;
extern long unkn1_pos_y;
extern struct TbSprite *unkn1_spr;

extern struct TbSprite *m_sprites;
/******************************************************************************/

void draw_unkn1_scaled_alpha_sprite(ushort frm, int scr_x, int scr_y, ushort scale, ushort alpha)
{
    struct Frame *p_frm;
    struct Element *p_el;
    int pos_x, pos_y;
    int swidth, sheight;

    p_frm = &frame[frm];
    lbSpriteReMapPtr = &pixmap.fade_table[256 * alpha];
    //TODO would probably make more sense to set the ghost ptr somewhere during game setup
    render_ghost = &pixmap.ghost_table[0*PALETTE_8b_COLORS];

    pos_x = 99999;
    pos_y = 99999;
    for (p_el = &melement_ani[p_frm->FirstElement]; p_el > melement_ani; p_el = &melement_ani[p_el->Next])
    {
        if (pos_x > p_el->X >> 1)
            pos_x = p_el->X >> 1;
        if (pos_y > p_el->Y >> 1)
            pos_y = p_el->Y >> 1;
    }

    swidth = p_frm->SWidth;
    sheight = p_frm->SHeight;
    word_1A5834 = pos_x;
    word_1A5836 = pos_y;
    if ((scale * swidth) >> 9 <= 1)
        return;
    if ((scale * sheight) >> 9 <= 1)
        return;

    dword_176CF0 = (scale * swidth) >> 9;
    dword_176CF4 = (scale * sheight) >> 9;
    dword_176CE0 = scr_x + ((scale * pos_x) >> 8);
    dword_176CE4 = scr_y + ((scale * pos_y) >> 8);
    dword_176CE8 = swidth >> 1;
    dword_176CEC = sheight >> 1;
    SetAlphaScalingData(dword_176CE0, dword_176CE4, dword_176CE8, dword_176CEC, dword_176CF0, dword_176CF4);

    for (p_el = &melement_ani[p_frm->FirstElement]; p_el > melement_ani; p_el = &melement_ani[p_el->Next])
    {
        struct TbSprite *p_spr;

        if ((p_el->Flags & 0xFE00) != 0)
            continue;
        p_spr = (struct TbSprite *)((ubyte *)m_sprites + p_el->ToSprite);
        if (p_spr <= m_sprites)
            continue;

        lbDisplay.DrawFlags = p_el->Flags & 0x0F;
        if ((lbDisplay.DrawFlags & Lb_SPRITE_TRANSPAR4) == 0)
            lbDisplay.DrawFlags |= Lb_SPRITE_TRANSPAR8;

        unkn1_pos_x = (p_el->X >> 1) - pos_x;
        unkn1_pos_y = (p_el->Y >> 1) - pos_y;
        unkn1_spr = p_spr;
        DrawSpriteWthShadowUsingScalingData(unkn1_pos_x, unkn1_pos_y, p_spr);
    }
    lbDisplay.DrawFlags = 0;
}

void draw_unkn2_scaled_alpha_sprite(ubyte *frv, ushort frm, short x, short y,
  ubyte bri)
{
    struct Frame *p_frm;
    struct Element *p_elem;
    int max_x, max_y;
    int min_x, min_y;
    int range_x, range_y;
    TbBool really_draw;

    really_draw = 0;
    max_x = -99999;
    max_y = -99999;
    min_x = 99999;
    min_y = 99999;
    p_frm = &frame[frm];

    for (p_elem = &melement_ani[p_frm->FirstElement]; p_elem > melement_ani;
      p_elem = &melement_ani[p_elem->Next])
    {
        struct TbSprite *p_spr;

        if (frv[(p_elem->Flags >> 4) & 0x1F] == ((p_elem->Flags >> 9) & 0x07))
        {
            int tmp;

            really_draw = 1;
            p_spr = (struct TbSprite *)((ubyte *)m_sprites + p_elem->ToSprite);
            if (min_x > p_elem->X >> 1)
                min_x = p_elem->X >> 1;
            if (min_y > p_elem->Y >> 1)
                min_y = p_elem->Y >> 1;
            tmp = p_spr->SWidth + (p_elem->X >> 1);
            if (max_x < tmp)
                max_x = tmp;
            tmp = p_spr->SHeight + (p_elem->Y >> 1);
            if (max_y < tmp)
                max_y = tmp;
        }
    }

    if (!really_draw)
        return;

    lbSpriteReMapPtr = &pixmap.fade_table[256 * bri];
    word_1A5834 = min_x;
    word_1A5836 = min_y;

    range_x = max_x - min_x;
    range_y = max_y - min_y;
    if ((range_x > 0) && (range_x <= 128) && (range_y > 0) && (range_y <= 128))
    {
        if ( (overall_scale * p_frm->SWidth) >> 9 > 1 && (overall_scale * p_frm->SHeight) >> 9 > 1 )
        {
            dword_176CE0 = ((min_x * overall_scale) >> 8) + x;
            dword_176CE4 = ((min_y * overall_scale) >> 8) + y;
            dword_176CE8 = range_x;
            dword_176CEC = range_y;
            dword_176CF0 = (range_x * overall_scale) >> 8;
            dword_176CF4 = (range_y * overall_scale) >> 8;
            SetAlphaScalingData(dword_176CE0, dword_176CE4, dword_176CE8,
              dword_176CEC, dword_176CF0, dword_176CF4);

            for (p_elem = &melement_ani[p_frm->FirstElement]; p_elem > melement_ani;
              p_elem = &melement_ani[p_elem->Next])
            {
                struct TbSprite *p_spr;

                p_spr = (struct TbSprite *)((ubyte *)m_sprites + p_elem->ToSprite);
                if (p_spr <= m_sprites)
                    continue;

                lbDisplay.DrawFlags = p_elem->Flags & 7;
                if ((lbDisplay.DrawFlags & Lb_SPRITE_TRANSPAR4) == 0)
                    lbDisplay.DrawFlags |= Lb_SPRITE_TRANSPAR8;

                if (frv[(p_elem->Flags >> 4) & 0x1F] == ((p_elem->Flags >> 9) & 0x07))
                {
                    unkn1_pos_x = (p_elem->X >> 1) - min_x;
                    unkn1_pos_y = (p_elem->Y >> 1) - min_y;
                    unkn1_spr = p_spr;
                    DrawSpriteWthShadowUsingScalingData(unkn1_pos_x, unkn1_pos_y, unkn1_spr);
                }
            }
            lbDisplay.DrawFlags = 0;
        }
    }
}


void draw_unkn3_scaled_alpha_sprite(ushort frm, short x, short y, ubyte bri)
{
    struct Frame *p_frm;
    struct Element *p_elem;

    p_frm = &frame[frm];
    for (p_elem = &melement_ani[p_frm->FirstElement]; p_elem > melement_ani;
      p_elem = &melement_ani[p_elem->Next])
    {
        struct TbSprite *p_spr;

        p_spr = (struct TbSprite *)((ubyte *)m_sprites + p_elem->ToSprite);
        if (p_spr <= m_sprites)
            continue;

        lbDisplay.DrawFlags = p_elem->Flags & 0x07;
        if ((p_elem->Flags & 0xFE00) == 0) {
            LbSpriteDrawRemap((p_elem->X >> 1) + x, (p_elem->Y >> 1) + y,
              p_spr, &pixmap.fade_table[256 * bri]);
        }
        if (word_1A5834 > p_elem->X >> 1)
            word_1A5834 = p_elem->X >> 1;
        if (word_1A5836 > p_elem->Y >> 1)
            word_1A5836 = p_elem->Y >> 1;
    }
    lbDisplay.DrawFlags = 0;
}

void draw_unkn4_scaled_alpha_sprite(ubyte *frv, ushort frm, short x, short y,
  ubyte bri)
{
    struct Frame *p_frm;
    struct Element *p_elem;

    p_frm = &frame[frm];
    for (p_elem = &melement_ani[p_frm->FirstElement]; p_elem > melement_ani;
      p_elem = &melement_ani[p_elem->Next])
    {
        struct TbSprite *p_spr;

        p_spr = (struct TbSprite *)((ubyte *)m_sprites + p_elem->ToSprite);
        if (p_spr <= m_sprites)
            continue;

        lbDisplay.DrawFlags = p_elem->Flags & 7;
        if (frv[(p_elem->Flags >> 4) & 0x1F] == ((p_elem->Flags >> 9) & 0x07))
        {
            if (((p_elem->Flags >> 4) & 0x1F) == 4)
                LbSpriteDraw((p_elem->X >> 1) + x, (p_elem->Y >> 1) + y, p_spr);
            else
                LbSpriteDrawRemap((p_elem->X >> 1) + x, (p_elem->Y >> 1) + y,
                  p_spr, &pixmap.fade_table[256 * bri]);
            if (word_1A5834 > p_elem->X >> 1)
                word_1A5834 = p_elem->X >> 1;
            if (word_1A5836 > p_elem->Y >> 1)
                word_1A5836 = p_elem->Y >> 1;
        }
    }
    lbDisplay.DrawFlags = 0;
}

/******************************************************************************/
