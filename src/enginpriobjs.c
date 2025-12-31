/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file enginpriobjs.c
 *     Primitive objects support required by the 3D engine.
 * @par Purpose:
 *     Implement functions for handling primitive objects in 3D world.
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
#include "enginpriobjs.h"

#include "bffile.h"

#include "enginpritxtr.h"
#include "enginsngobjs.h"
#include "enginsngtxtr.h"
#include "game_data.h"
#include "game_options.h"
#include "thing.h"
#include "swlog.h"
/******************************************************************************/

ushort prim_object_points_count = 1;
ushort prim_object_faces_count = 1;
ushort prim_object_faces4_count = 1;
ushort prim_objects_count = 1;

ushort old_next_object, old_next_object_face, old_next_object_point,
  old_next_normal, old_next_face_texture;

void read_primveh_obj(const char *fname, int a2)
{
    long firstval;
    TbFileHandle fh;

    fh = LbFileOpen(fname, Lb_FILE_MODE_READ_ONLY);
    if ( fh == INVALID_FILE )
        return;
    LbFileRead(fh, &firstval, sizeof(long));
    if ( firstval != 1 )
    {
      LbFileRead(fh, &prim_object_points_count, sizeof(ushort));
      LbFileRead(fh, &prim_object_faces_count, sizeof(ushort));
      LbFileRead(fh, &prim_object_faces4_count, sizeof(ushort));
      LbFileRead(fh, &prim_objects_count, sizeof(ushort));
      LbFileRead(fh, &prim4_textures_count, sizeof(ushort));
      LbFileRead(fh, &prim_face_textures_count, sizeof(ushort));
      LbFileRead(fh, &prim_unknprop01, sizeof(ushort));
      LbFileRead(fh, prim_object_points, sizeof(struct SinglePoint) * prim_object_points_count);
      LbFileRead(fh, prim_object_faces, sizeof(struct SingleObjectFace3) * prim_object_faces_count);
      LbFileRead(fh, prim_object_faces4, sizeof(struct SingleObjectFace4) * prim_object_faces4_count);
      LbFileRead(fh, prim_objects, sizeof(struct SingleObject) * prim_objects_count);
      LbFileRead(fh, prim4_textures, sizeof(Prim4Texture) * prim4_textures_count);
      LbFileRead(fh, prim_face_textures, sizeof(struct SingleTexture) * prim_face_textures_count);
    }
    LbFileClose(fh);
}

void point_unkn_func_03(struct SinglePoint *p_point)
{
    int x, y, z;

    x = unkn2_pos_x * p_point->X;
    y = unkn2_pos_y * p_point->Y;
    z = unkn2_pos_z * p_point->Z;
    p_point->X = x >> 6;
    p_point->Y = y >> 6;
    p_point->Z = z >> 6;
}

static TbBool face_textures_equal(struct SingleTexture *p_textr1, struct SingleTexture *p_textr2)
{
    return ((p_textr1->TMapX1 == p_textr2->TMapX1)
         && (p_textr1->TMapX2 == p_textr2->TMapX2)
         && (p_textr1->TMapX3 == p_textr2->TMapX3)
         && (p_textr1->TMapY1 == p_textr2->TMapY1)
         && (p_textr1->TMapY2 == p_textr2->TMapY2)
         && (p_textr1->TMapY3 == p_textr2->TMapY3)
         && (p_textr1->Page == p_textr2->Page));
}

static TbBool floor_textures_equal(struct SingleFloorTexture *p_textr1, struct SingleFloorTexture *p_textr2)
{
    return ((p_textr1->TMapX1 == p_textr2->TMapX1)
         && (p_textr1->TMapX2 == p_textr2->TMapX2)
         && (p_textr1->TMapX3 == p_textr2->TMapX3)
         && (p_textr1->TMapX4 == p_textr2->TMapX4)
         && (p_textr1->TMapY1 == p_textr2->TMapY1)
         && (p_textr1->TMapY2 == p_textr2->TMapY2)
         && (p_textr1->TMapY3 == p_textr2->TMapY3)
         && (p_textr1->TMapY4 == p_textr2->TMapY4)
         && (p_textr1->Page == p_textr2->Page));
}

/** Find within game_face_textures index of a texture equivalent to given.
 */
ushort find_face_texture(struct SingleTexture *p_textr)
{
    struct SingleTexture *p_ctextr;
    ushort txtr;

    for (txtr = 1; txtr < next_face_texture; txtr++)
    {
        p_ctextr = &game_face_textures[txtr];
        if (face_textures_equal(p_textr, p_ctextr))
            return txtr;
    }
    return 0;
}

/** Find within game_textures index of a texture equivalent to given.
 */
ushort find_floor_texture(struct SingleFloorTexture *p_textr)
{
    struct SingleFloorTexture *p_ctextr;
    ushort txtr;

    for (txtr = 1; txtr < next_floor_texture; txtr++)
    {
        p_ctextr = &game_textures[txtr];
        if (floor_textures_equal(p_textr, p_ctextr))
            return txtr;
    }
    return 0;
}

ushort obj_face3_create_normal(ushort a1, struct SingleObjectFace3 *p_oface, int a3, int a4)
{
    ushort ret;
    asm volatile (
      "call ASM_obj_face3_create_normal\n"
        : "=r" (ret) : "a" (a1), "d" (p_oface), "b" (a3), "c" (a4));
    return ret;
}

ushort update_texture_from_anim_tmap(ushort a1)
{
    ushort ret;
    asm volatile (
      "call ASM_update_texture_from_anim_tmap\n"
        : "=r" (ret) : "a" (a1));
    return ret;
}

int func_420f8(ushort a1)
{
    int ret;
    asm volatile (
      "call ASM_func_420f8\n"
        : "=r" (ret) : "a" (a1));
    return ret;
}

void prim_obj_mem_debug(int itm_beg, int itm_end)
{
}

void sub_6031C(short tx, short tz, short a3, short ty)
{
#if 1
    asm volatile ("call ASM_sub_6031C\n"
        : : "a" (tx), "d" (tz), "b" (a3), "c" (ty));
#endif
}

/******************************************************************************/
