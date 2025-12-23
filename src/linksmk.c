/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file linksmk.c
 *     Link between the main game and smacker playback library.
 * @par Purpose:
 *     Callback and setup functions to integrate bfsmacklib with the game.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     12 Nov 2011 - 13 Jun 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "linksmk.h"

#include <assert.h>

#include "bfsmack.h"

#include "game_data.h"

/******************************************************************************/
extern ulong smack_malloc_used_tot;

/******************************************************************************/
// not callable outide ASM
void *ac_opti_smack_malloc(int msize);
void ac_opti_smack_mfree(void *ptr);

/** Primitive but very fast mem allocation.
 */
void *opti_smack_malloc(u32 msize)
{
    void *ptr;

    assert(smack_malloc_used_tot + msize < scratch_malloc_size);
    ptr = scratch_malloc_mem + smack_malloc_used_tot;
    smack_malloc_used_tot += msize;
    return ptr;
}

void opti_smack_mfree(void *ptr)
{
    // Do not free any memory - we have enough space to play one video
}

void smack_malloc_free_all(void)
{
    smack_malloc_used_tot = 0;
}

void smack_malloc_setup(void)
{
    smack_malloc_used_tot = 0;
    set_smack_malloc(ac_opti_smack_malloc);
    set_smack_free(ac_opti_smack_mfree);
}

/******************************************************************************/
