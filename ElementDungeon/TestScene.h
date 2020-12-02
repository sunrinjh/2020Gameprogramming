#pragma once
#include <Zero.h>
#include "SocketClient.h"
#include "Player.h"
#include "VirtualPlayer.h"
#include "Tiles.h"
class TestScene :
    public ZeroIScene
{
private:
    enum class Direction {
        RIGHT, LEFT, UP, DOWN
    };
    Direction directionBuffer;
    Direction direction;
    float directionBufferTimer = 1;
    Player* player;
    float moveSpeed;
    bool isMoveable;
    int foodCounter;
    int playerHealth;
    VirtualPlayer* virtualPlayer;
    float godModTimer;
    int playerLocation[2] = { 1,1 };
    int playerNumber = 0;
    vector<Tiles*> tiles;
    byte map[16][22] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,1,0,1,1,1,1,0,0,1,1,0,1},
        {1,0,1,1,1,1,0,1,0,0,1,0,1,1,1,0,0,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,0,1,0,0,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1},
        {1,0,1,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
        {1,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,1},
        {1,0,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1},
        {1,0,1,1,0,1,0,0,0,0,1,0,1,0,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

    };
public:
    
    TestScene();
    ~TestScene();
    void Update(float eTime);
    void Render();
    void Move(float eTime);
    void TurnAnimation(float x,float y,float vx,float vy);
    void EatFood();
    ZeroVec MoveTowards(ZeroVec* pos, float maxDistanceDelta);
};

