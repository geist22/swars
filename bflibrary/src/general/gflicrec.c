/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file gflicrec.c
 *     Animation recording support to Autodesk FLIC format.
 * @par Purpose:
 *     Implements functions for encoding frames to FLIC animation.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     22 Apr 2024 - 28 Jan 2025
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "bfflic.h"

#include <stdlib.h>
#include "bffile.h"
#include "bfmemut.h"
#include "privbflog.h"
/******************************************************************************/

TbBool anim_read_data(struct Animation *p_anim, void *buf, u32 size);

/**
 * Writes the data into FLI animation.
 * @return Returns false on error, true on success.
 */
TbBool anim_write_data(struct Animation *p_anim, void *p_buf, u32 size)
{
    return LbFileWrite(p_anim->FileHandle, p_buf, size) == size;
}

/**
 * Stores data into FLI buffer.
 * @return Returns false on error, true on success.
 */
TbBool anim_store_data(struct Animation *p_anim, void *p_buf, u32 size)
{
    LbMemoryCopy(p_anim->ChunkBuf, p_buf, size);
    p_anim->ChunkBuf += size;
    return true;
}

u32 anim_make_FLI_COPY(struct Animation *p_anim)
{
    ubyte *blk_begin;
    ubyte *sbuf;
    short h;

    blk_begin = p_anim->ChunkBuf;
    sbuf = p_anim->FrameBuffer;

    for (h = p_anim->FLCFileHeader.Height; h > 0; h--)
    {
        LbMemoryCopy(p_anim->ChunkBuf, sbuf, p_anim->FLCFileHeader.Width);
        p_anim->ChunkBuf += p_anim->FLCFileHeader.Width;
        sbuf += p_anim->Scanline;
    }

    return (p_anim->ChunkBuf - (ubyte *)blk_begin);
}

u32 anim_make_FLI_COLOUR256(struct Animation *p_anim, ubyte *palette)
{
    ushort *change_count;
    ubyte *kept_count;
    short colridx;
    short change_chunk_len;
    short kept_chunk_len;

    if (memcmp(anim_palette, palette, 768) == 0) {
        return 0;
    }
    change_count = (ushort *)p_anim->ChunkBuf;
    p_anim->ChunkBuf += 2;

    change_chunk_len = 0;
    kept_chunk_len = 0;
    kept_count = NULL;
    *change_count = 0;

    for (colridx = 0; colridx < 256; colridx++)
    {
        ubyte *anipal;
        ubyte *srcpal;

        anipal = &anim_palette[3 * colridx];
        srcpal = &palette[3 * colridx];

        if (memcmp(anipal, srcpal, 3) == 0) {
            change_chunk_len = 0;
            kept_chunk_len++;
        } else {
            if (!change_chunk_len) {
                *p_anim->ChunkBuf = kept_chunk_len;
                kept_chunk_len = 0;
                p_anim->ChunkBuf++;
                kept_count = (ubyte *)p_anim->ChunkBuf;
                p_anim->ChunkBuf++;
            }
            ++change_chunk_len;
            *p_anim->ChunkBuf = 4 * srcpal[0];
            p_anim->ChunkBuf++;
            *p_anim->ChunkBuf = 4 * srcpal[1];
            p_anim->ChunkBuf++;
            *p_anim->ChunkBuf = 4 * srcpal[2];
            p_anim->ChunkBuf++;
            ++(*kept_count);
        }
        if (change_chunk_len == 1) {
            ++(*change_count);
        }
    }
    return (p_anim->ChunkBuf - (ubyte *)change_count);
}

/**
 * Compress data into FLI's BRUN block (8-bit Run-Length compression).
 * @return Returns packed size of the block which was compressed.
 */
