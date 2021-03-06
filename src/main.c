/*******************************************************************//**
*
* \file     main.c
*
* \brief    Application entry point.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "SystemInit.h"
#include "game.h"

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

/* *************************************
 * Functions definition
 * *************************************/

/*******************************************************************//**
*
* \brief    Application entry point.
*
* \return   Error code 0 (never returned).
*
************************************************************************/
int main(void)
{
    /* Initialize game libs and HW. */
    SystemInit();

    /* Main loop. */
    for (;;)
    {
        /* Execute the game. */
        game();
    }

    return 0;
}
