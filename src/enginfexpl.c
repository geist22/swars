/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file enginfexpl.c
 *     Make 3D objects explode into a cloud of faces.
 * @par Purpose:
 *     Implement functions for handling object explosions and debrit movement.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     13 Oct 2024 - 06 Nov 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "enginfexpl.h"

#include <limits.h>
#include <stdlib.h>
#include "bfmemut.h"
#include "bfutility.h"

#include "bigmap.h"
#include "bmbang.h"
#include "enginbckt.h"
#include "engincam.h"
#include "engindrwlstm.h"
#include "engindrwlstx.h"
#include "enginprops.h"
#include "enginshrapn.h"
#include "engintrns.h"
#include "frame_sprani.h"
#include "sound.h"
#include "swlog.h"
#include "thing.h"
/******************************************************************************/
#pragma pack(1)

struct rectangle { // sizeof=4
    ubyte x1;
    ubyte y1;
    ubyte x2;
    ubyte y2;
};

#pragma pack()

u32 next_ex_face = 1;

extern ushort word_1AA5CC;
extern struct rectangle redo_scanner[128];

extern s32 minimum_explode_depth;
extern u32 minimum_explode_and;
extern s32 minimum_explode_size;

extern s32 dword_1AA5C4;
extern s32 dword_1AA5C8;
extern s32 dword_1AA5D8;
extern s32 dword_1AA5DC;
extern s32 dword_1AA5E0;
extern s32 dword_1AA5E4;

extern ushort word_1E08B8;
extern s32 dword_1E08BC;

/******************************************************************************/

void init_free_explode_faces(void)
{
#if 0
    asm volatile ("call ASM_init_free_explode_faces\n"
        :  :  : "eax" );
#else
    int i;

    LbMemorySet(ex_faces, 0, sizeof(ex_faces));
    word_1AA5CC = 1;
    for (i = 1; i < EXPLODE_FACES_COUNT - 1; i++)
    {
        ex_faces[i].Timer = 0;
        ex_faces[i].Flags = i + 1;
    }
    ex_faces[i].Timer = 0;
    ex_faces[i].Flags = 0;

    dont_bother_with_explode_faces = 1;
#endif
}

void FIRE_add_flame(ThingIdx firetng, ushort fflame)
{
    struct SimpleThing *p_fire;
    struct FireFlame *p_fflame;

    if (fflame == 0) {
        return;
    }
    p_fire = &sthings[firetng];
    p_fflame = &FIRE_flame[fflame];

    p_fflame->next = p_fire->U.UFire.flame;
    p_fire->U.UFire.flame = fflame;
}

