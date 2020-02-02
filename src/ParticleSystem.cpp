
#include "ParticleSystem.hpp"
#include "Utils.h"
#include "Gfx.h"
#include "stdlib.h"

ParticleSystem::ParticleSystem()
{

}

RainSystem::RainSystem()
{
    Init();
}

void RainSystem::Init()
{
    for (int i = 0; i < N_PARTICLES; i++)
    {
        sParticle p = sParticle();
        p.X = rand() % X_SCREEN_RESOLUTION + 1;
        p.Y = rand() % Y_SCREEN_RESOLUTION + 1;
        p.accX = 1;
        p.accY = 3;
        p.speed = rand() % 2 + 1;
        p.lifespan = rand() % 150 + 50;
        p.ttl = 0;

        particles[i] = p;
    }
}

void RainSystem::Render(const Camera &cam)
{
    (void)cam;
    static int count = 0;
    count++;

    for (int i = 0; i < N_PARTICLES; i++)
    {
        sParticle p = particles[i];

        short x = p.X;
        short y = p.Y;

        cam.getPosition(x, y);

        x = (x + count) % X_SCREEN_RESOLUTION; 

        vec2 begin = vec2();
        begin.x = x;
        begin.y = y;

        vec2 end = vec2();
        end.x = begin.x + 2;
        end.y = begin.y + 5;

        GsLine line = CreateLine(begin, end, 180, 200, 245, true);
        (void)line;
    }
}

void RainSystem::Update(GlobalData &gData)
{
    (void)gData;

    for (int i = 0; i < N_PARTICLES; i++)
    {
        sParticle * p = &particles[i];

        // Use acceleration and speed here
        p->X += p->accX * p->speed;
		p->Y += p->accY * p->speed;
		p->ttl++;

		// Reset position once they reach the limit
        // TO DO
        if(p->ttl > p->lifespan || p->Y < 0)
        {
            p->X = rand() % X_SCREEN_RESOLUTION + 1;
            p->Y = rand() % Y_SCREEN_RESOLUTION + 1;
            p->ttl = 0;
        }


    }
}