u32 anim_make_FLI_BRUN(struct Animation *p_anim)
{
    ubyte *blk_begin;
    ubyte *sbuf;
    short h;

    blk_begin = p_anim->ChunkBuf;
    sbuf = p_anim->FrameBuffer;

    for (h = p_anim->FLCFileHeader.Height; h > 0; h--)
    {
        ubyte *ssbuf;
        short w;

        ssbuf = sbuf;
        p_anim->ChunkBuf++;
        for (w = p_anim->FLCFileHeader.Width; w > 0; )
        {
            short count;
            short k;

            count = 0;
            // Counting size of RLE block
            for (k = 1; w > 1; k++)
            {
                if (ssbuf[k] != ssbuf[0])
                    break;
                if (count == 127)
                    break;
                w--;
                count++;
            }
            // If RLE block would be valid
            if (count > 0)
            {
                if (count < 127) {
                    count++;
                    w--;
                }
                *p_anim->ChunkBuf = (sbyte)count;
                p_anim->ChunkBuf++;
                *p_anim->ChunkBuf = ssbuf[0];
                p_anim->ChunkBuf++;
                ssbuf += count;
            }
            else
            {
                if (w > 1)
                {
                    count = 0;
                    // Find the next block of at least 4 same pixels
                    for (k = 0; w > 0; k++)
                    {
                        if ((ssbuf[k+1] == ssbuf[k]) &&
                          (ssbuf[k+2] == ssbuf[k]) &&
                          (ssbuf[k+3] == ssbuf[k]))
                            break;
                        if (count == -127)
                            break;
                        count--;
                        w--;
                    }
                }
                else
                {
                    count =- 1;
                    w--;
                }
                if (count != 0)
                {
                    *p_anim->ChunkBuf = (sbyte)count;
                    p_anim->ChunkBuf++;
                    LbMemoryCopy(p_anim->ChunkBuf, ssbuf, -count);
                    ssbuf -= count;
                    p_anim->ChunkBuf -= count;
                }
            }
        }
        sbuf += p_anim->Scanline;
    }
    // Make the block size even
    if ((intptr_t)p_anim->ChunkBuf & 1) {
        *p_anim->ChunkBuf = '\0';
        p_anim->ChunkBuf++;
    }
    return (p_anim->ChunkBuf - blk_begin);
}

/**
 * Compress data into FLI's SS2 block.
 * @return Returns packed size of the block which was compressed.
 */
