#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	playerAnimation = new ZeroAnimation(1.0f, false);
    playerAnimation->PushSprite("Resources/Sprites/Character/pacman.png");
	playerAnimation->SetRotCenter(playerAnimation->GetCurrentSprite()->Width() / 2, playerAnimation->GetCurrentSprite()->Height() / 2);
    PushScene(playerAnimation);
	movingDirection = -1;
	movingDirectionBuffer = -1;
	moveSpeed = 100;
}

Player::~Player()
{
}

void Player::Render()
{
	playerAnimation->Render();
}

void Player::Update(float eTime)
{

	ZeroIScene::Update(eTime);
	Move(eTime);
}

void Player::Move(float eTime)
{
	//ZeroInputMgr로 방향을 버퍼에 넣어줌
	{ 
		if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON) {
			movingDirectionBuffer = 3;
		}
		else if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON) {
			movingDirectionBuffer = 1;
		}
		else if (ZeroInputMgr->GetKey('W') == INPUTMGR_KEYON) {
			movingDirectionBuffer = 0;
		}
		else if (ZeroInputMgr->GetKey('S') == INPUTMGR_KEYON) {
			movingDirectionBuffer = 2;
		}
	}

	switch (movingDirectionBuffer)
	{
	case 0:
		this->AddPosY(-moveSpeed * eTime);
		playerAnimation->SetRot(-90);
		break;
	case 1:
		this->AddPosX(moveSpeed * eTime);
		playerAnimation->SetRot(0);
		break;
	case 2:
		this->AddPosY(moveSpeed * eTime);
		playerAnimation->SetRot(90);
		break;
	case 3:
		this->AddPosX(-moveSpeed * eTime);
		playerAnimation->SetRot(180);
		break;
	default:
		break;
	}
}

ZeroSprite* Player::GetCurrentSprite()
{
    return nullptr;
}

void Player::SetPlayerPos(float x, float y)
{
}

void Player::SetPlayerPos(ZeroVec vec)
{
}
