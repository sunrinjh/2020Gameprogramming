#include "stdafx.h"
#include "SocketClient.h"

SocketClient::SocketClient()
{
	cout << "Socket Client Object Created" << endl;
	playerNumber = 0;
}

SocketClient::~SocketClient()
{
}

void SocketClient::Init()
{
	cout << "SocketClient Init" << endl;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(1234);
	tAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));
}

void SocketClient::Init(string ip)
{
	cout << "SocketClient Init" << endl;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(1234);
	tAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));
	//send(hSocket, "test", 1024, 0);
}

void SocketClient::SetIp(string ip)
{
	tAddr.sin_addr.s_addr = inet_addr(ip.c_str());
}

void SocketClient::JoinServer()
{
	send(hSocket, "join", 1024, 0);
	ZeroMemory(cBuffer, 1024);
	recv(hSocket, cBuffer, 1024, 0);
	playerNumber = stoi(cBuffer);
	cout << "Player Number : " << playerNumber << endl;
}

int SocketClient::GetPlayerNumber()
{
	return playerNumber;
}

void SocketClient::SendPlayerPos(ZeroVec* zeroVec)
{
	float x = zeroVec->x;
	float y = zeroVec->y;
	
	string msg = "pos" + to_string(playerNumber) + "," + to_string(x) + "," + to_string(y) + '\0';
	send(hSocket, msg.c_str(), msg.length(), 0);
}

ZeroVec* SocketClient::GetPlayerPos()
{
	ZeroMemory(cBuffer, 1024);
	recv(hSocket, cBuffer, 1024, 0);
	vector<string> vector_string;
	string temp_string;
	string s = cBuffer;
	stringstream ss;
	if (s.substr(0,3) == "pos") {
		ss.str(cBuffer);
		while (getline(ss, temp_string, ',')) {

			vector_string.push_back(temp_string);
			cout << temp_string << endl;
		}
	}
	return *playerPos;
}

void SocketClient::CoutServerMessage()
{
	ZeroMemory(cBuffer, 1024);
	recv(hSocket, cBuffer, 1024, 0);
	if (cBuffer != nullptr) {
		cout << cBuffer << endl;
	}
}
