#ifndef PLAYER_H
#define PLAYER_H

/*******************************************************************//**
*
* \file     Player.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Player module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Pad.hpp"
#include "Gfx.h"
#include "ArrayManager.hpp"
#include "GameEntity.hpp"
#include "GlobalData.hpp"
#include "AnimatedSprite.hpp"
#include <stddef.h>
#include <stdbool.h>
#include <psxgpu.h>

enum pl_state
{
    IDLE,
    RUNNING,
    JUMPING,
    FALLING,
    ROLLING,
    DEAD,
};

enum interactions
{
    TIME_FRAG,
    COPY,

    MAX_INTERACTIONS
};

enum pl_direction
{
    LEFT,
    RIGHT
};

struct sInteraction
{
    unsigned int uid;
    bool active;
    int x;
    int y;
    int size;   // compute later the box using first
                // point and box size

};

#define PLAYER_SZ                   ((short)64)
#define LAST_MOVEMENTS_BUF_SIZE     16

class Player : public GameEntity
{

public:
    enum playern
    {
        PLAYER_ONE,
        PLAYER_TWO
    };

    Player(const playern player_n, const bool active, const GsSprite &base_spr);

    static void Init(GsSprite *spr);
    static sInteraction enabled_interactions[MAX_INTERACTIONS];

    void Update(GlobalData &gData) override;
    void Render(const Camera &camera) override;
    void getPos(short &x, short &y) const override;
    enum playern getId() const;

    void CheckInteractions(GlobalData &gData);

    void SetState(pl_state state);
    void Hit(unsigned int hp_loss);
    void Push(int x, int y);
    void Reset(){/*todo*/}
    void GetLastMovements(const short **last_x_buf, const short **last_y_buf, const GsSprite **spr_buf) const __attribute__((nonnull));

private:
    const enum playern mId;
    Pad pad;
    pl_state state, prev_state;
    pl_direction dir;
    AnimatedSprite running, jumping, idle, rolling, falling, dead;
    unsigned int hp;
    short last_x[LAST_MOVEMENTS_BUF_SIZE], last_y[LAST_MOVEMENTS_BUF_SIZE];
    GsSprite last_sprites[LAST_MOVEMENTS_BUF_SIZE];
    box b;
    unsigned int record_timer;

    void UpdatePosition(short &new_x, short &new_y);
    void UpdateCollision(GlobalData &gData, short new_x, short new_y);
    unsigned int GetRecordTime();
    AnimatedSprite &GetAnimation();
};

#endif /* PLAYER_H */
