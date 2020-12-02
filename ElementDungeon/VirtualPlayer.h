#pragma once
#include <Zero.h>
class VirtualPlayer : public ZeroIScene
{
private:
    ZeroAnimation* playerAnimation;
    ZeroSprite* currentSprite;
public:
    VirtualPlayer();
    VirtualPlayer(int type);

    ~VirtualPlayer();
    void Update(float eTime);
    void Render();
    ZeroSprite* GetCurrentSprite();
};

