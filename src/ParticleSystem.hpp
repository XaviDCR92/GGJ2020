#pragma once

#include "GlobalData.hpp"
#include "Camera.hpp"

#define N_PARTICLES 200

struct sParticle{

    int X;
    int Y;
    
    int lifespan;
    int ttl;
    int speed;

    int accX;
    int accY;
} ;

class ParticleSystem
{
public:
    
    ParticleSystem();

    virtual void Init() = 0;
    virtual void Render(const Camera &cam) = 0;
    virtual void Update(GlobalData &gData) = 0;

protected:
    sParticle particles[N_PARTICLES];
};

class RainSystem : public ParticleSystem
{
public:
    
    RainSystem();

    void Init();
    void Render(const Camera &cam);
    void Update(GlobalData &gData);

private:
};