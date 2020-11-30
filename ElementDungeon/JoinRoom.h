#pragma once
#include <Zero.h>

class JoinRoom : public ZeroIScene
{
private:
	string ip;
	ZeroFont* ipFont;
	ZeroFont* errorMessage;
	int playerNumber;
	bool serverJoined;
public:
	JoinRoom();
	~JoinRoom();
	void Render();
	void Update(float eTime);
	void IpInput();
};

