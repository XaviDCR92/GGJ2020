#pragma once

#include <stdio.h>

/* float clamp(const float min, const float max, const float value)
{
    if(value < min)
        return min;
    if(value > max)
        return max;
    return value;
} */

template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    if(hi < lo){
        printf("Bad clamp values");
        while(1);
    }
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

float lerp(const int a, const int b, const float t)
{
    if(t < 0 || t > 1)
    {
        printf("Bad lerp factor");
        while(1);
    }

    return a + (t * (b - a));
}