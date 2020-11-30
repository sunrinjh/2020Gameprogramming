#include "stdafx.h"
#include "SocketClient.h"

SocketClient::SocketClient()
{
	cout << "Socket Client Object Created" << endl;
	playerNumber = 0;
	for (int i = 0; i < 4; i++) {
		playerPos[i]->x = 0;
		playerPos[i]->y = 0;
	}
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

int SocketClient::Init(string ip)
{
	cout << "SocketClient Init" << endl;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(1234);
	tAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	int connectResult = connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));
	return connectResult;
	//send(hSocket, "test", 1024, 0);
}

void SocketClient::SetIp(string ip)
{
	tAddr.sin_addr.s_addr = inet_addr(ip.c_str());
}

int SocketClient::JoinServer()
{
	int retval = send(hSocket, "join", 5, 0);
	if (retval != SOCKET_ERROR) {
		ZeroMemory(cBuffer, 1024);
		if (recv(hSocket, cBuffer, 1024, 0) != SOCKET_ERROR) {
			playerNumber = stoi(cBuffer);
			cout << "Player Number : " << playerNumber << endl;
			return retval;
		}
	}
	else {
		return retval;
	}
	
}

int SocketClient::GetPlayerNumber()
{
	return playerNumber;
}

int SocketClient::GetCurrentPlayerNumber()
{
	send(hSocket, "currentplayernum\0", 1024, 0);
	ZeroMemory(cBuffer, 1024);
	int tempInt = 0;
	if (recv(hSocket, cBuffer, 1024, 0) != SOCKET_ERROR) {
		tempInt = stoi(cBuffer);
	}
	return tempInt;
}

void SocketClient::SendPlayerPos(ZeroVec* zeroVec)
{
	float x = zeroVec->x;
	float y = zeroVec->y;
	
	string msg = "pos" + to_string(playerNumber) + "," + to_string(x) + "," + to_string(y) + '\0';
	send(hSocket, msg.c_str(), msg.length(), 0);
}

void SocketClient::SendStringToServer(string s)
{
	send(hSocket, s.c_str(), s.length(), 0);
}

void SocketClient::GetPlayerPos()
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
		}
	}
	int j = 0;
	for (int i = 1; i < vector_string.size(); i+=2) {
		playerPos[j]->x = stof(vector_string[i]);
		playerPos[j]->y = stof(vector_string[i + 1]);
		j++;
	}
	cout << playerPos[1]->x << endl;
}

string SocketClient::GetGameState()
{
	send(hSocket, "gamestate\0", 11, 0);
	ZeroMemory(cBuffer, 1024);

	if (recv(hSocket, cBuffer, 1024, 0) != SOCKET_ERROR) {
		return cBuffer;
	}
	else {
		return "wait";
	}
}

ZeroVec* SocketClient::GetPlayer1Pos()
{
	
	return playerPos[0];
}

ZeroVec* SocketClient::GetPlayer2Pos()
{
	return playerPos[1];
}

ZeroVec* SocketClient::GetPlayer3Pos()
{
	return playerPos[2];
}

ZeroVec* SocketClient::GetPlayer4Pos()
{
	return playerPos[3];
}


void SocketClient::CoutServerMessage()
{
	ZeroMemory(cBuffer, 1024);
	recv(hSocket, cBuffer, 1024, 0);
	if (cBuffer != nullptr) {
		cout << cBuffer << endl;
	}
}
