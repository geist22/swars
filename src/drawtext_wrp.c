/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file drawtext_wrp.c
 *     Drawing simple text within the 3D world, extended wrappers.
 * @par Purpose:
 *     Implement functions for drawing text, with its position transformed from
 *     in-mission map coordinated. Draws simple text, to be used for debug
 *     or in-game editors; for proper playtime text, use bitmap fonts instead.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     19 Apr 2022 - 27 Aug 2023
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "drawtext_wrp.h"

#include "bfline.h"
#include "bfscreen.h"

#include "drawtext.h"
#include "bigmap.h"
#include "display.h"
#include "engintrns.h"
#include "swlog.h"
/******************************************************************************/

void draw_line_transformed_at_ground(int x1, int y1, int x2, int y2, TbPixel colour)
{
#if 0
    asm volatile (
      "push %4\n"
      "call ASM_draw_line_transformed_at_ground\n"
        : : "a" (x1), "d" (y1), "b" (x2), "c" (y2), "g" (colour));
#endif
    int alt;
    struct EnginePoint ep1, ep2;

    ep1.X3d = x1 - engn_xc;
    alt = alt_at_point(x1, y1);
    ep1.Y3d = (alt >> 5);
    ep1.Z3d = y1 - engn_zc;
    ep1.Flags = 0;
    transform_point(&ep1);

    ep2.X3d = x2 - engn_xc;
    alt = alt_at_point(x2, y2);
    ep2.Y3d = (alt >> 5) - engn_yc;
    ep2.Z3d = y2 - engn_zc;
    ep2.Flags = 0;
    transform_point(&ep2);

    if ((ep1.pp.X > 0) && (ep1.pp.X < lbDisplay.GraphicsScreenWidth)
      && (ep1.pp.Y > 0) && (ep1.pp.Y < lbDisplay.GraphicsScreenHeight)
      && (ep2.pp.X > 0) && (ep2.pp.X < lbDisplay.GraphicsScreenWidth)
      && (ep2.pp.Y > 0) && (ep2.pp.Y < lbDisplay.GraphicsScreenHeight)) {
        LbDrawLine(ep1.pp.X, ep1.pp.Y, ep2.pp.X, ep2.pp.Y, colour);
    }
}

void draw_text_transformed_at_ground(int coord_x, int coord_z, const char *text)
{
#if 0
    asm volatile (
      "call ASM_draw_text_transformed_at_ground\n"
        : : "a" (coord_x), "d" (coord_z), "b" (text));
    return;
#endif
    int coord_y;

    coord_y = PRCCOORD_TO_YCOORD(alt_at_point(coord_x, coord_z));
    draw_text_transformed_col(coord_x, coord_y, coord_z, text, colour_lookup[ColLU_RED]);
}

void draw_number_transformed_at_ground(int coord_x, int coord_z, int num)
{
    char locstr[52];
    int coord_y;

    coord_y = PRCCOORD_TO_YCOORD(alt_at_point(coord_x, coord_z));
    sprintf(locstr, "%d", num);
    draw_text_transformed_col(coord_x, coord_y, coord_z, locstr, colour_lookup[ColLU_RED]);
}

/******************************************************************************/
