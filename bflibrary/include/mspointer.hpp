/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file mspointer.hpp
 *     Internal header file for mspointer.cpp.
 * @par Purpose:
 *     Graphics drawing support sdk class.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     16 Nov 2008 - 21 Nov 2009
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef BFLIBRARY_MSPOINTER_H_
#define BFLIBRARY_MSPOINTER_H_

#include "bfsemphr.hpp"
#include "bfscrsurf.h"
#include "bfplanar.h"
/******************************************************************************/

struct TbSprite;

class LbI_PointerHandler {
 public:
    LbI_PointerHandler(void);
    ~LbI_PointerHandler(void);
    void SetHotspot(long x, long y);
    void Initialise(const struct TbSprite *spr, struct TbPoint *,
      struct TbPoint *);
    void Release(void);
    void NewMousePos(void);
    bool OnMove(void);
    void OnBeginPartialUpdate(void);
    void OnEndPartialUpdate(void);
    void OnBeginSwap(void);
    void OnEndSwap(void);
    void OnBeginFlip(void);
    void OnEndFlip(void);
 protected:
    void ClipHotspot(void);
    void Draw(bool);
    void Undraw(bool);
    void Backup(bool);
    // Properties
    struct SSurface surf1;
    struct SSurface surf2;
    struct TbPoint *position;
    struct TbPoint *spr_offset;
    struct TbRect rect_1038;
    long draw_pos_x;
    long draw_pos_y;
    bool initialised;
    bool field_1054;
    const struct TbSprite *sprite;
    LbSemaphore sema_rel;
    };

extern long cursor_xsteps_array[];
extern long cursor_ysteps_array[];

#endif // BFLIBRARY_MSPOINTER_H_
/******************************************************************************/