void FIRE_new(int x, int y, int z, ubyte type)
{
#if 0
    asm volatile ("call ASM_FIRE_new\n"
        : : "a" (x), "d" (y), "b" (z), "c" (type));
#endif
    struct SimpleThing *p_fire;
    struct FireFlame *p_fflame;
    ThingIdx firetng;
    short flame_x, flame_z;
    ushort fflame;
    short flame_fvel;
    ushort flame_life;
    ushort i28;
    ushort i31;
    ushort v23;
    ushort i29;
    ushort v29;
    ushort i30;
    ushort n;
    ushort ii;
    ubyte v46;
    ushort v49;
    ushort jj;
    ushort kk;
    int cor_x, cor_z;
    int cor_y;
    short v61;
    ushort mm;
    ushort nn;
    ushort i1;
    ushort i2;
    char v81;
    ushort v87;
    ushort i3;
    ushort i4;
    ushort i5;
    char v106;
    ushort i6;
    ushort i7;
    ushort i8;
    ushort i9;
    ushort i10;
    ushort i11;
    ushort v160;
    ushort i24;
    ushort v172;
    ushort i25;
    unsigned int v176;
    int v177;
    struct MyMapElement *v178;
    unsigned int v179;
    unsigned int v180;
    struct MyMapElement *v181;
    ubyte v182;
    unsigned int v183;
    struct MyMapElement *v184;
    ubyte v185;
    int v186;
    unsigned int v187;
    struct MyMapElement *v188;
    ubyte v189;
    int v190;
    struct MyMapElement *v191;
    ubyte v192;
    unsigned int v193;
    int v194;
    struct MyMapElement *v195;
    ubyte v196;
    unsigned int v197;
    struct MyMapElement *v198;
    ubyte v199;
    unsigned int v200;
    int v201;
    struct MyMapElement *v202;
    ubyte v203;
    unsigned int v204;
    unsigned int v205;
    struct MyMapElement *v206;
    ubyte v207;
    ushort i12;
    ushort i13;
    ushort i14;
    ushort *v234;
    ushort i15;
    ushort i16;
    ushort *v246;
    ushort i17;
    ushort i18;
    ushort i19;
    ushort i20;
    ushort i21;
    ushort i22;
    short v290;
    ushort next;
    ushort *v293;
    ushort i23;
    struct MyMapElement *v329;
    ubyte v369;
    ubyte v377;
    ubyte v383;
    ubyte v391;
    ubyte v396;
    ubyte v398;
    ubyte v401;
    ubyte v410;
    ubyte v411;
    ubyte v412;
    ubyte v413;
    ubyte v414;
    ubyte v417;
    ubyte v418;
    ubyte v423;
    ubyte v427;
    ubyte v429;
    ubyte v430;
    ubyte v432;
    ubyte v434;
    ubyte v435;
    ubyte v443;
    ubyte v446;
    ubyte v448;
    ubyte v449;
    ubyte v451;
    ubyte v454;
    ubyte v456;
    ubyte v463;

    cor_y = y;
    if ( x <= 0x800000 && z <= 0x800000 )
    {
      if ( word_1E08B8 )
      {
        firetng = get_new_sthing();
        if ( firetng )
        {
          p_fire = &sthings[firetng];
          p_fire->Type = 52;
          p_fire->U.UFire.flame = 0;
          p_fire->Z = z;
          p_fire->Y = y;
          p_fire->X = x;
          play_dist_ssample(p_fire, 0x10u, 0x7Fu, 0x40u, 100, -1, 1);
          cor_z = z >> 8;
          cor_x = x >> 8;
          switch ( type )
          {
            case 1u:
              v410 = 18 + (LbRandomAnyShort() & 0xF);
              flame_life = 43 + (LbRandomAnyShort() & 0xF);
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = 50 + (LbRandomAnyShort() & 0x3F);
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i28 = nstart_ani[923]; ; i28 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i28;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v410;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v411 = (LbRandomAnyShort() & 0xF) + 18;
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i31 = nstart_ani[923]; ; i31 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i31;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v411;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v412 = (LbRandomAnyShort() & 0xF) + 18;
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              v23 = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                v23 = 0;
              }
              fflame = v23;
              if ( v23 )
              {
                p_fflame = &FIRE_flame[v23];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i29 = nstart_ani[923]; ; i29 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i29;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v412;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v413 = (LbRandomAnyShort() & 0xF) + 18;
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              v29 = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                v29 = 0;
              }
              fflame = v29;
              if ( v29 )
              {
                p_fflame = &FIRE_flame[v29];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i30 = nstart_ani[923]; ; i30 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i30;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v413;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v463 = (LbRandomAnyShort() & 0xF) + 18;
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              fflame = fflame;
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( n = nstart_ani[923]; ; n = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = n;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v463;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v414 = (LbRandomAnyShort() & 0xF) + 18;
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              fflame = fflame;
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( ii = nstart_ani[923]; ; ii = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = ii;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v414;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v46 = (LbRandomAnyShort() & 0xF) + 18;
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              v49 = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                v49 = 0;
              }
              fflame = v49;
              if ( v49 )
              {
                p_fflame = &FIRE_flame[v49];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( jj = nstart_ani[923]; ; jj = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = jj;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->count = v46;
                p_fflame->fvel = flame_fvel;
                p_fflame->life = flame_life;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v369 = (LbRandomAnyShort() & 0xF) + 18;
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              fflame = fflame;
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 4;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( kk = nstart_ani[923]; ; kk = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = kk;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v369;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v443 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              v61 = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              fflame = fflame;
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = v61;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( mm = nstart_ani[924]; ; mm = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = mm;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v443;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v417 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              fflame = fflame;
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( nn = nstart_ani[924]; ; nn = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = nn;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v417;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v418 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              fflame = fflame;
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i1 = nstart_ani[924]; ; i1 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i1;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v418;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v446 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              fflame = fflame;
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i2 = nstart_ani[924]; ; i2 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i2;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v446;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v81 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              v87 = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                v87 = 0;
              }
              fflame = v87;
              if ( v87 )
              {
                p_fflame = &FIRE_flame[v87];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i3 = nstart_ani[924]; ; i3 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i3;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v81;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v377 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i4 = nstart_ani[924]; ; i4 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i4;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v377;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v383 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i5 = nstart_ani[924]; ; i5 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i5;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v383;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v106 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i6 = nstart_ani[924]; ; i6 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i6;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v106;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v391 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i7 = nstart_ani[924]; ; i7 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i7;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v391;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v396 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i8 = nstart_ani[924]; ; i8 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i8;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v396;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v423 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i9 = nstart_ani[924]; ; i9 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i9;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v423;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v398 = (LbRandomAnyShort() & 0xF) + 24;
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 5;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i10 = nstart_ani[924]; ; i10 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i10;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v398;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
                FIRE_add_flame(firetng, fflame);
              }
              break;
            case 2u:
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 10;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i11 = nstart_ani[923]; ; i11 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i11;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = 2;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);
              break;
            case 3u:
              v176 = z >> 16;
              v177 = cor_x >> 8;
              v178 = &game_my_big_map[128 * (z >> 16) + (cor_x >> 8)];
              v329 = game_my_big_map;
              v178->Flags2 &= ~0x80u;
              v179 = (cor_z >> 8) - 1;
              v180 = (cor_x >> 8) - 1;
              if ( v180 <= 0x7F && v179 <= 0x7F )
              {
                v181 = &v329[128 * v179 + v180];
                v182 = v181->Flags2 & 0xF;
                v181->Flags2 = v182;
                v181->Flags2 = v182 | 0x70;
              }
              v183 = v176 - 1;
              if ( v177 <= 0x7F && v183 <= 0x7F )
              {
                v184 = &game_my_big_map[128 * v183 + v177];
                v185 = v184->Flags2 & 0xF;
                v184->Flags2 = v185;
                v184->Flags2 = v185 | 0x50;
              }
              v186 = v177 + 1;
              v187 = v176 - 1;
              if ( (v177 + 1) >= 0 && v186 <= 127 && v187 <= 0x7F )
              {
                v188 = &game_my_big_map[128 * v187 + v186];
                v189 = v188->Flags2 & 0xF;
                v188->Flags2 = v189;
                v188->Flags2 = v189 | 0x30;
              }
              v190 = v177 + 1;
              if ( (v177 + 1) >= 0 && v190 <= 127 && v176 <= 0x7F )
              {
                v191 = &game_my_big_map[128 * v176 + v190];
                v192 = v191->Flags2 & 0xF;
                v191->Flags2 = v192;
                v191->Flags2 = v192 | 0x10;
              }
              v193 = v176 + 1;
              v194 = v177 + 1;
              if ( (v177 + 1) >= 0 && v194 <= 127 && v193 <= 0x7F )
              {
                v195 = &game_my_big_map[128 * v193 + v194];
                v196 = v195->Flags2 & 0xF;
                v195->Flags2 = v196;
                v195->Flags2 = v196 | 0xF0;
              }
              v197 = v176 + 1;
              if ( v177 <= 0x7F && v197 <= 0x7F )
              {
                v198 = &game_my_big_map[128 * v197 + v177];
                v199 = v198->Flags2 & 0xF;
                v198->Flags2 = v199;
                v198->Flags2 = v199 | 0xD0;
              }
              v200 = v176 + 1;
              v201 = v177 - 1;
              if ( (v177 - 1) >= 0 && v201 <= 127 && v200 <= 0x7F )
              {
                v202 = &game_my_big_map[128 * v200 + v201];
                v203 = v202->Flags2 & 0xF;
                v202->Flags2 = v203;
                v202->Flags2 = v203 | 0xB0;
              }
              v204 = v177 - 1;
              if ( v204 <= 0x7F && v176 <= 0x7F )
              {
                v205 = (v176 << 7) + v204;
                v206 = game_my_big_map;
                v207 = game_my_big_map[v205].Flags2 & 0xF;
                game_my_big_map[v205].Flags2 = v207;
                v206[v205].Flags2 = v207 | 0x90;
              }

              v448 = 43 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 6;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i12 = nstart_ani[923]; ; i12 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i12;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v448;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v449 = 43 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 6;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i13 = nstart_ani[923]; ; i13 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i13;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v449;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v427 = 43 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 6;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i14 = nstart_ani[923]; ; i14 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i14;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v427;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v451 = 43 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 7;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                v234 = nstart_ani;
                p_fflame->ddbig = -1;
                for ( i15 = v234[923]; ; i15 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i15;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v451;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v429 = 43 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 7;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i16 = nstart_ani[923]; ; i16 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i16;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v429;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v430 = 43 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 43;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 7;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                v246 = nstart_ani;
                p_fflame->ddbig = -1;
                for ( i17 = v246[923]; ; i17 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i17;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v430;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v454 = 53 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 8;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i18 = nstart_ani[924]; ; i18 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i18;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v454;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v432 = 53 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 8;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i19 = nstart_ani[924]; ; i19 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i19;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v432;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v456 = 53 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0xFF) - 127;
              flame_x = cor_x + (LbRandomAnyShort() & 0xFF) - 127;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 8;
                p_fflame->big = 100;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i20 = nstart_ani[924]; ; i20 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i20;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v456;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v434 = 53 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 9;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i21 = nstart_ani[924]; ; i21 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i21;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v434;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v435 = 53 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              fflame = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 9;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i22 = nstart_ani[924]; ; i22 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i22;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v435;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);

              v401 = 53 - (LbRandomAnyShort() & 3);
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = (LbRandomAnyShort() & 0x1FF) + cor_z - 255;
              flame_x = cor_x + (LbRandomAnyShort() & 0x1FF) - 255;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              if ( word_1E08B8 )
              {
                v290 = word_1E08B8;
                next = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
                word_1E08B8 = next;
                fflame = v290;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 9;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                v293 = nstart_ani;
                p_fflame->ddbig = -1;
                for ( i23 = v293[924]; ; i23 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i23;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = v401;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);
              break;
            case 4u:
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = cor_z + (LbRandomAnyShort() & 0x3F) - 31;
              flame_x = cor_x + (LbRandomAnyShort() & 0x3F) - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              v160 = word_1E08B8;
              if ( word_1E08B8 )
              {
                word_1E08B8 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
              }
              else
              {
                v160 = 0;
              }
              fflame = v160;
              if ( v160 )
              {
                p_fflame = &FIRE_flame[v160];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 21;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i24 = nstart_ani[923]; ; i24 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i24;
                  if ( (LbRandomAnyShort() & 3) == 0 )
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = 6;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);
              goto LABEL_184;
            case 5u:
LABEL_184:
              flame_life = (LbRandomAnyShort() & 0xF) + 53;
              flame_z = (LbRandomAnyShort() & 0x3F) + cor_z - 31;
              flame_x = (LbRandomAnyShort() & 0x3F) + cor_x - 31;
              flame_fvel = (LbRandomAnyShort() & 0x3F) + 50;
              if ( word_1E08B8 )
              {
                fflame = word_1E08B8;
                v172 = FIRE_flame[word_1E08B8].next;
                ++dword_1E08BC;
                word_1E08B8 = v172;
              }
              else
              {
                fflame = 0;
              }
              if ( fflame )
              {
                p_fflame = &FIRE_flame[fflame];
                p_fflame->x = flame_x;
                p_fflame->z = flame_z;
                p_fflame->y = cor_y;
                p_fflame->type = 21;
                p_fflame->big = 30;
                p_fflame->dbig = 0;
                p_fflame->ddbig = -1;
                for ( i25 = nstart_ani[923]; ; i25 = frame[p_fflame->frame].Next )
                {
                  p_fflame->frame = i25;
                  if ((LbRandomAnyShort() & 3) == 0)
                    break;
                }
                p_fflame->life = flame_life;
                p_fflame->count = 12;
                p_fflame->fvel = flame_fvel;
                p_fflame->fcount = LbRandomAnyShort() & 0x7F;
              }
              FIRE_add_flame(firetng, fflame);
              break;
            default:
              break;
          }
          add_node_sthing(firetng);
        }
      }
    }
}

void SCANNER_fill_in_a_little_bit(int x1, int y1, int x2, int y2)
{
    asm volatile ("call ASM_SCANNER_fill_in_a_little_bit\n"
        : : "a" (x1), "d" (y1), "b" (x2), "c" (y2));
}

static void explode_face_delete(int exface)
{
    ex_faces[exface].Flags = word_1AA5CC;
    ex_faces[exface].Timer = 0;
    word_1AA5CC = exface;
}

static void set_explode_face_rotate_angle(ushort angX, ushort angY)
{
    dword_1AA5D8 = lbSinTable[(angX) & LbFPMath_AngleMask];
    dword_1AA5DC = lbSinTable[(angX + LbFPMath_PI/2) & LbFPMath_AngleMask];
    dword_1AA5E0 = lbSinTable[(angY) & LbFPMath_AngleMask];
    dword_1AA5E4 = lbSinTable[(angY + LbFPMath_PI/2) & LbFPMath_AngleMask];
}

static void explode_face_point_rotate(short *p_cor_x, short *p_cor_y, short *p_cor_z)
{
    int dist;
    int cor_x, cor_y, cor_z;

    cor_x = *p_cor_x;
    cor_y = *p_cor_y;
    cor_z = *p_cor_z;
    dist = (dword_1AA5D8 * cor_x + dword_1AA5DC * cor_z) >> 16;
    *p_cor_x = (dword_1AA5DC * cor_x - dword_1AA5D8 * cor_z) >> 16;
    *p_cor_y = (dword_1AA5E4 * cor_y - dist * dword_1AA5E0) >> 16;
    *p_cor_z = (dword_1AA5E4 * dist + dword_1AA5E0 * cor_y) >> 16;
}

static void animate_explode_face1_tri(int exface)
{
    struct ExplodeFace3 *p_exface;

    p_exface = &ex_faces[exface];

    set_explode_face_rotate_angle(4 * ((2 * exface) & 0xF) + 40, 4 * (exface & 7) + 20);
    p_exface->Timer--;
    if (p_exface->Timer == 0)
    {
        explode_face_delete(exface);
        bang_new4(p_exface->X << 8, p_exface->Y, p_exface->Z << 8, 35);
        return;
    }
    p_exface->X += p_exface->DX;
    p_exface->Y += p_exface->DY;
    p_exface->Z += p_exface->DZ;

    if ((p_exface->X < 0) || (p_exface->Z < 0))
    {
        p_exface->Timer = 0;
        explode_face_delete(exface);
        return;
    }
    // bounce from ground
    if (p_exface->DY < 0
      && ((p_exface->Y + p_exface->Y0 < 0)
       || (p_exface->Y + p_exface->Y1 < 0)
       || (p_exface->Y + p_exface->Y2 < 0)))
    {
        p_exface->Y -= p_exface->DY;
        p_exface->DY = -((200 * p_exface->DY) >> 8);
        if (p_exface->Timer < 0)
            p_exface->Timer = 10;
    }
    p_exface->DY -= 10;

    explode_face_point_rotate(&p_exface->X0, &p_exface->Y0, &p_exface->Z0);
    explode_face_point_rotate(&p_exface->X1, &p_exface->Y1, &p_exface->Z1);
    explode_face_point_rotate(&p_exface->X2, &p_exface->Y2, &p_exface->Z2);
}

static void animate_explode_face1_quad(int exface)
{
    struct ExplodeFace3 *p_exface;

    p_exface = &ex_faces[exface];

    set_explode_face_rotate_angle(4 * ((2 * exface) & 0xF) + 40, 4 * (exface & 7) + 20);
    p_exface->Timer--;
    if (p_exface->Timer == 0)
    {
        explode_face_delete(exface);
        bang_new4(p_exface->X << 8, p_exface->Y, p_exface->Z << 8, 35);
        return;
    }
    p_exface->X += p_exface->DX;
    p_exface->Y += p_exface->DY;
    p_exface->Z += p_exface->DZ;

    if ((p_exface->X < 0) || (p_exface->Z < 0))
    {
        p_exface->Timer = 0;
        explode_face_delete(exface);
        return;
    }
    // bounce from ground
    if (p_exface->DY < 0
      && ((p_exface->Y + p_exface->Y0 < 0)
       || (p_exface->Y + p_exface->Y1 < 0)
       || (p_exface->Y + p_exface->Y2 < 0)
       || (p_exface->Y + p_exface->Y3 < 0)))
    {
        p_exface->Y -= p_exface->DY;
        p_exface->DY = -((200 * p_exface->DY) >> 8);
        if (p_exface->Timer < 0)
            p_exface->Timer = 10;
    }
    p_exface->DY -= 10;

    explode_face_point_rotate(&p_exface->X0, &p_exface->Y0, &p_exface->Z0);
    explode_face_point_rotate(&p_exface->X1, &p_exface->Y1, &p_exface->Z1);
    explode_face_point_rotate(&p_exface->X2, &p_exface->Y2, &p_exface->Z2);
    explode_face_point_rotate(&p_exface->X3, &p_exface->Y3, &p_exface->Z3);
}

static void animate_explode_face3_tri(int exface)
{
    struct ExplodeFace3 *p_exface;
    struct ExplodeFace3 *p_neface;
    int rndv;
    int cor_x, cor_y, cor_z;
    int dist_x, dist_y, dist_z;
    int avg_x0, avg_y0, avg_z0;
    int avg_x1, avg_y1, avg_z1;
    int avg_x2, avg_y2, avg_z2;
    int eface;

    p_exface = &ex_faces[exface];

    cor_y = alt_at_point(p_exface->X0, p_exface->Z0) >> 5;
    if (p_exface->Y0 >= cor_y && p_exface->Y1 >= cor_y && p_exface->Y2 >= cor_y)
    {
        rndv = LbRandomAnyShort() & 0x3FF;
        if (p_exface->Y0 > rndv)
        {
            p_exface->X0 -= p_exface->DX;
            p_exface->Z0 -= p_exface->DZ;
        }
        rndv = LbRandomAnyShort() & 7;
        p_exface->Y0 += p_exface->DY - rndv;

        rndv = LbRandomAnyShort() & 0x3FF;
        if (p_exface->Y1 > rndv)
        {
            p_exface->X1 -= p_exface->DX;
            p_exface->Z1 -= p_exface->DZ;
        }
        rndv = LbRandomAnyShort() & 7;
        p_exface->Y1 += p_exface->DY - rndv;

        rndv = LbRandomAnyShort() & 0x3FF;
        if (p_exface->Y2 > rndv)
        {
            p_exface->X2 -= p_exface->DX;
            p_exface->Z2 -= p_exface->DZ;
        }
        rndv = LbRandomAnyShort() & 0x7;
        p_exface->Y2 += p_exface->DY - rndv;

        if (p_exface->DY > -120)
            p_exface->DY -= 3;
        return;
    }

    dist_x = abs(p_exface->X2 - p_exface->X0) + abs(p_exface->X1 - p_exface->X0);
    dist_y = abs(p_exface->Y2 - p_exface->Y0) + abs(p_exface->Y1 - p_exface->Y0);
    dist_z = abs(p_exface->Z2 - p_exface->Z0) + abs(p_exface->Z1 - p_exface->Z0);
    if ((dist_y + dist_x + dist_z) < 400)
    {
        p_exface->Timer = 0;
        explode_face_delete(exface);

        rndv = LbRandomAnyShort() & 0x3F;
        cor_z = (p_exface->Z0 + rndv - 31) << 8;
        rndv = LbRandomAnyShort() & 0x3F;
        cor_x = (p_exface->X0 + rndv - 31) << 8;
        bang_new4(cor_x, 32 * cor_y, cor_z, 65);
        return;
    }

    avg_y0 = (p_exface->Y1 + p_exface->Y0) >> 1;
    avg_z0 = (p_exface->Z1 + p_exface->Z0) >> 1;
    avg_x1 = (p_exface->X2 + p_exface->X1) >> 1;
    avg_y1 = (p_exface->Y2 + p_exface->Y1) >> 1;
    avg_z1 = (p_exface->Z2 + p_exface->Z1) >> 1;
    avg_x2 = (p_exface->X2 + p_exface->X0) >> 1;
    avg_z2 = (p_exface->Z0 + p_exface->Z2) >> 1;
    avg_x0 = (p_exface->X1 + p_exface->X0) >> 1;
    avg_y2 = (p_exface->Y0 + p_exface->Y2) >> 1;

    eface = word_1AA5CC;
    if (eface != 0)
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 3;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->X0 = p_exface->X0;
        p_neface->Y0 = p_exface->Y0;
        p_neface->Z0 = p_exface->Z0;
        p_neface->X1 = avg_x0;
        p_neface->Y2 = avg_y2;
        p_neface->Y1 = avg_y0;
        p_neface->Z1 = avg_z0;
        p_neface->X2 = avg_x2;
        p_neface->Z2 = avg_z2;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }

    eface = word_1AA5CC;
    if (eface != 0)
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 3;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->X0 = avg_x0;
        p_neface->Y0 = avg_y0;
        p_neface->Z0 = avg_z0;
        p_neface->X1 = p_exface->X1;
        p_neface->Y1 = p_exface->Y1;
        p_neface->Z1 = p_exface->Z1;
        p_neface->X2 = avg_x1;
        p_neface->Y2 = avg_y1;
        p_neface->Z2 = avg_z1;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }

    eface = word_1AA5CC;
    if (eface != 0)
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 3;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->X0 = avg_x1;
        p_neface->Y0 = avg_y1;
        p_neface->Z0 = avg_z1;
        p_neface->X1 = p_exface->X2;
        p_neface->Y1 = p_exface->Y2;
        p_neface->Z1 = p_exface->Z2;
        p_neface->Y2 = avg_y2;
        p_neface->X2 = avg_x2;
        p_neface->Z2 = avg_z2;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }

    eface = word_1AA5CC;
    if (eface != 0)
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 3;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->X0 = avg_x0;
        p_neface->Y2 = avg_y2;
        p_neface->Y0 = avg_y0;
        p_neface->Z2 = avg_z2;
        p_neface->Z0 = avg_z0;
        p_neface->X1 = avg_x1;
        p_neface->Y1 = avg_y1;
        p_neface->Z1 = avg_z1;
        p_neface->X2 = avg_x2;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }
    p_exface->Timer = 0;
    explode_face_delete(exface);
}

static void animate_explode_face3_quad(int exface)
{
    struct ExplodeFace3 *p_exface;
    struct ExplodeFace3 *p_neface;
    int rndv;
    int cor_x, cor_y, cor_z;
    int dist_x, dist_y, dist_z;
    int avg_x0, avg_y0, avg_z0;
    int avg_x1, avg_y1, avg_z1;
    int avg_x2, avg_y2, avg_z2;
    int avg_x3, avg_y3, avg_z3;
    int avg_x4, avg_y4, avg_z4;
    int eface;

    p_exface = &ex_faces[exface];

    cor_y = alt_at_point(p_exface->X0, p_exface->Z0) >> 5;
    if (p_exface->Y0 >= cor_y
        && p_exface->Y1 >= cor_y
        && p_exface->Y2 >= cor_y
        && p_exface->Y3 >= cor_y)
    {
        rndv = LbRandomAnyShort() & 0x3FF;
        if (p_exface->Y0 > rndv)
        {
            p_exface->X0 -= p_exface->DX;
            p_exface->Z0 -= p_exface->DZ;
        }
        rndv = LbRandomAnyShort() & 7;
        p_exface->Y0 += p_exface->DY - rndv;

        rndv = LbRandomAnyShort() & 0x3FF;
        if (p_exface->Y1 > rndv)
        {
            p_exface->X1 -= p_exface->DX;
            p_exface->Z1 -= p_exface->DZ;
        }
        rndv = LbRandomAnyShort() & 7;
        p_exface->Y1 += p_exface->DY - rndv;

        rndv = LbRandomAnyShort() & 0x3FF;
        if (p_exface->Y2 > rndv)
        {
            p_exface->X2 -= p_exface->DX;
            p_exface->Z2 -= p_exface->DZ;
        }
        rndv = LbRandomAnyShort() & 0x7;
        p_exface->Y2 += p_exface->DY - rndv;

        rndv = LbRandomAnyShort() & 0x3FF;
        if (p_exface->Y3 > rndv)
        {
            p_exface->X3 -= p_exface->DX;
            p_exface->Z3 -= p_exface->DZ;
        }
        rndv = LbRandomAnyShort() & 7;
        p_exface->Y3 += p_exface->DY - rndv;
        if (p_exface->DY > -120)
            p_exface->DY -= 3;
        return;
    }
    dist_x = abs(p_exface->X2 - p_exface->X0) + abs(p_exface->X1 - p_exface->X0);
    dist_y = abs(p_exface->Y2 - p_exface->Y0) + abs(p_exface->Y1 - p_exface->Y0);
    dist_z = abs(p_exface->Z2 - p_exface->Z0) + abs(p_exface->Z1 - p_exface->Z0);
    if ((dist_y + dist_x + dist_z) < minimum_explode_size)
    {
        int base_x, base_z;
        int tile_x, tile_z;

        p_exface->Timer = 0;
        explode_face_delete(exface);

        rndv = LbRandomAnyShort() & 0x1FF;
        base_x = rndv + p_exface->X0 - 255;
        rndv = LbRandomAnyShort() & 0x1FF;
        base_z = p_exface->Z0 + rndv - 255;
        bang_new4(base_x << 8, 32 * cor_y, base_z << 8, 65);

        cor_x = base_x - 16 * p_exface->DX;
        cor_z = base_z - 16 * p_exface->DZ;
        tile_x = cor_x >> 8;
        tile_z = cor_z >> 8;
        if (tile_x >= 0 && tile_x < 128)
        {
          if (tile_z >= 0 && tile_z < 128)
          {
              if ((minimum_explode_and & LbRandomAnyShort()) == 0)
              {
                  quick_crater(tile_x, tile_z, minimum_explode_depth);
                  bang_new4(cor_x << 8, 32 * cor_y, cor_z << 8, 20);
                  if ((LbRandomAnyShort() & 7) == 0)
                  {
                      FIRE_new(cor_x << 8, cor_y, cor_z << 8, 3u);
                  }
              }
          }
        }
        return;
    }
    avg_y0 = (p_exface->Y1 + p_exface->Y0) >> 1;
    avg_z0 = (p_exface->Z1 + p_exface->Z0) >> 1;
    avg_x1 = (p_exface->X3 + p_exface->X1) >> 1;
    avg_y1 = (p_exface->Y3 + p_exface->Y1) >> 1;
    avg_z1 = (p_exface->Z3 + p_exface->Z1) >> 1;
    avg_x2 = (p_exface->X2 + p_exface->X3) >> 1;
    avg_y2 = (p_exface->Y2 + p_exface->Y3) >> 1;
    avg_z2 = (p_exface->Z2 + p_exface->Z3) >> 1;
    avg_x3 = (p_exface->X0 + p_exface->X2) >> 1;
    avg_x0 = (p_exface->X0 + p_exface->X1) >> 1;
    avg_z3 = (p_exface->Z0 + p_exface->Z2) >> 1;
    avg_y3 = (p_exface->Y2 + p_exface->Y0) >> 1;
    avg_x4 = (avg_x3 + avg_x2 + avg_x0 + avg_x1) >> 2;
    avg_y4 = (avg_y3 + avg_y2 + avg_y1 + avg_y0) >> 2;
    avg_z4 = (avg_z3 + avg_z2 + avg_z1 + avg_z0) >> 2;

    eface = word_1AA5CC;
    if (eface != 0)
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 4;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->X0 = p_exface->X0;
        p_neface->Y0 = p_exface->Y0;
        p_neface->Z0 = p_exface->Z0;
        p_neface->X1 = avg_x0;
        p_neface->Y2 = avg_y3;
        p_neface->Y1 = avg_y0;
        p_neface->Z1 = avg_z0;
        p_neface->X2 = avg_x3;
        p_neface->Z2 = avg_z3;
        p_neface->X3 = avg_x4;
        p_neface->Y3 = avg_y4;
        p_neface->Z3 = avg_z4;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }

    eface = word_1AA5CC;
    if (eface != 0)
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 4;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->X0 = avg_x0;
        p_neface->Y0 = avg_y0;
        p_neface->Z0 = avg_z0;
        p_neface->X1 = p_exface->X1;
        p_neface->Y1 = p_exface->Y1;
        p_neface->Z1 = p_exface->Z1;
        p_neface->X2 = avg_x4;
        p_neface->Y2 = avg_y4;
        p_neface->Z2 = avg_z4;
        p_neface->X3 = avg_x1;
        p_neface->Y3 = avg_y1;
        p_neface->Z3 = avg_z1;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }

    eface = word_1AA5CC;
    if (eface != 0)
    {
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    }
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 4;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->X0 = avg_x4;
        p_neface->Y0 = avg_y4;
        p_neface->Z0 = avg_z4;
        p_neface->X1 = avg_x1;
        p_neface->Y1 = avg_y1;
        p_neface->Z1 = avg_z1;
        p_neface->X2 = avg_x2;
        p_neface->Y2 = avg_y2;
        p_neface->Z2 = avg_z2;
        p_neface->X3 = p_exface->X3;
        p_neface->Y3 = p_exface->Y3;
        p_neface->Z3 = p_exface->Z3;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }

    eface = word_1AA5CC;
    if (eface != 0)
    {
        word_1AA5CC = ex_faces[word_1AA5CC].Flags;
    }
    if (eface != 0)
    {
        p_neface = &ex_faces[eface];
        p_neface->Type = 4;
        p_neface->Texture = p_exface->Texture;
        p_neface->Flags = p_exface->Flags;
        p_neface->Col = p_exface->Col;
        p_neface->Y0 = avg_y3;
        p_neface->X0 = avg_x3;
        p_neface->Z0 = avg_z3;
        p_neface->X1 = avg_x4;
        p_neface->Y1 = avg_y4;
        p_neface->Z1 = avg_z4;
        p_neface->X2 = p_exface->X2;
        p_neface->Y2 = p_exface->Y2;
        p_neface->Z2 = p_exface->Z2;
        p_neface->X3 = avg_x2;
        p_neface->Y3 = avg_y2;
        p_neface->Z3 = avg_z2;
        p_neface->DX = p_exface->DX;
        p_neface->DY = p_exface->DY;
        p_neface->DZ = p_exface->DZ;
        p_neface->Timer = 1;
    }
    p_exface->Timer = 0;
    explode_face_delete(exface);
}

