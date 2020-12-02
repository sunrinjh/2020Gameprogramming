#include "stdafx.h"
#include "Ground.h"

Ground::Ground()
{
	
	groundSprite = new ZeroSprite("Resources/Sprites/road.png");
	PushScene(groundSprite);
}

Ground::~Ground()
{
}

void Ground::Render()
{
	groundSprite->Render();
}

void Ground::Update(float eTime)
{
}
