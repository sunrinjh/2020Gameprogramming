#include "stdafx.h"
#include "Server.h"

Server::Server()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(1234);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);
	iClntSize = sizeof(tClntAddr);
	hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

}

Server::~Server()
{
	closesocket(hClient);
	closesocket(hListen);


	WSACleanup();
}

void Server::RunServer()
{
	while (1) {
		int len = recv(hClient, cBuffer, 1024, 0);
		// 예기치 않은 문자가 마지막에 담아졌을 수 있으므로 마지막은 NULL 문자 처리
		std::cout << cBuffer << '\n';
		if (strcmp(cBuffer, "[exit]") == 0) {
			send(hClient, cMsg, strlen(cMsg), 0);
			std::cout << "서버 종료";
			break;
		}
		send(hClient, cMsg, strlen(cMsg), 0);
	}
}
