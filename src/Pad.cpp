/*******************************************************************//**
*
* \file     Pad.c
*
* \author   Xavier Del Campo
*
* \brief    Implementation of Pad module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Player.hpp"
#include "Pad.hpp"
#include "Timers.h"
#include <psx.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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

static uint64_t timer;

/* *************************************
 *  Local prototypes declaration
 * *************************************/

/* *************************************
 * Functions definition
 * *************************************/

Pad::Pad(const unsigned int _pad_n) :
    rawData{0},
    prev{},
    state{},
    pad_n(_pad_n)
{
}

void Pad::handler(void)
{
    timer++;

    prev = state;
    pad_read_raw(pad_n, rawData);
    PSX_PollPad_Fast_Ex(rawData, &state);
}

psx_pad_types Pad::getType(void)
{
    return static_cast<psx_pad_types>(state.type);
}

bool Pad::keyPressed(const enum Pad::Key key)
{
    static bool entered;

    if (not entered)
    {
        /* Calculate random seed based on timer counter values. */
        const int rootcounters = RootCounter1Get() ^ RootCounter2Get();

        /* Set random seed based on timer counters. */
        srand(rootcounters ^ ~timer);

        entered = true;
    }

    return state.buttons & (1 << key);
}

bool Pad::singlePress(const enum Pad::Key key)
{
    return keyPressed(key) && !(prev.buttons & (1 << key));
}

bool Pad::released(const enum Pad::Key key)
{
    return !keyPressed(key) && (prev.buttons & (1 << key));
}
