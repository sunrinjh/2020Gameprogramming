#include "stdafx.h"
#include "VirtualPlayer.h"

VirtualPlayer::VirtualPlayer()
{
	playerAnimation = new ZeroAnimation(2.f);
	playerAnimation->PushSprite("Resources/Sprites/Character/pacman_0.png");
	playerAnimation->PushSprite("Resources/Sprites/Character/pacman_1.png");
	playerAnimation->SetRotCenter(playerAnimation->GetCurrentSprite()->Width() / 2, playerAnimation->GetCurrentSprite()->Height() / 2);
	PushScene(playerAnimation);
}

VirtualPlayer::VirtualPlayer(int type)
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
	currentSprite = playerAnimation->GetCurrentSprite();
	playerAnimation->SetRotCenter(playerAnimation->GetCurrentSprite()->Width() / 2, playerAnimation->GetCurrentSprite()->Height() / 2);
	PushScene(playerAnimation);
}

VirtualPlayer::~VirtualPlayer()
{

}

void VirtualPlayer::Update(float eTime)
{
	ZeroIScene::Update(eTime);
}

void VirtualPlayer::Render()
{
	ZeroIScene::Render();
	playerAnimation->Render();
}

ZeroSprite* VirtualPlayer::GetCurrentSprite()
{
	return playerAnimation->GetCurrentSprite();;
}
