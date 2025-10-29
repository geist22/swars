/******************************************************************************/
// Syndicate Wars Fan Expansion, source port of the classic game from Bullfrog.
/******************************************************************************/
/** @file bmbang.h
 *     Header file for bmbang.c.
 * @par Purpose:
 *     On-map explosion effect implementation.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     19 Sep 2023 - 17 Mar 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef BMBANG_H
#define BMBANG_H

#include "bftypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
#pragma pack(1)


#pragma pack()
/******************************************************************************/

void new_bang(int x, int y, int z, int type, int owner, int c);
void bang_new5(int x, int y, int z, int type, int owner);
void bang_new4(int x, int y, int z, int type);

/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
