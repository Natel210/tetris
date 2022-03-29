//#include <WinSock2.h>
#include "UseServer.h"

#include <windows.h>
#include <thread>
#include <process.h>

//여기서만 사용할거야.
const static int MaxConnectCount = 10;
CRITICAL_SECTION UseServer::m_eCritical;
CRITICAL_SECTION UseServer::m_eCriticalSend;
CRITICAL_SECTION UseServer::m_eCriticalRecv;
int UseServer::m_iLastUptime = 0;
float UseServer::m_fLastTime = 0.0f;

static int sendcount = 0; 
static int recvcount = 0;
static int realrecvcount = 0;

void UseServer::PushSend(CommonPacket & msg)
{
	if (10000 == m_Sendpacklist.size())
	{
		//m_Sendpacklist.clear();
		return;
	}
	if (!m_bserverconect)
	{
		return;
	}

	//if (!getconected())
	//{
	//	return;
	//}


	msg.PacTime.ServerUpTime = m_iLastUptime;
	msg.PacTime.ServerTime = m_fLastTime;


	if (SOCKET_ERROR == send(UserSocket, (schar*)(&msg), sizeof(CommonPacket), 0))
	{
		m_bserverconect = false;

		int err = WSAGetLastError();
		TCHAR buff[_MAX_PATH] = { 0, };
		swprintf_s(buff, L"Send에서 %i의 에러가 발생했습니다.\n서버와 클라이언트를 다시 실행해 주세요..", err);
		//_itow_s(err, )
		MessageBoxW(NULL, buff, L"Send Error", MB_OK);
		m_bserverconect = false;
		//LeaveCriticalSection(&m_eCritical);
		return;
	}
	++sendcount;
	printf_s("%d   -   번째 보내기[%d][%.2f][%d][%d][%d][%d][%d] \n", sendcount, msg.PacTime.ServerUpTime, msg.PacTime.ServerTime, msg.PacProp.LinkNumber, msg.PacProp.iLocation1, msg.PacProp.iLocation2, msg.PacProp.iWork, msg.PacProp.iItem);

	return;


	/*



	//if (DuplicateSendPack(msg))
	//{
	//	return;
	//}

	m_Sendpacklist.push_back(msg);
	UseServer::Send();
	//여기서 비긴 쓰레드를하고 넘겨주어야겠다.
	//Sends
	//HANDLE SendHandle = (HANDLE)_beginthreadex(nullptr, 0, UseServer::Sends, (void*)this, 0, nullptr);
	//WaitForSingleObject(SendHandle, 10);
	//CloseHandle(SendHandle);

	*/
}

CommonPacket UseServer::PopRecv()
{
	if (0 == m_Recvpacklist.size())
	{
		return CommonPacket();
	}

	if (!getconected())
	{
		return DisConnected;
	}

	CommonPacket recvpp = m_Recvpacklist.front();
	EnterCriticalSection(&m_eCritical);
	m_Recvpacklist.pop_front();
	LeaveCriticalSection(&m_eCritical);
	
	if (recvpp.PacTime.ServerTime != 0.0f)
	{
		UseServer::m_fLastTime = recvpp.PacTime.ServerTime;
	}
	if (recvpp.PacTime.ServerUpTime != 0)
	{
		UseServer::m_iLastUptime = recvpp.PacTime.ServerUpTime;
	}
	
	return recvpp;
}

