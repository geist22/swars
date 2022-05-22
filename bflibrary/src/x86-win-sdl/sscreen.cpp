/******************************************************************************/
// Bullfrog Engine Emulation Library - for use to remake classic games like
// Syndicate Wars, Magic Carpet, Genewars or Dungeon Keeper.
/******************************************************************************/
/** @file sscreen.cpp
 *     Implementation of related functions.
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
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_syswm.h>
#include "bfscreen.h"

#include "bfscrsurf.h"
#include "bfpalette.h"
#include "bfmouse.h"
#include "bftext.h"
#include "bfexe_key.h"
#include "bflog.h"

#define to_SDLSurf(h) ((SDL_Surface  *)h)

extern char lbDrawAreaTitle[128];
extern short lbIconIndex;
extern ResourceMappingFunc userResourceMapping;

/** @internal
 * Informs if separate screen and draw surfaces were created
 * during LbScreenSetup().
 */
TbBool lbHasSecondSurface = false;

//int lbScreenDirectAccessActive;

/** Bytes per pixel expected by the engine.
 * On any try of entering different video BPP, this mode will be emulated. */
volatile unsigned short lbEngineBPP = 8;

static inline void *LbI_XMemCopy(void *dest, void *source, ulong len)
{
    ulong remain;
    ubyte *s;
    ubyte *d;
    s = (ubyte *)source;
    d = (ubyte *)dest;
    for (remain = len >> 2; remain != 0; remain--)
    {
        *(ulong *)d = *(ulong *)s;
        d += 4;
        s += 4;
    }
    return dest;
}

static inline void *LbI_XMemCopyAndSet(void *dest, void *source, ulong val, ulong len)
{
    ulong remain;
    ubyte *s;
    ubyte *d;
    s = (ubyte *)source;
    d = (ubyte *)dest;
    for (remain = len >> 2; remain != 0; remain--)
    {
        *(ulong *)d = *(ulong *)s;
        *(ulong *)s = val;
        d += 4;
        s += 4;
    }
    return dest;
}

#if defined(WIN32)

TbResult LbScreenUpdateIcon(void)
{
    HICON hIcon;
    HINSTANCE lbhInstance;
    SDL_SysWMinfo wmInfo;
    const char * rname;

    SDL_VERSION(&wmInfo.version);
    if (SDL_GetWMInfo(&wmInfo) < 0) {
        LIBLOG("Cannot set icon: Get SDL window info failed: %s", SDL_GetError());
        return Lb_FAIL;
    }

    rname = userResourceMapping(lbIconIndex);
    if (rname != NULL) {
        lbhInstance = GetModuleHandle(NULL);
        hIcon = LoadIcon(lbhInstance, rname);
    } else {
        LIBLOG("Cannot set icon: Resource mapped to NULL");
        return Lb_FAIL;
    }
    SendMessage(wmInfo.window, WM_SETICON, ICON_BIG,  (LPARAM)hIcon);
    SendMessage(wmInfo.window, WM_SETICON, ICON_SMALL,(LPARAM)hIcon);

    return Lb_SUCCESS;
}

#else

TbResult LbScreenUpdateIcon(void)
{
    Uint32          colorkey;
    SDL_Surface     *image;
    const char * rname;

    rname = userResourceMapping(lbIconIndex);
    if (rname != NULL) {
        image = SDL_LoadBMP(rname);
    } else {
        image = NULL;
    }
    if (image == NULL) {
        LIBLOG("Cannot set icon: Image load failed: %s", SDL_GetError());
        return Lb_FAIL;
    }
    colorkey = SDL_MapRGB(image->format, 255, 0, 255);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
    SDL_WM_SetIcon(image, NULL);

    return Lb_SUCCESS;
}

#endif

