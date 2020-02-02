#pragma once

#include "Camera.hpp"
#include "GlobalData.hpp"

enum TileType{
    SCENARIO = 0,
    PLAYER = 1,
    PLAYER_COPY = 2,
    DAMAGE = 3
};

class GameEntity
{
public:
    explicit GameEntity(bool active);
    GameEntity(bool active, short w, short h);
    virtual void Update(GlobalData &gData);
    virtual void UpdateInactive(GlobalData &gData);
    virtual void Render(const Camera &cam) = 0;
    bool isActive() const;
    virtual void getPos(short &x, short &y) const;
    void setPos(short x, short y);
    TileType type;
    virtual void getDimensions(short &w, short &h) const;
    short getWidth() const;
    short getHeight() const;
    virtual bool Collides(const GameEntity &other, short x, short y) const;

protected:
    bool active;
    short x, y;
    short w, h;
};
