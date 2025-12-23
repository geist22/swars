/******************************************************************************/
// Bullfrog Engine Smacker Playback Library - for use to remake classic games
// like Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file bfsmack.c
 *     External interface of the smacker playback library.
 * @par Purpose:
 *     Surfaces used for drawing on screen or compositing layers.
 * @par Comment:
 *     Depends on the video support library, which is SDL in this implementation.
 * @author   Tomasz Lis
 * @date     12 Nov 2011 - 13 Jun 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "bfsmack.h"

#include <assert.h>

#include "bfkeybd.h"
#include "bfmemut.h"
#include "bfpalette.h"
#include "bfscreen.h"
#include "bfsvaribl.h"

#include "smack2ail.h"

/******************************************************************************/
//SmackDrawCallback smack_draw_callback = NULL;
void *(*smack_malloc)(uint32_t);
void (*smack_free)(void *);

// Currenlty only in the main game
//TODO make a copy here, we only need the bflibrary calls
extern int game_hacky_update(void);

extern ubyte byte_1E56DC[PALETTE_8b_SIZE];
/******************************************************************************/

void set_smack_malloc(void *(*cb)(uint32_t))
{
    smack_malloc = cb;
}

void set_smack_free(void (*cb)(void *ptr))
{
    smack_free = cb;
}

//TODO place SMACK* functions into separate file
void * RADAPI RADMALLOC(uint32_t size)
{
    if (size == 0)
        return NULL;
    if (size == (uint32_t)-1)
        return NULL;
    return smack_malloc(size);
}

void RADAPI RADFREE(void *mem_ptr)
{
    smack_free(mem_ptr);
}

struct Smack * RADAPI SMACKOPEN(uint32_t extrabuf, uint32_t flags, const char *name)
{
    struct Smack *p_smk;

    assert(sizeof(struct Smack) == 0x4AC);
    asm volatile (
      "push %3\n"
      "push %2\n"
      "push %1\n"
      "call ASM_SMACKOPEN\n"
        : "=r" (p_smk) : "g" (extrabuf), "g" (flags), "g" (name));
    return p_smk;
}

uint32_t RADAPI SMACKDOFRAME(struct Smack *p_smk)
{
    uint32_t ret;
    asm volatile (
      "push %1\n"
      "call ASM_SMACKDOFRAME\n"
        : "=r" (ret) : "g" (p_smk));
    return ret;
}

void RADAPI SMACKNEXTFRAME(struct Smack *p_smk)
{
    asm volatile (
      "push %0\n"
      "call ASM_SMACKNEXTFRAME\n"
        : : "g" (p_smk));
}

uint32_t RADAPI SMACKWAIT(struct Smack *p_smk)
{
    uint32_t ret;
    asm volatile (
      "push %1\n"
      "call ASM_SMACKWAIT\n"
        : "=r" (ret) : "g" (p_smk));
    return ret;
}

void RADAPI SMACKCLOSE(struct Smack *p_smk)
{
    asm volatile (
      "push %0\n"
      "call ASM_SMACKCLOSE\n"
        : : "g" (p_smk));
}

void RADAPI SMACKTOBUFFER(uint32_t Flags, const void *buf,
 uint32_t destheight, uint32_t Pitch, uint32_t top, uint32_t left, struct Smack *p_smk)
{
    asm volatile (
      "push %6\n"
      "push %5\n"
      "push %4\n"
      "push %3\n"
      "push %2\n"
      "push %1\n"
      "push %0\n"
      "call ASM_SMACKTOBUFFER\n"
        : : "g" (Flags), "g" (buf), "g" (destheight), "g" (Pitch), "g" (top), "g" (left), "g" (p_smk));
}