static void animate_explode_face5_tri(int exface)
{
    struct ExplodeFace3 *p_exface;
    int rndv;

    p_exface = &ex_faces[exface];

    if (p_exface->Timer > 1000)
    {
        p_exface->Timer--;
        if (p_exface->Timer == 1000 && (LbRandomAnyShort() & 0x1F) == 0)
            bang_new4(p_exface->X << 8, p_exface->Y, p_exface->Z << 8, 100);
        return;
    }
    rndv = LbRandomAnyShort() & 0x3FF;
    if ((rndv > p_exface->Timer) && (LbRandomAnyShort() & 0xF) == 0)
    {
        p_exface->Timer = 0;
        bang_new4(p_exface->X << 8, p_exface->Y, p_exface->Z << 8, 35);
        explode_face_delete(exface);
        return;
    }
    set_explode_face_rotate_angle(p_exface->AngleDX, p_exface->AngleDY);
    p_exface->Timer--;
    p_exface->X += 8 * p_exface->DX;
    p_exface->Y += 8 * p_exface->DY;
    p_exface->Z += 8 * p_exface->DZ;
    if ((p_exface->X < 0) || (p_exface->Z < 0))
    {
        p_exface->Timer = 0;
        explode_face_delete(exface);
        return;
    }
    p_exface->DX -= (p_exface->DX >> 5);
    p_exface->DY -= (p_exface->DY >> 5);
    p_exface->DZ -= (p_exface->DZ >> 5);

    explode_face_point_rotate(&p_exface->X0, &p_exface->Y0, &p_exface->Z0);
    explode_face_point_rotate(&p_exface->X1, &p_exface->Y1, &p_exface->Z1);
    explode_face_point_rotate(&p_exface->X2, &p_exface->Y2, &p_exface->Z2);
}

