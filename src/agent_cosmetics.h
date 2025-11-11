/******************************************************************************/
// Syndicate Wars Port, source port of the classic strategy game from Bullfrog.
/******************************************************************************/
/** @file agent_cosmetics.h
 *     Header file for agent_cosmetics.c.
 * @par Purpose:
 *     Ingame appearance of player agents loading from file.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     20 May 2024 - 4 Jun 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#ifndef AGENT_COSMETICS_H
#define AGENT_COSMETICS_H

#include <stdbool.h>
#include "bftypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
#pragma pack(1)


#pragma pack()
/******************************************************************************/
extern char PlayerAgentHeads[4];
extern bool PlayerZealotIsHighPriest[4];
TbBool read_agent_cosmetics_file(void);
/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
