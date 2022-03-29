#pragma once
// TestConsolcn.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

//#include "stdafx.h"

//#include <WS2tcpip.h>
//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")
//#include <string.h>

#define BUF_SIZE 1024


int main()
{


	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUF_SIZE];
	int strLen;
	SOCKADDR_IN servAdr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (hSocket == INVALID_SOCKET)
	{
	}

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("172.20.13.13");
	servAdr.sin_port = htons(4560);

	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{

	}
	else
	{
		//puts
	}

	while (1)
	{
		fputs("Send Message (Exit -> E)", stdout);
		fgets(message, BUF_SIZE, stdin);
		if (!strcmp(message, "E\n") || !strcmp(message, "e\n"))
		{
			break;
		}

		send(hSocket, message, (int)strlen(message), 0);
		strLen = recv(hSocket, message, BUF_SIZE - 1, 0);
		message[strLen] = 0;
		printf_s("message : %s", message);
	}
	closesocket(hSocket);
	WSACleanup();


	return 0;
}