u32 anim_make_FLI_SS2(struct Animation *p_anim, ubyte *curdat, ubyte *prvdat, int scanline)
{
    ubyte *blk_begin;
    ubyte *cbuf;
    ubyte *pbuf;
    ubyte *cbf;
    ubyte *pbf;
    short h;
    short w;
    short k;
    short nsame;
    short ndiff;
    short wend;
    short wendt;
    cbuf = curdat;
    pbuf = prvdat;
    ushort *lines_count;
    ushort *pckt_count;

    blk_begin = p_anim->ChunkBuf;
    lines_count = (ushort *)p_anim->ChunkBuf;
    p_anim->ChunkBuf += 2;
    pckt_count = (ushort *)p_anim->ChunkBuf;

    wend = 0;
    for (h = p_anim->FLCFileHeader.Height; h > 0; h--)
    {
        cbf = cbuf;
        pbf = pbuf;
        if (wend == 0) {
            pckt_count = (ushort *)p_anim->ChunkBuf;
            p_anim->ChunkBuf += 2;
            (*lines_count)++;
        }
        for (w = p_anim->FLCFileHeader.Width; w > 0; )
        {
            for (k = 0; w > 0; k++)
            {
                if (*(ushort *)(pbf + 2 * k) != *(ushort *)(cbf + 2 * k))
                    break;
                w -= 2;
            }
            if (2 * k == p_anim->FLCFileHeader.Width)
            {
                wend--;
                cbf += scanline;
                pbf += scanline;
                continue;
            }
            if ( w > 0 ) {
                if (wend != 0) {
                    (*pckt_count) = wend;
                    pckt_count = (ushort *)p_anim->ChunkBuf;
                    p_anim->ChunkBuf += 2;
                }
                wendt = 2*k;
                wend = wendt;
                while (wend > 255) {
                    *(ubyte *)p_anim->ChunkBuf = 255;
                    p_anim->ChunkBuf++;
                    *(ubyte *)p_anim->ChunkBuf = 0;
                    p_anim->ChunkBuf++;
                    wend -= 255;
                    (*pckt_count)++;
                }
                cbf += wendt;
                pbf += wendt;
                for (nsame  =0; nsame < 127; nsame++)
                {
                    if (w <= 2)
                        break;
                    if ((*(ushort *)(pbf + 2 * nsame + 0) == *(ushort *)(cbf + 2 * nsame + 0)) &&
                      (*(ushort *)(pbf + 2 * nsame + 2) == *(ushort *)(cbf + 2 * nsame + 2))) {
                        break;
                    }
                    if (*(ushort *)(cbf + 2 * nsame + 2) != *(ushort *)(cbf))
                        break;
                    w -= 2;
                }
                if (nsame > 0) {
                    if (nsame < 127) {
                        nsame++;
                        w -= 2;
                    }
                    *(ubyte *)p_anim->ChunkBuf = wend;
                    p_anim->ChunkBuf++;
                    *(ubyte *)p_anim->ChunkBuf = -nsame;
                    p_anim->ChunkBuf++;
                    *(ushort *)p_anim->ChunkBuf = *(ushort *)cbf;
                    p_anim->ChunkBuf+=2;
                    pbf += 2*nsame;
                    cbf += 2*nsame;
                    wend = 0;
                    (*pckt_count)++;
                } else {
                    if (w == 2) {
                        ndiff = 1;
                        w -= 2;
                    } else {
                        for (ndiff=0; ndiff<127; ndiff++) {
                            if (w <= 0) break;
                            if (*(ushort *)(pbf + 2 * ndiff) == *(ushort *)(cbf + 2 * ndiff))
                                break;
                            if ((*(ushort *)(cbf + 2 * (ndiff+1)) == *(ushort *)(cbf + 2 * ndiff)) &&
                              (*(ushort *)(cbf + 2 * (ndiff+2)) == *(ushort *)(cbf + 2 * ndiff)) ) {
                                break;
                            }
                            w -= 2;
                        }
                    }
                    if (ndiff > 0) {
                        *(ubyte *)p_anim->ChunkBuf = wend;
                        p_anim->ChunkBuf++;
                        *(ubyte *)p_anim->ChunkBuf = ndiff;
                        p_anim->ChunkBuf++;
                        LbMemoryCopy(p_anim->ChunkBuf, cbf, 2 * ndiff);
                        p_anim->ChunkBuf += 2 * ndiff;
                        pbf += 2 * ndiff;
                        cbf += 2 * ndiff;
                        wend = 0;
                        (*pckt_count)++;
                    }
                }
            }
        }
        cbuf += scanline;
        pbuf += scanline;
    }

    if (p_anim->FLCFileHeader.Height+wend == 0) {
        (*lines_count) = 1;
        (*pckt_count) = 1;
        *(ubyte *)p_anim->ChunkBuf = 0;
        p_anim->ChunkBuf++;
        *(ubyte *)p_anim->ChunkBuf = 0;
        p_anim->ChunkBuf++;
    } else if (wend != 0) {
        p_anim->ChunkBuf -= 2;
        (*lines_count)--;
    }
    // Make the block size even
    if ((intptr_t)p_anim->ChunkBuf & 1) {
        *p_anim->ChunkBuf = '\0';
        p_anim->ChunkBuf++;
    }
    return p_anim->ChunkBuf - blk_begin;
}

/**
 * Compress data into FLI's LC block.
 * @return Returns packed size of the block which was compressed.
 */
