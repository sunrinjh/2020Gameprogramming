#pragma once
#include <Zero.h>
class Player :
    public ZeroIScene
{
private:
    ZeroAnimation* playerAnimation;
    void Move(float eTime);
    //movingDirection�� 0123������ �� ������ �Ʒ��� ����
    int movingDirection;
    int movingDirectionBuffer;
    float moveSpeed;
public:
    Player();
    ~Player();
    void Render();
    void Update(float eTime);
    ZeroSprite* GetCurrentSprite();
    void SetPlayerPos(float x, float y);
    void SetPlayerPos(ZeroVec vec);
};

