/******************************************************************************/
// Syndicate Wars Port - open-source reimplementation of SW.
/******************************************************************************/
/** @file game_speed.c
 *     Control of the game speed.
 * @par Purpose:
 *     Variables and functions keeping game speed and frame rate at required pace.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     10 Feb 2024 - 02 May 2024
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "game_speed.h"

#include <assert.h>
#include "bfkeybd.h"
#include "bftime.h"
#include "keyboard.h"
#include "swlog.h"

short frameskip = 0;
ushort game_num_fps = 16;

/******************************************************************************/

void frameskip_clip(void)
{
    if (frameskip > 512)
        frameskip = 512;
    else if (frameskip < 0)
        frameskip = 0;
}

void frameskip_increase(void)
{
    if (frameskip < 2)
        frameskip++;
    else if (frameskip < 16)
        frameskip += 2;
    else
        frameskip += (frameskip/3);
    frameskip_clip();
    //show_onscreen_msg(game_num_fps+frameskip, "Frame skip %d",frameskip);
}

void frameskip_decrease(void)
{
    if (frameskip <= 2)
        frameskip--;
    else if (frameskip <= 16)
        frameskip -= 2;
    else
        frameskip -= (frameskip/4);
    frameskip_clip();
    //show_onscreen_msg(game_num_fps+frameskip, "Frame skip %d",frameskip);
}

/**
 * Handles game speed control inputs.
 * @return Returns true if packet was created, false otherwise.
 */
TbBool get_speed_control_inputs(void)
{
    if (is_key_pressed(KC_ADD,KMod_CONTROL))
    {
        frameskip_increase();
        clear_key_pressed(KC_ADD);
    }
    if (is_key_pressed(KC_EQUALS,KMod_CONTROL))
    {
        frameskip_increase();
        clear_key_pressed(KC_EQUALS);
    }
    if (is_key_pressed(KC_SUBTRACT,KMod_CONTROL))
    {
        frameskip_decrease();
        clear_key_pressed(KC_SUBTRACT);
    }
    if (is_key_pressed(KC_MINUS,KMod_CONTROL))
    {
        frameskip_decrease();
        clear_key_pressed(KC_MINUS);
    }
    return false;
}

void wait_next_gameturn(void)
{
    static TbClockMSec last_loop_time = 0;
    TbClockMSec curr_time = LbTimerClock();
    TbClockMSec sleep_end = last_loop_time + 1000/game_num_fps;

    // If we missed the normal sleep target (ie. there was a slowdown), reset the value and do not sleep
    if ((sleep_end < curr_time) || (sleep_end > curr_time + 1000/game_num_fps)) {
        LOGNO("missed FPS target, last frame time %ld too far from current %ld",
          (ulong)sleep_end, (ulong)curr_time);
        sleep_end = curr_time;
    }
    LbSleepUntil(sleep_end);
    last_loop_time = sleep_end;
}

/******************************************************************************/