CommonPacket UseServer::PopRecv(int LinkNumver, int Location1, int Location2, int Work, int Item)
{
	if (0 == m_Recvpacklist.size())
	{
		return CommonPacket();
	}

	CommonPacket popPack = CommonPacket();
	//if (!Location1)
	//{
	//	return popPack;
	//}

	//if (!getconected())
	//{
	//	return DisConnected;
	//}
	//Sleep(10);
	std::list<CommonPacket>::iterator StartIter = m_Recvpacklist.begin();
	std::list<CommonPacket>::iterator EndIter = m_Recvpacklist.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		if (Location1 == StartIter->PacProp.iLocation1)
		{
			if (Location2 == StartIter->PacProp.iLocation2)
			{
				if (Work == StartIter->PacProp.iWork)
				{
					if (Item == StartIter->PacProp.iItem)
					{
						popPack = (*StartIter);
						//EnterCriticalSection(&m_eCritical);
						m_Recvpacklist.erase(StartIter);//수동으로 빼준다.
						//LeaveCriticalSection(&m_eCritical);
						if (popPack.PacTime.ServerTime != 0.0f)
						{
							UseServer::m_fLastTime = popPack.PacTime.ServerTime;
						}
						if (popPack.PacTime.ServerUpTime != 0)
						{
							UseServer::m_iLastUptime = popPack.PacTime.ServerUpTime;
						}
						//Sleep(5);
						return popPack;
					}
					else if (0 == Item)
					{
						popPack = (*StartIter);
						//EnterCriticalSection(&m_eCritical);
						m_Recvpacklist.erase(StartIter);//수동으로 빼준다.
						//LeaveCriticalSection(&m_eCritical);
						if (popPack.PacTime.ServerTime != 0.0f)
						{
							UseServer::m_fLastTime = popPack.PacTime.ServerTime;
						}
						if (popPack.PacTime.ServerUpTime != 0)
						{
							UseServer::m_iLastUptime = popPack.PacTime.ServerUpTime;
						}
						//Sleep(5);
						return popPack;
					}
				}
				else if (0 == Work)
				{
					//여기구간에서 알아서 처리
					popPack = (*StartIter);
					//EnterCriticalSection(&m_eCritical);
					m_Recvpacklist.erase(StartIter);//수동으로 빼준다.
					//LeaveCriticalSection(&m_eCritical);
					if (popPack.PacTime.ServerTime != 0.0f)
					{
						UseServer::m_fLastTime = popPack.PacTime.ServerTime;
					}
					if (popPack.PacTime.ServerUpTime != 0)
					{
						UseServer::m_iLastUptime = popPack.PacTime.ServerUpTime;
					}
					//Sleep(5);
					return popPack;
				}
			}
			else if (0 == Location2)
			{
				//여기구간에서 알아서 처리
				popPack = (*StartIter);
				//EnterCriticalSection(&m_eCritical);
				m_Recvpacklist.erase(StartIter);//수동으로 빼준다.
				//LeaveCriticalSection(&m_eCritical);
				if (popPack.PacTime.ServerTime != 0.0f)
				{
					UseServer::m_fLastTime = popPack.PacTime.ServerTime;
				}
				if (popPack.PacTime.ServerUpTime != 0)
				{
					UseServer::m_iLastUptime = popPack.PacTime.ServerUpTime;
				}
				//Sleep(5);
				return popPack;
			}
			//popPack = (*StartIter);
			//EnterCriticalSection(&m_eCritical);
			//m_Recvpacklist.erase(StartIter);//수동으로 빼준다.
			//LeaveCriticalSection(&m_eCritical);
			//return popPack;
		}
	}
	//Sleep(10);



	return popPack;
	
}

bool UseServer::DuplicateRecvPack(CommonPacket msg)
{
	EnterCriticalSection(&m_eCriticalRecv);
	if (m_Recvpacklist.size() == 0)
	{
		LeaveCriticalSection(&m_eCriticalRecv);
		return false;
	}
	std::list<CommonPacket>::iterator startiter = m_Recvpacklist.begin();
	std::list<CommonPacket>::iterator enditer = m_Recvpacklist.end();
	for (; startiter != enditer; ++startiter)
	{
		if ((*startiter).PacProp == msg.PacProp)
		{
			if (msg.PacTime == 0 || (*startiter).PacTime == 0)
			{
				startiter->SetComment(msg.Comments, CommentSize);
				LeaveCriticalSection(&m_eCriticalRecv);
				return true;
			}
			else if (msg.PacTime > (*startiter).PacTime)
			{
				startiter->SetComment(msg.Comments, CommentSize);
				LeaveCriticalSection(&m_eCriticalRecv);
				return true;
			}
		}
	}


	LeaveCriticalSection(&m_eCriticalRecv);
	return false;
}

