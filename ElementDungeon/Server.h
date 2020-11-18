#pragma once
#include <Zero.h>
class Server
{
public:
	Server();
	~Server();
	void RunServer();
private:
	WSADATA wsaData;
	SOCKET hListen, hClient;
	SOCKADDR_IN tListenAddr;
	int iClntSize;
	SOCKADDR_IN tClntAddr = {};
	char cBuffer[1024] = {};
	char cMsg[12] = "Server Send";
};

