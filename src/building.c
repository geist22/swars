/******************************************************************************/
// Syndicate Wars Port, source port of the classic strategy game from Bullfrog.
/******************************************************************************/
/** @file building.c
 *     Buildings related functions.
 * @par Purpose:
 *     Implement functions for handling buildings.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     27 May 2022 - 12 Jun 2023
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "building.h"

#include "bfmath.h"
#include "bfmemory.h"
#include "bfutility.h"
#include "enginsngobjs.h"
#include "game_speed.h"
#include "game.h"
#include "matrix.h"
#include "thing.h"
#include "swlog.h"
/******************************************************************************/
ubyte dome_open_speed = 4;


struct Thing *create_building_thing(int x, int y, int z, ushort obj, ushort nobj, ushort a6)
{
    struct Thing *ret;
    asm volatile (
      "push %6\n"
      "push %5\n"
      "call ASM_create_building_thing\n"
        : "=r" (ret) : "a" (x), "d" (y), "b" (z), "c" (obj), "g" (nobj), "g" (a6));
    return ret;
}

void set_dome_col(struct Thing *p_building, ubyte flag)
{
    struct ColVectList *p_cvlist;
    ushort cvl_beg, cvl_num;
    ushort  cvl;

    cvl_beg = p_building->U.UObject.BuildStartVect;
    cvl_num = p_building->U.UObject.BuildNumbVect;
    if (flag)
    {
        for (cvl = cvl_beg; cvl < cvl_beg + cvl_num; cvl++)
        {
            p_cvlist = &game_col_vects_list[cvl];
            p_cvlist->NextColList |= 0x8000;
        }
    }
    else
    {
        for (cvl = cvl_beg; cvl < cvl_beg + cvl_num; cvl++)
        {
            p_cvlist = &game_col_vects_list[cvl];
            p_cvlist->NextColList &= ~0x8000;
        }
    }
}

void do_dome_rotate1(struct Thing *p_building)
{
#if 0
    asm volatile ("call ASM_do_dome_rotate1\n"
        : : "a" (p_building));
#endif
    ushort obj, i;
    ushort pt1_beg, pt1_num;

    obj = p_building->U.UObject.Object;
    pt1_beg = game_objects[obj].StartPoint;
    pt1_num = game_objects[obj].EndPoint - pt1_beg;
    for (i = obj + 1; i < obj + 8; i++)
    {
        int factrS, factrC;
        short angle;
        ushort pt2_beg;
        ushort dpt;

        angle = (i - obj) * p_building->SubState;
        pt2_beg = game_objects[i].StartPoint;
        factrC = lbSinTable[angle + 512];
        factrS = lbSinTable[angle];
        for (dpt = 0; dpt <= pt1_num; dpt++)
        {
            struct SinglePoint *p_point1;
            struct SinglePoint *p_point2;
            p_point1 = &game_object_points[pt1_beg + dpt];
            p_point2 = &game_object_points[pt2_beg + dpt];
            p_point2->Y = (factrC * p_point1->Y - factrS * p_point1->Z) >> 16;
            p_point2->Z = (factrC * p_point1->Z + factrS * p_point1->Y) >> 16;
        }
    }
}

