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
	send(hSocket, "test", 1024, 0);
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
	send(hSocket, "test", 1024, 0);
}

void SocketClient::SetIp(string ip)
{
	tAddr.sin_addr.s_addr = inet_addr(ip.c_str());
}

void SocketClient::JoinServer()
{
	send(hSocket, "join", 1024, 0);
	ZeroMemory(cBuffer, 1024);
	//recv(hSocket, cBuffer, 1024, 0);
	//cout << cBuffer << endl;
	//playerNumber = stoi(cBuffer);

}

int SocketClient::GetPlayerNumber()
{
	return playerNumber;
}

void SocketClient::SendPlayerPos(ZeroVec* zeroVec)
{
	float x = zeroVec->x;
	float y = zeroVec->y;
	
	string msg = "pos," + to_string(x) + "," + to_string(y) + '\0';
	send(hSocket, msg.c_str(), msg.length(), 0);
}

ZeroVec* SocketClient::GetPlayerPos()
{
	ZeroMemory(cBuffer, 1024);
	recv(hSocket, cBuffer, 1024, 0);
	if (cBuffer != nullptr) {
		ss.str(cBuffer);
		tempStringVector.clear();
		while (getline(ss, tempString, ',')) {
			tempStringVector.push_back(tempString);
		}
		int index = 0;
		int jindex = 0;
		for (auto iter = tempStringVector.begin(); iter != tempStringVector.end(); iter++) {

			if (jindex == 0) {
				playerPos[index]->x = stof((*iter));
				jindex++;
			}
			else if (jindex == 1) {
				playerPos[index]->y = stof((*iter));
				index++;
				jindex = 0;
			}

		}
	}
	return *playerPos;
}
