#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "UserErrorCode.h"
#include "UserPacket.h"

#pragma comment(lib, "ws2_32")


class UseServer
{
private:
	static int m_iLastUptime;
	static float m_fLastTime;
private:
	SOCKET UserSocket;
	bool m_bServerClose = true;
	bool m_bIsSend = false;
	bool m_bIsRecv = false;


	bool m_bserverconect = false;
public:
	bool getconected() const {
		return m_bserverconect;
	}


public:
	int MyUniqueNum = -1;
public:
	void ServerClose()
	{
		m_bServerClose = false;
		m_bserverconect = false;
	}

private:
	static CRITICAL_SECTION m_eCritical;
	static CRITICAL_SECTION m_eCriticalSend;
	static CRITICAL_SECTION m_eCriticalRecv;


public:
	// 초기상태
	bool init(schar* IP, u_short PORT);
	// 리부트가 필요하고......
	void reboot(schar* IP, u_short PORT);
	//제거가 필요하고
	void release();
	
public:
	void Send();
	void Recv();

private:
	/////////////////////////////////
	std::list<CommonPacket> m_Sendpacklist;
	std::list<CommonPacket> m_Recvpacklist;

	// 주고 받고 필요하고.  //항상 돌아가고 있어야 한다.

	//////////////////////////////////
	//실제 사용하는 클라이언트에서 직접 넣어라.
public:
	void PushSend(CommonPacket& msg);
	CommonPacket PopRecv();
	CommonPacket PopRecv(int LinkNumver, int Location1 = 0, int Location2 = 0, int Work = 0, int Item = 0);
private:
	bool DuplicateRecvPack(CommonPacket msg);
	bool DuplicateSendPack(CommonPacket msg);
	//////////////////////////////////
	//디버그 기능
	//////////////////////////////////

	//콘솔출력
private:
	std::vector<Tstring> m_strLogvec;
public:
	void PrintLog();
	void LogClear();

	// 나는 나의 고유이름, 위치, 방식을 보내준다.
	// 일단은 이동부터 만든 것이 맞는 판단이다.
	// 그러면 일단 윈도우를 만들고.... 컴포넌트까지 만들 필요는 당장에는 없다.


public:

	static unsigned __stdcall Recvs(void* p)
	{
		static_cast<UseServer*>(p)->Recv();
		return 1;
	}

	static unsigned __stdcall Sends(void* p)
	{
		static_cast<UseServer*>(p)->Send();
		return 1;
	}

public:
	UseServer();
	~UseServer();
};
