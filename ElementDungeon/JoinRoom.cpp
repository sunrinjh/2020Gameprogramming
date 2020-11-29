#include "stdafx.h"
#include "JoinRoom.h"
#include "SocketClient.h"
JoinRoom::JoinRoom()
{
	ip = "호스트의 IP를 입력해주세요. 정확하게 입력했는데 접속이 안되면 1234포트를 열어달라고 찡찡대면 됩니다.";
	ipFont = new ZeroFont(30, "", "굴림");
	ipFont->SetColor(0xFF000000);
	
	//ip.clear();
}

JoinRoom::~JoinRoom()
{

}

void JoinRoom::Render()
{
	ZeroIScene::Render();
	ipFont->Render();
}

void JoinRoom::Update(float eTime)
{
	ZeroIScene::Update(eTime);
	ipFont->SetString(ip);
	IpInput();
	if (ZeroInputMgr->GetKey(VK_RETURN) == INPUTMGR_KEYDOWN) {
		Socket->Init(ip);
		Socket->JoinServer();
	}
}

void JoinRoom::IpInput()
{
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
