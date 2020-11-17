#include "stdafx.h"
#include "PressurePlate.h"

PressurePlate::PressurePlate(Player* player)
{
	this->player = player;
	list_PressurePlate.clear();
	list_PressurePlateState.clear();
}

PressurePlate::~PressurePlate()
{
}


void PressurePlate::AddPressurePlate(float x, float y)
{
	list_PressurePlate.push_back(new ZeroAnimation(1, false));
	list_PressurePlate.back()->PushSprite("Resources/Sprites/PressurePlate/off.png");
	list_PressurePlate.back()->PushSprite("Resources/Sprites/PressurePlate/on.png");
	list_PressurePlate.back()->SetPos(x, y);
	list_PressurePlateState.push_back(false);
}

list<bool> PressurePlate::GetPressurePlateState()
{
	return list_PressurePlateState;
}

void PressurePlate::SetPressurePlateState(int index, bool bValue)
{
	list<bool>::iterator biter = list_PressurePlateState.begin();
	advance(biter, index);
	(*biter) = bValue;
}

void PressurePlate::Render()
{
	ZeroIScene::Render();
	for (auto iter = list_PressurePlate.begin(); iter != list_PressurePlate.end(); iter++) {
		(*iter)->Render();
	}

}

void PressurePlate::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	int index = 0;
	ZeroVec playerPos;
	playerPos.x = ( player->Pos().x + (player->GetCurrentSprite()->Width() / 2));
	playerPos.y = ( player->Pos().y + player->GetCurrentSprite()->Height());
	for (auto iter = list_PressurePlate.begin(); iter != list_PressurePlate.end(); iter++) {
		ZeroVec pressurePlatePos = (*iter)->Pos();
		//if ((*iter)->GetCurrentSprite()->IsOverlapped(player->GetCurrentSprite())) {
		//	(*iter)->SetCurrentFrame(1);
		//	list<bool>::iterator biter = list_PressurePlateState.begin();
		//	advance(biter, index);
		//	(*biter) = true;
		//}
		if ((pressurePlatePos.x < playerPos.x && pressurePlatePos.x + (*iter)->GetCurrentSprite()->Width() > playerPos.x) && (pressurePlatePos.y <  playerPos.y && pressurePlatePos.y + (*iter)->GetCurrentSprite()->Height() > playerPos.y)) {
			(*iter)->SetCurrentFrame(1);
			list<bool>::iterator biter = list_PressurePlateState.begin();
			advance(biter, index);
			(*biter) = true;
		}

		/*else {
			(*iter)->SetCurrentFrame(0);
			list<bool>::iterator biter = list_PressurePlateState.begin();
			advance(biter, index);
			(*biter) = false;
		}*/
		index++;
	}

}
