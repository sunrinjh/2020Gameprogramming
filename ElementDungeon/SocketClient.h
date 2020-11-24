#pragma once
#include <Zero.h>
class SocketClient
{
private:
    WSAData wsaData;
    SOCKET hSocket;
    SOCKADDR_IN tAddr = {};
    ZeroVec* playerPos[4] = { new ZeroVec(), };
    int playerNumber;
    char cBuffer[1024] = {};
    vector<string> tempStringVector;
    string tempString;
    stringstream ss;
public:
    SocketClient();
    ~SocketClient();
    void Init();
    void Init(string ip);
    void SetIp(string ip);
    void JoinServer();
    int GetPlayerNumber();
    void SendPlayerPos(ZeroVec* zeroVec);
    ZeroVec* GetPlayerPos();
    void CoutServerMessage();
};

