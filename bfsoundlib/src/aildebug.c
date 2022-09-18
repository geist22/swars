/******************************************************************************/
// Bullfrog Sound Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file aildebug.c
 *     OpenAL based reimplementation of MSS API.
 * @par Purpose:
 *     Wrappers for MSS API functions, providing debug log capabilities.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     12 Jun 2022 - 05 Sep 2022
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "aildebug.h"
#include "ail.h"
/******************************************************************************/
extern uint16_t AIL_debug;
extern uint16_t AIL_sys_debug;
extern FILE *AIL_debugfile;
extern uint32_t AIL_indent;

AIL_DRIVER *AIL_install_driver(const uint8_t *driver_image, uint32_t n_bytes)
{
    AIL_DRIVER *drvr;

    AIL_indent++;
    if (AIL_debug && (AIL_indent == 1 || AIL_sys_debug))
        fprintf(AIL_debugfile, "%s(0x%p,%u)\n", __func__, driver_image, n_bytes);

    drvr = AIL2OAL_API_install_driver(driver_image, n_bytes);

    if (AIL_debug && (AIL_indent == 1 || AIL_sys_debug))
        fprintf(AIL_debugfile, "Result = 0x%p\n", drvr);
    AIL_indent--;

    return drvr;
}

/******************************************************************************/
