/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file bfmouse.h
 *     Header file for smouse.cpp.
 * @par Purpose:
 *     Unknown.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     12 Nov 2008 - 05 Nov 2021
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef BFLIBRARY_BFMOUSE_H_
#define BFLIBRARY_BFMOUSE_H_

#include "bftypes.h"

#ifdef __cplusplus
extern "C" {
#endif

struct TbSprite;
struct TbPoint;

enum MouseAction {
    MActn_NONE = 0,
    MActn_MOUSEMOVE,
    MActn_LBUTTONDOWN,
    MActn_LBUTTONUP,
    MActn_RBUTTONDOWN,
    MActn_RBUTTONUP,
    MActn_MBUTTONDOWN,
    MActn_MBUTTONUP,
    MActn_WHEELMOVEUP,
    MActn_WHEELMOVEDOWN,
};

typedef ubyte TbMouseAction;

typedef void *TbMouseToScreen(struct TbPoint *);

extern volatile TbBool lbMouseInstalled;
extern volatile TbBool lbMouseOffline;
extern volatile TbBool lbInteruptMouse;
extern volatile TbBool lbMouseAutoReset;
extern volatile TbMouseToScreen *lbMouseToScreen;

TbResult LbMousePlace(void);
TbResult LbMouseRemove(void);

/**
 * Set offset within pointer sprite where the mouse actually points at.
 *  Also called LbMouseSetPointerHotspot().
 */
TbResult LbMouseChangeSpriteOffset(ulong hot_x, ulong hot_y);

TbResult LbMouseChangeSprite(const struct TbSprite *pointer_spr);

/**
 * Changes mouse movement ratio.
 * Note that this function can be run even before mouse setup. Still, the factor
 *  will be reset during the installation - so use it after LbMouseSetup().
 *
 * @param ratio_x Movement ratio in X direction; 256 means unchanged ratio from OS.
 * @param ratio_y Movement ratio in Y direction; 256 means unchanged ratio from OS.
 * @return Lb_SUCCESS if the ratio values were of correct range and have been set.
 */
TbResult LbMouseChangeMoveRatio(long ratio_x, long ratio_y);

TbResult LbMouseSetup(const struct TbSprite *pointer_spr, int ratio_x, int ratio_y);
TbResult LbMouseReset(void);
TbResult LbMouseSuspend(void);
TbResult LbMouseSetWindow(long x, long y, long width, long height);
TbResult LbMouseSetPosition(long x, long y);
TbResult LbMouseUpdatePosition(void);

/** Default callback for converting raw mouse coords into screen coords.
 *
 *  Computes shift in mouse position, and uses it with internal move ration
 *  to determine relative shift expected on screen. Then replaces the given
 *  pos with one pointed by that shift.
 *
 * @param pos The source 2D point, and where result is placed.
 */
void MouseToScreen(struct TbPoint *pos);

/** Platform-independent mouse control handler.
 *
 *  Can be used to react on mouse changes, when called within
 *  platform-dependent handler.
 */
TbResult mouseControl(TbMouseAction action, struct TbPoint *pos);

#ifdef __cplusplus
};
#endif

#endif // BFLIBRARY_BFMOUSE_H_
/******************************************************************************/