TbResult LbScreenSetupAnyMode(TbScreenMode mode, TbScreenCoord width,
    TbScreenCoord height, ubyte *palette)
{
    SDL_Surface * prevScreenSurf;
    long hot_x, hot_y;
    const struct TbSprite *msspr;
    TbScreenModeInfo *mdinfo;
    unsigned long sdlFlags;

    msspr = NULL;
    LbExeReferenceNumber();
    if (lbDisplay.MouseSprite != NULL) {
        msspr = lbDisplay.MouseSprite;
        LbMouseGetSpriteOffset(&hot_x, &hot_y);
    }
    prevScreenSurf = to_SDLSurf(lbScreenSurface);
    LbMouseChangeSprite(NULL);
    if (lbHasSecondSurface) {
        SDL_FreeSurface(to_SDLSurf(lbDrawSurface));
    }
    lbDrawSurface = NULL;
    lbScreenInitialised = false;

    if (prevScreenSurf != NULL) {
    }

    // No need for old video mode in window-based environments
    if (lbDisplay.OldVideoMode == 0)
        lbDisplay.OldVideoMode = 0xFF;

    mdinfo = LbScreenGetModeInfo(mode);
    if (!LbScreenIsModeAvailable(mode)) {
        LIBLOG("%s resolution %dx%d (mode %d) not available",
            (mdinfo->VideoMode & Lb_VF_WINDOWED) ? "Windowed" : "Full screen",
            (int)mdinfo->Width, (int)mdinfo->Height, (int)mode);
        return Lb_FAIL;
    }

    // No need for video buffer paging when using SDL
    lbDisplay.VesaIsSetUp = false;

    // SDL video mode flags
    sdlFlags = 0;
    sdlFlags |= SDL_SWSURFACE;
    if (mdinfo->BitsPerPixel == lbEngineBPP) {
        sdlFlags |= SDL_HWPALETTE;
    }
#if 0
    if (lbDoubleBufferingRequested) {
        sdlFlags |= SDL_DOUBLEBUF;
    }
#endif
    if ((mdinfo->VideoMode & Lb_VF_WINDOWED) == 0) {
        sdlFlags |= SDL_FULLSCREEN;
    }

    // Set SDL video mode (also creates window).
    lbScreenSurface = lbDrawSurface = SDL_SetVideoMode(mdinfo->Width, mdinfo->Height,
      mdinfo->BitsPerPixel, sdlFlags);

    if (lbScreenSurface == NULL) {
        LIBLOG("Failed to initialize mode %d: %s", (int)mode, SDL_GetError());
        return Lb_FAIL;
    }

    SDL_WM_SetCaption(lbDrawAreaTitle, lbDrawAreaTitle);
    LbScreenUpdateIcon();

    // Create secondary surface if necessary,
    // that is if BPP or dimensions do not match.
    if ((mdinfo->BitsPerPixel != lbEngineBPP) ||
        (mdinfo->Width != width) || (mdinfo->Height != height))
    {
        lbDrawSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
          width, height, lbEngineBPP, 0, 0, 0, 0);
        if (lbDrawSurface == NULL) {
            LIBLOG("Secondary surface creation error: %s", SDL_GetError());
            LbScreenReset();
            return Lb_FAIL;
        }
        lbHasSecondSurface = true;
    }

    lbDisplay.DrawFlags = 0;
    lbDisplay.DrawColour = 0;
#if defined(ENABLE_SHADOW_COLOUR)
    lbDisplay.ShadowColour = 0;
#endif
    lbDisplay.PhysicalScreenWidth = mdinfo->Width;
    lbDisplay.PhysicalScreenHeight = mdinfo->Height;
    lbDisplay.ScreenMode = mode;
    lbDisplay.PhysicalScreen = NULL;
    // The graphics screen size should be really taken after screen is locked
    lbDisplay.GraphicsScreenWidth  = width;
    lbDisplay.GraphicsScreenHeight = height;
    //lbDisplay.WScreen = NULL; // TODO re-enable when WScreen is used properly
    lbDisplay.GraphicsWindowPtr = NULL;

    lbScreenInitialised = true;
    LIBLOG("Mode %dx%dx%d setup succeeded", (int)to_SDLSurf(lbScreenSurface)->w, (int)to_SDLSurf(lbScreenSurface)->h,
      (int)to_SDLSurf(lbScreenSurface)->format->BitsPerPixel);
    if (palette != NULL)
    {
        TbResult ret;
        ret = LbPaletteSet(palette);
        if (ret != Lb_SUCCESS) {
            LIBLOG("Palette setting failed");
            LbScreenReset();
            return Lb_FAIL;
        }
    }
    LbScreenSetGraphicsWindow(0, 0, mdinfo->Width, mdinfo->Height);
    LbTextSetWindow(0, 0, mdinfo->Width, mdinfo->Height);
    LIBLOG("Done filling display properties struct");
    if ( LbMouseIsInstalled() )
    {
        LbMouseSetWindow(0, 0, lbDisplay.PhysicalScreenWidth, lbDisplay.PhysicalScreenHeight);
        LbMouseSetPosition(lbDisplay.PhysicalScreenWidth / 2, lbDisplay.PhysicalScreenHeight / 2);
        LbMouseChangeSpriteOffset(hot_x, hot_y);
        if (msspr != NULL)
          LbMouseChangeSprite(msspr);
    }
#if 0
    LbInputRestate();
    LbScreenActivationUpdate();
#endif
    LIBLOG("Finished");
    return Lb_SUCCESS;
}

int LbScreenClearGraphicsWindow_TODO()
{
// code at 0001:000956dc
}

int LbScreenClear_TODO()
{
// code at 0001:00095728
}

