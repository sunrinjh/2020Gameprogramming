#include "stdafx.h"
#include "JoinRoom.h"
#include "SocketClient.h"
#include "TestScene.h"
JoinRoom::JoinRoom()
{
	ip = "호스트의 IP를 입력하고 엔터를 눌러주세요. 정확하게 입력했는데 접속이 안되면 1234포트를 열어달라고 찡찡대면 됩니다.";
	ipFont = new ZeroFont(30, "","둥근모꼴", "Resources/Fonts/DungGeunMo.ttf");
	errorMessage = new ZeroFont(30, "", "둥근모꼴", "Resources/Fonts/DungGeunMo.ttf");
	
	ipFont->SetColor(0xFF000000);
	errorMessage->SetColor(0xFFFF0000);
	errorMessage->SetPos(0, 30);
	ipFont->SetPos(0, 180);
	serverJoined = false;

	//ip.clear();
}

JoinRoom::~JoinRoom()
{

}

void JoinRoom::Render()
{
	ZeroIScene::Render();
	ipFont->Render();
	errorMessage->Render();
}

void JoinRoom::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	ipFont->SetString(ip);
	IpInput();
	if (ZeroInputMgr->GetKey(VK_RETURN) == INPUTMGR_KEYDOWN && !serverJoined) {
		int count = 0;
		for (int i = 0; i < ip.size(); i++) {
			if (ip[i] == '.') {
				count++;
			}
		}
		if (count == 3) {
			if (Socket->Init(ip) == SOCKET_ERROR) {
				errorMessage->SetString("접속 오류");
			}
			else {
				Socket->JoinServer();
				serverJoined = true;
			}
		}
		else {
			errorMessage->SetString("정확하지 않은 ip 값입니다");
		}
	}
	if (serverJoined) {
		if (Socket->GetGameState() == "start") {
			ZeroSceneMgr->ChangeScene(new TestScene());
		}
	}
}

void JoinRoom::IpInput()
{
	if (!serverJoined) {
		if (ip.length() != 15) {
			if (ZeroInputMgr->GetKey(0x30) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("0");
			}
			if (ZeroInputMgr->GetKey(0x31) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("1");
			}
			if (ZeroInputMgr->GetKey(0x32) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("2");
			}
			if (ZeroInputMgr->GetKey(0x33) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("3");
			}
			if (ZeroInputMgr->GetKey(0x34) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("4");
			}
			if (ZeroInputMgr->GetKey(0x35) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("5");
			}
			if (ZeroInputMgr->GetKey(0x36) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("6");
			}
			if (ZeroInputMgr->GetKey(0x37) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("7");
			}
			if (ZeroInputMgr->GetKey(0x38) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("8");
			}
			if (ZeroInputMgr->GetKey(0x39) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					ip.clear();
				}
				ip.append("9");
			}
			if (ZeroInputMgr->GetKey(VK_OEM_PERIOD) == INPUTMGR_KEYDOWN) {
				if (ip.length() >= 100) {
					return;
				}
				ip.append(".");
			}
		}
		if (ZeroInputMgr->GetKey(VK_BACK) == INPUTMGR_KEYDOWN) {
			if (ip.length() >= 100) {
				ip.clear();
			}
			if (!ip.empty()) {
				ip.pop_back();
			}
		}
	}
}
