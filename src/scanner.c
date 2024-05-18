/******************************************************************************/
// Syndicate Wars Port, source port of the classic strategy game from Bullfrog.
/******************************************************************************/
/** @file scanner.c
 *     Ingame scanner (minimap/radar) support.
 * @par Purpose:
 *     Implement functions for handling the scanner map and its state.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     19 Apr 2022 - 27 May 2022
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "scanner.h"

#include "bfutility.h"
#include "bigmap.h"
#include "campaign.h"
#include "thing.h"
#include "player.h"
#include "game.h"
#include "game_speed.h"
#include "lvobjctv.h"
#include "display.h"
#include "swlog.h"
/******************************************************************************/

extern ushort signal_count;
extern ulong turn_last; // = 999;
extern ulong SCANNER_keep_arcs;
extern ulong dword_1DB1A0;

void SCANNER_init(void)
{
    asm volatile ("call ASM_SCANNER_init\n"
        :  :  : "eax" );
}

void SCANNER_set_colour(ubyte col)
{
    asm volatile ("call ASM_SCANNER_set_colour\n"
        :  : "a" ((long)col));
}

void SCANNER_fill_in(void)
{
    asm volatile ("call ASM_SCANNER_fill_in\n"
        :  :  : "eax" );
}

void SCANNER_init_arcpoint(int x1, int z1, int x2, int z2, int c)
{
    asm volatile (
      "push %4\n"
      "call ASM_SCANNER_init_arcpoint\n"
        : : "a" (x1), "d" (z1), "b" (x2), "c" (z2), "g" (c));
}

void SCANNER_unkn_func_196(void)
{
    asm volatile ("call ASM_SCANNER_unkn_func_196\n"
        :  :  : "eax" );
}

void SCANNER_data_to_screen(void)
{
    SCANNER_unkn_func_196();
}

void SCANNER_set_screen_box(short x, short y, short width, short height, short cutout)
{
    short i;
    short hlimit;

    hlimit = sizeof(ingame.Scanner.Width)/sizeof(ingame.Scanner.Width[0]);
    if (height >= hlimit)
        height = hlimit - 1;

    ingame.Scanner.X1 = x;
    ingame.Scanner.Y1 = y;
    ingame.Scanner.X2 = ingame.Scanner.X1 + width;
    ingame.Scanner.Y2 = ingame.Scanner.Y1 + height;

    if (cutout != 0)
    {
        for (i = 0; i + ingame.Scanner.Y1 <= ingame.Scanner.Y2; i++) {
            ingame.Scanner.Width[i] = min(width - cutout + i, width);
        }
    }
    else
    {
        for (i = 0; i + ingame.Scanner.Y1 <= ingame.Scanner.Y2; i++) {
            ingame.Scanner.Width[i] = width;
        }
    }
}

void SCANNER_update_arcpoint(ushort arc_no, short fromX, short fromZ, short toX, short toZ)
{
    if (arc_no >= SCANNER_ARC_COUNT)
        return;
    ingame.Scanner.Arc[arc_no].X1 = fromX;
    ingame.Scanner.Arc[arc_no].Z1 = fromZ;
    ingame.Scanner.Arc[arc_no].X2 = toX;
    ingame.Scanner.Arc[arc_no].Z2 = toZ;
}

void SCANNER_init_blippoint(ushort blip_no, int x, int z, int colour)
{
    if (blip_no >= SCANNER_BIG_BLIP_COUNT)
        return;
    ingame.Scanner.BigBlip[blip_no].X = x;
    ingame.Scanner.BigBlip[blip_no].Z = z;
    ingame.Scanner.BigBlip[blip_no].Speed = 4;
    ingame.Scanner.BigBlip[blip_no].Colour = colour;
    ingame.Scanner.BigBlip[blip_no].Period = 32;
}

void SCANNER_find_position(int x, int y, int *U, int *V)
{
    asm volatile (
      "call ASM_SCANNER_find_position\n"
        : : "a" (x), "d" (y), "b" (U), "c" (V));
}

TbBool mouse_move_over_scanner(void)
{
    short dx, dy;
    dx = lbDisplay.MMouseX - ingame.Scanner.X1;
    dy = lbDisplay.MMouseY - ingame.Scanner.Y1;

    return (dy >= 0) && (ingame.Scanner.Y1 + dy <= ingame.Scanner.Y2)
        && (dx >= 0) && (dx <= SCANNER_width[dy]);
}

