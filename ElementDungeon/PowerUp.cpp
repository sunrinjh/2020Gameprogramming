#include "stdafx.h"
#include "PowerUp.h"

PowerUp::PowerUp()
{
	eaten = false;
	roadSprite = new ZeroSprite("Resources/Sprites/emptyRoad.png");
	powerUpSprite = new ZeroSprite("Resources/Sprites/powerUpRoad.png");
	PushScene(roadSprite);
	PushScene(powerUpSprite);
}

PowerUp::~PowerUp()
{
}

void PowerUp::Render()
{
	ZeroIScene::Render();
	if (!eaten) {
		powerUpSprite->Render();
	}
	else {
		roadSprite->Render();
	}
}

void PowerUp::Update(float eTime)
{
	ZeroIScene::Update(eTime);
}

void PowerUp::SetEaten(bool bValue)
{
	eaten = bValue;
}

bool PowerUp::GetEaten()
{
	return eaten;
}
