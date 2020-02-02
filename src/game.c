#include "game.h"
#include "Gfx.h"
#include "pad.h"
#include "IO.h"
#include <psxgpu.h>
#include <stdio.h>
#include <string.h>

#define lengthof(a)                                 \
    _Generic(&(a),                                  \
        typeof (*a)**: (void)0,                     \
        typeof (*a)*const *: (void)0,               \
        default: sizeof (a) / sizeof ((a)[0]))

static GsSprite player_spr;
static GsSprite tile_spr;
static short orig_player_spr_w, orig_player_spr_h;
static short orig_tile_spr_w, orig_tile_spr_h, orig_tile_spr_u, orig_tile_spr_v;

#define TILE_SIZE 32
#define TILE_ROWS_COLUMNS 16
#define TILE_MAP_SIZE (TILE_ROWS_COLUMNS * TILE_ROWS_COLUMNS)

static uint8_t tilemap[TILE_MAP_SIZE];

static struct entity
{
    short x, y, w, h, u, v, u_init, v_init;
    unsigned int walk_ticks;
    size_t walk_i;
    enum
    {
        NORTH,
        SOUTH,
        WEST,
        EAST
    } direction;
} player;

static void player_direction(void)
{
    short v = player.v_init;

    enum
    {
        WALK_SPEED = 2
    };

    short x = player.x, y = player.y;

    if (pad_key_pressed(LEFT))
    {
        player.direction = WEST;
        x -= WALK_SPEED;
    }
    else if (pad_key_pressed(RIGHT))
    {
        player.direction = EAST;
        x += WALK_SPEED;
    }
    else if (pad_key_pressed(UP))
    {
        player.direction = NORTH;
        y -= WALK_SPEED;
    }
    else if (pad_key_pressed(DOWN))
    {
       player.direction = SOUTH;
       y += WALK_SPEED;
    }

    player.x = x;
    player.y = y;

    switch (player.direction)
    {
    case NORTH:
        break;

    case SOUTH:
        v += player.h * 2;
        break;

    case WEST:
        v += player.h * 3;
        break;

    case EAST:
        v += player.h;
        break;
    }

    player.v = v;
}

static void player_animation(void)
{
    if (pad_direction_key_pressed())
    {
        enum
        {
            ANIMATION_TICKS = 10
        };

        if (++player.walk_ticks >= ANIMATION_TICKS)
        {
            player.walk_ticks = 0;

            static const uint8_t pattern[] = {1, 2, 1, 0};

            if (++player.walk_i >= lengthof (pattern))
            {
                player.walk_i = 0;
            }

            player.u = player.u_init + (player.w * pattern[player.walk_i]);
        }
    }
    else
    {
        /* Still animation located at [1,y]. */
        player.u = player.u_init + player.w;
        player.walk_ticks = 0;
        player.walk_i = 0;
    }
}

static int game_update(void)
{
    pad_update();

    player_direction();
    player_animation();

    return 0;
}

static void tilemap_render(void)
{
    for (size_t i = 0; i < TILE_ROWS_COLUMNS; i++)
        for (size_t j = 0; j < TILE_ROWS_COLUMNS; j++)
        {
            const enum
            {
                TILE_FLOOR,

                MAX_TILES
            } tile = tilemap[j + (i * TILE_ROWS_COLUMNS)];

            static const struct
            {
                short u, v;
            } offsets[MAX_TILES] =
            {
                [TILE_FLOOR] = {0, 0}
            };

            tile_spr.u = orig_tile_spr_u + offsets[tile].u;
            tile_spr.v = orig_tile_spr_v + offsets[tile].v;
            tile_spr.x = TILE_SIZE * j;
            tile_spr.y = TILE_SIZE * i;

            GfxSortSprite(&tile_spr);
        }
}

static int game_render(void)
{
    tilemap_render();

    player_spr.x = player.x;
    player_spr.y = player.y;
    player_spr.u = player.u;
    player_spr.v = player.v;

    GfxSortSprite(&player_spr);

    return 0;
}

static void game_loop(void)
{
    for (;;)
    {
        if (game_update())
            break;

        while (GfxIsBusy())
            ;

        GsSortCls(0, 0, 0);

        if (game_render())
            break;

        GfxDrawScene();
    }
}

static void player_init(void)
{
    GfxSpriteFromFile("\\sprites\\charact.tim", &player_spr);

    orig_player_spr_w = player_spr.w;
    orig_player_spr_h = player_spr.h;

    player.w = 24;
    player.h = 32;

    player_spr.w = player.w;
    player_spr.h = player.h;
    player.u_init = player_spr.u;
    player.v_init = player_spr.v;
    player.u = player.u_init;
    player.v = player.v_init;
}

static void tiles_init(void)
{
    GfxSpriteFromFile("\\sprites\\dungeon.tim", &tile_spr);

    orig_tile_spr_w = tile_spr.w;
    orig_tile_spr_h = tile_spr.h;
    orig_tile_spr_u = tile_spr.u;
    orig_tile_spr_v = tile_spr.v;

    tile_spr.w = tile_spr.h = TILE_SIZE;
}

static int level_init(void)
{
    size_t sz;

    const uint8_t *const buf = IOLoadFile("\\levels\\level1.lvl", &sz);

    if (sz != sizeof tilemap || !buf)
    {
        printf("File size mismatch: got %d bytes, expected %d bytes\n", sz, sizeof tilemap);
        return 1;
    }

    memmove(tilemap, buf, sz);

    printf("tilemap ok\n");

    return 0;
}

static int game_init(void)
{
    int ret = 0;

    player_init();
    tiles_init();

    ret = level_init();

    return ret;
}

void game(void)
{
    if (game_init())
        return;

    while (GfxIsBusy())
        ;

    game_loop();
}
