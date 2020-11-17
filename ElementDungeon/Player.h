#pragma once
#include <Zero.h>
class Player :
    public ZeroIScene
{
private:
    ZeroAnimation* upIdleAnimation;
    ZeroAnimation* rightIdleAnimation;
    ZeroAnimation* downIdleAnimation;
    ZeroAnimation* walkAnimation;
    ZeroAnimation* attackAnimation;
    float moveSpeed;
    float health;
    struct MovingPosition {
        bool top;
        bool buttom;
        bool left;
        bool right;
    };
    struct Moveable
    {
        bool top;
        bool buttom;
        bool left;
        bool right;
    };
    Moveable moveable = { true, };
    MovingPosition movingPosition = { true, false,false,false };
    void SetMovingPosition(bool bTop, bool bButtom, bool bLeft, bool bRight) {
        movingPosition.top = bTop;
        movingPosition.buttom = bButtom;
        movingPosition.left = bLeft;
        movingPosition.right = bRight;
    }
    
public:
    Player();
    ~Player();
    void Render();
    void Update(float eTime);
    void SetMoveableTop(bool bValue) {
        moveable.top = bValue;
    }
    void SetMoveableButtom(bool bValue) {
        moveable.buttom = bValue;
    }
    void SetMoveableLeft(bool bValue) {
        moveable.left = bValue;
    }
    void SetMoveableRight(bool bValue) {
        moveable.right = bValue;
    }
    Moveable GetMoveable() {
        return moveable;
    }
    ZeroSprite* GetCurrentSprite() {
        return upIdleAnimation->GetCurrentSprite();

    }
};

