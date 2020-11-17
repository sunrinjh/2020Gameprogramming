#pragma once
#include <Zero.h>
#include "Player.h"
class Lever :
    public ZeroIScene
{
private:
    Player* player;
    list<ZeroAnimation*> list_Lever;
    list<bool> list_LeverState;
public:
    Lever(Player* player);
    ~Lever();
    void AddLever(float x, float y);
    list<bool> GetLeverState();
    void SetLeverState(int index, bool bValue);
    void Render();
    void Update(float eTime);

};

