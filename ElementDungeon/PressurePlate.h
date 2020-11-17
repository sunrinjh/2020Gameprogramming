#pragma once
#include <Zero.h>
#include "Player.h"
class PressurePlate :
    public ZeroIScene
{
private:
    Player* player;
    list<ZeroAnimation*> list_PressurePlate;
    list<bool> list_PressurePlateState;
public:
    PressurePlate(Player* player);
    ~PressurePlate();
    void AddPressurePlate(float x, float y);
    list<bool> GetPressurePlateState();
    void SetPressurePlateState(int index, bool bValue);
    void Render();
    void Update(float eTime);
};

