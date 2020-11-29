#include "stdafx.h"
#include "CreateRoom.h"

CreateRoom::CreateRoom()
{
	ShellExecute(NULL, _T("open"), _T("SocketServer.exe"), NULL, NULL, SW_SHOW);
	clickNumberToMakeRoom = new ZeroFont(30, "������Դϴ�", "�ü�");
	errorMessage = new ZeroFont(30, "", "�ü�");
	currentPlayerCount = new ZeroFont(30, "1", "�ü�");


	currentPlayerCount->SetColor(0xFF000000);
	clickNumberToMakeRoom->SetColor(0xFF000000);
	errorMessage->SetColor(0xFF000000);


	PushScene(errorMessage);
	PushScene(clickNumberToMakeRoom);
	PushScene(currentPlayerCount);
	currentPlayerCount->SetPos(0, 30);
	errorMessage->SetPos(0, 60);
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

	clickNumberToMakeRoom->Render();
	errorMessage->Render();
	currentPlayerCount->Render();
}

void CreateRoom::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	currentPlayerCount->SetString(Socket->GetCurrentPlayerNumber());
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
		switch (Socket->GetCurrentPlayerNumber()) {
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			errorMessage->SetString("�ο��� ������� �ʽ��ϴ�");
			break;
		}
	}
}
