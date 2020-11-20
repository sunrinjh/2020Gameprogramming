#pragma once
#include <Zero.h>
class Player :
    public ZeroIScene
{
private:
    ZeroAnimation* playerAnimation;
    void Move(float eTime);
    //movingDirection은 0123순으로 위 오른쪽 아랫쪽 왼쪽
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

