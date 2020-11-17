#include <iostream>
#include <WinSock2.h>
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
	char cBuffer[PACKET_SIZE] = {};
	while (1) {
		int len = recv(hClient, cBuffer, PACKET_SIZE, 0);
		// 예기치 않은 문자가 마지막에 담아졌을 수 있으므로 마지막은 NULL 문자 처리
		std::cout << cBuffer << '\n';
		if (strcmp(cBuffer, "[exit]") == 0) {
			send(hClient, cMsg, strlen(cMsg), 0);
			std::cout << "서버 종료";
			break;
		}
		send(hClient, cMsg, strlen(cMsg), 0);
	}

	closesocket(hClient);
	closesocket(hListen);


	WSACleanup();
	return 0;
}