u32 anim_make_FLI_LC(struct Animation *p_anim, ubyte *curdat, ubyte *prvdat, int scanline)
{
    ubyte *blk_begin;
    ubyte *cbuf;
    ubyte *pbuf;
    ubyte *cbf;
    ubyte *pbf;
    ubyte *outptr;
    short h;
    short w;
    short hend;
    short wend;
    short hdim;
    short wendt;
    short k;
    short nsame;
    short ndiff;
    int blksize;

    blk_begin = p_anim->ChunkBuf;
    cbuf = curdat;
    pbuf = prvdat;
    for (hend = p_anim->FLCFileHeader.Height; hend > 0;  hend--)
    {
        wend = 0;
        for (w = p_anim->FLCFileHeader.Width; w > 0; w--)
        {
            if (cbuf[wend] != pbuf[wend])
                break;
            ++wend;
        }
        if (wend != p_anim->FLCFileHeader.Width)
            break;
        cbuf += scanline;
        pbuf += scanline;
    }
    if (hend != 0) {
        hend = p_anim->FLCFileHeader.Height - hend;
        blksize = p_anim->FLCFileHeader.Width * (p_anim->FLCFileHeader.Height - 1);
        cbuf = curdat + blksize;
        pbuf = prvdat + blksize;
        for (h = p_anim->FLCFileHeader.Height; h > 0; h--) {
            wend = 0;
            for (w = p_anim->FLCFileHeader.Width; w > 0; w--) {
                if (cbuf[wend] != pbuf[wend])
                    break;
                wend++;
            }
            if (wend != p_anim->FLCFileHeader.Width)
                break;
            cbuf -= scanline;
            pbuf -= scanline;
        }
        hdim = h - hend;
        blksize = p_anim->FLCFileHeader.Width * hend;
        cbuf = curdat + blksize;
        pbuf = prvdat + blksize;
        *(ushort *)p_anim->ChunkBuf = hend;
        p_anim->ChunkBuf += 2;
        *(ushort *)p_anim->ChunkBuf = hdim;
        p_anim->ChunkBuf += 2;

        for (h = hdim; h>0; h--) {
            cbf = cbuf;
            pbf = pbuf;
            outptr = p_anim->ChunkBuf++;
            for (w=p_anim->FLCFileHeader.Width; w>0; ) {
                for ( wend=0; w>0; wend++) {
                    if ( cbf[wend] != pbf[wend]) break;
                    w--;
                }
                wendt = wend;
                if (p_anim->FLCFileHeader.Width == wend) continue;
                if ( w <= 0 ) break;
                while ( wend > 255 ) {
                    *(ubyte *)p_anim->ChunkBuf = 255;
                    p_anim->ChunkBuf++;
                    *(ubyte *)p_anim->ChunkBuf = 0;
                    p_anim->ChunkBuf++;
                    wend -= 255;
                    (*(ubyte *)outptr)++;
                }
                cbf += wendt;
                pbf += wendt;
                k = 0;
                nsame = 0;
                while (w > 1) {
                    if (nsame == -127)
                        break;
                    if ((cbf[k+0] == pbf[k+0]) &&
                      (cbf[k+1] == pbf[k+1]) &&
                      (cbf[k+2] == pbf[k+2]))
                        break;
                    if (cbf[k+1] != cbf[0])
                        break;
                    w--;
                    k++;
                    nsame--;
                }
                if ( nsame ) {
                    if (nsame != -127) {
                        nsame--;
                        w--;
                    }
                    *(ubyte *)p_anim->ChunkBuf = wend;
                    p_anim->ChunkBuf++;
                    *(ubyte *)p_anim->ChunkBuf = nsame;
                    p_anim->ChunkBuf++;
                    *(ubyte *)p_anim->ChunkBuf = cbf[0];
                    cbf -= nsame;
                    pbf -= nsame;
                    p_anim->ChunkBuf++;
                    (*(ubyte *)outptr)++;
                } else {
                    if (w == 1) {
                        ndiff = nsame + 1;
                        w--;
                    } else {
                        k = 0;
                        ndiff = 0;
                        while (w != 0) {
                            if (ndiff == 127)
                                break;
                            if ((cbf[k+0] == pbf[k+0]) &&
                              (cbf[k+1] == pbf[k+1]) &&
                              (cbf[k+2] == pbf[k+2]))
                                break;
                            if ((cbf[k+1] == cbf[k+0]) &&
                              (cbf[k+2] == cbf[k+0]) &&
                              (cbf[k+3] == cbf[k+0]))
                                break;
                            w--;
                            k++;
                            ndiff++;
                        }
                    }
                    if (ndiff != 0) {
                        *(ubyte *)p_anim->ChunkBuf = wend;
                        p_anim->ChunkBuf++;
                        *(ubyte *)p_anim->ChunkBuf = ndiff;
                        p_anim->ChunkBuf++;
                        LbMemoryCopy(p_anim->ChunkBuf, cbf, ndiff);
                        p_anim->ChunkBuf += ndiff;
                        cbf += ndiff;
                        pbf += ndiff;
                        (*(ubyte *)outptr)++;
                    }
                }
            }
            cbuf += scanline;
            pbuf += scanline;
        }
    } else {
        *(short *)p_anim->ChunkBuf = 0;
        p_anim->ChunkBuf += 2;
        *(short *)p_anim->ChunkBuf = 1;
        p_anim->ChunkBuf += 2;
        *(sbyte *)p_anim->ChunkBuf = 0;
        p_anim->ChunkBuf++;
    }
    // Make the block size even
    if ((intptr_t)p_anim->ChunkBuf & 1) {
        *p_anim->ChunkBuf = '\0';
        p_anim->ChunkBuf++;
    }
    return p_anim->ChunkBuf - blk_begin;
}

