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

}

void TitleScene::Render()
{
	ZeroIScene::Render();
	titleText->Render();
	startSprite->Render();
	exitSprite->Render();
}
