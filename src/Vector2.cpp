#include "Vector2.hpp"

Vector2::Vector2() :
    X(0),
    Y(0)
{
}

Vector2::Vector2(const int& initialX, const int& initialY) :
    X(Fix16((int16_t)initialX)),
    Y(Fix16((int16_t)initialY))
{
}

Vector2::Vector2(const Fix16& initialX, const Fix16& initialY) :
    X(initialX),
    Y(initialY)
{
}

Vector2::Vector2(const Vector2& otherVector)
{
    X = otherVector.X;
    Y = otherVector.Y;
}

Fix16 Vector2::Distance() const
{
    return Fix16(fix16_sqrt(DistanceSqrt()));
}

Fix16 Vector2::DistanceSqrt() const
{
    return X*X + Y*Y;
}

Fix16 Vector2::DistanceToPoint(const Vector2& otherPoint) const
{
    return (otherPoint - *this).Distance();
}

Fix16 Vector2::DistanceToPointSqrt(const Vector2& otherPoint) const
{
    return Vector2(otherPoint - *this).DistanceSqrt();
}

Vector2 Vector2::operator+=(const Vector2& rhs)
{
    X = X+rhs.X;
    Y = Y+rhs.Y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return Vector2(X+rhs.X, Y+rhs.Y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return Vector2(X-rhs.X, Y - rhs.Y);
}

Vector2 Vector2::operator-=(const Vector2& rhs)
{
    X = X - rhs.X;
    Y = Y - rhs.Y;
    return *this;
}

Vector2 Vector2::operator*(const Fix16& rhs) const
{
    return Vector2(X * rhs, Y * rhs);
}

Vector2 Vector2::operator/=(const Fix16& rhs) const
{
    return Vector2(X / rhs, Y / rhs);
}

bool Vector2::operator!=(const Vector2& rhs) const
{
    return (X != rhs.X) || (Y != rhs.Y);
}

Vector2 Vector2::operator/(const Fix16& rhs) const
{
    return Vector2(X / rhs, Y / rhs);
}
