#include "stdafx.h"
#include "CreateRoom.h"
#include "TestScene.h"
CreateRoom::CreateRoom()
{
	Socket->MakeServer();
	waitFont = new ZeroFont(60, "대기중입니다", "둥근모꼴", "Resources/Fonts/DungGeunMo.ttf");
	errorFont = new ZeroFont(60, "", "둥근모꼴", "Resources/Fonts/DungGeunMo.ttf");
	startSprite = new ZeroSprite("Resources/Sprites/UI/start.png");

	waitFont->SetColor(0xFF000000);
	errorFont->SetColor(0xFFFF0000);



	PushScene(startSprite);
	PushScene(waitFont);
	waitFont->SetPos(780, 120);
	errorFont->SetPos(600, 180);
	startSprite->SetPos(SCREEN_WIDTH/2 - startSprite->Width() / 2, 500);
	waitForClient = false;

	Socket->Init();
	Socket->JoinServer();
	Socket->GetPlayerNumber();
	
}

CreateRoom::~CreateRoom()
{

}

void CreateRoom::Render()
{
	ZeroIScene::Render();
	startSprite->Render();
	errorFont->Render();
	waitFont->Render();
}

void CreateRoom::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN && startSprite->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
		switch (Socket->GetCurrentPlayerNumber()) {
		case 2:
			Socket->SendStringToServer("start\0");
			cout << "sending" << endl;
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			errorFont->SetString("인원이 충분하지 않습니다");
			break;
		}
	}
	if (Socket->GetGameState() == "start") {
		cout << Socket->GetGameState();
		ZeroSceneMgr->ChangeScene(new TestScene());
	}
	//if (ZeroInputMgr->GetKey(VK_ESCAPE) == INPUTMGR_KEYDOWN) {
	//	Socket->CloseServer();
	//}
}
