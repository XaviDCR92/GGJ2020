#include "GameEntity.hpp"

GameEntity::GameEntity(const bool active) :
    active(active),
    x(0),
    y(0),
    w(0),
    h(0)
{
}

GameEntity::GameEntity(const bool active, const short w, const short h) :
    active(active),
    x(0),
    y(0),
    w(w),
    h(h)
{
}

void GameEntity::Update(GlobalData &gData)
{
    (void)gData;
}

void GameEntity::UpdateInactive(GlobalData &gData)
{
    (void)gData;
}

bool GameEntity::isActive() const
{
    return active;
}

void GameEntity::getPos(short &x, short &y) const
{
    x = this->x;
    y = this->y;
}

void GameEntity::setPos(const short x, const short y)
{
    this->x = x;
    this->y = y;
}

void GameEntity::getDimensions(short &w, short &h) const
{
    w = this->w;
    h = this->h;
}

short GameEntity::getWidth() const
{
    return w;
}

short GameEntity::getHeight() const
{
    return h;
}

bool GameEntity::Collides(const GameEntity &other, short x, short y) const
{
    if (active && other.isActive())
    {
// Here I have used an old macro that I found on nextvolume's source code for "A Small Journey", IIRC.
// Totally fool-proof, so I dint' want to complicate things!
#define check_bb_collision(x1,y1,w1,h1,x2,y2,w2,h2) (!( ((x1)>=(x2)+(w2)) || ((x2)>=(x1)+(w1)) || \
                                                        ((y1)>=(y2)+(h2)) || ((y2)>=(y1)+(h1)) ))

        short ox, oy, ow, oh;
        other.getPos(ox, oy);
        other.getDimensions(ow, oh);

        return check_bb_collision(x, y, w, h, ox, oy, ow, oh);
    }

    return false;
}
