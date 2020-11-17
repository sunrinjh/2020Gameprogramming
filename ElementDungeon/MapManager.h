#pragma once
#include <Zero.h>
#include "Player.h"
class MapManager : public ZeroIScene
{
private:
	ZeroSprite* background;
	Player* player;
	// �� ��������Ʈ�� ������ ����
	D3DXCOLOR wallColor[3840][2160];
	int playerHeight, playerWidth;
	// �浹ó���� ������ ������
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

