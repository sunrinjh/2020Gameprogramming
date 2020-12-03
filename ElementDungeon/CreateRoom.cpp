#include "stdafx.h"
#include "CreateRoom.h"
#include "TestScene.h"
CreateRoom::CreateRoom()
{
	Socket->MakeServer();
	waitFont = new ZeroFont(60, "������Դϴ�", "�ձٸ��", "Resources/Fonts/DungGeunMo.ttf");
	errorFont = new ZeroFont(60, "", "�ձٸ��", "Resources/Fonts/DungGeunMo.ttf");
	playerCounterFont = new ZeroFont(60, "���� �ο� : 1", "�ձٸ��" , "Resources/Fonts/DungGeunMo.ttf");
	startSprite = new ZeroSprite("Resources/Sprites/UI/start.png");

	waitFont->SetColor(0xFF000000);
	errorFont->SetColor(0xFFFF0000);
	playerCounterFont->SetColor(0xFF000000);


	PushScene(startSprite);
	PushScene(waitFont);
	PushScene(playerCounterFont);
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
	playerCounterFont->Render();
}

void CreateRoom::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	string s = "���� �ο� : ";
	s.append(to_string(Socket->GetCurrentPlayerNumber()));
	playerCounterFont->SetString(s);
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
			errorFont->SetString("�ο��� ������� �ʽ��ϴ�");
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
