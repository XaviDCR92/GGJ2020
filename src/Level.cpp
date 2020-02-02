/*******************************************************************//**
*
* \file     Level.cpp
*
* \brief    Implementation file for Level module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Level.hpp"
#include "Camera.hpp"
#include "IO.h"
#include "Gfx.h"

/* *************************************
 * Defines
 * *************************************/

//Tiles
enum{
	LEVEL_TILE_EMPTY,
	LEVEL_TILE_EMPTY_2,
	LEVEL_TILE_EMPTY_3,
	LEVEL_TILE_GROUND_FILL,

	LEVEL_TILE_GROUND_T,
	LEVEL_TILE_GROUND_T2,
	LEVEL_TILE_GROUND_T3,
	LEVEL_TILE_GROUND_T4,

	LEVEL_TILE_GROUND_TL,
	LEVEL_TILE_GROUND_TR,
	LEVEL_TILE_GROUND_BL,
	LEVEL_TILE_GROUND_BR,

	LEVEL_TILE_GROUND_B,
	LEVEL_TILE_GROUND_B2,
	LEVEL_TILE_GROUND_L,
	LEVEL_TILE_GROUND_R,
	LEVEL_TILE_16,
	LEVEL_TILE_17,
	LEVEL_TILE_18,
	LEVEL_TILE_19,

	LEVEL_TILE_GROUND_PO,
	LEVEL_TILE_GROUND_PU,
	LEVEL_TILE_GROUND_PI,
	LEVEL_TILE_GROUND_PA,

	LEVEL_MAX_TILES
};

//Terran types
enum{
	LEVEL_TILE_AIR = '.',
	LEVEL_TILE_FLOOR = '_'
};

/* *************************************
 * Types definition
 * *************************************/

/* *************************************
 * Global variables definition
 * *************************************/

/* *************************************
 * Local variables definition
 * *************************************/

/* *************************************
 *  Local prototypes declaration
 * *************************************/

/* *************************************
 * Functions definition
 * *************************************/
Level::Level() : level_loaded(false), width(0), height(0){
}

void Level::Update(GlobalData& data){
	(void)data;
}

void Level::Render(const Camera& cam){
	if(!level_loaded) return;

	for(size_t i=0; i<width; i++){
		for(size_t j=0; j<height; j++){
			tile_set.x = i * TILE_SIZE;
			tile_set.y = j * TILE_SIZE;
			cam.getPosition(tile_set.x, tile_set.y);

			const uint8_t tile = tiles[i + j*width];
			tile_set.u = tile_set_zero_u + TILE_SIZE*(tile%tile_set_width_tiles);
			tile_set.v = tile_set_zero_v + TILE_SIZE*(tile/tile_set_width_tiles);

			GfxSortSprite(&tile_set);
		}
	}
}

#include <stdio.h>

bool Level::Load(const char* file_name){
	level_loaded = false;

	/* File size in bytes. Modified by IOLoadFile(). */
    size_t e_size;

    /* Get buffer address where file data is contained. */
    const uint8_t *const buffer = IOLoadFile(file_name, &e_size);

    if(!buffer || e_size == IO_INVALID_FILE_SIZE)
    	return false;

    width = buffer[0];
    height = buffer[1];

    if(width > MAX_LEVEL_SIZE_WIDTH || height > MAX_LEVEL_SIZE_HEIGHT)
    	return false;

    for (size_t i=0; i<e_size-2; i++) {
    	if(buffer[i+2] >= LEVEL_MAX_TILES)
			tiles[i] = 0;
    	else
    		tiles[i] = buffer[i+2];
    }

    level_loaded = true;
    return true;
}

bool Level::LoadAssets(){
	bool ret = GfxSpriteFromFile("DATA\\SPRITES\\tileset.TIM", &tile_set);
	tile_set_total_width = tile_set.w;
	tile_set_total_height = tile_set.h;
	tile_set_zero_u = tile_set.u;
	tile_set_zero_v = tile_set.v;

	tile_set_width_tiles = tile_set_total_width / TILE_SIZE;
	tile_set.w = tile_set.h = TILE_SIZE;
	return ret;
}

bool Level::IsTileSolid(short x, short y)
{
	short map_w, map_h;

	GetDimensions(map_w, map_h);

	if (x > map_w || y > map_h)
		return false;

	const short column = x % TILE_SIZE;
	const short row = y / TILE_SIZE;
	const size_t offset = column + (row * width);

	const uint8_t t = tiles[offset];

	if (t < LEVEL_MAX_TILES)
	{
		printf("t=%d,off=%d,x=%d,y=%d\n", t, offset, x, y);
		return false;
		switch (t)
		{
			case LEVEL_TILE_EMPTY:
				// Fall through.
			case LEVEL_TILE_EMPTY_2:
				// Fall through.
			case LEVEL_TILE_EMPTY_3:
				// Fall through.
			case LEVEL_TILE_AIR:
				return false;

			default:
				return true;
		}
	}

	return false;
}

void Level::GetDimensions(short& w, short& h) const{
	w = width * TILE_SIZE;
	h = height * TILE_SIZE;
}

/*******************************************************************//**
*
* \brief
*
************************************************************************/
