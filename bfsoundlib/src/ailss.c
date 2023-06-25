/******************************************************************************/
// Bullfrog Sound Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file ailss.c
 *     OpenAL based reimplementation of MSS API.
 * @par Purpose:
 *     SS functions from MSS API.
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
#include <stdbool.h>
#include <assert.h>

#include "ailss.h"
#include "aildebug.h"
#include "ail.h"
#include "mssdig.h"
/******************************************************************************/
extern size_t sound_source_count;
extern SNDSAMPLE sound_samples[];

DIG_DRIVER *SS_construct_DIG_driver(AIL_DRIVER *drvr, const SNDCARD_IO_PARMS *iop)
{
    DIG_DRIVER *digdrv;
    int32_t n;

    digdrv = calloc(1, sizeof(*digdrv));
    assert(sizeof(SNDSAMPLE) == 0x894);

    digdrv->n_samples = sound_source_count;
    digdrv->buffer_flag = calloc(1, sizeof (int16_t));
    digdrv->build_buffer = calloc(digdrv->n_samples, 4);
    digdrv->build_size = 4 * digdrv->n_samples;
    digdrv->bytes_per_channel = 2;
    digdrv->channels_per_sample = 2;
    digdrv->channels_per_buffer = 2;
    digdrv->drvr = drvr;
    digdrv->hw_format = 3;
    digdrv->master_volume = 127;
    digdrv->playing  = 1;
    digdrv->DMA_rate = 44100;
    digdrv->half_buffer_size = 2048;
    digdrv->samples = sound_samples;

    for (n = 0; n < digdrv->n_samples; n++)
    {
        digdrv->samples[n].driver = digdrv;
        digdrv->samples[n].status = 1;
    }

    return digdrv;
}

uint32_t AIL2OAL_API_sample_status(SNDSAMPLE *s)
{
    return s->status;
}

void AIL2OAL_API_init_sample(SNDSAMPLE *s)
{
    asm volatile (
      "push %0\n"
      "call ASM_AIL_API_init_sample\n"
      "add $0x4, %%esp\n"
        :  : "g" (s) : "eax" );
}

SNDSAMPLE *AIL2OAL_API_allocate_sample_handle(DIG_DRIVER *dig)
{
    int32_t i;
    SNDSAMPLE *s;

    if (dig == NULL)
        return NULL;

    AIL_lock();

    // Look for an unallocated sample structure
    for (i = 0; i < dig->n_samples; i++)
    {
        if (dig->samples[i].status == SNDSMP_FREE)
            break;
    }

    if (i == dig->n_samples)
    {
        AIL_set_error("Out of sample handles.");
        AIL_unlock();
        return NULL;
    }

    s = &dig->samples[i];

    // Initialize sample to status SNDSMP_DONE with nominal
    // sample attributes
    AIL_init_sample(s);

    AIL_unlock();
    return s;
}

/******************************************************************************/
