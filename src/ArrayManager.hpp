#pragma once

#include "Camera.hpp"
#include "GameEntity.hpp"
#include "PlayerCopy.hpp"

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

struct GlobalData;

template<class T>
class ArrayManager
{
public:
    ArrayManager(const size_t size, T *const a) __attribute__((nonnull)) :
        mSize(size),
        mLast(0),
        mArray(a)
    {
        if (!size)
        {
            printf("Invalid given information\n");
            while (1);
        }
    }

    bool areAllInactive(void)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T &t = mArray[i];

            if (t.isActive())
            {
                return false;
            }
        }

        return true;
    }

    T *AddElement(const T &element)
    {
        for (size_t i = mLast + 1; ; i++)
        {
            if (i >= mSize)
            {
                i = 0;
            }

            T &t = mArray[i];

            if (!t.isActive())
            {
                t = element;

                t.setActive(true);
                return &t;
            }

            if (i == mLast)
            {
                break;
            }
        }

        return nullptr;
    }

    void update(GlobalData &data)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T &t = mArray[i];

            if (t.isActive())
                t.Update(data);
            else
                t.UpdateInactive(data);
        }
    }

    T *get(const size_t i) const
    {
        if (i < mSize)
        {
            return &mArray[i];
        }

        return nullptr;
    }

    size_t count(void) const
    {
        return mSize;
    }

    void render(const Camera &cam)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T &t = mArray[i];

            if (t.isActive())
            {
                t.Render(cam);
            }
        }
    }

    void setActive(const bool state)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            T &t = mArray[i];

            t.setActive(state);
        }
    }

    bool isSolid() const
    {
        return solid;
    }

    GameEntity* collides(T *const t, const short x, const short y) __attribute__((nonnull))
    {
        GameEntity* out = nullptr;
        for (size_t i = 0; i < mSize; i++)
        {
            if (&mArray[i] != t)
            {
                if (t->Collides(mArray[i], x, y))
                    return &mArray[i];
            }
            else
            {
                // Avoid calculating collision with itself
            }
        }

        return out;
    }

    bool StartFirst()
    {
        for (size_t i = 0; i < mSize; i++)
        {
            if (!mArray[i].isActive())
            {
                mArray[i].StartTimer();
                return true;
            }
        }

        return false;
    }

    bool TriggerFirst(GlobalData &gData)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            if (!mArray[i].isActive())
            {
                mArray[i].Trigger(gData);
                return true;
            }
        }

        return false;
    }

private:
    const size_t mSize;
    size_t mLast;
    T *const mArray;
    bool solid;
};
