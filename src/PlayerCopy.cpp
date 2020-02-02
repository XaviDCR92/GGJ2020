#include "PlayerCopy.hpp"
#include "GameEntity.hpp"
#include "Player.hpp"
#include "Utils.h"
#include <stdlib.h>
#include <stddef.h>

#define MIN_SPAWN_TIME 500
#define MAX_SPAWN_TIME 1500

PlayerCopy::PlayerCopy(const Player &pl) :
    GameEntity(false, pl.getWidth(), pl.getHeight()),
    pl(pl),
    spawn_timer(0),
    prev_spawn_timer(0),
    timer_running(false)
{
}

void PlayerCopy::StartTimer()
{
    spawn_timer = rand_min_max(MIN_SPAWN_TIME, MAX_SPAWN_TIME);
    timer_running = true;
    printf("Started copy timer with %d ticks\n", spawn_timer);
}

void PlayerCopy::Trigger(GlobalData &gData)
{
    if (pl.isActive())
    {
        const short *last_x_buf, *last_y_buf;
        const GsSprite *spr_buf;

        pl.GetLastMovements(&last_x_buf, &last_y_buf, &spr_buf);

        if (last_x_buf && last_y_buf && spr_buf)
        {
            if (spr_buf)
            {
                unsigned int retries = 0;
                bool success = true;
                size_t i;
                short x, y;

                do
                {
                    if (retries >= LAST_MOVEMENTS_BUF_SIZE)
                    {
                        success = false;
                        break;
                    }

                    i = rand_min_max(0, LAST_MOVEMENTS_BUF_SIZE - 1);
                    x = last_x_buf[i];
                    y = last_y_buf[i];

                    retries++;
                } while (!x && !y);

                if (success)
                {
                    const GsSprite &s = spr_buf[i];
                    spr = s;
                    printf("spr.x = %d, spr.y = %d\n", spr.x, spr.y);
                    setPos(x, y);
                    printf("x = %d, y = %d\n", x, y);
                    active = true;
                }
                else
                {
                    printf("Could not find any recorded position!\n");
                }
            }
        }

        gData.pl[pl.getId()].plcopies.StartFirst();
    }
}

void PlayerCopy::UpdateInactive(GlobalData &gData)
{
    if (timer_running && pl.isActive())
    {
        if (spawn_timer)
        {
            spawn_timer--;

            if (spawn_timer < 20 && prev_spawn_timer >= 20)
            {
                gData.camera.Shake(rand_min_max(5,15), 20);
            }
        }
        else if (!active)
            // Create copy!
            Trigger(gData);

        prev_spawn_timer = spawn_timer;
    }
}

void PlayerCopy::Render(const Camera &cam)
{
    if (active)
    {
        getPos(spr.x, spr.y);
        cam.getPosition(spr.x, spr.y);

        GfxSortSprite(&spr);
    }
}
