#pragma once
#include <Zero.h>
#include "Tiles.h"
class Wall : public Tiles
{
private:
	ZeroSprite* wallSprite;

public:
	//enum class Direction
	//{
	//	LEFT, RIGHT, TOP, BUTTOM
	//};
	//Direction direction;
	Wall();
	//Wall(Direction direction);
	~Wall();
	void Render();
	void Update(float eTime);
};

