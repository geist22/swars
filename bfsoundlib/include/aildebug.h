/******************************************************************************/
// Bullfrog Sound Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file aildebug.h
 *     Header file for aildebug.c.
 * @par Purpose:
 *     OpenAL based reimplementation of MSS API.
 * @par Comment:
 *     Wrappers for MSS API functions, providing debug log capabilities.
 * @author   Tomasz Lis
 * @date     12 Jun 2022 - 05 Sep 2022
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef AIL2OAL_AILDEBUG_H_
#define AIL2OAL_AILDEBUG_H_

#include "mssal.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/

AIL_DRIVER *AIL_install_driver(const uint8_t *driver_image, uint32_t n_bytes);

/******************************************************************************/
#ifdef __cplusplus
};
#endif

#endif // AIL2OAL_AILDEBUG_H_
