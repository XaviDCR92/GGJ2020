#include "Game.h"
#include "Gfx.h"
#include <stdio.h>

static int GameCalculations(void)
{
    return 0;
}

static int GameGfx(void)
{
    return 0;
}

static void GameLoop(void)
{
    for (;;)
    {
        if (GameCalculations())
            break;

        while (GfxIsBusy())
            ;

        if (GameGfx())
            break;
    }
}

static void GameInit(void)
{
}

void Game(void)
{
    GameInit();

    while (GfxIsBusy())
        ;

    GameLoop();
}
