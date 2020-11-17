#include "stdafx.h"
#include "MapManager.h"


MapManager::MapManager(Player* pValue, const char* sValue1, const char* sValue2)
{

	player = pValue;
	background = new ZeroSprite(sValue1);
	ZeroSprite* wall = new ZeroSprite(sValue2);
	LPDIRECT3DTEXTURE9 pTexture;
	D3DLOCKED_RECT LockRect;
	pTexture = wall->GetLPDIRECT3DTEXTURE9();
	pTexture->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);
	DWORD* pColor = (DWORD*)LockRect.pBits;
	int width = (int)background->Width();
	int height = (int)background->Height();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int colorIndex = y * width + x;
			D3DXCOLOR pixelColor = pColor[colorIndex];
			wallColor[x][y] = pixelColor;
		}
	}
	
	pTexture->UnlockRect(0);
	SAFE_DELETE(wall);
	playerHeight = (int)player->GetCurrentSprite()->Height();
	playerWidth = (int)player->GetCurrentSprite()->Width();
}

MapManager::~MapManager()
{
}

void MapManager::Render()
{
	ZeroIScene::Render();
	background->Render();
}

void MapManager::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	ZeroVec playerPos = player->Pos();
	int x = (int)round(playerPos.x);
	int y = (int)round(playerPos.y);
	// 두개인 이유는 일단 양 꼭짓점에서만 검사
	if (wallColor[x + playerWidth +threshold][y + playerHeight + threshold].a > 0 || wallColor[x - threshold][y + playerHeight + threshold].a > 0 || wallColor[x + playerWidth + threshold][y - threshold].a > 0 || wallColor[x-threshold][y-threshold].a > 0) {
		if (wallColor[x + playerWidth+threshold][y + playerHeight+ threshold] == D3DXCOLOR(0xFF000000) || wallColor[x- threshold][y + playerHeight+ threshold] == D3DXCOLOR(0xFF000000)) {
			// 아래쪽 벽 검은색
			player->SetMoveableButtom(false);
			//cout << "아래로못감" << endl;
		}
		else {
			player->SetMoveableButtom(true);
		}
		if (wallColor[x + playerWidth+ threshold][y + playerHeight+ threshold] == D3DXCOLOR(0xFFFF0000) || wallColor[x + playerWidth+ threshold][y- threshold] == D3DXCOLOR(0xFFFF0000)) {
			//오른쪽 벽
			player->SetMoveableRight(false);
			//cout << "오른쪽으로못감" << endl;
		}
		else {
			player->SetMoveableRight(true);
		}
		if (wallColor[x + playerWidth+ threshold][y- threshold] == D3DXCOLOR(0xFF00FF00) || wallColor[x- threshold][y-threshold] == D3DXCOLOR(0xFF00FF00)) {
			//위쪽 벽
			player->SetMoveableTop(false);
			//cout << "위쪽으로못감" << endl;
		}
		else {
			player->SetMoveableTop(true);
		}
		if (wallColor[x- threshold][y- threshold] == D3DXCOLOR(0xFF0000FF) || wallColor[x- threshold][y + playerHeight+ threshold] == D3DXCOLOR(0xFF0000FF)) {
			//왼쪽 벽
			player->SetMoveableLeft(false);
			//cout << "왼쪽으로못감" << endl;
		}
		else {
			player->SetMoveableLeft(true);
		}
	}
	else {
		player->SetMoveableRight(true);
		player->SetMoveableTop(true);
		player->SetMoveableButtom(true);
		player->SetMoveableLeft(true);
	}
	
}
