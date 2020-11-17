#include "stdafx.h"
#include "TopLayer.h"

TopLayer::TopLayer()
{
	blackSprite = new ZeroSprite("Resources/Sprites/BlackSprite.png");
}

TopLayer::~TopLayer()
{
}

void TopLayer::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	
}

void TopLayer::Render()
{
	ZeroIScene::Render();
	if (timer >= 0) {
		blackSprite->Render();
	}
}

void TopLayer::ShowBlackSprite(float timer)
{
	this->timer = timer;
}
