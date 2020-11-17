#include "stdafx.h"
#include "Lever.h"

Lever::Lever(Player* player)
{
    this->player = player;
}

Lever::~Lever()
{
}

void Lever::AddLever(float x, float y)
{
	list_Lever.push_back(new ZeroAnimation(1, false));
	list_Lever.back()->PushSprite("Resources/Sprites/off.png");
	list_Lever.back()->PushSprite("Resources/Sprites/on.png");
	list_Lever.back()->SetPos(x, y);
	list_Lever.push_back(false);
}

list<bool> Lever::GetLeverState()
{
    return list<bool>();
}

void Lever::SetLeverState(int index, bool bValue)
{
}

void Lever::Render()
{
}

void Lever::Update(float eTime)
{
}
