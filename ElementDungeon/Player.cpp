#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	upIdleAnimation = new ZeroAnimation(1.0f);
	for (int i = 1; i <= 1; i++) {
		upIdleAnimation->PushSprite("Resources/Sprites/Character/up_idle.png");
	}
	rightIdleAnimation = new ZeroAnimation(1.0f);
	for (int i = 1; i <= 1; i++) {
		rightIdleAnimation->PushSprite("Resources/Sprites/Character/right_idle.png");
	}
	downIdleAnimation = new ZeroAnimation(1.0f);
	for (int i = 1; i <= 1; i++) {
		downIdleAnimation->PushSprite("Resources/Sprites/Character/down_idle.png");
	}

	rightIdleAnimation->SetScalingCenter(rightIdleAnimation->GetCurrentSprite()->Width() / 2, rightIdleAnimation->GetCurrentSprite()->Height() / 2);

	attackAnimation = new ZeroAnimation(3.0f);
	walkAnimation = new ZeroAnimation(3.0f);
	health = 10;
	moveSpeed = 10;
	PushScene(upIdleAnimation);
	PushScene(rightIdleAnimation);
	PushScene(attackAnimation);
	PushScene(downIdleAnimation);
	PushScene(walkAnimation);
}

Player::~Player()
{
}

void Player::Render()
{
	ZeroIScene::Render();
	if (movingPosition.top) {
		upIdleAnimation->Render();
	}
	if (movingPosition.buttom) {
		downIdleAnimation->Render();
	}
	if (movingPosition.right || movingPosition.left) {
		rightIdleAnimation->Render();
	}
	attackAnimation->Render();
	walkAnimation->Render();
}

void Player::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey('W') == INPUTMGR_KEYON) {
		if (moveable.top) {
			this->AddPosY(-300 * eTime);
		}
		SetMovingPosition(true, false, false, false);
	}

	if (ZeroInputMgr->GetKey('S') == INPUTMGR_KEYON) {
		if (moveable.buttom) {
			this->AddPosY(300 * eTime);
		}
		SetMovingPosition(false, true, false, false);
	}
	if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON) {
		if (moveable.right) {
			this->AddPosX(300 * eTime);
		}
		SetMovingPosition(false, false, false, true);
		rightIdleAnimation->SetScale(1, 1);
	}
	if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON) {
		if (moveable.left) {
			this->AddPosX(-300 * eTime);
		}
		rightIdleAnimation->SetScale(-1, 1);
		SetMovingPosition(false, false, true, false);

	}

}
