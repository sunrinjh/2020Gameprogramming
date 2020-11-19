#include "stdafx.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "Stage1.h"

TitleScene::TitleScene()
{
	//¹è°æÀ½¾Ç
	ZeroSoundMgr->PushSound("Resources/Sounds/TitleBGM.mp3", "Title");
	ZeroSoundMgr->PushChannel("Title", "TChannel");

	titleText = new ZeroFont(100, "Element Dungeon", "µÕ±Ù¸ğ²Ã", "Resources/Fonts/DungGeunMo.ttf");
	startSprite = new ZeroSprite("Resources/Sprites/UI/StartScene/start.png");
	exitSprite = new ZeroSprite("Resources/Sprites/UI/StartScene/exit.png");
	

	startSprite->SetPos(SCREEN_WIDTH / 2 - (startSprite->Width() / 2), SCREEN_HEIGHT / 2 - (startSprite->Height() / 2));
	exitSprite->SetPos(SCREEN_WIDTH / 2 - (exitSprite->Width() / 2), SCREEN_HEIGHT / 2 - (exitSprite->Height() / 2));

	PushScene(titleText);
	PushScene(startSprite);
	PushScene(exitSprite);

	titleText->SetColor(0xFF000000);
	
	startSprite->SetPosY(550);
	exitSprite->SetPosY(700);

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(1234);
	tAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	send(hSocket, cMsg.c_str(), cMsg.length(), 0);
	char cBuffer[1024] = {};
	recv(hSocket, cBuffer, 1024, 0);

}

TitleScene::~TitleScene()
{

}

void TitleScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_LBUTTON) && startSprite->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
		ZeroSceneMgr->ChangeScene(new Stage1());
		
	}
	else if (ZeroInputMgr->GetKey(VK_LBUTTON) && exitSprite->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
		//PostQuitMessage(0);
	}
	cMsg = to_string(eTime);
	send(hSocket, cMsg.c_str(), cMsg.length(), 0);
}

void TitleScene::Render()
{
	ZeroIScene::Render();
	titleText->Render();
	startSprite->Render();
	exitSprite->Render();
}
