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

ushort my_draw_text(short x, short y, const char *text, ushort startline)
{
#if 0
    ushort ret;
    asm volatile ("call ASM_my_draw_text\n"
        : "=r" (ret) : "a" (x), "d" (y), "b" (text), "c" (startline));
    return ret;
#endif
  int v007;
  int v008;
  int v009;
  ubyte NewChar;
  int v013;
  ubyte v017;
  ubyte v22;
  int v23;
  char v27;
  int v29;
  const char *v32;
  int v33;
  const char *v35;
  int v36;
  int v39;
  int k;
  char v50;
  int v52;
  char v56;
  int v57;
  int n;
  char v67;
  int v68;
  char v71;
  int v73;
  int v74;
  ubyte v78;
  ubyte v79;
  char v83;
  int v84;
  int v85;
  char v88;
  int v89;
  int v90;
  short v91;
  short v92;
  ushort v93;
  ushort v95;
  ushort v96;
  ubyte v97[6];
  short v97_hw;
  int v98;
  ushort v99;
  int v100;
  ubyte v101;
  ubyte v102;
  ubyte v103;
  ubyte v104;

  v89 = 0;
  v100 = 0;
  v98 = 0;
  v90 = 0;
  if (text == NULL)
    return 0;
  v007 = text_window_x1;
  v95 = 0;
  v008 = v007 + x;
  v96 = 0;
  *(u32 *)v97 = v008;
  v97_hw = text_window_y1 + y;
  v99 = text_window_x2 - v008;
  while ( 1 )
  {
    v009 = v89 + 1;
    NewChar = text[v89++];
    if (NewChar == '\0')
        break;
    if ((lbFontPtr != small_med_font) || (language_3str[0] != 'e'))
    {
        NewChar = fontchrtoupper(NewChar);
    }

    if (NewChar < 0x0A)
    {
        if (NewChar != 1)
          goto LABEL_131;
    }
    else if (NewChar == 0x0A)
    {
        if ( (ushort)v100 >= startline )
        {
            if ( v97_hw < text_window_y1 )
              goto LABEL_33;
            if ((lbDisplay.DrawFlags & 0x0080) != 0) {
                v008 = v99 - v90 + v008;
            } else if ((lbDisplay.DrawFlags & 0x0100) != 0) {
                v008 = ((v99 - (ushort)v90) >> 1) + v008;
            }

            for (v013 = v96; v013 < v89 - 1; v013++)
            {
                v22 = text[v013];
                if ((ubyte)v22 == 0x01)
                {
                    if ((lbDisplay.DrawFlags & 0x0004) != 0) {
                        lbDisplay.DrawFlags &= ~0x0004;
                    } else {
                        lbDisplay.DrawFlags |= 0x0004;
                    }
                    goto LABEL_80;
                }
                else if ((ubyte)v22 == 0x0C)
                {
                    if ((lbDisplay.DrawFlags & 0x0040) != 0) {
                        lbDisplay.DrawFlags &= 0x0040;
                    } else {
                        lbDisplay.DrawFlags |= 0x0040;
                    }
                    goto LABEL_80;
                }
                else if ((ubyte)v22 == 0x0E)
                {
                    lbDisplay.DrawColour = text_colours[text[++v013] - 1];
                    goto LABEL_80;
                }
                else if ((ubyte)v22 == 0x1B)
                {
                    lbDisplay.DrawFlags |= 0x0040;
                    goto LABEL_80;
                }
                else if ((ubyte)v22 == 0x1C)
                {
                    lbDisplay.DrawFlags &= 0x0040;
                    goto LABEL_80;
                }
                else if ((ubyte)v22 == 0x1E)
                {
                    lbDisplay.DrawFlags &= ~0x0004;
                    goto LABEL_80;
                }
                else
                {
                    v104 = text[v013];
                    if ( v104 <= 0x1Fu )
                        goto LABEL_80;
                    if ((lbFontPtr != small_med_font) || (language_3str[0] != 'e')) {
                        v104 = fontchrtoupper(v104);
                    }
                    v017 = my_font_to_yshift(lbFontPtr, v104);
                    if ((lbDisplay.DrawFlags & 0x0040) != 0) {
                        LbSpriteDrawOneColour(v008, v97_hw - v017,
                          &lbFontPtr[v104 - 31], lbDisplay.DrawColour);
                    } else {
                        LbSpriteDraw(v008, v97_hw - v017, &lbFontPtr[v104 - 31]);
                    }
                    v008 += LbTextCharWidth(v104);
                    goto LABEL_80;
                }
LABEL_80:
                ;
            }

LABEL_33:
              v97_hw += (ubyte)byte_197160 + font_height('A');
              if ( v97_hw + font_height('A') > text_window_y2 )
                return v100;
              goto LABEL_121;
        }

        for (v23 = v96; v23 >= v89 - 1; v23++)
        {
            v27 = text[v23];
            if ((ubyte)v27 == 0x01)
            {
                if ((lbDisplay.DrawFlags & 0x0004) == 0) {
                    lbDisplay.DrawFlags |= 0x0004;
                } else {
                    lbDisplay.DrawFlags &= ~0x0004;
                }
            }
            else if ((ubyte)v27 == 0x0C)
            {
                if ((lbDisplay.DrawFlags & 0x0040) != 0) {
                    lbDisplay.DrawFlags &= ~0x0040;
                }
            }
            else if ((ubyte)v27 == 0x0E)
            {
                lbDisplay.DrawColour = text_colours[text[++v23] - 1];
            }
            else if ((ubyte)v27 == 0x1C)
            {
                lbDisplay.DrawFlags &= ~0x0040;
            }
            else if ((ubyte)v27 == 0x1E)
            {
                lbDisplay.DrawFlags &= ~0x0004;
            }
            else if ((ubyte)v27 == 0x1B)
            {
                lbDisplay.DrawFlags |= 0x0040;
            }
        }

LABEL_121:
            v008 = *(ushort *)v97;
            if ( text[v89] )
              ++v100;
            v96 = v89;
            v95 = v89;
            v90 = 0;
            goto LABEL_144;

    }
    else if (NewChar < 0x0E)
    {
        if (NewChar != 0x0C)
          goto LABEL_131;
    }
    else if (NewChar == 0x0E)
    {
        v89++;
    }
    else if (NewChar < 0x1E)
    {
      if ( NewChar < 0x1Bu || NewChar > 0x1Cu )
        goto LABEL_131;
    }
    else if (NewChar > 0x1E)
    {
      if (NewChar == 0x20 || NewChar == 0x2D)
      {
        v95 = v89;
        if (NewChar == 0x2D)
        {
          v29 = v90 + LbTextCharWidth(NewChar);
        }
        else
        {
          v29 = v90;
        }
        v98 = v29;
      }
LABEL_131:
      if ( NewChar > 0x1Fu )
      {
        v90 += LbTextCharWidth(NewChar);
      }
    }

LABEL_144:
    if ( (ushort)v90 > v99 )
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
        v93 = v92 + LbTextCharWidth(31 + 14);
        if ( startline > (ushort)v100 )
        {
          for (v52 = v96; v52 < v89 - 1; v52++)
          {
              v56 = text[v52];
              if ((ubyte)v56 == 0x01)
              {
                  if ((lbDisplay.DrawFlags & 0x0004) == 0) {
                      lbDisplay.DrawFlags |= 0x0004;
                  } else {
                      lbDisplay.DrawFlags &= ~0x0004;
                  }
              }
              else if ((ubyte)v56 == 0x0C)
              {
                  if ((lbDisplay.DrawFlags & 0x0040) == 0) {
                      lbDisplay.DrawFlags |= 0x0040;
                  } else {
                      lbDisplay.DrawFlags &= ~0x0040;
                  }
              }
              else if ((ubyte)v56 == 0x0E)
              {
                  lbDisplay.DrawColour = text_colours[text[++v52] - 1];
              }
              else if ((ubyte)v56 == 0x1B)
              {
                  lbDisplay.DrawFlags |= 0x0040;
              }
              else if ((ubyte)v56 == 0x1Cu)
              {
                  lbDisplay.DrawFlags &= ~0x0040;
              }
              else if ((ubyte)v56 == 0x1E)
              {
                  lbDisplay.DrawFlags &= ~0x0004;
              }
          }
          goto LABEL_284;
        }
        if ( v97_hw < text_window_y1 )
          goto LABEL_261;
        if ((lbDisplay.DrawFlags & 0x0080) != 0)
        {
            v39 = v99 - v93;
            v008 += v39;
        }
        else if ((lbDisplay.DrawFlags & 0x0100) != 0)
        {
            v39 = (v99 - v93) >> 1;
            v008 += v39;
        }

        for ( k = v96; k < v89; ++k )
        {
            v50 = text[k];
            if ((ubyte)v50 == 0x01)
            {
                if ((lbDisplay.DrawFlags & 0x0004) == 0) {
                    lbDisplay.DrawFlags |= 0x0004;
                } else {
                    lbDisplay.DrawFlags &= ~0x0004;
                }
                continue;
            }
            if ((ubyte)v50 == 0x0C)
            {
                if ((lbDisplay.DrawFlags & 0x0040) == 0) {
                    lbDisplay.DrawFlags |= 0x0040;
                } else {
                    lbDisplay.DrawFlags &= ~0x0040;
                }
                continue;
            }
            if ((ubyte)v50 == 0x0E) {
                lbDisplay.DrawColour = text_colours[text[++k] - 1];
                continue;
            }
            if ((ubyte)v50 == 0x1B) {
                lbDisplay.DrawFlags |= 0x0040;
                continue;
            }
            if ((ubyte)v50 == 0x1C) {
                lbDisplay.DrawFlags &= ~0x0040;
                continue;
            }
            if ((ubyte)v50 == 0x1E) {
                lbDisplay.DrawFlags &= ~0x0004;
                continue;
            }

            v102 = text[k];
            if (v102 > 0x1F)
            {
              if ((lbFontPtr != small_med_font) || (language_3str[0] != 'e')) {
                  v102 = fontchrtoupper(v102);
              }
              v017 = my_font_to_yshift(lbFontPtr, v102);
              if ((lbDisplay.DrawFlags & 0x0040) != 0) {
                  LbSpriteDrawOneColour(v008, v97_hw - v017,
                    &lbFontPtr[v102 - 31], lbDisplay.DrawColour);
              } else {
                  LbSpriteDraw(v008, v97_hw - v017, &lbFontPtr[v102 - 31]);
              }
              v008 += LbTextCharWidth(v102);
              continue;
            }
        }
        v017 = my_font_to_yshift(lbFontPtr, 31+14);
        if ((lbDisplay.DrawFlags & 0x0040) != 0) {
              LbSpriteDrawOneColour(v008, v97_hw - v017,
                &lbFontPtr[14], lbDisplay.DrawColour);
        } else {
              LbSpriteDraw(v008, v97_hw - v017, &lbFontPtr[14]);
        }
LABEL_261:
        v97_hw += font_height(0x41u) + (ubyte)byte_197160;
        if ( v97_hw + font_height(0x41u) > text_window_y2 )
            return v100;
LABEL_284:
        v008 = *(ushort *)v97;
        v95 = v89;
        v96 = v89;
        v98 = 0;
        v90 = 0;
        ++v100;
      }
      else
      {
        if ( (ushort)v100 < startline )
        {
          for (v68 = v96; v68 < v89 - 1; v68++)
          {
              v71 = text[v68];
              if ((ubyte)v71 == 0x01)
              {
                  if ((lbDisplay.DrawFlags & 0x0004) == 0) {
                      lbDisplay.DrawFlags |= 0x0004;
                  } else {
                      lbDisplay.DrawFlags &= ~0x0004;
                  }
              }
              else if ((ubyte)v71 == 0x0C)
              {
                  if ((lbDisplay.DrawFlags & 0x0040) == 0) {
                      lbDisplay.DrawFlags |= 0x0040;
                  } else {
                      lbDisplay.DrawFlags &= ~0x0040;
                  }
              }
              else if ((ubyte)v71 == 0x0E)
              {
                  lbDisplay.DrawColour = text_colours[text[++v68] - 1];
              }
              else if ((ubyte)v71 == 0x1B)
              {
                 lbDisplay.DrawFlags |= 0x0040;
              }
              else if ((ubyte)v71 == 0x1C)
              {
                  lbDisplay.DrawFlags &= ~0x0040;
              }
              else if ((ubyte)v71 == 0x1E)
              {
                  lbDisplay.DrawFlags &= ~0x0004;
              }
          }
          goto LABEL_382;
        }
        if ( v97_hw >= text_window_y1 )
        {
          if ((lbDisplay.DrawFlags & 0x0080) == 0)
          {
            if ((lbDisplay.DrawFlags & 0x0100) == 0)
            {
LABEL_292:
              for ( n = v96; ; ++n )
              {
                if ( n >= v95 )
                  goto LABEL_359;
                v67 = text[n];
                if ((ubyte)v67 == 0x01)
                {
                    if ((lbDisplay.DrawFlags & 0x0004) != 0) {
                        lbDisplay.DrawFlags &= ~0x0004;
                    } else {
                        lbDisplay.DrawFlags |= 0x0004;
                    }
                }
                else if ((ubyte)v67 == 0x0C)
                {
                    if ((lbDisplay.DrawFlags & 0x0040) != 0) {
                        lbDisplay.DrawFlags &= ~0x0040;
                    } else {
                        lbDisplay.DrawFlags |= 0x0040;
                    }
                }
                else if ((ubyte)v67 == 0x0E)
                {
                    lbDisplay.DrawColour = text_colours[text[++n] - 1];
                }
                else if ((ubyte)v67 == 0x1B)
                {
                    lbDisplay.DrawFlags |= 0x0040;
                }
                else if ((ubyte)v67 == 0x1C)
                {
                    lbDisplay.DrawFlags &= ~0x0040;
                }
                else if ((ubyte)v67 == 0x1E)
                {
                    lbDisplay.DrawFlags &= ~0x0004;
                }
                else
                {
                    v103 = text[n];
                    if ( v103 <= 0x1Fu )
                      goto LABEL_338;
                    if ((lbFontPtr != small_med_font) || (language_3str[0] != 'e'))
                    {
                      v103 = fontchrtoupper(v103);
                    }
                    v017 = my_font_to_yshift(lbFontPtr, v103);
                    if ((lbDisplay.DrawFlags & 0x0040) != 0) {
                        LbSpriteDrawOneColour(v008, v97_hw - v017,
                          &lbFontPtr[v103 - 31], lbDisplay.DrawColour);
                    } else {
                        LbSpriteDraw(v008, v97_hw - v017, &lbFontPtr[v103 - 31]);
                    }
                    v008 += LbTextCharWidth(v103);
                    goto LABEL_338;
                }

LABEL_338:
                ;
              }


            }
            v57 = (v99 - (ushort)v98) >> 1;
          }
          else
          {
            v57 = v99 - v98;
          }
          v008 += v57;
          goto LABEL_292;
        }
LABEL_359:
        v97_hw += font_height(0x41u) + (ubyte)byte_197160;
        if ( v97_hw + font_height(0x41u) > text_window_y2 )
          return v100;
LABEL_382:
        v96 = v95;
        ++v100;
        v90 -= v98;
        if ( text[v95 - 1] == 32 )
        {
          v90 = (ushort)v90 - LbTextCharWidth(32);
        }
        v008 = *(ushort *)v97;
      }
    }
  }
  if ( (ushort)v100 >= startline )
  {
    if ( v97_hw < text_window_y1 )
      return v100 + 1;
    if ((lbDisplay.DrawFlags & 0x0080) != 0)
    {
      v73 = v99 - v90;
      goto LABEL_394;
    }
    if ((lbDisplay.DrawFlags & 0x0100) != 0)
    {
      v73 = (v99 - (ushort)v90) >> 1;
LABEL_394:
      v008 += v73;
    }
    v74 = v96;
    if ( v96 >= v89 - 1 )
      return v100 + 1;
    while ( 2 )
    {
        v83 = text[v74];
        if ((ubyte)v83 == 0x01)
        {
            if ((lbDisplay.DrawFlags & 0x0004) != 0) {
                lbDisplay.DrawFlags &= ~0x0004;
            } else {
                lbDisplay.DrawFlags |= 0x0004;
            }
            goto LABEL_442;
        }
        else if (v83 == 0x0C)
        {
            if ((lbDisplay.DrawFlags & 0x0040) != 0)
            {
              lbDisplay.DrawFlags &= ~0x0040;
              goto LABEL_442;
            }
            lbDisplay.DrawFlags |= 0x0040;
            goto LABEL_442;
        }
        else if ((ubyte)v83 == 0x0E)
        {
            lbDisplay.DrawColour = text_colours[text[++v74] - 1];
            goto LABEL_442;
        }
        else if ((ubyte)v83 == 0x1B)
        {
            lbDisplay.DrawFlags |= 0x0040;
            goto LABEL_442;
        }
        else if ((ubyte)v83 == 0x1C)
        {
            lbDisplay.DrawFlags &= ~0x0040;
            goto LABEL_442;
        }
        else if ((ubyte)v83 == 0x1E)
        {
            lbDisplay.DrawFlags &= ~0x0004;
            goto LABEL_442;
        }
        else
        {
          v101 = text[v74];
          if (v101 <= 0x1F)
            goto LABEL_442;
          if ((lbFontPtr != small_med_font) || (language_3str[0] != 'e')) {
            v101 = fontchrtoupper(v101);
          }
          v017 = my_font_to_yshift(lbFontPtr, v101);
          if ((lbDisplay.DrawFlags & 0x0040) != 0) {
              LbSpriteDrawOneColour(v008, v97_hw - v017,
                &lbFontPtr[v101 - 31], lbDisplay.DrawColour);
          } else {
              LbSpriteDraw(v008, v97_hw - v017, &lbFontPtr[v101 - 31]);
          }
          v008 += LbTextCharWidth(v101);
          goto LABEL_442;
        }

LABEL_442:
        if ( ++v74 >= v89 - 1 )
            return v100 + 1;
        continue;
    }
  }
  v84 = v96;
  v85 = v009 - 1;
  if ( v96 >= v009 - 1 )
    return v100;
  while ( 1 )
  {
LABEL_476:
    while ( 1 )
    {
      v88 = text[v84];
      if ((ubyte)v88 < 0x0E)
        break;
      if ((ubyte)v88 == 0x0E)
      {
          lbDisplay.DrawColour = text_colours[text[v84 + 1] - 1];
          v84 += 2;
          if (v84 >= v85)
            return v100;
      }
      else if ((ubyte)v88 < 0x1C)
      {
        if (v88 == 0x1B) {
          goto LABEL_467;
        }
        if (++v84 >= v85) {
          return v100;
        }
      }
      else
      {
        if ((ubyte)v88 <= 0x1C)
          goto LABEL_466;
        if ( v88 == 30 )
        {
LABEL_470:
          lbDisplay.DrawFlags &= ~0x0004;
          if ( ++v84 >= v85 )
            return v100;
          continue;
        }
        if ( ++v84 >= v85 )
          return v100;
      }
    }
    if (v88 == 0)
      goto LABEL_489;
    if ( (ubyte)v88 > 1u )
      break;
    if ((lbDisplay.DrawFlags & 0x0004) != 0)
      goto LABEL_470;
    lbDisplay.DrawFlags |= 0x0004;
    if ( ++v84 >= v85 )
      return v100;
  }
  if ( v88 != 12 )
    goto LABEL_489;
  if ((lbDisplay.DrawFlags & 0x0040) == 0)
  {
LABEL_467:
    lbDisplay.DrawFlags |= 0x0040;
    if ( ++v84 >= v85 )
      return v100;
    goto LABEL_476;
  }
LABEL_466:
  lbDisplay.DrawFlags &= ~0x0040;
LABEL_489:
  if ( ++v84 < v85 )
    goto LABEL_476;
  return v100;
}

/******************************************************************************/
