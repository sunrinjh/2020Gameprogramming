#pragma once
#include <Zero.h>
#include "SocketClient.h"
class CreateRoom : public ZeroIScene
{
private:
	ZeroFont* waitFont;
	ZeroFont* errorFont;
	ZeroFont* playerCounterFont;
	ZeroSprite* startSprite;
	bool waitForClient;
	int roomsize;
public:
	CreateRoom();
	~CreateRoom();
	void Render();
	void Update(float eTime);

};

