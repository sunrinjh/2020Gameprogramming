#pragma once
#include <Zero.h>
#include "Player.h"
#include "MapManager.h"
#include "PressurePlate.h"
#include "FootHolder.h"
#include "Door.h"
class Stage1 :
    public ZeroIScene
{
private:
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN tAddr = {};
    string cMsg = "Client Send";
    int currentRoom;
    ZeroSprite* black1;
    ZeroSprite* black2;
    ZeroSprite* black3;
    
    Player* player;
    MapManager* mapManager;
    PressurePlate* pressurePlate;
    FootHolder* footHolder;
    Door* door;
public:
    Stage1();
    ~Stage1();
    void Update(float eTime);
    void Render();
};

