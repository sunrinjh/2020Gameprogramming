#include <iostream>
#include <WinSock2.h>
#include <vector>
#include <string>
#include "Vector2.h"
#include <sstream>
using namespace std;
#pragma comment(lib, "ws2_32")

#define PORT 1234
#define PACKET_SIZE 1024
int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);

	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);
	char cMsg[] = "Server Send";
	char cBuffer[1024] = {};

	vector<Vector2*> playerPos;

	playerPos.clear();
	while (1) {
		int len = recv(hClient, cBuffer, sizeof(cBuffer), 0);
		string tempBuffer = cBuffer;
		// 예기치 않은 문자가 마지막에 담아졌을 수 있으므로 마지막은 NULL 문자 처리
		if (strcmp(cBuffer, "[exit]") == 0) {
			send(hClient, cMsg, strlen(cMsg), 0);
			std::cout << "서버 종료";
			break;
		}
		if (strcmp(cBuffer, "join") == 0) {
			playerPos.push_back(new Vector2());
			//string tempString;
			//tempString = "join " + playerPos.size();
			//send(hClient, tempString.c_str(), tempString.length(), 0);
		}
		if (tempBuffer.substr(0, 3) == "pos") {
			stringstream ss;
			ss.str(tempBuffer);
			vector<string> tempStringVector;
			string tempString;
			while (getline(ss, tempString, ',')) {
				tempStringVector.push_back(tempString);
				
			}
			cout << tempStringVector[1] << " , ";
			cout << tempStringVector[2] << endl;

		}

	}

	closesocket(hClient);
	closesocket(hListen);


	WSACleanup();
	return 0;
}