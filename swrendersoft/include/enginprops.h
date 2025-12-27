/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file enginprops.h
 *     Header file for enginprops.c.
 * @par Purpose:
 *     Stores render engine properties, used for altering the rendering.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     13 Oct 2024 - 22 Dec 2025
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef ENGINPROPS_H
#define ENGINPROPS_H

#include "bftypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
#pragma pack(1)


#pragma pack()
/******************************************************************************/
/** Animation turn for the animations controlled within the render engine.
 *
 * Animations which are independent of game action, like moving colours
 * on shiny text, may be implemented within the render engine completely.
 *
 * Such animations use this value as a measure of progressing time, and
 * therefore progressing animation frames.
 *
 * The value is expected to be incremented or set to game turns within
 * the game code.
 */
extern u32 render_anim_turn;

/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
