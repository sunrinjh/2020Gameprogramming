#include "stdafx.h"
#include "TestScene.h"
#include "Wall.h"
#include "Food.h"
#include "PowerUp.h"
#include "TitleScene.h"
TestScene::TestScene()
{
	foodCounter = 0;
	backgroundSprite = new ZeroSprite("Resources/Sprites/backgroundSprite.png");
	pacmanWinSprite = new ZeroSprite("Resources/Sprites/UI/pacmanwin.png");
	ghostWinSprite = new ZeroSprite("Resources/Sprites/UI/ghostwin.png");
	switch (playerNumber = Socket->GetPlayerNumber()) {
	case 1:
		player = new Player(0);
		virtualPlayer = new VirtualPlayer(1);
		moveSpeed = 128;
		playerLocation[0] = 1;
		playerLocation[1] = 1;
		player->SetPos(playerLocation[0] * 64, playerLocation[1] * 64);
		break;
	case 2:
		player = new Player(1);
		virtualPlayer = new VirtualPlayer(0);
		moveSpeed = 144;
		playerLocation[0] = 20;
		playerLocation[1] = 14;
		player->SetPos(playerLocation[0] * 64, playerLocation[1] * 64);
		break;
	default:
		player = new Player(0);
		virtualPlayer = new VirtualPlayer(1);
		moveSpeed = 128;
		playerLocation[0] = 1;
		playerLocation[1] = 1;
		player->SetPos(playerLocation[0] * 64, playerLocation[1] * 64);
		break;
	}
	playerHealth = 2;
	virtualPlayer->SetRotCenter(32, 32);
	player->SetRotCenter(32, 32);
	isMoveable = true;
	PushScene(player);
	PushScene(virtualPlayer);
	for (int i = 0; i < (sizeof(map) / sizeof(map[0])); i++) {
		for (int j = 0; j < (sizeof(map[0]) / sizeof(map[0][0])); j++) {
			switch (map[i][j])
			{
			case 1:
				tiles.push_back(new Wall());
				tiles.back()->SetPos(j * 64, i * 64);
				tiles.back()->SetName("Wall");
				PushScene(tiles.back());
				break;
			case 0:
				tiles.push_back(new Food());
				tiles.back()->SetPos(j * 64, i * 64);
				tiles.back()->SetName("Food");
				PushScene(tiles.back());
				foodCounter++;
				break;
			case 2:
				tiles.push_back(new PowerUp());
				tiles.back()->SetPos(j * 64, i * 64);
				tiles.back()->SetName("PowerUp");
				PushScene(tiles.back());
				break;
			}
		}
	}
	ghostMoveTimer = -1;
	godModTimer = -1;
	powerUpTimer = -1;
	direction = Direction::RIGHT;


}

TestScene::~TestScene()
{
}

