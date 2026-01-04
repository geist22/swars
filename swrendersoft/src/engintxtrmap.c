/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file engintxtrmap.c
 *     Engine texture map atlas storage.
 * @par Purpose:
 *     Implement functions for allocating and maintaining texture atlas.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     29 Sep 2023 - 02 Jan 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "engintxtrmap.h"

#include "bffile.h"
#include "bfmemory.h"
#include "bfmemut.h"

#include "game_options.h"
#include "swlog.h"
/******************************************************************************/

/******************************************************************************/

TbResult alloc_texturemaps(uint tmap_count)
{
    ubyte *p_buf;
    uint i;

    p_buf = NULL;
    if (tmap_count > 0)
    {
        p_buf = LbMemoryAlloc((tmap_count + 2) * (VEC_TMAP_WIDTH * VEC_TMAP_HEIGHT));
    }
    if (p_buf == NULL)
    {
        return Lb_FAIL;
    }
    ingame__Tmaps = p_buf;
    dword_1810D1 = p_buf;
    p_buf += VEC_TMAP_WIDTH * VEC_TMAP_HEIGHT;
    p_buf = (ubyte *)(((uintptr_t)p_buf + 0xffff) & ~0xffff);
    dword_1810D5 = p_buf - dword_1810D1;
    for (i = 0; i < tmap_count; i++)
    {
        vec_tmap[i] = p_buf;
        p_buf += VEC_TMAP_WIDTH * VEC_TMAP_HEIGHT;
    }
    ingame.LastTmap = tmap_count - 1;
    return Lb_SUCCESS;
}

/******************************************************************************/
