#include "stdafx.h"
#include "TestScene.h"

TestScene::TestScene()
{
	player = new Player();
	PushScene(player);

	socketClient = new SocketClient();
	socketClient->Init();
	socketClient->JoinServer();
	for (int i = 0; i < sizeof(map); i++) {
		for (int j = 0; j < sizeof(map[i]); j++) {
			switch (map[i][j])
			{
			case 1:
				tiles.push_back(new ZeroSprite("Resources/Sprites/wall.png"));
				tiles.back()->SetPos(j * 64, i * 64);
				break;
			case 0:
				tiles.push_back(new ZeroSprite("Resources/Sprites/road.png"));
				tiles.back()->SetPos(j * 64, i * 64);
				break;
			}
		}
	}
	
}

TestScene::~TestScene()
{
}

void TestScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	player->Update(eTime);
	socketClient->SendPlayerPos(&(player->Pos()));
}

void TestScene::Render()
{
	ZeroIScene::Render();
	for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
		(*iter)->Render();
	}
	player->Render();

}