bool UseServer::DuplicateSendPack(CommonPacket msg)
{
	EnterCriticalSection(&m_eCriticalSend);
	if (m_Sendpacklist.size() == 0)
	{
		LeaveCriticalSection(&m_eCriticalSend);
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
		//m_Sendpacklist
	std::list<CommonPacket>::iterator startiter = m_Sendpacklist.begin();
	std::list<CommonPacket>::iterator enditer = m_Sendpacklist.end();
	if (startiter == enditer)
	{
		LeaveCriticalSection(&m_eCriticalSend);
		return false;
	}

	if ((*startiter).PacProp == msg.PacProp)
	{
		if (msg.PacTime == 0 || (*startiter).PacTime == 0)
		{
			startiter->SetComment(msg.Comments, CommentSize);
			LeaveCriticalSection(&m_eCriticalSend);
			return true;
		}
		else if (msg.PacTime >= (*startiter).PacTime)
		{
			startiter->SetComment(msg.Comments, CommentSize);
			LeaveCriticalSection(&m_eCriticalSend);
			return true;
		}
		//startiter->SetComment(msg.Comments, CommentSize);
		//return true;
	}
	LeaveCriticalSection(&m_eCriticalSend);
	return false;
}

void UseServer::PrintLog()
{
	system("cls");
	std::cout << "=======================================";
	for (unsigned int i = 0 ;i <= m_strLogvec.size(); ++i)
	{
		std::cout << m_strLogvec[i].c_str();
	}
	std::cout << "=======================================" << std::endl;
}

void UseServer::LogClear()
{
	m_strLogvec.clear();
}

UseServer::UseServer() : UserSocket(NULL)
{
	//EnterCriticalSection(&m_eCritical);
	if (!m_Sendpacklist.empty())
	{
		m_Sendpacklist.pop_front();
	}
	//LeaveCriticalSection(&m_eCritical);

}


UseServer::~UseServer()
{
}


//초기 상태 설정
bool UseServer::init(schar* IP, u_short PORT)// 설정 시에 IP와 포트를 설정해야한다.
{

	InitializeCriticalSection(&m_eCritical);
	InitializeCriticalSection(&m_eCriticalSend);
	InitializeCriticalSection(&m_eCriticalRecv);
	
	WSADATA wData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wData);
	if (iResult  != 0)
	{
		ServerErr("[WSA 생성 실패]USER에서 WSADATA 생성에 실패 했습니다.\n");
		return false;
	}


	m_strLogvec.clear();
	m_strLogvec.reserve(1000);
	Tstring Log = _T("[WSA 생성 완료] USER에서 생성이 완료되었습니다. \n");
	m_strLogvec.push_back(Log);


	//UserSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	UserSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//ipv4망, 소켓, TCP

	SOCKADDR_IN Addr;
	Addr.sin_family = AF_INET;
	Addr.sin_addr.s_addr = inet_addr(IP);
	Addr.sin_port = htons(PORT);

	///////////////////////////////////////////////
	//연결
	///////////////////////////////////////////////

	int connectResult = -1;
	int connectrecount = 0;
	Log.clear();
	connectResult = connect(UserSocket, (sockaddr*)&Addr, sizeof(SOCKADDR_IN));
	if(connectResult == -1)
	{
		m_bserverconect = false;
		release();
		return false;
	}
	else
	{
		m_bserverconect = true;
	}


	Log.clear();
	Log = _T("[연결 성공] 연결에 성공했습니다.\n");

	CommonPacket FirstRecv;
	while (true)
	{
		memset(&FirstRecv, 0, sizeof(CommonPacket));
		if (-1 == recv(UserSocket, (schar*)(&FirstRecv), sizeof(CommonPacket), 0))
		{
			m_bserverconect = false;
			release();
			return false;
		}
		if (FirstRecv.PacProp.iLocation1 == SL_SYS)
		{
			//이게바로 너의 아이디이다!
			memcpy(&MyUniqueNum, FirstRecv.Comments, sizeof(int));
			std::cout << MyUniqueNum << std::endl;
			if (-1 == send(UserSocket, (schar*)(&FirstRecv), sizeof(CommonPacket), 0))
			{
				m_bserverconect = false;
				release();
				return false;
			}
			//그리고 응답합니다.
			break;
		}
		else
		{
			//경고
			 continue;
		}
	}
	
	return true;



}

