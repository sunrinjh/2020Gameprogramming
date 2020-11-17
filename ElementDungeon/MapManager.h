#pragma once
#include <Zero.h>
#include "Player.h"
class MapManager : public ZeroIScene
{
private:
	ZeroSprite* background;
	Player* player;
	// 벽 스프라이트의 사이즈 정함
	D3DXCOLOR wallColor[3840][2160];
	int playerHeight, playerWidth;
	// 충돌처리의 간격을 조절함
	int threshold = 20;

public:
	MapManager(Player* pValue, const char* sValue1, const char* sValue2);
	~MapManager();
	void Render();
	void Update(float eTime);
	void SetBackground(const char* sValue) {
		background = new ZeroSprite(sValue);
	}

};