void TestScene::Update(float eTime)
{
	
	ZeroIScene::Update(eTime);
	float virtualPlayerPos[2] = { virtualPlayer->Pos().x, virtualPlayer->Pos().y };
	float playerPos[2] = { player->Pos().x, player->Pos().y };
	
	player->Update(eTime);
	virtualPlayer->Update(eTime);
	Move(eTime);
	EatFood();
	Socket->SendPlayerPos(&(player->Pos()));
	Socket->GetPlayerPos();
	switch (playerNumber)
	{
	case 1:
		powerUpTimer -= eTime;
		godModTimer -= eTime;
		virtualPlayer->SetPos(Socket->GetPlayer2Pos()->x, Socket->GetPlayer2Pos()->y);
		if (godModTimer < 0 && powerUpTimer < 0) {
			if (player->GetCurrentSprite()->IsOverlapped(virtualPlayer->GetCurrentSprite()))
			{
				playerHealth--;
				godModTimer = 1.5;
				if (playerHealth <= 0){
					Socket->SendStringToServer("gameover");
					ghostWin = true;
				}
			}
		}
		break;
	case 2:
		ghostMoveTimer -= eTime;
		if (ghostMoveTimer < 0) {
			if (player->GetCurrentSprite()->IsOverlapped(virtualPlayer->GetCurrentSprite()))
			{
				ghostMoveTimer = 1.5;
				playerHealth--;
				if (playerHealth <= 0) {
					Socket->SendStringToServer("gameover");
					ghostWin = true;
				}
			}
		}
		virtualPlayer->SetPos(Socket->GetPlayer1Pos()->x, Socket->GetPlayer1Pos()->y);
		break;
	default:
		break;
	}
	TurnAnimation(playerPos[0],playerPos[1], virtualPlayerPos[0], virtualPlayerPos[1]);
	if (pacmanWin) {
		winTimer += eTime;
		if (winTimer > 2) {
			
			if (playerNumber == 1) {
				Socket->CloseServer();
				
			}
			PostQuitMessage(0);
		}

	}
	else if (ghostWin) {
		winTimer += eTime;
		if (winTimer > 2) {
			
			if (playerNumber == 1) {
				Socket->CloseServer();
				
			}
			PostQuitMessage(0);
		}
	}
}

void TestScene::Render()
{
	ZeroIScene::Render();
	backgroundSprite->Render();
	for (auto iter = tiles.begin(); iter != tiles.end(); iter++) {
		(*iter)->Render();
	}
	player->Render();
	virtualPlayer->Render();
	if (pacmanWin) {
		pacmanWinSprite->Render();
	}
	else if (ghostWin) {
		ghostWinSprite->Render();
	}
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
	if (isMoveable && ghostMoveTimer < 0) {
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

void TestScene::TurnAnimation(float x, float y, float vx, float vy)
{
	float virtualPlayerPos[2] = { virtualPlayer->Pos().x, virtualPlayer->Pos().y };
	float playerPos[2] = { player->Pos().x, player->Pos().y };
	if (playerPos[0] != x) {
		if (x < playerPos[0]) {
			player->SetRot(0);
		}
		else {
			player->SetRot(180);
		}
	}
	else if (playerPos[1] != y) {
		if (y < playerPos[1]) {
			player->SetRot(90);
		}
		else {
			player->SetRot(-90);
		}
	}
	if (virtualPlayerPos[0] != vx) {
		if (vx < virtualPlayerPos[0]) {
			virtualPlayer->SetRot(0);
		}
		else {
			virtualPlayer->SetRot(180);
		}
	}
	if (virtualPlayerPos[1] != vy) {
		if (vy < virtualPlayerPos[1]) {
			virtualPlayer->SetRot(90);
		}
		else {
			virtualPlayer->SetRot(-90);
		}
	}
}

void TestScene::EatFood()
{
	float playerX = player->Pos().x;
	float playerY = player->Pos().y;
	switch (playerNumber)
	{
	case 1:
		playerX = player->Pos().x;
		playerY = player->Pos().y;
		break;
	case 2:
		playerX = virtualPlayer->Pos().x;
		playerY = virtualPlayer->Pos().y;
		break;
	default:
		break;
	}
	if ((abs(fmod(playerX, 64)) < 5) && (abs(fmod(playerY, 64)) < 5)) {
		//충돌 처리
		int relativeX = round(playerX) / 64;
		int relativeY = round(playerY) / 64 * sizeof(map[0]) / sizeof(map[0][0]);
		
		if (tiles[relativeY + relativeX]->GetEaten() == false) {
			tiles[relativeY + relativeX]->SetEaten(true);
			if (tiles[relativeY + relativeX]->Name() == "Food") {

				foodCounter--;
				if (foodCounter <= 0) {
					cout << "gameclear" << endl;
					Socket->SendStringToServer("gameclear");
					pacmanWin = true;
				}
			}
			else if (tiles[relativeY + relativeX]->Name() == "PowerUp") {
				powerUpTimer = 3;
			}
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
