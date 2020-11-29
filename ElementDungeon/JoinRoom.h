#pragma once
#include <Zero.h>

class JoinRoom : public ZeroIScene
{
private:
	string ip;
	ZeroFont* ipFont;
	int playerNumber;
public:
	JoinRoom();
	~JoinRoom();
	void Render();
	void Update(float eTime);
	void IpInput();
};

