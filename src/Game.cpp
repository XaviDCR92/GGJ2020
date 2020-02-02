/***************************************************************************//**
*
* \file     Game.cpp
*
* \brief    Game main module and entry point for game logic.
*
*******************************************************************************/

/* *****************************************************************************
 * Includes
 * ****************************************************************************/

#include "GlobalData.hpp"
#include "ParticleSystem.hpp"
#include "Game.hpp"
#include "Gfx.h"
#include "Menu.h"
#include "Level.hpp"
#include "Player.hpp"
#include "PlayerCopy.hpp"
#include "ArrayManager.hpp"
#include "Camera.hpp"
#include "Serial.h"
#include "Utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* *****************************************************************************
 * Defines
 * ***************************************************************************e*/

/* *****************************************************************************
 * Types definition
 * ****************************************************************************/

/* *****************************************************************************
 * Global variables definition
 * ****************************************************************************/

/* *****************************************************************************
 * Local variables definition
 * ****************************************************************************/

static Level level;

#include "AnimatedSprite.hpp"

/* *****************************************************************************
 * Local prototypes declaration
 * ****************************************************************************/

static void GameStart(const size_t players);
static void GameInit(const size_t players);
static void GameInitFiles(void);
static void GameLoop(const size_t players);

/* *****************************************************************************
 * Functions definition
 * ****************************************************************************/

/***************************************************************************//**
*
* \brief    Game logic entry point.
*
*******************************************************************************/
void Game(void)
{
    /* Execute game main menu and determine
     * next steps depending on its result. */
    size_t players;

    switch (Menu(&players))
    {
        case MENU_RESULT_GAME_START:
            /* Start gameplay given number of players. */
            GameStart(players);
            break;

        case MENU_RESULT_UNDEFINED:
            /* Fall through. */
        default:
            /* Invalid result. Restart game. */
            break;
    }
}

/***************************************************************************//**
*
* \brief    Initializes a level indicated by eSelectedLevel and
*           all game structures.
*
* \param    players
*               Number of active players.
*
*******************************************************************************/
static void GameStart(const size_t players)
{
    /* Game initialization. */
    GameInit(players);

    /* Gameplay. */
    GameLoop(players);
}

/***************************************************************************//**
*
* \brief    Initializes basic elements.
*
* \param    players
*               Number of active players.
*
*******************************************************************************/
static void GameInit(const size_t players)
{
    static bool initDone;

    (void)players;

    if (!initDone)
    {
        /* Load needed files. */
        GameInitFiles();

        /* Set first game initialization flag. */
        initDone = true;
    }
}

static GsSprite gatete;

static void GameInitFiles(void)
{
    Player::Init(&gatete);
    level.LoadAssets();
    level.Load("DATA\\LEVELS\\level.lvl");
    LoadCharTileSet();
}



static void GameLoop(const size_t players)
{
    Camera cam;
    static RainSystem rain;

    // Players
    Player player_array[2] =
    {
        {Player::PLAYER_ONE, players > Player::PLAYER_ONE, gatete},
        {Player::PLAYER_TWO, players > Player::PLAYER_TWO, gatete}
    };

    player_array[0].setPos((X_SCREEN_RESOLUTION >> 1) - 64, Y_SCREEN_RESOLUTION - 96);
    player_array[1].setPos((X_SCREEN_RESOLUTION >> 1) - 64, Y_SCREEN_RESOLUTION - 96);

    // Dirty hack, but I want PlayerCopy to inherit from GameEntity!
    PlayerCopy plcopy[2][16] =
    {
        {
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),

            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),

            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),

            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0]),
            PlayerCopy(player_array[0])
        },

        {
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),

            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),

            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),

            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1]),
            PlayerCopy(player_array[1])
        }
    };

    ArrayManager<Player> pl(ARRAY_SIZE(player_array), player_array);

    ArrayManager<PlayerCopy> pl0copies(ARRAY_SIZE(*plcopy), plcopy[0]);
    ArrayManager<PlayerCopy> pl1copies(ARRAY_SIZE(*plcopy), plcopy[1]);

    GlobalData data =
    {
        pl, // ArrayManager<Player>& Players;
        cam, // Camera
        {
            pl0copies,
            pl1copies
        },
        level
    };

    // cam.Shake(5, 10);

    if (player_array[0].isActive())
        pl0copies.StartFirst();

    if (player_array[1].isActive())
        pl1copies.StartFirst();

    while (GfxIsBusy())
        ;

    for (;;)
    {
        // GAME LOGIC

        // Update players
        pl.update(data);

        // Update camera
        short x;
        short y;
        player_array[0].getPos(x, y);
        cam.Update( x, y, level );

        // Update particle systems
        rain.Update(data);

        pl0copies.update(data);
        pl1copies.update(data);

        // Rendering
        while (GfxIsBusy())
            ;

        GfxClear();

        // Render map level
        level.Render(cam);

        DrawText("HOLI\0", 20, 20, 255, 255, 0);

        // Render players
        pl.render(cam);

        // Render particle systems
        rain.Render(cam);

        pl0copies.render(cam);
        pl1copies.render(cam);

        // Last call
        GfxDrawScene();
    }
}