ushort do_group_scanner(struct Objective *p_objectv, ushort next_signal)
{
    ushort n;
    ubyte colr;
    short dcthing;
    short nearthing;
    ushort group;
    int X, Z;

    group = p_objectv->Thing;
    dcthing = players[local_player_no].DirectControl[0];

    n = next_signal;
    // Find thing in group close to dcthing
    if (objective_target_is_ally(p_objectv)) {
        nearthing = find_nearest_from_group(&things[dcthing],group, 0);
        colr = colour_lookup[1];
    } else if (objective_target_is_to_be_acquired(p_objectv)) {
        nearthing = find_nearest_from_group(&things[dcthing], group, 1);
        colr = colour_lookup[3];
    } else {
        nearthing = find_nearest_from_group(&things[dcthing], group, 0);
        colr = colour_lookup[2];
    }
    ingame.Scanner.NearThing1 = nearthing;

    if (ingame.Scanner.NearThing1 != 0)
    {
        if (ingame.Scanner.NearThing1 <= 0) {
            struct SimpleThing *p_sthing;
            p_sthing = &sthings[ingame.Scanner.NearThing1];
            X = p_sthing->X;
            Z = p_sthing->Z;
        } else {
            struct Thing *p_thing;
            p_thing = &things[ingame.Scanner.NearThing1];
            X = p_thing->X;
            Z = p_thing->Z;
        }
        SCANNER_init_blippoint(n, X, Z, colr);
        n++;
        if (ingame.Scanner.GroupCount < SCANNER_GROUP_COUNT)
        {
            int sgroup;

            sgroup = ingame.Scanner.GroupCount;
            ++ingame.Scanner.GroupCount;
            ingame.Scanner.Group[sgroup] = group;
            ingame.Scanner.GroupCol[sgroup] = colr;
        }
    }
    return n;
}

ushort do_group_near_thing_scanner(struct Objective *p_objectv, ushort next_signal)
{
    ushort n;
    ubyte colr;
    short tgthing;
    short nearthing;
    ushort group;
    long X1, Z1;
    int X2, Z2;

    group = p_objectv->Arg2;
    tgthing = p_objectv->Thing;

    n = next_signal;
    // Find thing in group close to tgthing
    if (objective_target_is_ally(p_objectv)) {
        nearthing = find_nearest_from_group(&things[tgthing], group, 0);
        colr = colour_lookup[1];
    } else if (objective_target_is_to_be_acquired(p_objectv)) {
        nearthing = find_nearest_from_group(&things[tgthing], group, 1);
        colr = colour_lookup[3];
    } else {
        nearthing = find_nearest_from_group(&things[tgthing], group, 0);
        colr = colour_lookup[2];
    }
    ingame.Scanner.NearThing1 = nearthing;

    // Blip the target thing
    n = next_signal;
    if (tgthing <= 0) {
        struct SimpleThing *p_sthing;
        p_sthing = &sthings[tgthing];
        X1 = p_sthing->X;
        Z1 = p_sthing->Z;
    } else {
        struct Thing *p_thing;
        p_thing = &things[tgthing];
        X1 = p_thing->X;
        Z1 = p_thing->Z;
    }
    SCANNER_init_blippoint(n, X1, Z1, colr);
    n++;

    // Arc the nearest group member
    if (nearthing != 0)
    {
        if (nearthing <= 0) {
            struct SimpleThing *p_sthing;
            p_sthing = &sthings[nearthing];
            X2 = p_sthing->X;
            Z2 = p_sthing->Z;
        } else {
            struct Thing *p_thing;
            p_thing = &things[nearthing];
            X2 = p_thing->X;
            Z2 = p_thing->Z;
        }
        if (dword_1DB1A0)
        {
            SCANNER_update_arcpoint(0, Z2, X2, Z1, X1);
        }
        else
        {
            struct Thing *p_thing;
            p_thing = &things[ingame.TrackThing];
            if (((ingame.TrackThing == 0) || p_thing->Flag & TngF_PlayerAgent) && (ingame.Flags & GamF_Unkn2000))
                SCANNER_init_arcpoint(Z2, X2, Z1, X1, 1);
        }
        SCANNER_keep_arcs = 1;

        n++;
        if (ingame.Scanner.GroupCount < SCANNER_GROUP_COUNT)
        {
            int sgroup;

            sgroup = ingame.Scanner.GroupCount;
            ++ingame.Scanner.GroupCount;
            ingame.Scanner.Group[sgroup] = group;
            ingame.Scanner.GroupCol[sgroup] = colr;
        }
    }
    return n;
}

