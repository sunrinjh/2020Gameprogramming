#pragma once
#include <Zero.h>
class Player :
    public ZeroIScene
{
private:
    ZeroAnimation* playerAnimation;
public:
    Player();
    //0Àº player 1Àº »¡°­, 2´Â ºÐÈ«, 3Àº ÆÄ¶û
    Player(int type);
    ~Player();
    void Render();
    void Update(float eTime);
    ZeroSprite* GetCurrentSprite();
};