TbResult play_smk_direct(const char *fname, u32 smkflags, ushort plyflags, ushort mode)
{
#if 0
    TbResult ret;
    asm volatile ("call ASM_play_smk_direct\n"
        : "=r" (ret) : "a" (fname), "d" (smkflags), "b" (plyflags), "c" (mode));
    return ret;
#else
    struct Smack *p_smk;
    int scr_x, scr_y;
    uint frm_no;
    TbBool finish, update_pal;
    uint32_t soflags;

    if ((plyflags & 0x0001) == 0)
    {
        struct DIG_DRIVER *p_snddrv;

        p_snddrv = GetSoundDriver();
        if (p_snddrv != NULL) {
            SMACKSOUNDUSEMSS(0, p_snddrv);
        } else {
            plyflags |= 0x0001;
        }
    }

    if ((plyflags & 0x0001) != 0)
        soflags = 0;
    else
        soflags = 0xFE000;
    p_smk = SMACKOPEN(0xFFFFFFFF, soflags, fname);
    if (p_smk == NULL) {
        return Lb_FAIL;
    }

    if ((plyflags & 0x0100) != 0)
    {
#if defined(DOS)||defined(GO32)
        scr_x = (320 - p_smk->Width) >> 1;
        scr_y = (200 - p_smk->Height) >> 1;
        SMACKTOBUFFER(0, 0xA0000, 200, 320, scr_y, scr_x, p_smk);
#else
        assert(!"hardware framebuffer access not supported");
#endif
    }
    else
    {
        scr_x = (lbDisplay.GraphicsScreenWidth - p_smk->Width) >> 1;
        scr_y = (lbDisplay.GraphicsScreenHeight - p_smk->Height) >> 1;
        SMACKTOBUFFER(0, lbDisplay.WScreen, lbDisplay.GraphicsScreenHeight,
          lbDisplay.GraphicsScreenWidth, scr_y,  scr_x, p_smk);
    }

    finish = false;
    for (frm_no = 0; !finish; frm_no++)
    {
        if ((plyflags & 0x0400) == 0)
        {
            if (frm_no >= p_smk->Frames)
                break;
        }
        if ((plyflags & 0x0100) != 0)
        {
            if (p_smk != (struct Smack *)-108)
            {
                LbMemoryCopy(byte_1E56DC, p_smk->Palette, PALETTE_8b_SIZE);
                LbPaletteSet(byte_1E56DC);
            }
            SMACKDOFRAME(p_smk);
        }
        else
        {
            update_pal = false;
            if (p_smk != (struct Smack *)-108)
            {
                update_pal = true;
                LbMemoryCopy(byte_1E56DC, p_smk->Palette, PALETTE_8b_SIZE);
            }
            SMACKDOFRAME(p_smk);
            if (update_pal)
            {
                LbScreenWaitVbi();
                LbPaletteSet(byte_1E56DC);
            }
            LbScreenSwap();
        }
        SMACKNEXTFRAME(p_smk);

        while (SMACKWAIT(p_smk))
        {
            game_hacky_update();
            if ((plyflags & 0x0002) != 0)
                continue;
            if (lbKeyOn[KC_ESCAPE] || lbKeyOn[KC_RETURN] || lbKeyOn[KC_SPACE] || lbDisplay.MLeftButton)
            {
                finish = true;
            }
        }
    }
    SMACKCLOSE(p_smk);
    return Lb_SUCCESS;
#endif
}

TbResult play_smk_via_buffer(const char *fname, u32 smkflags, ushort plyflags, SmackDrawCallback callback)
{
    TbResult ret;
    asm volatile ("call ASM_play_smk_via_buffer\n"
        : "=r" (ret) : "a" (fname), "d" (smkflags), "b" (plyflags), "c" (callback));
    return ret;
}

TbResult play_smk(const char *fname, u32 smkflags, ushort plyflags)
{
    TbResult ret;

    lbDisplay.MLeftButton = 0;
    if ( (smack_draw_callback != NULL) || ((plyflags & SMK_PixelDoubleWidth) != 0)
        /*|| ((plyflags & SMK_InterlaceLine) != 0)*/ || ((plyflags & SMK_PixelDoubleLine) != 0)
        /*|| (LbScreenIsDoubleBufferred())*/ ) {
        plyflags &= ~SMK_UnknFlag100;
        ret = play_smk_via_buffer(fname, smkflags, plyflags, smack_draw_callback);
    } else {
        if (lbDisplay.GraphicsScreenHeight >= 400)
          plyflags &= ~SMK_UnknFlag100;
        ret = play_smk_direct(fname, smkflags, plyflags, lbDisplay.ScreenMode);
    }
    return ret;
}

/******************************************************************************/
