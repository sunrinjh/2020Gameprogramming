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
    Direction direction;
    SocketClient* socketClient;
    Player* player;
    VirtualPlayer* virtualPlayer;
    int playerLocation[2] = { 1,1 };
    vector<Tiles*> tiles;
    byte map[16][16] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
        {1,0,0,0,1,1,0,1,1,0,1,0,0,0,0,1},
        {1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1},
        {1,0,1,0,1,1,0,1,1,0,1,0,0,0,0,1},
        {1,0,0,0,1,1,0,1,1,0,1,1,1,1,0,1},
        {1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1},
        {1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

    };
public:
    
    TestScene();
    ~TestScene();
    void Update(float eTime);
    void Render();
    ZeroVec MoveTowards(ZeroVec* pos, float maxDistanceDelta);
};

