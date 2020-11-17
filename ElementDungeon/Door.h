#pragma once
#include <Zero.h>
#include "Player.h"
class Door :
    public ZeroIScene
{
private:
    bool teleport = false;
    float teleportTimer = 0;
    ZeroSprite* blackSprite;
    Player* player;
    list<bool> l_DoorLockState;
    list<ZeroAnimation*> l_DoorSprite;
    list<ZeroVec*> l_DestinationVec;
public:
    Door(Player* player);
    ~Door();
    void Update(float eTime);
    void Render();
    void AddDoor(float x, float y, float dx, float dy);
    list<bool> GetDoorLockState() {
        return l_DoorLockState;
    }
    void SetDoorLockState(int index, bool doorLockState);
    
};

