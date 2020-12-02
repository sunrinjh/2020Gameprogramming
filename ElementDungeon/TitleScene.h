#pragma once
#include <Zero.h>
#include "include/ZeroIScene.h"
class TitleScene :
    public ZeroIScene
{
private:
    ZeroSprite* createSprite, * joinSprite, * backgroundSprite, * exitSprite, * backboard;
    ZeroAnimation* pacmanAnimation;
    ZeroFont* exitText;
    bool exitState[2] = { false,false };
public:
    TitleScene();
    ~TitleScene();
    void Update(float eTime);
    void Render();
};

