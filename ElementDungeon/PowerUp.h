#pragma once
#include "Tiles.h"
class PowerUp : public Tiles
{
private:
	ZeroSprite* powerUpSprite;
	ZeroSprite* roadSprite;
	bool eaten;
public:
	PowerUp();
	~PowerUp();
	void Render();
	void Update(float eTime);
	void SetEaten(bool bValue);
	bool GetEaten();
};

