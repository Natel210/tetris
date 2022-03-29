// ConsoleServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#include "stdafx.h"
#include "ServerProgress.h"
#include <thread>
#include <process.h>
#include <windows.h>


static bool Boot = true;

static BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	case CTRL_BREAK_EVENT:
	{
		ControllerServer::release();
		NetCore::release();
		TimeManager::release();
		if (ControllerServer::m_pProgress)
		{
			ControllerServer::getSingle()->ServerClose();
			delete ControllerServer::m_pProgress;
			ControllerServer::m_pProgress = nullptr;
		}

		//MessageBox(ClientCore::mainhWnd, TEXT("F4�� ������� �ʰ� ����ÿ��� ������ ���ѵ˴ϴ�."), TEXT("���"), 0);


		break;
	}
	default:
		break;
	}
	return false;
}


int main()
{
	//setlocale(LC_ALL, "");
	std::wcout.imbue(std::locale("KOR"));
	//std::locale::global(std::locale("KOR"));


#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(146);
	int * newint = new int;
#endif // _DEBUG
	

	BOOL EXIT = SetConsoleCtrlHandler(PHANDLER_ROUTINE(CtrlHandler), TRUE);


	TimeManager::init();



	ControllerServer::inst();
	ControllerServer::m_pProgress = new ServerProgress;
	ControllerServer::getSingle()->init(IP,PORT);
	////////////////////////////////////////////////////////////////////////////
	//�����带 ���� ���� ����
	//HANDLE AcceptHandle = (HANDLE)_beginthreadex(nullptr, 0, ControllerServer::AcceptClient, (void*)nullptr, 0, nullptr);
	//WaitForSingleObject(AcceptHandle, TWOSTOPBITS);

	NetCore::Init();

	while (Boot)
	{
		if (!EXIT)
		{
			ControllerServer::getSingle()->EventSelectRealease();
			NetCore::SavePlayer();
			ControllerServer::release();
			NetCore::release();
			TimeManager::release();
		}
		if (GetAsyncKeyState(VK_F4) & 0x8000)
		{
			//ControllerServer::getSingle()->EventSelectRealease();
			//NetCore::SavePlayer();
			//ControllerServer::release();
			//NetCore::release();
			//TimeManager::release();
			Boot = false;
		}

		///////////////////////////////////////////////
		float delthtime = 0;
		if (TimeManager::IsTimer(_T("MainTime")))
		{
			//�ð������� �Ҵ� ����
			TimeManager::FindTimer(_T("MainTime"))->EndCheck();
			TimeManager::FindTimer(_T("MainTime"))->StartCheck();
			delthtime = MainTime;
		}

		ServerProgressBase::m_fSurverTime += delthtime;
		if (ServerProgressBase::m_fSurverTime > 3.0e+38F)
		{
			++ServerProgressBase::m_iSurverTimeUp;
			ServerProgressBase::m_fSurverTime -= 3.0e+38F;
		}
		NetCore::ClearRooms();

		int results = 0;
		results = ControllerServer::getSingle()->EventSelect();

		if (results == 0)
		{
			Boot = false;
		}

	

		////////////////////////////////////////////////////////
		//������ Ư���ð� ���� ������ �����ؾ߰ڴ�.
		//�����Ŀ� ����

		//







		//////////////////////////////////////////////////////////





		//�����
		//std::cout << "�����ð�: " << ServerProgressBase::m_iSurverTimeUp << ServerProgressBase::m_fSurverTime << "   ��ŸŸ��: " << delthtime << "   FPS: " << 1/delthtime << std::endl;


		//Sleep(5);
	}

	ControllerServer::getSingle()->EventSelectRealease();
	NetCore::SavePlayer();
	ControllerServer::release();
	NetCore::release();
	TimeManager::release();
	


    return 0;
}

