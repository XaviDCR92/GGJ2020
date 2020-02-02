#include "Camera.hpp"
#include "Math.hpp"
#include "Level.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <psxgpu.h>

int tmpShakingX = 0;

Camera::Camera() :
    X(X_SCREEN_RESOLUTION/2),
    Y(Y_SCREEN_RESOLUTION/2)
{
    Default();
}

void Camera::Default()
{
    shake_elapsed = 0;
	shake_length = 0;
	shake_amount = 0;
}

void Camera::getPosition(short& x, short& y) const
{
    x += ((X_SCREEN_RESOLUTION >> 1) - 32) - X;
    y += (Y_SCREEN_RESOLUTION - 64) - Y; // Camera is not centered in Y
}

void Camera::Update(const int x, const int y, const Level& level)
{
    LookAt( x, y, level );

    if (shake_length > 0)
	{
		int shakeX = rand() % (shake_amount * 2) - shake_amount;
		int shakeY = rand() % (shake_amount * 2) - shake_amount;

        X += shakeX;
		Y += shakeY;

		shake_length--;
	}
}

void Camera::Shake(unsigned int amount, unsigned int length)
{
    if (shake_length > 0)
    {
        printf("Already shaking camera!");
        return;
    }

    // Assign shaking values
    shake_amount = amount;
	shake_length = length;

    tmpShakingX = X;
}

void Camera::LookAt(const int x, const int y, const Level& level)
{
	short mapWidth;
    short mapHeight;

    level.GetDimensions(mapWidth, mapHeight);

	int marginX0 = (X_SCREEN_RESOLUTION >> 1) - 32;
    int marginX1 = mapWidth - (X_SCREEN_RESOLUTION >> 1) - 32;

    Y = y;

    if(shake_length > 0)
    {
        if(x <= marginX0)
        {
            X = marginX0;
        }else if (x >= marginX1)
        {
            X = marginX1;
        }else
        {
            X = x;
        }
        return;
    }

    if(x >= marginX0 && x <= marginX1)
    {
        X = x;
    }
}
