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
