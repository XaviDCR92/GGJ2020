#ifndef PAD_H
#define PAD_H

/*******************************************************************//**
*
* @file     Pad.h
*
* @author   Xavier Del Campo
*
* @brief    Include file for Pad module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include <stdint.h>
#include <stdbool.h>
#include <psx.h>

/* *************************************
 * Defines
 * *************************************/

/* *************************************
 * Public types definition
 * *************************************/

class Pad
{
    public:
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

        Pad(const unsigned int _pad_n);
        void handler(void);
        bool keyPressed(const enum Key key);
        bool singlePress(const enum Key key);
        bool released(const enum Key key);
        psx_pad_types getType(void);

    private:
        enum
        {
            RAW_DATA_SIZE = 21
        };

        uint8_t rawData[RAW_DATA_SIZE];
        psx_pad_state prev, state;
        const unsigned int pad_n;
};

#endif /* PAD_H */
