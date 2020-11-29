#pragma once
#include <Zero.h>
#include "SocketClient.h"
class CreateRoom : public ZeroIScene
{
private:
	ZeroFont* clickNumberToMakeRoom;
	ZeroFont* currentPlayerCount;
	ZeroFont* errorMessage;
	bool waitForClient;
	int roomsize;
public:
	CreateRoom();
	~CreateRoom();
	void Render();
	void Update(float eTime);

};