static void animate_explode_face5_quad(int exface)
{
    struct ExplodeFace3 *p_exface;
    int rndv;

    p_exface = &ex_faces[exface];

    if (p_exface->Timer > 1000)
    {
        p_exface->Timer--;
        if (p_exface->Timer == 1000 && (LbRandomAnyShort() & 0x1F) == 0)
            bang_new4(p_exface->X << 8, p_exface->Y, p_exface->Z << 8, 100);
        return;
    }
    rndv = LbRandomAnyShort() & 0x3FF;
    if ((rndv > p_exface->Timer) && (LbRandomAnyShort() & 0xF) == 0)
    {
        p_exface->Timer = 0;
        bang_new4(p_exface->X << 8, p_exface->Y, p_exface->Z << 8, 35);
        explode_face_delete(exface);
        return;
    }
    set_explode_face_rotate_angle(p_exface->AngleDX, p_exface->AngleDY);
    p_exface->Timer--;
    p_exface->X += 8 * p_exface->DX;
    p_exface->Y += 8 * p_exface->DY;
    p_exface->Z += 8 * p_exface->DZ;
    if ((p_exface->X < 0) || (p_exface->Z < 0))
    {
        p_exface->Timer = 0;
        explode_face_delete(exface);
        return;
    }
    p_exface->DX -= (p_exface->DX >> 5);
    p_exface->DY -= (p_exface->DY >> 5);
    p_exface->DZ -= (p_exface->DZ >> 5);

    explode_face_point_rotate(&p_exface->X0, &p_exface->Y0, &p_exface->Z0);
    explode_face_point_rotate(&p_exface->X1, &p_exface->Y1, &p_exface->Z1);
    explode_face_point_rotate(&p_exface->X2, &p_exface->Y2, &p_exface->Z2);
    explode_face_point_rotate(&p_exface->X3, &p_exface->Y3, &p_exface->Z3);
}

