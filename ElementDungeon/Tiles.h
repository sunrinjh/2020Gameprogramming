#pragma once
#include <Zero.h>
class Tiles :
    public ZeroIScene
{

public:
    virtual enum class Type {
        FOOD, WALL, POWERUP
    };
    Type type;
    virtual void Render();
    virtual void Update(float eTime);
    virtual bool GetEaten();
    virtual void SetEaten(bool bValue);
    virtual ZeroSprite* GetCurrentSprite();
};

