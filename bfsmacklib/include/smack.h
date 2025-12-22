/******************************************************************************/
// Bullfrog Engine Smacker Playback Library - for use to remake classic games
// like Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file smack.h
 *     Header file for Smacker API.
 * @par Purpose:
 *     Interface of the smacker library.
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
#ifndef BFSMACKLIB_SMACK_H_
#define BFSMACKLIB_SMACK_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
struct SNDSAMPLE;
typedef struct SmackSndTrk SmackSndTrk;
typedef struct Smack Smack;

struct SmackSndTrk { // sizeof=112
    uint32_t field_0[5];
    uint32_t field_14;
    uint32_t field_18[7];
    SmackSndTrk *next;
    struct SNDSAMPLE *smp;
    uint32_t field_3C;
    uint32_t field_40;
    uint32_t field_44;
    uint32_t field_48;
    uint32_t field_4C;
    uint32_t field_50;
    void *field_54;
    uint32_t field_58;
    uint32_t field_5C[3];
    uint32_t field_68;
    uint32_t field_6C;
};

struct Smack { // sizeof=1196
    uint32_t Version;
    uint32_t Width;
    uint32_t Height;
    uint32_t Frames;
    uint32_t MSPerFrame;
    uint32_t SmackerType;
    uint32_t LargestInTrack[7];
    uint32_t tablesize;
    uint32_t codesize;
    uint32_t absize;
    uint32_t detailsize;
    uint32_t typesize;
    uint32_t TrackType[7];
    uint32_t extra;
    uint32_t NewPalette;
    uint8_t Palette[772];
    uint32_t PalType;
    uint32_t FrameNum;
    uint32_t FrameSize;
    uint32_t SndSize;
    uint32_t LastRectx;
    uint32_t LastRecty;
    uint32_t LastRectw;
    uint32_t LastRecth;
    uint32_t OpenFlags;
    uint32_t LeftOfs;
    uint32_t TopOfs;
    uint32_t LargestFrameSize;
    uint32_t Highest1SecRate;
    uint32_t Highest1SecFrame;
    uint32_t ReadError;
    uint32_t addr32;
    uint8_t field_3B0[84];
    uint8_t field_0[1024];
    SmackSndTrk *Unkn404PerTrack[7];
    uint8_t field_420[144];
};

/******************************************************************************/

#if defined(WIN32) && 0 // Disabled - `mkwrappers` expects cdecl on C side
#  define RADAPI __stdcall
#else
#  define RADAPI
#endif

/******************************************************************************/

/** Open .SMK video file for playback.
 *
 * Note, the order of parameters is reverted in later versions of Smacker API.
 * Well, these were clearly implemented assumung the correct order, just
 * the used calling convention was incorrect.
 *
 * @param extrabuf Extra space to be alocated at end of Smack structure.
 * @param flags Open options flags.
 * @param name File name to be opened.
 * @return The Smack playback state structure, or NULL on error.
 */
struct Smack * RADAPI SMACKOPEN(uint32_t extrabuf, uint32_t flags, const char *name);

/** Process the next frame for SMK file playback.
 */
uint32_t RADAPI SMACKDOFRAME(struct Smack *p_smk);

/** Signal the playback engine to advance SMK file playback to the next frame.
 */
void RADAPI SMACKNEXTFRAME(struct Smack *p_smk);

/** Wait the proper amount of time before each frame to ensure correct playback speed.
 */
uint32_t RADAPI SMACKWAIT(struct Smack *p_smk);

/** Gracefully close a SMK file and releases any resources used for playback.
 */
void RADAPI SMACKCLOSE(struct Smack *p_smk);

/** Decode a frame of SMK video into the specified memory buffer.
 */
void RADAPI SMACKTOBUFFER(uint32_t Flags, const void *buf,
 uint32_t destheight, uint32_t Pitch, uint32_t top, uint32_t left, struct Smack *p_smk);

/******************************************************************************/

#ifdef __cplusplus
};
#endif

#endif // BFSMACKLIB_SMACK_H_
/******************************************************************************/
