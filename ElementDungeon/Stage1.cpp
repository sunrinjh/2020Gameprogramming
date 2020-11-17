#include "stdafx.h"
#include "Stage1.h"

Stage1::Stage1()
{
	currentRoom = 1;
	player = new Player();
	PushScene(player);
	player->SetPos(484, 1820);
	
	black1 = new ZeroSprite("Resources/Sprites/Stage1/Black1.png");
	black2 = new ZeroSprite("Resources/Sprites/Stage1/Black2.png");
	black3 = new ZeroSprite("Resources/Sprites/Stage1/Black3.png");
	PushScene(black1);
	PushScene(black2);
	PushScene(black3);

	mapManager = new MapManager(player, "Resources/Sprites/Stage1/Stage1.png", "Resources/Sprites/Stage1/Stage1_wall.png");
	PushScene(mapManager);

	pressurePlate = new PressurePlate(player);
	
	pressurePlate->AddPressurePlate(217-30, 1940-31);

	PushScene(pressurePlate);

	door = new Door(player);
	door->AddDoor(480-32, 1640-26, 500,1400);

	PushScene(door);

	footHolder = new FootHolder(player);

	ZeroApp->GetDevice()->ShowCursor(false);

	ZeroCameraMgr->SetCameraOn();
	ZeroCameraMgr->SetScreen(3840, 2160);
	ZeroCameraMgr->SetTarget(player);

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(1234);
	tAddr.sin_addr.s_addr = inet_addr("192.168.0.4");
	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	send(hSocket, cMsg.c_str(), cMsg.length(), 0);
	char cBuffer[1024] = {};
	recv(hSocket, cBuffer, 1024, 0);
	
}

Stage1::~Stage1()
{

}

void Stage1::Update(float eTime)
{
	cMsg = to_string(player->Pos().x) + " , " + to_string(player->Pos().y) ;
	send(hSocket, cMsg.c_str(), cMsg.length(), 0);
	ZeroIScene::Update(eTime);
	mapManager->Update(eTime);
	footHolder->Update(eTime);
	pressurePlate->Update(eTime);
	door->Update(eTime);
	player->Update(eTime);
	list<bool> pressurePlateState = pressurePlate->GetPressurePlateState();
	list<bool>::iterator firstDoor = pressurePlateState.begin();
	advance(firstDoor, 0);
	if ((*firstDoor)) {
		door->SetDoorLockState(0, true);
		currentRoom = 2;
	}
	if ((int)player->Pos().x == 500 && (int)player->Pos().y == 1400) {
		
	}
}

void Stage1::Render()
{
	ZeroIScene::Render();
	mapManager->Render();
	footHolder->Render();
	pressurePlate->Render();
	door->Render();
	if (currentRoom == 1) {
		black1->Render();
	}
	else if (currentRoom == 2) {
		black2->Render();
	}
	player->Render();
}
