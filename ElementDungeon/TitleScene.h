#pragma once
#include <Zero.h>
#include "include/ZeroIScene.h"
class TitleScene :
    public ZeroIScene
{
private:
    ZeroFont* titleText;
    ZeroSprite* startSprite, * exitSprite;

public:
    TitleScene();
    ~TitleScene();
    void Update(float eTime);
    void Render();
};

