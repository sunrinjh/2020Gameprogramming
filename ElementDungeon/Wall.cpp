#include "stdafx.h"
#include "Wall.h"
#include "Player.h"

Wall::Wall()
{
	type = Type::WALL;
	wallSprite = new ZeroSprite("Resources/Sprites/wall.png");

	PushScene(wallSprite);
}

//Wall::Wall(Direction _direction)
//{
//	wallSprite = new ZeroSprite("Resources/Sprites/wall.png");
//
//	PushScene(wallSprite);
//}

Wall::~Wall()
{
}

void Wall::Render()
{
	wallSprite->Render();
}

void Wall::Update(float eTime)
{
}
