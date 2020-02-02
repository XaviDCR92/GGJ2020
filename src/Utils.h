#pragma once

#include <psxgpu.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct vec2 {
    int x;
    int y;
};

int rand_min_max(const int min, const int max);
GsLine CreateLine(const struct vec2 begin, const struct vec2 end, unsigned char r, unsigned char g, unsigned char b, bool drawLine);
void LoadCharTileSet(void);
void DrawText(const char *str, unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b);

#ifdef __cplusplus
}
#endif
