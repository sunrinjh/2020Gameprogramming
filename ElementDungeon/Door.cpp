#include "stdafx.h"
#include "Door.h"

Door::Door(Player* player)
{
	blackSprite = new ZeroSprite("Resources/Sprites/BlackSprite.png");
	this->player = player;
	l_DoorSprite.clear();
	l_DoorLockState.clear();
}


Door::~Door()
{
}

void Door::AddDoor(float x, float y, float dx, float dy)
{
	l_DoorSprite.push_back(new ZeroAnimation(1, false));
	l_DoorSprite.back()->PushSprite("Resources/Sprites/Door/lock.png");
	l_DoorSprite.back()->PushSprite("Resources/Sprites/Door/open.png");
	l_DoorSprite.back()->SetPos(x, y);
	l_DestinationVec.push_back(new ZeroVec(dx, dy));
	l_DoorLockState.push_back(false);
}

void Door::SetDoorLockState(int index, bool doorLockState)
{
	list<bool>::iterator diter = l_DoorLockState.begin();
	advance(diter, index);
	(*diter) = doorLockState;

}
void Door::Update(float eTime)
{
	if (teleport) {
		teleportTimer += eTime;
		if (teleportTimer > 3) {
			teleport = false;
			teleportTimer = 0;

		}
	}
	ZeroIScene::Update(eTime);
	int iindex = 0;
	for (auto iter = l_DoorLockState.begin(); iter != l_DoorLockState.end(); iter++) {
		if ((*iter)) {
			list<ZeroAnimation*>::iterator diter = l_DoorSprite.begin();
			advance(diter, iindex);
			(*diter)->SetCurrentFrame(1);
		}
		else {
			list<ZeroAnimation*>::iterator diter = l_DoorSprite.begin();
			advance(diter, iindex);
			(*diter)->SetCurrentFrame(0);
		}
		iindex++;
	}
	ZeroVec playerPos;
	playerPos.x = (player->Pos().x + (player->GetCurrentSprite()->Width() / 2));
	playerPos.y = (player->Pos().y + player->GetCurrentSprite()->Height() / 2);
	int jindex = 0;
	for (auto iter = l_DoorSprite.begin(); iter != l_DoorSprite.end(); iter++) {
		ZeroVec doorPos = (*iter)->Pos();
		//if ((*iter)->GetCurrentSprite()->IsOverlapped(player->GetCurrentSprite())) {
		//	(*iter)->SetCurrentFrame(1);
		//	list<bool>::iterator biter = list_PressurePlateState.begin();
		//	advance(biter, index);
		//	(*biter) = true;
		//}
		if ((doorPos.x < playerPos.x && doorPos.x + (*iter)->GetCurrentSprite()->Width() > playerPos.x) && (doorPos.y <  playerPos.y && doorPos.y + (*iter)->GetCurrentSprite()->Height() > playerPos.y)) {
			list<bool>::iterator diter = l_DoorLockState.begin();
			advance(diter, jindex);
			if (jindex == 0 && (*diter)) {
				teleport = true;
				list<ZeroVec*>::iterator viter = l_DestinationVec.begin();
				advance(viter, jindex);
				float x = (*viter)->x;
				float y = (*viter)->y;
				player->SetPos(x,y);

			}
		}

		/*else {
			(*iter)->SetCurrentFrame(0);
			list<bool>::iterator biter = list_PressurePlateState.begin();
			advance(biter, index);
			(*biter) = false;
		}*/
		jindex++;
	}
}

void Door::Render()
{
	ZeroIScene::Render();
	for (auto iter = l_DoorSprite.begin(); iter != l_DoorSprite.end(); iter++) {
		(*iter)->Render();
	}
	if (teleport) {
		blackSprite->Render();
	}
}


