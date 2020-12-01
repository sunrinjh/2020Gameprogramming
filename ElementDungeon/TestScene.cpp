#include "stdafx.h"
#include "TestScene.h"
#include "Wall.h"
#include "Ground.h"

TestScene::TestScene()
{
	player = new Player();
	moveSpeed = 128;
	isMoveable = true;
	PushScene(player);
	virtualPlayer = new VirtualPlayer();
	PushScene(virtualPlayer);
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
	direction = Direction::RIGHT;
	playerNumber = Socket->GetPlayerNumber();

}

TestScene::~TestScene()
{
}

void TestScene::Update(float eTime)
{
	
	ZeroIScene::Update(eTime);
	player->Update(eTime);
	Move(eTime);


	Socket->SendPlayerPos(&(player->Pos())); 
	Socket->GetPlayerPos();
	switch (playerNumber)
	{
	case 1:
		virtualPlayer->SetPos(Socket->GetPlayer2Pos()->x, Socket->GetPlayer2Pos()->y);
		break;
	case 2:
		virtualPlayer->SetPos(Socket->GetPlayer1Pos()->x, Socket->GetPlayer1Pos()->y);
		break;
	default:
		break;
	}
	
	
	
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

void TestScene::Move(float eTime)
{
	if (directionBufferTimer < 0) {
		directionBufferTimer = 1;
		directionBuffer = direction;
	}
	else {
		directionBufferTimer -= eTime;
	}
	//키보드 인풋 받아서 버퍼에 넣음
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
		directionBuffer = Direction::UP;
	}
	else if (ZeroInputMgr->GetKey(VK_DOWN) == INPUTMGR_KEYDOWN) {
		directionBuffer = Direction::DOWN;
	}
	else if (ZeroInputMgr->GetKey(VK_LEFT) == INPUTMGR_KEYDOWN) {
		directionBuffer = Direction::LEFT;
	}
	else if (ZeroInputMgr->GetKey(VK_RIGHT) == INPUTMGR_KEYDOWN) {
		directionBuffer = Direction::RIGHT;
	}
	if (directionBuffer != direction) {
		switch (directionBuffer)
		{
		case TestScene::Direction::RIGHT:
			if (direction == Direction::LEFT) {
				direction = directionBuffer;
			}
			break;
		case TestScene::Direction::LEFT:
			if (direction == Direction::RIGHT) {
				direction = directionBuffer;
			}
			break;
		case TestScene::Direction::UP:
			if (direction == Direction::DOWN) {
				direction = directionBuffer;
			}
			break;
		case TestScene::Direction::DOWN:
			if (direction == Direction::UP) {
				direction = directionBuffer;
			}
			break;
		default:
			break;
		}
	}
	isMoveable = true;
	float playerX = player->Pos().x;
	float playerY = player->Pos().y;

	//타일 가운데에 있는지 검사
	if ((abs(fmod(playerX, 64)) < 2) && (abs(fmod(playerY, 64)) < 2)) {
		//충돌 처리
		int relativeX = round(playerX) / 64;
		int relativeY = round(playerY) / 64;
		direction = directionBuffer;

		switch (direction)
		{
		case TestScene::Direction::RIGHT:
			if (map[relativeY][relativeX + 1] == 1) {
				player->SetPos(round(playerX), round(playerY));
				isMoveable = false;
			}
			break;
		case TestScene::Direction::LEFT:
			if (map[relativeY][relativeX -1] == 1) {
				player->SetPos(round(playerX), round(playerY));
				isMoveable = false;
			}
			break;
		case TestScene::Direction::UP:
			if (map[relativeY-1][relativeX] == 1) {
				player->SetPos(round(playerX), round(playerY));
				isMoveable = false;
			}
			break;
		case TestScene::Direction::DOWN:
			if (map[relativeY + 1][relativeX] == 1) {
				player->SetPos(round(playerX), round(playerY));
				isMoveable = false;
			}
			break;
		default:
			break;
		}
	}
	
	
	//최종 이동 처리
	if (isMoveable) {
		switch (direction)
		{
		case TestScene::Direction::RIGHT:
			player->AddPosX(moveSpeed * eTime);
			//player->SetPosY(round(player->Pos().y));
			break;
		case TestScene::Direction::LEFT:
			player->AddPosX(-moveSpeed * eTime);
			//player->SetPosY(round(player->Pos().y));
			break;
		case TestScene::Direction::UP:
			player->AddPosY(-moveSpeed * eTime);
			//player->SetPosX(round(player->Pos().x));
			break;
		case TestScene::Direction::DOWN:
			player->AddPosY(moveSpeed * eTime);
			//player->SetPosX(round(player->Pos().x));
			break;
		default:
			break;
		}
	}
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
