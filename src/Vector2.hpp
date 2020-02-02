#pragma once

#include <fixmath.h>

class Vector2
{
public:

    Vector2();
    Vector2(const int& initialX, const int& initialY);
    Vector2(const Fix16& initialX, const Fix16& initialY);
    Vector2(const Vector2& otherVector);

    Fix16 Distance() const;
    Fix16 DistanceSqrt() const;
    Fix16 DistanceToPoint(const Vector2& otherPoint) const;
    Fix16 DistanceToPointSqrt(const Vector2& otherPoint) const;

    Vector2 operator+=(const Vector2& rhs);
    bool operator!=(const Vector2& rhs) const;
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator-=(const Vector2& rhs);
    Vector2 operator*(const Fix16& rhs) const;
    Vector2 operator/=(const Fix16& rhs) const;
    Vector2 operator/(const Fix16& rhs) const;

    Fix16 X, Y;

};