/*
 * Returns size of the FLI movie frame buffer, for given width
 * and height of animation. The buffer of returned size is big enough
 * to store one frame of any kind (any compression).
 */
u32 anim_buffer_size(int width, int height, int bpp)
{
    int n;
    n = (bpp >> 3);
    if (bpp % 8) n++;
    return abs(width)*abs(height)*n + 32767;
}

TbResult anim_make_open(struct Animation *p_anim, int width, int height, int bpp, uint flags)
{
    if (flags & p_anim->Flags) {
        LOGERR("Cannot record anim");
        return Lb_FAIL;
    }
    if (flags & 0x01) {
        LOGSYNC("Record new anim, '%s'", p_anim->Filename);
        p_anim->Flags |= flags;

        p_anim->FileHandle = LbFileOpen(p_anim->Filename, Lb_FILE_MODE_NEW);
        if (p_anim->FileHandle == INVALID_FILE) {
            LOGERR("Cannot open movie file");
            return Lb_FAIL;
        }
        p_anim->FLCFileHeader.Magic = 0xAF12;
        p_anim->FLCFileHeader.NumberOfFrames = 0;
        p_anim->FLCFileHeader.Width = width;
        p_anim->FLCFileHeader.Height = height;
#if defined(LB_ENABLE_FLIC_FULL_HEADER)
        p_anim->FLCFileHeader.dsize = 128;
        p_anim->FLCFileHeader.Depth = bpp;
        p_anim->FLCFileHeader.Flags = 3;
        p_anim->FLCFileHeader.FrameSpeed = 57;
        p_anim->FLCFileHeader.Created = 0;
        p_anim->FLCFileHeader.Creator = 0x464C4942;//'BILF'
        p_anim->FLCFileHeader.Updated = 0;
        p_anim->FLCFileHeader.Updater = 0x464C4942;
        p_anim->FLCFileHeader.AspectX = 6;
        p_anim->FLCFileHeader.AspectY = 5;
        p_anim->FLCFileHeader.Reserved2 = 0;
        LbMemorySet(p_anim->FLCFileHeader.Reserved3, 0, sizeof(p_anim->FLCFileHeader.Reserved3));
        p_anim->FLCFileHeader.OffsetFrame1 = 0;
        p_anim->FLCFileHeader.OffsetFrame2 = 0;
        LbMemorySet(p_anim->FLCFileHeader.Reserved4, 0, sizeof(p_anim->FLCFileHeader.Reserved4));
#endif
        if (!anim_write_data(p_anim, &p_anim->FLCFileHeader, sizeof(struct FLCFileHeader))) {
            LOGERR("Anim write error");
            LbFileClose(p_anim->FileHandle);
            return Lb_FAIL;
        }
        LbMemorySet(anim_palette, -1, sizeof(anim_palette));
    }
    if (flags & 0x02)  {
        LOGSYNC("Resume recording, \"%s\" file",p_anim->Filename);
        p_anim->Flags |= flags;
        p_anim->FileHandle = LbFileOpen(p_anim->Filename, Lb_FILE_MODE_OLD);
        if (p_anim->FileHandle == INVALID_FILE) {
            return Lb_FAIL;
        }
        // Reading header
        if (!anim_read_data(p_anim, &p_anim->FLCFileHeader, sizeof(struct FLCFileHeader))) {
            LOGERR("Anim header read error");
            LbFileClose(p_anim->FileHandle);
            return Lb_FAIL;
        }
        // TODO unfinished
        LbFileClose(p_anim->FileHandle);
        return Lb_FAIL;
    }
    return Lb_SUCCESS;
}

/******************************************************************************/
