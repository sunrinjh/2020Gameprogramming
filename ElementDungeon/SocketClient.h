#pragma once
#include <Zero.h>

#define Socket SocketClient::instance()
class SocketClient
{
private:
    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    WSAData wsaData;
    SOCKET hSocket;
    SOCKADDR_IN tAddr = {};
    ZeroVec* playerPos[4] = { new ZeroVec(0,0), new ZeroVec(0,0) ,new ZeroVec(0,0) ,new ZeroVec(0,0)};
    int playerNumber;
    char cBuffer[1024] = {};

public:
    static SocketClient* instance() {
        static SocketClient* instance = new SocketClient();
        return instance;
    }


    SocketClient();
    ~SocketClient();
    void MakeServer();
    void CloseServer();
    void Init();
    int Init(string ip);
    void SetIp(string ip);
    int JoinServer();
    int GetPlayerNumber();
    int GetCurrentPlayerNumber();
    void SendPlayerPos(ZeroVec* zeroVec);
    void SendStringToServer(string s);
    void GetPlayerPos();
    string GetGameState();
    ZeroVec* GetPlayer1Pos();
    ZeroVec* GetPlayer2Pos();
    ZeroVec* GetPlayer3Pos();
    ZeroVec* GetPlayer4Pos();
    //Debug
    void CoutServerMessage();
};

