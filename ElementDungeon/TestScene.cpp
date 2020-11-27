#include "stdafx.h"
#include "TestScene.h"
#include "Wall.h"
#include "Ground.h"
TestScene::TestScene()
{
	player = new Player();
	PushScene(player);
	virtualPlayer = new VirtualPlayer();
	PushScene(virtualPlayer);
	socketClient = new SocketClient();
	socketClient->Init();
	socketClient->JoinServer();
	for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
		for (int j = 0; j < (sizeof(map[0]) / sizeof(map[0][0])); j++) {
			switch (map[i][j])
			{
			case 1:
				tiles.push_back(new Wall());
				tiles.back()->SetPos(j * 64, i * 64);
				break;
			case 0:
				tiles.push_back(new Ground());
				tiles.back()->SetPos(j * 64, i * 64);
				break;
			}
		}
	}
	playerLocation[0] = 1;
	playerLocation[1] = 1;
	player->SetPos(playerLocation[0] * 64, playerLocation[1] * 64);
	direction = Direction::LEFT;

}

TestScene::~TestScene()
{
}

void TestScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	player->Update(eTime);
	int playerLocationX = playerLocation[0];
	int playerLocationY = playerLocation[1];
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
		if (map[playerLocationY - 1][playerLocationX] == 0)
			playerLocation[1] -= 1;

}
	else if (ZeroInputMgr->GetKey(VK_DOWN) == INPUTMGR_KEYDOWN) {
		if (map[playerLocationY+1][playerLocationX] == 0)
			playerLocation[1] += 1;
	}
	else if (ZeroInputMgr->GetKey(VK_LEFT) == INPUTMGR_KEYDOWN) {
		if (map[playerLocationY][playerLocationX-1] == 0)
			playerLocation[0] -= 1;

	}
	else if (ZeroInputMgr->GetKey(VK_RIGHT) == INPUTMGR_KEYDOWN) {
		if (map[playerLocationY][playerLocationX+1] == 0)
			playerLocation[0] += 1;
	}
	player->SetPos(playerLocation[0] * 64, playerLocation[1] * 64);
	/*if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
		direction = Direction::UP;

	}
	else if (ZeroInputMgr->GetKey(VK_DOWN) == INPUTMGR_KEYDOWN) {
		if (map[++playerLocationY][playerLocationX] == 0)
			direction = Direction::DOWN;
	}
	else if (ZeroInputMgr->GetKey(VK_LEFT) == INPUTMGR_KEYDOWN) {
		if (map[playerLocationY][--playerLocationX] == 0)
			direction = Direction::LEFT;

	}
	else if (ZeroInputMgr->GetKey(VK_RIGHT) == INPUTMGR_KEYDOWN) {
		if (map[playerLocationY][++playerLocationX] == 0)
			direction = Direction::RIGHT;
	}
	if (playerLocationX * 64 >= (int)player->Pos().x -2 && playerLocationX * 64 <= (int)player->Pos().x + 2)
	{

		switch (direction)
		{
		case TestScene::Direction::RIGHT:
			if (map[playerLocationY][++playerLocationX] == 0)
				playerLocation[0]++;
			break;
		case TestScene::Direction::LEFT:
			if (map[playerLocationY][--playerLocationX] == 0)
				playerLocation[0]--;
			break;
		case TestScene::Direction::UP:
			if (map[--playerLocationY][playerLocationX] == 0)
				playerLocation[1]--;
			break;
		case TestScene::Direction::DOWN:
			if (map[++playerLocationY][playerLocationX] == 0)
				playerLocation[1]++;
			break;
		default:
			break;
		}
	
		player->SetPos(playerLocation[0] * 64, playerLocation[1] * 64);
	}*/
	//player->SetPos(MoveTowards(new ZeroVec(playerLocationX * 64, playerLocationY * 64), 128* eTime));
	//cout << player->Pos() << endl;

	socketClient->SendPlayerPos(&(player->Pos())); 
	//socketClient->CoutServerMessage();
	socketClient->GetPlayerPos();
}

void TestScene::Render()
{
	ZeroIScene::Render();
	for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
		(*iter)->Render();
	}
	player->Render();
	virtualPlayer->Render();
}

ZeroVec TestScene::MoveTowards(ZeroVec* pos, float maxDistanceDelta)
{
	float playerPosX = player->Pos().x;
	float playerPosY = player->Pos().y;
	float destPosX = pos->x;
	float destPosY = pos->y;
	bool xIsSame = false;
	bool yIsSame = false;
	if (abs(destPosX - playerPosX) <= maxDistanceDelta) {
		xIsSame = true;
	}
	else if (abs(destPosY - playerPosY) <= maxDistanceDelta) {
		yIsSame = true;
	}
	if (!xIsSame) {
		if (!yIsSame) {
			return ZeroVec(playerPosX - ((playerPosX > destPosX) - (playerPosX < destPosX)) * maxDistanceDelta, playerPosY - ((playerPosY > destPosY) - (playerPosY < destPosY)) * maxDistanceDelta);
		}
		else {
			return ZeroVec(playerPosX - ((playerPosX > destPosX) - (playerPosX < destPosX)) * maxDistanceDelta, playerPosY);
		}
	}
	else {
		if (!yIsSame) {
			return ZeroVec(playerPosX, playerPosY - ((playerPosY > destPosY) - (playerPosY < destPosY)) * maxDistanceDelta);
		}
		else {
			return ZeroVec(playerPosX, playerPosY);
		}
	}
	
}
