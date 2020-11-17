#pragma once
#include <Zero.h>
#include "Player.h"
class FootHolder :
    public ZeroIScene
{
private:
    list<ZeroVec*> l_Destination;
    list<ZeroVec*> l_Origin;
    list<ZeroSprite*> l_FootHolder;
    list<bool> l_Straight; // true 일 경우 origin에서 destinaton으로 가는중, false 일 경우 destination에서 origin으로 가는 중
    float moveSpeed;
    Player* player;
public:
    FootHolder(Player* player);
    ~FootHolder();
    void AddFootHolder(float originX, float originY, float destX, float destY);
    void Render();
    void Update(float eTime);
};