void animate_explode(void)
{
#if 0
    asm volatile ("call ASM_animate_explode\n"
        :  :  : "eax" );
    return;
#endif
    struct ExplodeFace3 *p_exface;
    int i;
    int remain;

    if (dont_bother_with_explode_faces)
    {
        while (dword_1AA5C8 != dword_1AA5C4)
        {
            struct rectangle *p_rct;
            p_rct = &redo_scanner[dword_1AA5C8];
            SCANNER_fill_in_a_little_bit(p_rct->x1, p_rct->y1, p_rct->x2, p_rct->y2);
            dword_1AA5C8 = (dword_1AA5C8 + 1) & 0x7F;
        }
        return;
    }

    remain = 0;

    for (i = 1; i < EXPLODE_FACES_COUNT; i++)
    {
        p_exface = &ex_faces[i];
        if (p_exface->Timer == 0) {
            continue;
        }
        ++remain;

        switch (p_exface->Type)
        {
        case 1:
            animate_explode_face1_tri(i);
            break;

        case 2:
            animate_explode_face1_quad(i);
            break;

        case 3:
            animate_explode_face3_tri(i);
            break;

        case 4:
            animate_explode_face3_quad(i);
            break;

        case 5:
            animate_explode_face5_tri(i);
            break;

        case 6:
            animate_explode_face5_quad(i);
            break;
        }
    }
    if (remain == 0)
        dont_bother_with_explode_faces = 1;
}


