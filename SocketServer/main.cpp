#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Vector2.h"
#include <vector>
#include <sstream>
using namespace std;
#pragma comment(lib, "ws2_32")
#define BUFSIZE 1024

int playerNumber = 0;
vector<Vector2*> playerPos;
string gamestate = "wait";
DWORD WINAPI ProcessClient(LPVOID arg)
{
    SOCKET client_sock = (SOCKET)arg;
    char buf[BUFSIZE + 1];
    SOCKADDR_IN clientaddr;
    int addrlen;
    int retval;

    addrlen = sizeof(clientaddr);
    getpeername(client_sock, (SOCKADDR*)&clientaddr, &addrlen);



    // 클라이언트와 데이터 통신
    while (1)
    {
        retval = recv(client_sock, buf, BUFSIZE, 0);
        if (retval == SOCKET_ERROR)
        {
            cout << "수신() 에러\n";
            break;
        }
        else if (retval == 0)
            break;
        

        // 받은 데이터 출력
        buf[retval] = '\0';
        string s = buf;
        //printf("[TCP /%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buf);
        if ((strcmp(buf, "join")) == 0) {
            ++playerNumber;
            playerPos.push_back(new Vector2());
            retval = send(client_sock, to_string(playerNumber).c_str(),to_string(playerNumber).size(), 0);

        }
        if ((strcmp(buf, "start")) == 0) {
            gamestate = "start";
            
        }
        if ((strcmp(buf, "gameclear")) == 0) {
            gamestate = "gameclear";
        }
        if ((strcmp(buf, "gameover")) == 0) {
            gamestate = "gameover";
        }
        if ((strcmp(buf, "gamestate")) == 0) {
            retval = send(client_sock, gamestate.c_str(), gamestate.size(), 0);
        }
        if ((strcmp(buf, "currentplayernum")) == 0) {
            retval = send(client_sock, to_string(playerNumber).c_str(), 1024, 0);
        }
        if (s.substr(0, 3) == "pos") {
            stringstream ss;
            ss.str(s);
            vector<string> tempStringVector;
            string tempString;
            while (getline(ss, tempString, ',')) {
                tempStringVector.push_back(tempString);

            }
            switch (s.at(3))
            {
            case '1':
                playerPos[0]->x = stof(tempStringVector[1]);
                playerPos[0]->y = stof(tempStringVector[2]);
                break;
            case '2':
                playerPos[1]->x = stof(tempStringVector[1]);
                playerPos[1]->y = stof(tempStringVector[2]);
                break;
            case '3':
                playerPos[2]->x = stof(tempStringVector[1]);
                playerPos[2]->y = stof(tempStringVector[2]);
                break;
            case '4':
                playerPos[3]->x = stof(tempStringVector[1]);
                playerPos[3]->y = stof(tempStringVector[2]);
                break;
            default:
                break;
            }
            string posSend = "pos";
            for (int i = 0; i < playerPos.size(); i++) {
                posSend.append(",");
                posSend.append(to_string(playerPos[i]->x));
                posSend.append(",");
                posSend.append(to_string(playerPos[i]->y));

            }
            posSend.append("\0");
            retval = send(client_sock, posSend.c_str(), 1024, 0);
		}


        if (retval == SOCKET_ERROR)
        {
            printf("송신() 에러\n");
            break;
        }
    }



    // closesocket()
    closesocket(client_sock);
    printf("TCP 서버, 클라이언트 종료 : IP 주소 = %s, 포트번호 = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

    return 0;

}

int main()
{
  
    // 윈속초기화
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    // 리턴 값 저장시킬 변수
    int return_val;

    // socket() 
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) printf("소켓() 에러염\n");


    long port;
    port = 1234;

    // bind()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1234);

    /*
    XP 이전에는 INADDR_ANY의 값에 빈 스트링을 넘겨줄 경우 INADDR_ANY로 세팅되었지만,
    2003 이후로는 INADDR_NONE의 에러값을 넘겨준다, INADDR_NONE은 IP대역이 A.B.C.D 중 하나라도 255를 초과 할 경우 세팅
    INADDR_ANY는 어느 주소로 접속하던 접속을 받아들인다.
    */

    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    return_val = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)); // connect가 아니라 bind

    if (return_val == SOCKET_ERROR) printf("바인딩() 에러염\n");

    // listen()
    return_val = listen(listen_sock, SOMAXCONN);
    if (return_val == SOCKET_ERROR) printf("리슨() 에러염\n");

    // 데이터 통신에 사용할 변수
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    char buf[BUFSIZE + 1];
    int addrlen;

    HANDLE hThread;              // 스레드 핸들
    DWORD ThreadID;              // 스레드 아이디

    // 서버와 데이터 통신 
    while (1)
    {
        // accept()
        addrlen = sizeof(clientaddr);

        client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            printf("accept() 에러\n");
            continue;
        }
        
        printf("TCP 서버, 클라이언트 접속 : IP 주소 = %s, 포트번호 = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, &ThreadID);
        if (hThread == NULL)
        {
            printf("스레드 생성 실패ㅠㅠ\n");
        }
        else
        {
            CloseHandle(hThread);
        }

    }

    closesocket(listen_sock);

    // 윈속 종료
    WSACleanup();
    return 0;

}



//#include <iostream>
//#include <WinSock2.h>
//#include <vector>
//#include <string>
//#include "Vector2.h"
//#include <sstream>
//using namespace std;
//#pragma comment(lib, "ws2_32")
//
//#define PORT 1234
//#define PACKET_SIZE 1024
//int main() {
//	WSADATA wsaData;
//	WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//	SOCKET hListen;
//	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//	
//	SOCKADDR_IN tListenAddr = {};
//	tListenAddr.sin_family = AF_INET;
//	tListenAddr.sin_port = htons(PORT);
//	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//
//	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
//	listen(hListen, SOMAXCONN);
//
//	SOCKADDR_IN tClntAddr = {};
//	int iClntSize = sizeof(tClntAddr);
//	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);
//	char cMsg[] = "Server Send";
//	char cBuffer[1024] = {};
//
//	vector<Vector2*> playerPos;
//
//	playerPos.clear();
//	while (1) {
//		int len = recv(hClient, cBuffer, sizeof(cBuffer), 0);
//		string tempBuffer = cBuffer;
//		// 예기치 않은 문자가 마지막에 담아졌을 수 있으므로 마지막은 NULL 문자 처리
//		if (strcmp(cBuffer, "[exit]") == 0) {
//			send(hClient, cMsg, strlen(cMsg), 0);
//			std::cout << "서버 종료";
//			break;
//		}
//		if (strcmp(cBuffer, "join") == 0) {
//			playerPos.push_back(new Vector2());
//			//string tempString;
//			//tempString = "join " + playerPos.size();
//			//send(hClient, tempString.c_str(), tempString.length(), 0);
//		}
//		if (tempBuffer.substr(0, 3) == "pos") {
//			stringstream ss;
//			ss.str(tempBuffer);
//			vector<string> tempStringVector;
//			string tempString;
//			while (getline(ss, tempString, ',')) {
//				tempStringVector.push_back(tempString);
//				
//			}
//			cout << tempStringVector[1] << " , ";
//			cout << tempStringVector[2] << endl;
//
//		}
//
//	}
//
//	closesocket(hClient);
//	closesocket(hListen);
//
//
//	WSACleanup();
//	return 0;
//}