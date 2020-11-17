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
    list<bool> l_Straight; // true �� ��� origin���� destinaton���� ������, false �� ��� destination���� origin���� ���� ��
    float moveSpeed;
    Player* player;
public:
    FootHolder(Player* player);
    ~FootHolder();
    void AddFootHolder(float originX, float originY, float destX, float destY);
    void Render();
    void Update(float eTime);
};

