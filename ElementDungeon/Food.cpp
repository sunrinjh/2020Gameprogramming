#include "stdafx.h"
#include "Food.h"

Food::Food()
{
	type = Type::FOOD;
	foodSprite = new ZeroSprite("Resources/Sprites/foodRoad.png");
	roadSprite = new ZeroSprite("Resources/Sprites/emptyRoad.png");
	PushScene(foodSprite);
	PushScene(roadSprite);
	eaten = false; // ³ªÁß¿¡ ¸ÔÈù°ÇÁö ¾È¸ÔÈù°ÇÁö ¾Ë¾Æº¸±â À§ÇØ¼­ ÀÖÀ½
}

Food::~Food()
{
}

void Food::Render()
{
	if (!eaten) {
		foodSprite->Render();
	}
	else {
		roadSprite->Render();
	}
}

void Food::Update(float eTime)
{
}

void Food::SetEaten(bool bValue)
{
	eaten = bValue;
}

bool Food::GetEaten()
{
	return eaten;
}

ZeroSprite* Food::GetCurrentSprite()
{
	ZeroSprite* tempSprite;
	if (!eaten) {
		tempSprite = foodSprite;
	}
	else {
		tempSprite = roadSprite;
	}
	return tempSprite;
}
