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



    // Ŭ���̾�Ʈ�� ������ ���
    while (1)
    {
        retval = recv(client_sock, buf, BUFSIZE, 0);
        if (retval == SOCKET_ERROR)
        {
            cout << "����() ����\n";
            break;
        }
        else if (retval == 0)
            break;
        

        // ���� ������ ���
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
            printf("�۽�() ����\n");
            break;
        }
    }



    // closesocket()
    closesocket(client_sock);
    printf("TCP ����, Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

    return 0;

}

int main()
{
  
    // �����ʱ�ȭ
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    // ���� �� �����ų ����
    int return_val;

    // socket() 
    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == INVALID_SOCKET) printf("����() ������\n");


    long port;
    port = 1234;

    // bind()
    SOCKADDR_IN serveraddr;
    ZeroMemory(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1234);

    /*
    XP �������� INADDR_ANY�� ���� �� ��Ʈ���� �Ѱ��� ��� INADDR_ANY�� ���õǾ�����,
    2003 ���ķδ� INADDR_NONE�� �������� �Ѱ��ش�, INADDR_NONE�� IP�뿪�� A.B.C.D �� �ϳ��� 255�� �ʰ� �� ��� ����
    INADDR_ANY�� ��� �ּҷ� �����ϴ� ������ �޾Ƶ��δ�.
    */

    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    return_val = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr)); // connect�� �ƴ϶� bind

    if (return_val == SOCKET_ERROR) printf("���ε�() ������\n");

    // listen()
    return_val = listen(listen_sock, SOMAXCONN);
    if (return_val == SOCKET_ERROR) printf("����() ������\n");

    // ������ ��ſ� ����� ����
    SOCKET client_sock;
    SOCKADDR_IN clientaddr;
    char buf[BUFSIZE + 1];
    int addrlen;

    HANDLE hThread;              // ������ �ڵ�
    DWORD ThreadID;              // ������ ���̵�

    // ������ ������ ��� 
    while (1)
    {
        // accept()
        addrlen = sizeof(clientaddr);

        client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
        if (client_sock == INVALID_SOCKET) {
            printf("accept() ����\n");
            continue;
        }
        
        printf("TCP ����, Ŭ���̾�Ʈ ���� : IP �ּ� = %s, ��Ʈ��ȣ = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, &ThreadID);
        if (hThread == NULL)
        {
            printf("������ ���� ���ФФ�\n");
        }
        else
        {
            CloseHandle(hThread);
        }

    }

    closesocket(listen_sock);

    // ���� ����
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
//		// ����ġ ���� ���ڰ� �������� ������� �� �����Ƿ� �������� NULL ���� ó��
//		if (strcmp(cBuffer, "[exit]") == 0) {
//			send(hClient, cMsg, strlen(cMsg), 0);
//			std::cout << "���� ����";
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