void UseServer::reboot(schar* IP, u_short PORT)
{
	shutdown(UserSocket, 0x02);
	closesocket(UserSocket);
	UserSocket = NULL;
	WSACleanup();

	DeleteCriticalSection(&m_eCritical);
	DeleteCriticalSection(&m_eCriticalSend);
	DeleteCriticalSection(&m_eCriticalRecv);
	////////////////////////////////////////

	init(IP, PORT);
}

void UseServer::release()
{
	LogClear();
	shutdown(UserSocket, 0x02);
	closesocket(UserSocket);
	UserSocket = NULL;
	WSACleanup();

	DeleteCriticalSection(&m_eCritical);
	DeleteCriticalSection(&m_eCriticalSend);
	DeleteCriticalSection(&m_eCriticalRecv);
}

void UseServer::Send()
{
	if (!m_bserverconect)
	{
		return;
	}

	double getticks = GetTickCount();
	CommonPacket snedpp;
	if(m_bServerClose)
	{
		////////////////////////
		memset(&snedpp, 0, sizeof(CommonPacket));
		//EnterCriticalSection(&m_eCritical);
		if (m_Sendpacklist.size() == 0)
		{
			//LeaveCriticalSection(&m_eCritical);
			return;
		}
		if (!m_Sendpacklist.empty())
		{
			if (!m_bServerClose)
			{
				//LeaveCriticalSection(&m_eCritical);
				return;
			}

			m_bIsSend = true;
			//EnterCriticalSection(&m_eCriticalSend);
			std::list<CommonPacket> copysend = m_Sendpacklist;
			//LeaveCriticalSection(&m_eCriticalSend);

			int size = (int)copysend.size();

			//-842150451
			if (0 != size)
			{
				if (!m_bServerClose)
				{
					//LeaveCriticalSection(&m_eCritical);
					return;
				}
				snedpp = copysend.front();
			}
			
			if (snedpp.PacProp.LinkNumber == 0 )
			{
				//LeaveCriticalSection(&m_eCritical);
				return;
				//continue;
			}
			if (snedpp.PacProp.LinkNumber == -842150451)
			{
				//EnterCriticalSection(&m_eCritical);
				//while (true)
				//{

				//}
				//EnterCriticalSection(&m_eCriticalSend);
				std::list<CommonPacket>::iterator eraseiter;
				eraseiter = m_Sendpacklist.begin();
				m_Sendpacklist.erase(eraseiter);
				//LeaveCriticalSection(&m_eCriticalSend);
				Send();
				return;
				//LeaveCriticalSection(&m_eCritical);
			}
			
		

			if (!m_bServerClose)
			{
				m_bserverconect = false; 
				//LeaveCriticalSection(&m_eCritical);
				return;
			}

			//EnterCriticalSection(&m_eCritical);
			//EnterCriticalSection(&m_eCriticalSend);
			std::list<CommonPacket>::iterator eraseiter;
			eraseiter = m_Sendpacklist.begin();
			m_Sendpacklist.erase(eraseiter);
			//LeaveCriticalSection(&m_eCriticalSend);
			//LeaveCriticalSection(&m_eCritical);
			

			if (SOCKET_ERROR == send(UserSocket, (schar*)(&snedpp), sizeof(CommonPacket), 0))
			{
				m_bserverconect = false;

				int err = WSAGetLastError();
				TCHAR buff[_MAX_PATH] = {0,};
				swprintf_s(buff, L"Send에서 %i의 에러가 발생했습니다.\n서버와 클라이언트를 다시 실행해 주세요..", err);
				//_itow_s(err, )
				MessageBoxW(NULL, buff, L"Send Error", MB_OK);
				m_bserverconect = false;
				//LeaveCriticalSection(&m_eCritical);
				return;
			}
			++sendcount;
			printf_s("%d   -   번째 보내기[%d][%.2f][%d][%d][%d][%d][%d] \n", sendcount, snedpp.PacTime.ServerUpTime, snedpp.PacTime.ServerTime, snedpp.PacProp.LinkNumber, snedpp.PacProp.iLocation1, snedpp.PacProp.iLocation2, snedpp.PacProp.iWork, snedpp.PacProp.iItem);


			m_bserverconect = true;

			//if (!m_bServerClose)
			//{
			//	LeaveCriticalSection(&m_eCritical);
			//	return;
			//}
			m_bIsSend = false;
		}
		//LeaveCriticalSection(&m_eCritical);
		

	}

	return;
}

