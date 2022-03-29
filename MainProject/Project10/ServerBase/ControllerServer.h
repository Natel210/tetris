#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

//////////////////////////////////////////
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include "UserPacket.h"
#include "UserErrorCode.h"

#pragma comment(lib, "ws2_32")

// �̱������� �����.
#define BUF_SIZE 1024
class ControllerServer
{
	WSADATA m_wsaData;
	SOCKET m_hServSock, m_hClntSock;
	SOCKADDR_IN m_servAdr, m_clntAdr;
	TIMEVAL m_timeout;
	fd_set m_reads, m_cpyReads;
	LPWSAOVERLAPPED m_lpOvLP;
	int m_adrSz;
	int m_strLen, m_fdNum;
	UINT m_i;
	CommonPacket buf;
	int mode = 1;
	//char buf[BUF_SIZE];

public:
	int EventSelect();
	void EventSelectRealease();
private:







	//////////////////////////////////////////////////////////////////////////////////////////
	static std::list<struct ClientsProfile>Clientslist;
	static int m_iAllCountNumber;
	static std::list<struct CommonPacket> m_Syscompack;
private:
	static class ControllerServer* m_pinst;
public:
	static class ServerProgressBase* m_pProgress;
public:
	static bool inst();
	static void release();
	static class ControllerServer* getSingle();
	static const std::list<struct ClientsProfile>* getClientlist();
	static void AllSendComment(struct CommonPacket _compack);
	static void AllSendclear();

	static ClientsProfile FindClientFromSock(SOCKET _sock);

private:
	static SOCKET ServerSocket;
	static bool m_bServerClose;
	fd_set readfds, otherfds, allfds;
	static fd_set testfds;


public:
	void ServerClose()
	{
		m_bServerClose = false;
	}

public:
	static CRITICAL_SECTION m_eCritical;
	

public:
	// �ʱ����
	bool init(schar* IP, u_short PORT);
	// ����Ʈ�� �ʿ��ϰ�......
	void reboot(schar* IP, u_short PORT);
	//���Ű� �ʿ��ϰ�
	

public:
	static unsigned __stdcall AcceptClient(void* arg);

	//���� ��Ʈ��Ʈ�� �������̴�.
	static unsigned __stdcall DoRecv(void*arg);		
	//static unsigned __stdcall DoSend(void * arg);

public:
	//const std::vector<int>& PrintCurClientsNum() const;
	//const std::unordered_map<int ,std::vector<Tstring>>& PrintLogAll() const;
	//const std::vector<Tstring>& PrintLog(int Num) const;

	void LogClear(int Num);
	void LogClearAll();


private:
	ControllerServer();
	~ControllerServer();
};

