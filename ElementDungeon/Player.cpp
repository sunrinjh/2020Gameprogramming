#include "stdafx.h"
#include "Player.h"



Player::Player()
{
	playerAnimation = new ZeroAnimation(2.f);
    playerAnimation->PushSprite("Resources/Sprites/Character/pacman_0.png");
    playerAnimation->PushSprite("Resources/Sprites/Character/pacman_1.png");
	playerAnimation->SetRotCenter(playerAnimation->GetCurrentSprite()->Width() / 2, playerAnimation->GetCurrentSprite()->Height() / 2);
	PushScene(playerAnimation);
}

Player::Player(int type)
{
	playerAnimation = new ZeroAnimation(2.f);
	switch (type)
	{
	case 0:
		playerAnimation->PushSprite("Resources/Sprites/Character/pacman_0.png");
		playerAnimation->PushSprite("Resources/Sprites/Character/pacman_1.png");
		break;
	case 1:
		playerAnimation->PushSprite("Resources/Sprites/Character/red_right_0.png");
		playerAnimation->PushSprite("Resources/Sprites/Character/red_right_1.png");
		break;
	default:
		break;
	}
	playerAnimation->SetRotCenter(playerAnimation->GetCurrentSprite()->Width() / 2, playerAnimation->GetCurrentSprite()->Height() / 2);
	PushScene(playerAnimation);
}

Player::~Player()
{
}

void Player::Render()
{
	ZeroIScene::Render();
	playerAnimation->Render();
}

void Player::Update(float eTime)
{
	ZeroIScene::Update(eTime);
}

ZeroSprite* Player::GetCurrentSprite()
{
    return playerAnimation->GetCurrentSprite();
}
