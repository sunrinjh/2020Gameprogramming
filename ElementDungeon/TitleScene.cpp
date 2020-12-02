#include "stdafx.h"
#include "TitleScene.h"
#include "CreateRoom.h"
#include "JoinRoom.h"

TitleScene::TitleScene()
{
	createSprite = new ZeroSprite("Resources/Sprites/UI/StartScene/create.png");
	joinSprite = new ZeroSprite("Resources/Sprites/UI/StartScene/join.png");
	backgroundSprite = new ZeroSprite("Resources/Sprites/UI/StartScene/background.png");
	pacmanAnimation = new ZeroAnimation(4.f);
	pacmanAnimation->PushSprite("Resources/Sprites/UI/StartScene/pacman_0.png");
	pacmanAnimation->PushSprite("Resources/Sprites/UI/StartScene/pacman_1.png");
	
	backboard = new ZeroSprite("Resources/Sprites/UI/StartScene/pacmanbackboard.png");
	backboard->SetPos(-930, 100);
	exitSprite = new ZeroSprite("Resources/Sprites/UI/StartScene/exit.png");
	exitSprite->SetPos(30, 1000);

	exitText = new ZeroFont(50, "-> 정말로요? 정말이면 Y를 눌러주세요....", "둥근모꼴", "Resources/Fonts/DungGeunMo.ttf");
	exitText->SetColor(0xFFFF0000);
	exitText->SetPos(350, 1000);
	createSprite->SetPos(SCREEN_WIDTH / 2 - (createSprite->Width() / 2), SCREEN_HEIGHT / 2 - (createSprite->Height() / 2));
	joinSprite->SetPos(SCREEN_WIDTH / 2 - (joinSprite->Width() / 2), SCREEN_HEIGHT / 2 - (joinSprite->Height() / 2));
	pacmanAnimation->SetPos(-130, 20);
	PushScene(backgroundSprite);
	PushScene(createSprite);
	PushScene(joinSprite);
	PushScene(pacmanAnimation);
	PushScene(backboard);
	
	createSprite->SetPosY(550);
	joinSprite->SetPosY(700);
	
	
	
}

TitleScene::~TitleScene()
{

}

void TitleScene::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	backboard->AddPosX(200 * eTime);
	pacmanAnimation->AddPosX(200 * eTime);
	if (pacmanAnimation->Pos().x > 2000) {
		backboard->AddPosX(-3000);
		pacmanAnimation->AddPosX(-3000);
	}
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN && createSprite->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
		ZeroSceneMgr->ChangeScene(new CreateRoom());
		
	}
	else if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN && joinSprite->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
		ZeroSceneMgr->ChangeScene(new JoinRoom());
	}
	else if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN && exitSprite->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
		if (!exitState[0]) {
			exitState[0] = true;
		}
	}
	if (exitState[0] && ZeroInputMgr->GetKey('Y')) {
		PostQuitMessage(0);
	}

}

void TitleScene::Render()
{
	ZeroIScene::Render();
	backgroundSprite->Render();
	createSprite->Render();
	joinSprite->Render();
	backboard->Render();
	pacmanAnimation->Render();
	exitSprite->Render();
	if (exitState[0]) {
		exitText->Render();
	}
}