TbResult LbScreenReset(void)
{
    if (!lbScreenInitialised)
      return Lb_FAIL;

    LbMouseSuspend();
    if (lbDisplay.WScreen != NULL) {
        LIBLOG("Screen got reset while locked");
        LbScreenUnlock();
    }
    if (lbHasSecondSurface) {
        SDL_FreeSurface(to_SDLSurf(lbDrawSurface));
    }
    // do not free screen surface, it is freed automatically
    // on SDL_Quit or next call to set video mode
    lbHasSecondSurface = false;
    lbDrawSurface = NULL;
    lbScreenSurface = NULL;
    // Mark as not initialized
    lbScreenInitialised = false;

    return Lb_SUCCESS;
}

TbResult LbScreenLock_TODO(void)
{
    LIBLOG("Starting");
    if (!lbScreenInitialised)
        return Lb_FAIL;

    if (SDL_MUSTLOCK(to_SDLSurf(lbDrawSurface))) {
        if (SDL_LockSurface(to_SDLSurf(lbDrawSurface)) < 0) {
            LIBLOG("error: SDL Lock Surface: %s", SDL_GetError());
            lbDisplay.GraphicsWindowPtr = NULL;
            lbDisplay.WScreen = NULL;
            return Lb_FAIL;
        }
    }

    lbDisplay.WScreen = (unsigned char *) to_SDLSurf(lbDrawSurface)->pixels;
    lbDisplay.GraphicsScreenWidth = to_SDLSurf(lbDrawSurface)->pitch;
    lbDisplay.GraphicsWindowPtr = &lbDisplay.WScreen[lbDisplay.GraphicsWindowX +
        lbDisplay.GraphicsScreenWidth * lbDisplay.GraphicsWindowY];

    return Lb_SUCCESS;
}

TbResult LbScreenUnlock_TODO(void)
{
    LIBLOG("Starting");
    if (!lbScreenInitialised)
        return Lb_FAIL;

    lbDisplay.WScreen = NULL;
    lbDisplay.GraphicsWindowPtr = NULL;

    if (SDL_MUSTLOCK(to_SDLSurf(lbDrawSurface)))
        SDL_UnlockSurface(to_SDLSurf(lbDrawSurface));

    return Lb_SUCCESS;
}

int LbScreenSetDoubleBuffering_TODO()
{
// code at 0001:000957b8
}

int LbScreenSetWScreenInVideo_TODO()
{
// code at 0001:000957d8
}

int LbScreenFindVideoModes_TODO()
{
// code at 0001:000957f8
}

TbResult LbScreenSwap(void)
{
    TbResult ret;

    assert(!lbDisplay.VesaIsSetUp); // video mem paging not supported with SDL

    LbMousePlace();
    {
        ulong blremain;
        blremain = lbDisplay.GraphicsScreenHeight * lbDisplay.GraphicsScreenWidth;
        LbI_XMemCopy(lbDisplay.PhysicalScreen, lbDisplay.WScreen, blremain);
        ret = Lb_SUCCESS;
    }
    LbMouseRemove();
/*
    int blresult;
    LIBLOG("Starting");
    ret = LbMouseOnBeginSwap();
    // Put the data from Draw Surface onto Screen Surface
    if ((ret == Lb_SUCCESS) && (lbHasSecondSurface)) {
        blresult = SDL_BlitSurface(to_SDLSurf(lbDrawSurface), NULL,
          to_SDLSurf(lbScreenSurface), NULL);
        if (blresult < 0) {
            LIBLOG("Blit failed: %s", SDL_GetError());
            ret = Lb_FAIL;
        }
    }
    // Flip the image displayed on Screen Surface
    if (ret == Lb_SUCCESS) {
        // calls SDL_UpdateRect for entire screen if not double buffered
        blresult = SDL_Flip(to_SDLSurf(lbScreenSurface));
        if (blresult < 0) {
            // In some cases this situation seems to be quite common
            LIBLOG("Flip failed: %s", SDL_GetError());
            ret = Lb_FAIL;
        }
    }
    LbMouseOnEndSwap();
*/
    return ret;
}

int LbScreenSwapBoxClear_TODO()
{
// code at 0001:00095964
}

TbResult LbScreenSwapClear(TbPixel colour)
{
    assert(!lbDisplay.VesaIsSetUp); // video mem paging not supported with SDL

    LbMousePlace();
    {
        int blsize;
        ubyte *blsrcbuf;
        blsrcbuf = lbDisplay.WScreen;
        blsize = lbDisplay.GraphicsScreenHeight * lbDisplay.GraphicsScreenWidth;
        LbI_XMemCopyAndSet(lbDisplay.PhysicalScreen, blsrcbuf, 0x01010101 * colour, blsize);
    }
    LbMouseRemove();
    return Lb_SUCCESS;
}

int LbScreenSwapBox_TODO()
{
// code at 0001:00095c38
}

int LbScreenDrawHVLineDirect_TODO()
{
// code at 0001:00095dc4
}

int LbScreenWaitVbi_TODO()
{
// code at 0001:000961b0
}


/******************************************************************************/
