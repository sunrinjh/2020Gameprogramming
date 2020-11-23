#pragma once
#include <Zero.h>
class Wall :	public ZeroIScene
{
private:
	ZeroSprite* wallSprite;
	enum Direction
	{
		left, right, top, buttom
	};
	Direction direction;
public:
	Wall();
	Wall(Direction direction);
	~Wall();
};