void draw_explode(void)
{
    ushort exface;

    if (next_ex_face != 0)
        animate_explode();

    if (dont_bother_with_explode_faces)
        return;

    for (exface = 1; exface < EXPLODE_FACES_COUNT; exface++)
    {
        struct ShEnginePoint sp1, sp2, sp3, sp4;
        struct ExplodeFace3 *p_exface;
        struct SpecialPoint *p_specpt;
        int cor_x, cor_y, cor_z;
        ushort npoints;
        ushort flags_all;
        short depth_max;
        ushort pt;

        p_exface = &ex_faces[exface];

        if (next_screen_point + 4 > screen_points_limit)
            break;

        if (p_exface->Timer == 0)
            continue;

        switch (p_exface->Type)
        {
        case 1:
        case 2:
            npoints = (p_exface->Type == 2) ? 4 : 3;
            pt = next_screen_point;
            p_exface->PointOffset = pt;
            next_screen_point += npoints;

            cor_x = p_exface->X + p_exface->X0 - engn_xc;
            cor_z = p_exface->Z + p_exface->Z0 - engn_zc;
            cor_y = p_exface->Y + p_exface->Y0 - engn_yc;
            transform_shpoint(&sp1, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 0];
            p_specpt->X = sp1.X;
            p_specpt->Y = sp1.Y;

            cor_x = p_exface->X + p_exface->X1 - engn_xc;
            cor_z = p_exface->Z + p_exface->Z1 - engn_zc;
            cor_y = p_exface->Y + p_exface->Y1 - engn_yc;
            transform_shpoint(&sp2, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 1];
            p_specpt->X = sp2.X;
            p_specpt->Y = sp2.Y;

            cor_x = p_exface->X + p_exface->X2 - engn_xc;
            cor_z = p_exface->Z + p_exface->Z2 - engn_zc;
            cor_y = p_exface->Y + p_exface->Y2 - engn_yc;
            transform_shpoint(&sp3, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 2];
            p_specpt->X = sp3.X;
            p_specpt->Y = sp3.Y;

            depth_max = SHRT_MIN;
            if (depth_max < sp1.Depth)
                depth_max = sp1.Depth;
            if (depth_max < sp2.Depth)
                depth_max = sp2.Depth;
            if (depth_max < sp3.Depth)
                depth_max = sp3.Depth;

            flags_all = sp3.Flags & sp2.Flags & sp1.Flags;

            if (npoints > 3)
            {
                cor_x = p_exface->X + p_exface->X3 - engn_xc;
                cor_z = p_exface->Z + p_exface->Z3 - engn_zc;
                cor_y = p_exface->Y + p_exface->Y3 - engn_yc;
                transform_shpoint(&sp4, cor_x, cor_y - 8 * engn_yc, cor_z);

                p_specpt = &game_screen_point_pool[pt + 3];
                p_specpt->X = sp4.X;
                p_specpt->Y = sp4.Y;

                flags_all &= sp4.Flags;
                if (depth_max < sp4.Depth)
                    depth_max = sp4.Depth;
            }

            if ((flags_all & 0xF) != 0)
                break;

            dword_176D68++;
            draw_item_add(DrIT_Unkn5, exface, BUCKET_MID + depth_max);
            break;
        case 3:
        case 4:
            npoints = (p_exface->Type == 4) ? 4 : 3;
            pt = next_screen_point;
            p_exface->PointOffset = pt;
            next_screen_point += npoints;

            cor_x = p_exface->X0 - engn_xc;
            cor_z = p_exface->Z0 - engn_zc;
            cor_y = p_exface->Y0 - engn_yc;
            transform_shpoint(&sp1, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 0];
            p_specpt->X = sp1.X;
            p_specpt->Y = sp1.Y;

            cor_x = p_exface->X1 - engn_xc;
            cor_z = p_exface->Z1 - engn_zc;
            cor_y = p_exface->Y1 - engn_yc;
            transform_shpoint(&sp2, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 1];
            p_specpt->X = sp2.X;
            p_specpt->Y = sp2.Y;

            cor_x = p_exface->X2 - engn_xc;
            cor_z = p_exface->Z2 - engn_zc;
            cor_y = p_exface->Y2 - engn_yc;
            transform_shpoint(&sp3, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 2];
            p_specpt->X = sp3.X;
            p_specpt->Y = sp3.Y;

            depth_max = SHRT_MIN;
            if (depth_max < sp1.Depth)
                depth_max = sp1.Depth;
            if (depth_max < sp2.Depth)
                depth_max = sp2.Depth;
            if (depth_max < sp3.Depth)
                depth_max = sp3.Depth;

            flags_all = sp3.Flags & sp2.Flags & sp1.Flags;

            if (npoints > 3)
            {
                cor_x = p_exface->X3 - engn_xc;
                cor_z = p_exface->Z3 - engn_zc;
                cor_y = p_exface->Y3 - engn_yc;
                transform_shpoint(&sp4, cor_x, cor_y - 8 * engn_yc, cor_z);

                p_specpt = &game_screen_point_pool[pt + 3];
                p_specpt->X = sp4.X;
                p_specpt->Y = sp4.Y;

                flags_all &= sp4.Flags;
                if (depth_max < sp4.Depth)
                    depth_max = sp4.Depth;
            }

            if ((flags_all & 0xF) != 0)
                break;

            dword_176D68++;
            draw_item_add(DrIT_Unkn5, exface, BUCKET_MID + depth_max);
            break;
        case 5:
        case 6:
            npoints = (p_exface->Type == 6) ? 4 : 3;
            pt = next_screen_point;
            p_exface->PointOffset = pt;
            next_screen_point += npoints;

            cor_x = p_exface->X + p_exface->X0 - engn_xc;
            cor_z = p_exface->Z + p_exface->Z0 - engn_zc;
            cor_y = p_exface->Y + p_exface->Y0 - engn_yc;
            transform_shpoint(&sp1, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 0];
            p_specpt->X = sp1.X;
            p_specpt->Y = sp1.Y;

            cor_x = p_exface->X + p_exface->X1 - engn_xc;
            cor_z = p_exface->Z + p_exface->Z1 - engn_zc;
            cor_y = p_exface->Y + p_exface->Y1 - engn_yc;
            transform_shpoint(&sp2, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 1];
            p_specpt->X = sp2.X;
            p_specpt->Y = sp2.Y;

            cor_x = p_exface->X + p_exface->X2 - engn_xc;
            cor_z = p_exface->Z + p_exface->Z2 - engn_zc;
            cor_y = p_exface->Y + p_exface->Y2 - engn_yc;
              transform_shpoint(&sp3, cor_x, cor_y - 8 * engn_yc, cor_z);

            p_specpt = &game_screen_point_pool[pt + 2];
            p_specpt->X = sp3.X;
            p_specpt->Y = sp3.Y;

            depth_max = SHRT_MIN;
            if (depth_max < sp1.Depth)
                depth_max = sp1.Depth;
            if (depth_max < sp2.Depth)
                depth_max = sp2.Depth;
            if (depth_max < sp3.Depth)
                depth_max = sp3.Depth;

            flags_all = sp3.Flags & sp2.Flags & sp1.Flags;

            if (npoints > 3)
            {
                cor_x = p_exface->X + p_exface->X3 - engn_xc;
                cor_z = p_exface->Z + p_exface->Z3 - engn_zc;
                cor_y = p_exface->Y + p_exface->Y3 - engn_yc;
                transform_shpoint(&sp4, cor_x, cor_y - 8 * engn_yc, cor_z);

                p_specpt = &game_screen_point_pool[pt + 3];
                p_specpt->X = sp4.X;
                p_specpt->Y = sp4.Y;

                flags_all &= sp4.Flags;
                if (depth_max < sp4.Depth)
                    depth_max = sp4.Depth;
            }

            if ((flags_all & 0xF) != 0)
                break;

            dword_176D68++;
            draw_item_add(DrIT_Unkn5, exface, BUCKET_MID + depth_max);
            break;
        case 0:
        default:
            break;
        }
    }
}

/******************************************************************************/
