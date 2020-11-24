#include "stdafx.h"
#include "VirtualPlayer.h"

VirtualPlayer::VirtualPlayer()
{
	playerAnimation = new ZeroAnimation(1.0f, false);
	playerAnimation->PushSprite("Resources/Sprites/Character/pacman.png");
	playerAnimation->SetRotCenter(playerAnimation->GetCurrentSprite()->Width() / 2, playerAnimation->GetCurrentSprite()->Height() / 2);
	PushScene(playerAnimation);
}

VirtualPlayer::~VirtualPlayer()
{

}

void VirtualPlayer::Update(float eTime)
{
}

void VirtualPlayer::Render()
{
	playerAnimation->Render();
}
