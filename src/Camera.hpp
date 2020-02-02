#pragma once

#include "Vector2.hpp"

class Player;
class Level;

class Camera
{
public:
    
    Camera();

    void Default();
    
    void getPosition(short& x, short& y) const;

    void Update(const int x, const int y, const Level& level);
    void Shake(unsigned int amount, unsigned int length);
    void LookAt(const int x, const int y, const Level& level);

private:
    
    int X;
    int Y;

    float smooth_value; // ojo con el float

    unsigned int shake_elapsed;
	unsigned int shake_length;
	unsigned int shake_amount;

};
