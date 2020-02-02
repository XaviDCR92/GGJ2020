#ifndef PAD_H
#define PAD_H

#include <stdbool.h>

enum Key
{
    L2,
    R2,
    L1,
    R1,
    TRIANGLE,
    CIRCLE,
    CROSS,
    SQUARE,
    SELECT,
    LANALOGB,
    RANALOGB,
    START,
    UP,
    RIGHT,
    DOWN,
    LEFT,

    MAX
};

void pad_update(void);
bool pad_key_pressed(enum Key key);
bool pad_single_press(enum Key key);
bool pad_released(enum Key key);
bool pad_direction_key_pressed(void);

#endif /* PAD_H */
