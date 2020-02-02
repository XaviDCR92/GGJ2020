#pragma once

#include "GameEntity.hpp"
#include "Player.hpp"
#include "GlobalData.hpp"
#include "Camera.hpp"

class PlayerCopy : public GameEntity
{
public:
    explicit PlayerCopy(const Player &pl);
    void UpdateInactive(GlobalData &gData) override;
    void Render(const Camera &cam) override;
    void StartTimer();
    void Trigger(GlobalData &gData);

private:
    const Player &pl;
    GsSprite spr;
    unsigned int spawn_timer, prev_spawn_timer;
    bool timer_running;
};
