#pragma once

#include "Gfx.h"
#include "Camera.hpp"
#include <psxgpu.h>
#include <stdint.h>
#include <stdbool.h>

class AnimatedSprite;

typedef void (*animation_end_cb)(AnimatedSprite &ani, void* args);

struct animation_config
{
    short w, h;
    uint32_t nticks;
    bool loop;
    uint8_t start_frame, end_frame;
    animation_end_cb cb;
};

struct box
{
    short x, y, w, h;
};

class AnimatedSprite
{
public:
    AnimatedSprite(const GsSprite &base_spr, const animation_config &c, const box *b, void *args) __attribute__((nonnull(1)));
    void Render(const Camera &cam);
    void SetPos(short x, short y);
    void GetPos(short &x, short &y);
    void getDimensions(short &w, short &h) const;
    void Repeat();
    unsigned char GetSprAttribute();
    void SetSprAttribute(unsigned char attr);
    GsSprite getSprite() const;

private:
    const animation_config c;
    GsSprite spr;
    const short base_w;
    const short tpage_div;
    const uint8_t start_tpage;
    const short start_u, start_v;
    short x, y, u, v, prev_u, prev_v;
    uint16_t ticks_c;
    uint8_t frames_c;
    bool finished, mirror;
    void *const args;
    const box *const b;

    void PreRender();
};
