#include "stdafx.h"
#include "FootHolder.h"
FootHolder::FootHolder(Player* player)
{
	this->player = player;
	moveSpeed = 30;
	l_FootHolder.clear();
	l_Origin.clear();
	l_Destination.clear();
	l_Straight.clear();

}

FootHolder::~FootHolder()
{

}

void FootHolder::AddFootHolder(float originX, float originY, float destX, float destY)
{
	l_Origin.push_back(new ZeroVec(originX, originY));
	l_Destination.push_back(new ZeroVec(destX, destY));
	l_FootHolder.push_back(new ZeroSprite("Resources/Sprites/on.png"));
	l_FootHolder.back()->SetPos(originX, originY);
	bool way;
	if (destX - originX || originX - destX) {
		way = true;
	}
	else {
		way = false;
	}
	cout << way << endl;
	l_Straight.push_back(true);
}

void FootHolder::Render()
{
	ZeroIScene::Render();
	for (auto iter = l_FootHolder.begin(); iter != l_FootHolder.end(); iter++) {
		(*iter)->Render();
	}
}

void FootHolder::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	int index = 0;
	for (auto footHolderIter = l_FootHolder.begin(); footHolderIter != l_FootHolder.end(); footHolderIter++) {
		list<ZeroVec*>::iterator originIter = l_Origin.begin();
		advance(originIter, index);
		
		list<ZeroVec*>::iterator destIter = l_Destination.begin();
		advance(destIter, index);

		list<bool>::iterator straightIter = l_Straight.begin();
		advance(straightIter, index);

		if ((*straightIter)) {
			(*footHolderIter)->AddPosY(-moveSpeed * eTime);
		}
		

		index++;
	}
}
