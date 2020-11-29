#pragma once
#include <Zero.h>
class VirtualPlayer : public ZeroIScene
{
private:
    ZeroAnimation* playerAnimation;
    
public:
    VirtualPlayer();
    ~VirtualPlayer();
    void Update(float eTime);
    void Render();
};