ushort do_target_thing_scanner(struct Objective *p_objectv, ushort next_signal)
{
    long X, Z;
    ushort n;
    ubyte colr;
    ThingIdx thing;

    thing = p_objectv->Thing;

    if (objective_target_is_ally(p_objectv))
        colr = colour_lookup[1];
    else if (objective_target_is_to_be_acquired(p_objectv))
        colr = colour_lookup[3];
    else
        colr = colour_lookup[2];

    n = next_signal;
    if (thing <= 0) {
        struct SimpleThing *p_sthing;
        p_sthing = &sthings[thing];
        X = p_sthing->X;
        Z = p_sthing->Z;
    } else {
        struct Thing *p_thing;
        p_thing = &things[thing];
        X = p_thing->X;
        Z = p_thing->Z;
    }
    SCANNER_init_blippoint(n, X, Z, colr);
    n++;
    return n;
}

ushort do_target_item_scanner(struct Objective *p_objectv, ushort next_signal)
{
    long X, Z;
    ushort n;
    ushort weapon;
    ubyte colr;
    ThingIdx thing;

    thing = p_objectv->Thing;
    weapon = p_objectv->Arg2;

    if (objective_target_is_ally(p_objectv))
        colr = colour_lookup[1];
    else if (objective_target_is_to_be_acquired(p_objectv))
        colr = colour_lookup[3];
    else
        colr = colour_lookup[2];

    n = next_signal;
    if (thing <= 0)
    {
        struct SimpleThing *p_sthing;
        p_sthing = &sthings[thing];
        if ((p_sthing->Type == SmTT_DROPPED_ITEM) &&
          (p_sthing->U.UWeapon.WeaponType == weapon)) {
            X = p_sthing->X;
            Z = p_sthing->Z;
        } else if (p_sthing->Type == SmTT_CARRIED_ITEM) {
            struct Thing *p_person;
            p_person = &things[p_sthing->U.UWeapon.Owner];
            X = p_person->X;
            Z = p_person->Z;
        } else {
            struct Thing *p_person;
            ThingIdx person;
            person = find_person_carrying_weapon(weapon);
            p_person = &things[person];
            X = p_person->X;
            Z = p_person->Z;
        }
    }
    else
    {
        return n;
    }
    SCANNER_init_blippoint(n, X, Z, colr);
    n++;
    return n;
}

ushort do_thing_arrive_area_scanner(struct Objective *p_objectv, ushort next_signal)
{
    long X, Z;
    ushort n;
    ubyte colr;
    ThingIdx thing;

    thing = p_objectv->Thing;

    if (objective_target_is_ally(p_objectv))
        colr = colour_lookup[1];
    else if (objective_target_is_to_be_acquired(p_objectv))
        colr = colour_lookup[3];
    else
        colr = colour_lookup[2];

    n = next_signal;
    SCANNER_init_blippoint(n, MAPCOORD_TO_PRCCOORD(p_objectv->X,0), MAPCOORD_TO_PRCCOORD(p_objectv->Z,0), colr);
    n++;
    if (thing <= 0) {
        struct SimpleThing *p_sthing;
        p_sthing = &sthings[thing];
        X = p_sthing->X;
        Z = p_sthing->Z;
    } else {
        struct Thing *p_thing;
        p_thing = &things[thing];
        X = p_thing->X;
        Z = p_thing->Z;
    }
    if (dword_1DB1A0)
    {
        SCANNER_update_arcpoint(0, Z, X,
          MAPCOORD_TO_PRCCOORD(p_objectv->Z,0),
          MAPCOORD_TO_PRCCOORD(p_objectv->X,0));
    }
    else
    {
        struct Thing *p_thing;
        p_thing = &things[ingame.TrackThing];
        if (((ingame.TrackThing == 0) || p_thing->Flag & TngF_PlayerAgent) && (ingame.Flags & GamF_Unkn2000))
            SCANNER_init_arcpoint(Z, X,
              MAPCOORD_TO_PRCCOORD(p_objectv->Z,0),
              MAPCOORD_TO_PRCCOORD(p_objectv->X,0), 1);
    }
    SCANNER_keep_arcs = 1;
    return n;
}

