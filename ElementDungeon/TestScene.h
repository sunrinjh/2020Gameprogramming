#pragma once
#include <Zero.h>
#include "Player.h"
#include "MapManager.h"
#include "PressurePlate.h"
#include "FootHolder.h"
#include "Door.h"
class TestScene :
    public ZeroIScene
{
private:
    Player* player;
    MapManager* mapManager;
    PressurePlate* pressurePlate;
    FootHolder* footHolder;
    Door* door;
public:
    TestScene();
    ~TestScene();
    void Update(float eTime);
    void Render();
};

