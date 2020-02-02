/*******************************************************************//**
*
* \file     Menu.c
*
* \brief    Main menu handling.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Menu.h"
#include "Game.hpp"
#include "stdbool.h"
#include "Gfx.h"
#include <psxgpu.h>
#include <stdio.h>
#include <psx.h>

/* *************************************
 * Defines
 * *************************************/

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

static bool MenuInit(void);
static enum tMenuResult MenuLoop(size_t* players);

/* *************************************
 * Functions definition
 * *************************************/

/*******************************************************************//**
*
* \brief    Reportedly, this function initializes the main menu.
*
************************************************************************/
static bool MenuInit(void)
{
    static bool init;

    if (!init)
    {

        init = true;
    }

    return true;
}

/*******************************************************************//**
*
* \brief    Game logic entry point.
*
************************************************************************/
enum tMenuResult Menu(size_t* players)
{
    if (MenuInit())
    {
        return MenuLoop(players);
    }
    else
    {
        /* An error has happened while
         * initialising main menu. */
    }

    /* This result will be returned in case
     * menu initialization fails. */
    return MENU_RESULT_GAME_START;
}

static enum tMenuResult MenuLoop(size_t* players)
{
    *players = 1;

    return MENU_RESULT_GAME_START;
}

/*******************************************************************//**
*
* \brief    This function returns level selected by user.
*
* \return   \ref tLevel selected by user.
*
************************************************************************/
enum tLevel MenuGetSelectedLevel(void)
{
    return LEVEL_1;
}

size_t MenuGetSelectedPlayers(void)
{
    return 1;
}
