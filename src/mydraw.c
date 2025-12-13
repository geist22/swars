/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file mydraw.c
 *     Modified drawing routines adjusted for the specific app.
 * @par Purpose:
 *     Functions which one of original devs apparently considered his.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     22 Apr 2024 - 28 Sep 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "mydraw.h"

#include "bffont.h"
#include "bfsprite.h"
#include "bftext.h"

#include "display.h"
#include "game.h"
#include "game_data.h"
#include "game_sprts.h"
#include "swlog.h"
#include "util.h"
/******************************************************************************/
extern ubyte text_colours[15];

ubyte my_char_to_upper(ubyte c)
{
    ubyte ret;
    asm volatile ("call ASM_my_char_to_upper\n"
        : "=r" (ret) : "a" (c));
    return ret;
}

int font_word_length(const char *text)
{
    const ubyte *p;
    int len;

    len = 0;
    for (p = (const ubyte *)text; *p != '\0'; p++)
    {
        struct TbSprite *spr;

        if (*p == 32)
            break;
        spr = &small_font[*p - 31];
        len += spr->SWidth;
    }
    return len;
}

int my_font_to_yshift(const struct TbSprite *p_font, char chr)
{
    if ((p_font == small_font) || (p_font == small2_font))
    {
        return 1;
    }
    else if (p_font == small_med_font)
    {
        if ((ubyte)chr >= (ubyte)'a' && (ubyte)chr <= (ubyte)'z')
            return 0;
        return 2;
    }
    else if (p_font == med_font || p_font == med2_font)
    {
        return 2;
    }
    else if (p_font == big_font)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

/** Parse control char from given string, return num bytes recognized.
 */
ubyte my_draw_apply_control_char(const char *ctext)
{
    ubyte cc;

    cc = (ubyte)ctext[0];

    if (cc == 0x01)
    {
        if ((lbDisplay.DrawFlags & 0x0004) != 0) {
            lbDisplay.DrawFlags &= ~0x0004;
        } else {
            lbDisplay.DrawFlags |= 0x0004;
        }
        return 1;
    }
    if (cc == 0x0C)
    {
        if ((lbDisplay.DrawFlags & 0x0040) != 0) {
            lbDisplay.DrawFlags &= 0x0040;
        } else {
            lbDisplay.DrawFlags |= 0x0040;
        }
        return 1;
    }
    if (cc == 0x0E)
    {
        lbDisplay.DrawColour = text_colours[ctext[1] - 1];
        return 2;
    }
    if (cc == 0x1B)
    {
        lbDisplay.DrawFlags |= 0x0040;
        return 1;
    }
    if (cc == 0x1C)
    {
        lbDisplay.DrawFlags &= 0x0040;
        return 1;
    }
    if (cc == 0x1E)
    {
        lbDisplay.DrawFlags &= ~0x0004;
        return 1;
    }
    return 0;
}

static short my_draw_one_char(short x, short y, char c)
{
    ubyte uc;
    short dy;

    uc = (ubyte)c;
    if ((lbFontPtr != small_med_font) || (language_3str[0] != 'e')) {
        uc = fontchrtoupper(c);
    }
    dy = my_font_to_yshift(lbFontPtr, uc);

    if ((lbDisplay.DrawFlags & Lb_TEXT_ONE_COLOR) != 0) {
        LbSpriteDrawOneColour(x, y - dy,
          &lbFontPtr[uc - 31], lbDisplay.DrawColour);
    } else {
        LbSpriteDraw(x, y - dy, &lbFontPtr[uc - 31]);
    }
    return LbTextCharWidth(uc);
}

/** Draw characters from `text` between `k_beg` and `k_end`, minding control sequences.
 */
static short my_draw_chunk(short x, short y, short tot_width, const char *text, short k_beg, short k_end)
{
    short cx, k;

    cx = x;
    if ((lbDisplay.DrawFlags & Lb_TEXT_HALIGN_RIGHT) != 0)
    {
        cx += (tot_width);
    }
    else if ((lbDisplay.DrawFlags & Lb_TEXT_HALIGN_CENTER) != 0)
    {
        cx += (tot_width >> 1);
    }

    for (k = k_beg; k < k_end; k++)
    {
        char c;
        ubyte nb;

        c = text[k];
        if ((ubyte)c <= 0x1f)
        {
            nb = my_draw_apply_control_char(&text[k]);
            if (nb > 1)
                k += nb - 1;
        }
        else
        {
            cx += my_draw_one_char(cx, y, c);
        }
    }

    return cx - x;
}

/** Skips characters from `text` between `k_beg` and `k_end`, minding control sequences.
 *
 * Replacement for `my_draw_chunk()` when the actual drawing should not be performed.
 */
static void my_skip_chunk(short x, short y, short tot_width, const char *text, short k_beg, short k_end)
{
    short k;

    for (k = k_beg; k < k_end; k++)
    {
        char c;
        ubyte nb;

        c = text[k];
        if ((ubyte)c <= 0x1f)
        {
            nb = my_draw_apply_control_char(&text[k]);
            if (nb > 1)
                k += nb - 1;
        }
    }
}

ushort my_draw_text(short x, short y, const char *text, ushort startline)
{
#if 0
    ushort ret;
    asm volatile ("call ASM_my_draw_text\n"
        : "=r" (ret) : "a" (x), "d" (y), "b" (text), "c" (startline));
    return ret;
#endif
    int beg_x, scr_x;
    int v009;
    ubyte NewChar;
    int v29;
    const char *v32;
    int v33;
    const char *v35;
    int v36;
    int v89;
    int v90;
    short v91;
    short v92;
    ushort v93;
    ushort v95;
    ushort v96;
    short scr_y;
    int v98;
    ushort wndw_width;
    int cur_line;

    v89 = 0;
    cur_line = 0;
    v98 = 0;
    v90 = 0;
    if (text == NULL)
        return 0;
    v95 = 0;
    beg_x = text_window_x1 + x;
    v96 = 0;
    scr_x = beg_x;
    scr_y = text_window_y1 + y;
    wndw_width = text_window_x2 - scr_x;

    while ( 1 )
    {
        v009 = v89 + 1;
        NewChar = text[v89++];
        if (NewChar == '\0')
            break;
        if ((lbFontPtr != small_med_font) || (language_3str[0] != 'e')) {
            NewChar = fontchrtoupper(NewChar);
        }

        if (NewChar == 1)
        {
            goto LABEL_144;
        }
        else if (NewChar == 0x0A)
        {
            if (cur_line < startline)
            {
                my_skip_chunk(scr_x, scr_y, wndw_width - v90, text, v96, v89 - 1);
            }
            else
            {
                if (scr_y >= text_window_y1) {
                    scr_x += my_draw_chunk(scr_x, scr_y, wndw_width - v90, text, v96, v89 - 1);
                }
                scr_y += font_height('A') + byte_197160;
                if (scr_y + font_height('A') > text_window_y2)
                    return cur_line;
            }

            scr_x = beg_x;
            if ( text[v89] )
                  ++cur_line;
            v96 = v89;
            v95 = v89;
            v90 = 0;
            goto LABEL_144;
        }
        else if (NewChar == 0x0C)
        {
            goto LABEL_144;
        }
        else if (NewChar == 0x0E)
        {
            v89++;
            goto LABEL_144;
        }
        else if ((NewChar >= 0x1B) && (NewChar <= 0x1C))
        {
            goto LABEL_144;
        }
        else if (NewChar == 0x2D)
        {
            v95 = v89;
            v29 = v90 + LbTextCharWidth(NewChar);
            v98 = v29;
        }
        else if (NewChar == 0x20)
        {
            v95 = v89;
            v29 = v90;
            v98 = v29;
        }
        else if (NewChar == 0x1E)
        {
          goto LABEL_144;
        }
        else
        {
          goto LABEL_131;
        }

LABEL_131:
        if ( NewChar > 0x1Fu )
        {
            v90 += LbTextCharWidth(NewChar);
        }

LABEL_144:
        if ( (ushort)v90 > wndw_width )
        {
          if ( v95 == v96 )
          {
            if ( text[v89] )
            {
              v90 -= LbTextCharWidth(text[v89]);
            }
            v32 = &text[v89];
            do
            {
              v33 = *--v32;
              --v89;
            }
            while ( v33 < 32 );
            v91 = v90 - LbTextCharWidth(*v32);
            v35 = &text[v89];
            do
            {
              v36 = *--v35;
              --v89;
            }
            while ( v36 < 32 );
            v92 = v91 - LbTextCharWidth(*v35);
            v93 = v92 + LbTextCharWidth('-');

            if (startline > cur_line)
            {
                my_skip_chunk(scr_x, scr_y, wndw_width - v93, text, v96, v89 - 1);
            }
            else
            {
                if (scr_y < text_window_y1) {
                    scr_x += my_draw_chunk(scr_x, scr_y, wndw_width - v93, text, v96, v89);
                    scr_x += my_draw_one_char(scr_x, scr_y, '-');
                }
                scr_y += font_height('A') + byte_197160;
                if (scr_y + font_height('A') > text_window_y2)
                    return cur_line;
            }

            scr_x = beg_x;
            v95 = v89;
            v96 = v89;
            v98 = 0;
            v90 = 0;
            ++cur_line;
          }
          else
          {
            if (cur_line < startline)
            {
                my_skip_chunk(scr_x, scr_y, wndw_width - v98, text, v96, v89 - 1);
            }
            else
            {
                if (scr_y >= text_window_y1) {
                    scr_x += my_draw_chunk(scr_x, scr_y, wndw_width - v98, text, v96, v95);
                }
                scr_y += font_height('A') + byte_197160;
                if (scr_y + font_height('A') > text_window_y2)
                    return cur_line;
            }


            v96 = v95;
            ++cur_line;
            v90 -= v98;
            if ( text[v95 - 1] == 32 )
            {
              v90 = (ushort)v90 - LbTextCharWidth(32);
            }
            scr_x = beg_x;
          }
        }
    }

    if (cur_line < startline)
    {
        my_draw_chunk(scr_x, scr_y, wndw_width - v90, text, v96, v009 - 1);
    }
    else
    {
        if (scr_y >= text_window_y1) {
            scr_x += my_draw_chunk(scr_x, scr_y, wndw_width - v90, text, v96, v89 - 1);
        }
        cur_line += 1;
    }
    return cur_line;
}

/******************************************************************************/