void UseServer::Recv()
{
	CommonPacket Recvpp;
	while (m_bServerClose)
	{
		//m_bserverconect
		memset(&Recvpp, 0, sizeof(CommonPacket));
		Recvpp = CommonPacket();
		//recv(UserSocket, (TCHAR*)(&Recvpp), sizeof(CommonPacket), 0);
		if (SOCKET_ERROR == recv(UserSocket, (schar*)(&Recvpp), sizeof(CommonPacket), 0))
		{
			m_bserverconect = false;
			
			int err = WSAGetLastError();
			TCHAR buff[_MAX_PATH] = { 0, };
			_stprintf_s(buff, _T("Recv에서 %i의 에러가 발생했습니다.\n서버와 클라이언트를 다시 실행해 주세요.."), err);
			//_itow_s(err, )
			MessageBoxW(NULL, buff, L"Send Error", MB_OK);

			return;
		}
		++recvcount;
		m_bserverconect = true;
		
		if (Recvpp.PacProp.LinkNumber == 0 || Recvpp.PacProp.LinkNumber == -794746542)
		{
			printf_s("%d[%d]   -   번째 받기Err[%d][%.2f][%d][%d][%d][%d][%d] \n", recvcount, realrecvcount, Recvpp.PacTime.ServerUpTime, Recvpp.PacTime.ServerTime, Recvpp.PacProp.LinkNumber, Recvpp.PacProp.iLocation1, Recvpp.PacProp.iLocation2, Recvpp.PacProp.iWork, Recvpp.PacProp.iItem);
			continue;
		}	

		
		//if (100 == m_Recvpacklist.size())
		//{
		//	if (!DuplicateRecvPack(Recvpp))
		//	{
		//		++realrecvcount;
		//		printf_s("%d[%d]   -   번째 받기[%d][%.2f][%d][%d][%d][%d][%d] \n", recvcount, realrecvcount, Recvpp.PacTime.ServerUpTime, Recvpp.PacTime.ServerTime, Recvpp.PacProp.LinkNumber, Recvpp.PacProp.iLocation1, Recvpp.PacProp.iLocation2, Recvpp.PacProp.iWork, Recvpp.PacProp.iItem);
		//		m_Recvpacklist.push_back(Recvpp);
		//	}
		//	continue;;
		//}

		++realrecvcount;
		printf_s("%d[%d]   -   번째 받기[%d][%.2f][%d][%d][%d][%d][%d] \n", recvcount, realrecvcount, Recvpp.PacTime.ServerUpTime, Recvpp.PacTime.ServerTime, Recvpp.PacProp.LinkNumber, Recvpp.PacProp.iLocation1, Recvpp.PacProp.iLocation2, Recvpp.PacProp.iWork, Recvpp.PacProp.iItem);
		m_Recvpacklist.push_back(Recvpp);
	}

	return;
}
