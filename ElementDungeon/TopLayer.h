#pragma once
#include <Zero.h>
class TopLayer :
    public ZeroIScene
{
private:
    ZeroSprite* blackSprite;
    float timer = 0;
public:
    TopLayer();
    ~TopLayer();
    void Update(float eTime);
    void Render();
    void ShowBlackSprite(float timer);
};

