#ifndef MENU_H
#define MENU_H

/*******************************************************************//**
*
* \file     Menu.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Menu module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Game.hpp"
#include <stddef.h>
#include <psxgpu.h>

/* *************************************
 * Defines
 * *************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* *************************************
 * Public types definition
 * *************************************/

enum tMenuResult
{
    MENU_RESULT_UNDEFINED,
    MENU_RESULT_EDITOR,
    MENU_RESULT_GAME_START
};

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

enum tMenuResult Menu(size_t* players);
enum tLevel MenuGetSelectedLevel(void);
size_t MenuGetSelectedPlayers(void);

#ifdef __cplusplus
}
#endif

#endif /* MENU_H */
