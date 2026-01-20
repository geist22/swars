/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file drawtext_wrp.h
 *     Header file for drawtext_wrp.c.
 * @par Purpose:
 *     Drawing simple text within the 3D world.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     19 Apr 2022 - 27 Aug 2023
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef DRAWTEXT_WRP_H
#define DRAWTEXT_WRP_H

#include "bftypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
#pragma pack(1)


#pragma pack()
/******************************************************************************/

void draw_line_transformed_at_ground(int x1, int y1, int x2, int y2, TbPixel colour);
void draw_number_transformed_at_ground(int coord_x, int coord_z, int num);
void draw_text_transformed_at_ground(int coord_x, int coord_z, const char *text);

/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
