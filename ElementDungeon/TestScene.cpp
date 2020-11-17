#include "stdafx.h"
#include "TestScene.h"

TestScene::TestScene()
{
	player = new Player();
	PushScene(player);
	player->SetPos(1920, 1080);

	mapManager = new MapManager(player, "Resources/Sprites/map.png", "Resources/Sprites/wall.png");
	PushScene(mapManager);

	pressurePlate = new PressurePlate(player);

	pressurePlate->AddPressurePlate(1700, 1080);
	pressurePlate->AddPressurePlate(1764, 1080);
	
	door = new Door(player);
	footHolder = new FootHolder(player);

	ZeroApp->GetDevice()->ShowCursor(false);

	ZeroCameraMgr->SetCameraOn(); 
	ZeroCameraMgr->SetScreen(3840,2160);
	ZeroCameraMgr->SetTarget(player);
}

TestScene::~TestScene()
{
}

void TestScene::Update(float eTime)
{
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
	}
	
}

void TestScene::Render()
{
	ZeroIScene::Render();
	mapManager->Render();
	footHolder->Render();
	pressurePlate->Render();
	door->Render();
	player->Render();

}