ushort do_thing_near_thing_scanner(struct Objective *p_objectv, ushort next_signal)
{
    long X1, Z1;
    long X2, Z2;
    ushort n;
    ubyte colr;
    ThingIdx thing1, thing2;

    thing1 = p_objectv->Thing;
    thing2 = p_objectv->Y;

    if (objective_target_is_ally(p_objectv))
        colr = colour_lookup[1];
    else if (objective_target_is_to_be_acquired(p_objectv))
        colr = colour_lookup[3];
    else
        colr = colour_lookup[2];

    n = next_signal;
    if (thing1 <= 0) {
        struct SimpleThing *p_sthing;
        p_sthing = &sthings[thing1];
        X1 = p_sthing->X;
        Z1 = p_sthing->Z;
    } else {
        struct Thing *p_thing;
        p_thing = &things[thing1];
        X1 = p_thing->X;
        Z1 = p_thing->Z;
    }
    SCANNER_init_blippoint(n, X1, Z1, colr);
    n++;
    if (thing2 <= 0) {
        struct SimpleThing *p_sthing;
        p_sthing = &sthings[thing2];
        X2 = p_sthing->X;
        Z2 = p_sthing->Z;
    } else {
        struct Thing *p_thing;
        p_thing = &things[thing2];
        X2 = p_thing->X;
        Z2 = p_thing->Z;
    }
    if (dword_1DB1A0)
    {
        SCANNER_update_arcpoint(0, Z2, X2, Z1, X1);
    }
    else
    {
        struct Thing *p_thing;
        p_thing = &things[ingame.TrackThing];
        if (((ingame.TrackThing == 0) || p_thing->Flag & TngF_PlayerAgent) && (ingame.Flags & GamF_Unkn2000))
            SCANNER_init_arcpoint(Z2, X2, Z1, X1, 1);
    }
    SCANNER_keep_arcs = 1;
    return n;
}

ushort do_group_arrive_area_scanner(struct Objective *p_objectv, ushort next_signal)
{
    ushort n;
    ubyte colr;

    if (objective_target_is_ally(p_objectv))
        colr = colour_lookup[1];
    else if (objective_target_is_to_be_acquired(p_objectv))
        colr = colour_lookup[3];
    else
        colr = colour_lookup[2];

    n = next_signal;
    SCANNER_init_blippoint(n, MAPCOORD_TO_PRCCOORD(p_objectv->X,0),
      MAPCOORD_TO_PRCCOORD(p_objectv->Z,0), colr);
    n++;
    return n;
}

void clear_all_scanner_signals(void)
{
    int i;

    signal_count = 0;
    for (i = 0; i < SCANNER_BIG_BLIP_COUNT; i++)
        ingame.Scanner.BigBlip[i].Period = 0;
    for (i = 0; i < SCANNER_ARC_COUNT; i++)
        ingame.Scanner.Arc[i].Period = 0;
}

void add_blippoint_to_scanner(int x, int z, ubyte colour)
{
    SCANNER_init_blippoint(signal_count, x, z, colour);
    ingame.Scanner.BigBlip[signal_count].Counter = 32;
    signal_count++;
}

void add_signal_to_scanner(struct Objective *p_objectv, ubyte flag)
{
    if (flag)
        clear_all_scanner_signals();
    if (gameturn != turn_last)
    {
        turn_last = gameturn;
        ingame.Scanner.GroupCount = 0;
    }
    if ((p_objectv == NULL) || ((p_objectv->Flags & GObjF_HIDDEN) != 0))
        return;

    if (signal_count >= SCANNER_BIG_BLIP_COUNT) {
        LOGWARN("Scaner blips limit reached, blip discarded.");
        return;
    }

    if (objective_target_is_group_to_area(p_objectv))
    {
        signal_count = do_group_arrive_area_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_group_to_vehicle(p_objectv))
    {
        signal_count = do_group_near_thing_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_group_to_thing(p_objectv))
    {
        signal_count = do_group_near_thing_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_group(p_objectv))
    {
        signal_count = do_group_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_person_to_area(p_objectv))
    {
        signal_count = do_thing_arrive_area_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_person_to_thing(p_objectv))
    {
        signal_count = do_thing_near_thing_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_person(p_objectv))
    {
        signal_count = do_target_thing_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_vehicle_to_area(p_objectv))
    {
        signal_count = do_thing_arrive_area_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_vehicle(p_objectv))
    {
        signal_count = do_target_thing_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_item_to_area(p_objectv))
    {
        signal_count = do_thing_arrive_area_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_item(p_objectv))
    {
        signal_count = do_target_item_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_object(p_objectv))
    {
        signal_count = do_target_thing_scanner(p_objectv, signal_count);
    }
    else if (objective_target_is_any_thing(p_objectv))
    {
        signal_count = do_target_thing_scanner(p_objectv, signal_count);
    }
}

/******************************************************************************/
