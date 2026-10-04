/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file app_box_lt.c
 *     Implementation of related functions.
 * @par Purpose:
 *     App-specific box drawing with soft transparency.
 * @par Comment:
 *     This is a modification of `gbox.c` from bflibrary.
 * @author   Tomasz Lis
 * @date     22 Apr 2023 - 02 Oct 2026
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "app_box.h"

#include <string.h>
#include <assert.h>
#include "bfscreen.h"
#include "bfline.h"

#include "app_line.h"
#include "app_sprite.h"

/******************************************************************************/

TbResult AppDrawBoxLowTransGrey(s32 X, s32 Y, s32 Width, s32 Height, TbPixel colour)
{
    //TODO implement
    return Lb_SUCCESS;
}

/******************************************************************************/
