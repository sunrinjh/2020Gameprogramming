#pragma once
#include <Zero.h>
#include "Tiles.h"
class Ground : public Tiles
{
private:
	ZeroSprite* groundSprite;
public:
	Ground();
	~Ground();
	void Render();
	void Update(float eTime);
};

