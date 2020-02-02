#pragma once

class Player;
class Camera;
class PlayerCopy;
template<class T>
class ArrayManager;
class Level;

#define ARRAY_SIZE(a)   (sizeof (a) / sizeof (a[0]))

struct GlobalData
{
    ArrayManager<Player> &Players;
    Camera &camera;
    struct
    {
        ArrayManager<PlayerCopy> &plcopies;
    } pl[2];
    Level &level;
};
