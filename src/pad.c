#include "pad.h"
#include "Timers.h"
#include <psxpad.h>
#include <psx.h>
#include <stdint.h>
#include <stdlib.h>

static psx_pad_state state, prev;
static uint32_t timer;

bool pad_key_pressed(const enum Key key)
{
    static bool entered;

    if (!entered)
    {
        /* Calculate random seed based on timer counter values. */
        const int rootcounters = RootCounter1Get() ^ RootCounter2Get();

        /* Set random seed based on timer counters. */
        srand(rootcounters ^ ~timer);

        entered = true;
    }

    return state.buttons & (1 << key);
}

bool pad_single_press(const enum Key key)
{
    return pad_key_pressed(key) && !(prev.buttons & (1 << key));
}

bool pad_released(const enum Key key)
{
    return !pad_key_pressed(key) && (prev.buttons & (1 << key));
}

bool pad_direction_key_pressed(void)
{
    return pad_key_pressed(LEFT) ||
        pad_key_pressed(RIGHT) ||
        pad_key_pressed(UP) ||
        pad_key_pressed(DOWN);
}

void pad_update(void)
{
    enum
    {
        RAW_DATA_SIZE = 21
    };

    prev = state;

    static uint8_t raw_data[RAW_DATA_SIZE];

    pad_read_raw(0, raw_data);
    PSX_PollPad_Fast_Ex(raw_data, &state);
}
