#include "Utils.h"
#include "Gfx.h"
#include "psxgpu.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static GsSprite char_tile_set;
static unsigned short char_tile_set_total_width;
static unsigned short char_tile_set_total_height;
static unsigned char char_tile_set_zero_u;
static unsigned char char_tile_set_zero_v;

enum{
    CHAR_FIRST = 32,
    CHAR_WIDTH = 7,
    CHAR_HEIGHT = 9,
    CHARS_PER_ROW = 18
};

int rand_min_max(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

GsLine CreateLine(const struct vec2 begin, const struct vec2 end, unsigned char r, unsigned char g, unsigned char b, bool drawLine)
{
    GsLine line = {0};
    // Init values
    line.r = r;
    line.g = g;
    line.b = b;

    line.x[0] = begin.x;
    line.x[1] = end.x;

    line.y[0] = begin.y;
    line.y[1] = end.y;

    if(drawLine)
        GsSortLine(&line);

    return line;
}

void DrawLine(GsLine* line)
{
    GsSortLine(line);
}

void LoadCharTileSet(void){
    GfxSpriteFromFile("DATA\\SPRITES\\font_wh.TIM", &char_tile_set);
    char_tile_set_total_width = char_tile_set.w;
    char_tile_set_total_height = char_tile_set.h;
    char_tile_set_zero_u = char_tile_set.u;
    char_tile_set_zero_v = char_tile_set.v;

    char_tile_set.w = CHAR_WIDTH;
    char_tile_set.h = CHAR_HEIGHT;
}

//str must be null terminated
void DrawText(const char *str, unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b){
    size_t i = 0;

    char_tile_set.y = y;

    while(str[i] != '\0'){
        short c = str[i] - CHAR_FIRST;
        size_t pos = i++;

        if(c < 0 || c > 95) continue;

        char_tile_set.x = x + pos * CHAR_WIDTH;
        char_tile_set.u = char_tile_set_zero_u + CHAR_WIDTH*(c % CHARS_PER_ROW);
        char_tile_set.v = char_tile_set_zero_v + CHAR_HEIGHT*(c / CHARS_PER_ROW);
        char_tile_set.r = r;
        char_tile_set.g = g;
        char_tile_set.b = b;

        GfxSortSprite(&char_tile_set);
    }
}

