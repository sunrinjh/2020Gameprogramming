#pragma once
#include <Zero.h>
#include "include/ZeroIScene.h"
#include "Server.h"
class TitleScene :
    public ZeroIScene
{
private:
    ZeroFont* titleText;
    ZeroSprite* startSprite, * exitSprite;
    Server* server;
public:
    TitleScene();
    ~TitleScene();
    void Update(float eTime);
    void Render();
};

