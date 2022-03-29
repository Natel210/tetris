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
	// �ʱ����
	bool init(schar* IP, u_short PORT);
	// ����Ʈ�� �ʿ��ϰ�......
	void reboot(schar* IP, u_short PORT);
	//���Ű� �ʿ��ϰ�
	void release();
	
public:
	void Send();
	void Recv();

private:
	/////////////////////////////////
	std::list<CommonPacket> m_Sendpacklist;
	std::list<CommonPacket> m_Recvpacklist;

	// �ְ� �ް� �ʿ��ϰ�.  //�׻� ���ư��� �־�� �Ѵ�.

	//////////////////////////////////
	//���� ����ϴ� Ŭ���̾�Ʈ���� ���� �־��.
public:
	void PushSend(CommonPacket& msg);
	CommonPacket PopRecv();
	CommonPacket PopRecv(int LinkNumver, int Location1 = 0, int Location2 = 0, int Work = 0, int Item = 0);
private:
	bool DuplicateRecvPack(CommonPacket msg);
	bool DuplicateSendPack(CommonPacket msg);
	//////////////////////////////////
	//����� ���
	//////////////////////////////////

	//�ܼ����
private:
	std::vector<Tstring> m_strLogvec;
public:
	void PrintLog();
	void LogClear();

	// ���� ���� �����̸�, ��ġ, ����� �����ش�.
	// �ϴ��� �̵����� ���� ���� �´� �Ǵ��̴�.
	// �׷��� �ϴ� �����츦 �����.... ������Ʈ���� ���� �ʿ�� ���忡�� ����.


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
