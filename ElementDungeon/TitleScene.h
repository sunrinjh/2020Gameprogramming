#pragma once
#include <Zero.h>
#include "include/ZeroIScene.h"
class TitleScene :
    public ZeroIScene
{
private:
    ZeroFont* titleText;
    ZeroSprite* startSprite, * exitSprite;
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN tAddr = {};
    string cMsg = "Client Send";

public:
    TitleScene();
    ~TitleScene();
    void Update(float eTime);
    void Render();
};

