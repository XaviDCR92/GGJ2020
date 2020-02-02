#ifndef GFX_H
#define GFX_H

/*******************************************************************//**
*
* \file     Gfx.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Gfx module.
*
************************************************************************/

/*******************************************************************//**
*
* \defgroup GFX   Gfx
*
*           This module provides high-level interaction with primitives
*           and PSX graphics sinthetizer (GPU).
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include <psxgpu.h>
#include <stdbool.h>

/* *************************************
 * Defines
 * *************************************/

#define SPRITE_INDEX_INVALID    (size_t)(0xFFFFFFFF)

/*******************************************************************//**
*
* \brief    Maximum size for a GsSprite instance supported by PSX
*           hardware.
*
*           Even if user can use big sprites e.g.: 384x240 px, PSX
*           hardware can only support up to 255x255 px primitives.
*           Bigger sprites are then split into two primitives and drawn
*           separately.
*
* \see      GfxSortSprite().
*
************************************************************************/
#define MAX_SIZE_FOR_GSSPRITE   ((short)256)

enum
{
    GFX_TPAGE_WIDTH = 64,
    GFX_TPAGE_WIDTH_BITSHIFT = __builtin_ctz(GFX_TPAGE_WIDTH)
};

#ifdef __cplusplus
extern "C"
{
#endif

/* *************************************
 * Public types definition
 * *************************************/

enum
{
    X_SCREEN_RESOLUTION = 368,
    Y_SCREEN_RESOLUTION = 240
};

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

void GfxInit(void);
bool GfxSpriteFromFile(const char* const strFilePath, GsSprite *const pSpr);
void GfxSortSprite(GsSprite *const psSpr);
bool GfxIsInsideScreenArea(const short x, const short y, const short w, const short h);
bool GfxIsSpriteInsideScreenArea(const GsSprite *const psSpr);
void GfxDrawScene(void);
void GfxClear(void);
int GfxToDegrees(const int rotate);
int GfxFromDegrees(const int degrees);
bool GfxIsBusy(void);
void GfxDrawRectangle(GsRectangle* const rect);

/** \} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_H */
