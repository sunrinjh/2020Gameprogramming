#pragma once
#include <Zero.h>
class Player :
    public ZeroIScene
{
private:
    ZeroAnimation* playerAnimation;
public:
    Player();
    //0�� player 1�� ����, 2�� ��ȫ, 3�� �Ķ�
    Player(int type);
    ~Player();
    void Render();
    void Update(float eTime);
    ZeroSprite* GetCurrentSprite();
};