void process_dome1(struct Thing *p_building)
{
#if 0
    asm volatile ("call ASM_process_dome1\n"
        : : "a" (p_building));
#endif
    uint timer0;

    switch (p_building->State)
    {
    case 1:
        timer0 = p_building->SubState - dome_open_speed;
        p_building->SubState = timer0;
        if (timer0 <= 127)
        {
            if ((timer0 >= 111u) && (timer0 < 111u + dome_open_speed)) {
                set_dome_col(p_building, 1);
            }
            do_dome_rotate1(p_building);
        }
        else
        {
            p_building->SubState = 0;
            p_building->Timer1 = 100;
            p_building->State = 7;
        }
        break;
    case 4:
        timer0 = p_building->SubState + dome_open_speed;
        p_building->SubState = timer0;
        if (timer0 <= 127)
        {
            if ((timer0 >= 112u) && (timer0 < 112u + dome_open_speed)) {
                set_dome_col(p_building, 0);
            }
            do_dome_rotate1(p_building);
        }
        else
        {
            p_building->SubState = 127;
            p_building->Timer1 = 100;
            p_building->State = 8;
        }
        break;
    case 7:
        if ((p_building->Flag & 0x0080) != 0)
            p_building->State = 4;
        p_building->Flag &= ~(0x0080|0x0040);
        break;
    case 8:
        if ((p_building->Flag & 0x0040) != 0)
            p_building->State = 1;
        p_building->Flag &= ~(0x0080|0x0040);
        break;
    default:
        p_building->SubState = 127;
        p_building->Timer1 = 100;
        p_building->State = 8;
        break;
    }
}

void collapse_building(short x, short height, short z, struct Thing *p_thing)
{
    asm volatile (
      "call ASM_collapse_building\n"
        :  : "a" (x), "d" (height), "b" (z), "c" (p_thing));
}

short create_a_pod(struct Thing *p_thing, struct Thing *p_loader, ushort pod_id)
{
    short ret;
    asm volatile (
      "call ASM_create_a_pod\n"
        : "=r" (ret) : "a" (p_thing), "d" (p_loader), "b" (pod_id));
    return ret;
}

void process_shuttle_loader(struct Thing *p_building)
{
    asm volatile ("call ASM_process_shuttle_loader\n"
        : : "a" (p_building));
}

void process_mounted_gun(struct Thing *p_building)
{
    asm volatile ("call ASM_process_mounted_gun\n"
        : : "a" (p_building));
}

void process_gate1(struct Thing *p_building)
{
    asm volatile ("call ASM_process_gate1\n"
        : : "a" (p_building));
}

void process_bld36(struct Thing *p_building)
{
    struct M33 *mat;
    mat = &local_mats[p_building->U.UObject.MatrixIndex];
    rotate_object_axis(mat, 0, 0, 32);
}

void process_building(struct Thing *p_building)
{
#if 0
    asm volatile ("call ASM_process_building\n"
        : : "a" (p_building));
#endif
    if ((p_building->Flag & 0x040000) != 0)
    {
        if ((p_building->Flag & 0x0002) != 0)
        {
            p_building->Flag &= ~0x040000;
            return;
        }
        collapse_building(p_building->X >> 8, p_building->Y >> 8, p_building->Z >> 8, p_building);
        return;
    }

    switch (p_building->SubType)
    {
    case SubTT_BLD_SHUTLDR:
        if ((p_building->Flag & 0x0002) == 0)
        {
            if ((p_building->U.UObject.PrevThing == 0) && ((p_building->Flag & 0x8000000) == 0)) {
                process_shuttle_loader(p_building);
            }
            if ((p_building->U.UObject.PrevThing == 0) && ((p_building->Flag & 0x8000000) != 0)
              && ((LbRandomAnyShort() & 3) == 0) && (((gameturn + p_building->ThingOffset) & 7) == 0)) {
                create_a_pod(0, p_building, 0);
            }
        }
        break;
    case SubTT_BLD_DOME:
        if ((p_building->Flag & 0x0002) == 0)
            process_dome1(p_building);
        break;
    case SubTT_BLD_MGUN:
        if ((p_building->Flag & 0x0002) == 0)
            process_mounted_gun(p_building);
        break;
    case SubTT_BLD_GATE:
        process_gate1(p_building);
        break;
    case SubTT_BLD_36:
        process_bld36(p_building);
        break;
    default:
        if (p_building->State == 9) {
            collapse_building(p_building->X >> 8, p_building->Y >> 8, p_building->Z >> 8, p_building);
        }
        break;
    }
}

/******************************************************************************/
