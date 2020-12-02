#pragma once
#include "Tiles.h"
class Food : public Tiles
{
private:
	ZeroSprite* foodSprite;
	ZeroSprite* roadSprite;
	bool eaten;
public:
	Food();
	~Food();
	void Render();
	void Update(float eTime);
	void SetEaten(bool bValue);
	bool GetEaten();
	ZeroSprite* GetCurrentSprite();
};

