#include "ControllerServer.h"
#include <thread>
#include <process.h>


#include "ServerProgressBase.h"

class ServerProgressBase* ControllerServer::m_pProgress = nullptr;

std::list<ClientsProfile> ControllerServer::Clientslist;
ControllerServer* ControllerServer::m_pinst = nullptr;
std::list<CommonPacket> ControllerServer::m_Syscompack;

bool ControllerServer::m_bServerClose = true;
SOCKET ControllerServer::ServerSocket = SOCKET();
int ControllerServer::m_iAllCountNumber = 1;

CRITICAL_SECTION ControllerServer::m_eCritical;

fd_set ControllerServer::testfds;

ControllerServer::ControllerServer()
{
}


ControllerServer::~ControllerServer()
{
}

int ControllerServer::EventSelect()
{
	//while (true)
	//{
		CommonPacket recvPack;
		//����
		m_cpyReads = m_reads;

		//�ð� ����
		m_timeout.tv_sec = 100;
		m_timeout.tv_usec = 100000;


		if ((m_fdNum = select(0, &m_cpyReads, 0, 0, &m_timeout)) == SOCKET_ERROR)
		{
			return 0;
		}

		if (m_fdNum == 0)
		{
			return 1;//���ư��� �ٽ��ض�.
		}

		for (m_i = 0; m_i < m_reads.fd_count ; ++m_i)
		{
			recvPack = CommonPacket();


			if (FD_ISSET(m_reads.fd_array[m_i], &m_cpyReads))
			{
				if (m_reads.fd_array[m_i] == m_hServSock)//��û��
				{
					ClientsProfile pnewclient = ClientsProfile(m_iAllCountNumber);
					int client_len = 0;
					ServerLog(_T("[���� ����] "), m_iAllCountNumber, SL_SYS, SysM_UniqueNum, 0, 0);

					m_adrSz = sizeof(m_clntAdr);
					m_hClntSock = accept(m_hServSock, (SOCKADDR*)&m_clntAdr, &m_adrSz);
					FD_SET(m_hClntSock, &m_reads);
					printf_s("%d ��Ĺ�� Ŭ���̾�Ʈ�� �����߽��ϴ�.\n", (int)m_hClntSock);
					/////////////////////////////////////////////////////////////////////////////////////
					pnewclient.EnterNumber = m_iAllCountNumber;
					pnewclient.ClientSocket = m_hClntSock;
					pnewclient.UniqueNumber = m_iAllCountNumber;

					CommonPacket FirstSend = CommonPacket();

					FirstSend.PacProp.iLocation1 = (int)SL_SYS;
					FirstSend.PacProp.iLocation2 = (int)SysM_UniqueNum;
					FirstSend.PacProp.iWork = (int)CC_SEND;
					FirstSend.PacProp.iItem = (int)SysI_Unique;
					memcpy(FirstSend.Comments, &m_iAllCountNumber, sizeof(int));
					//memcpy(FirstSend.Comments, &ServerProgressBase::m_iSurverTimeUp, sizeof(int));
					//memcpy(FirstSend.Comments, &ServerProgressBase::m_fSurverTime, sizeof(float));

					if (-1 == send(m_hClntSock, (char*)(&FirstSend), sizeof(CommonPacket), 0))
					{
						return 1;
					}
					memset(&FirstSend, 0, sizeof(CommonPacket));
					if (-1 == recv(m_hClntSock, (char*)(&FirstSend), sizeof(CommonPacket), 0))
					{
						return 1;
					}

					if (FirstSend.PacProp.iLocation1 == SL_Err)
					{
						return 1;
					}
					ServerLog(_T("[���� ����] "), m_iAllCountNumber, SL_SYS, SysM_IntologinScene, 0, 0);
					Clientslist.push_back(pnewclient);
					++m_iAllCountNumber;

				}
				else
				{
					m_strLen = recv(m_reads.fd_array[m_i], (char*)(&recvPack), sizeof(CommonPacket), 0);

					CommonPacket resultPack;
					if (recvPack.PacProp.LinkNumber != 0)
					{
						if (m_pProgress)
						{
							ServerProgressBase* copys = m_pProgress->Copy();
							resultPack = copys->Progress(recvPack);

							delete copys;
							copys = nullptr;

						}
						ServerLog(_T("[���� ���]"), resultPack.PacProp.LinkNumber, resultPack.PacProp.iLocation1, resultPack.PacProp.iLocation2, resultPack.PacProp.iWork, resultPack.PacProp.iItem);
					}
					else
					{
						int ierror =WSAGetLastError();
						//if (m_strLen == -1 || m_strLen == 0) //�ݱ� ��û
						//{
						//	FD_CLR(m_reads.fd_array[m_i], &m_reads);
						//	closesocket(m_cpyReads.fd_array[m_i]);
						//	printf_s("%d ��Ĺ�� Ŭ���̾�Ʈ�� ���� �Ǿ����ϴ�.\n", (int)m_cpyReads.fd_array[m_i]);
						//	continue;
						//}
						//continue;
					}
					resultPack.PacTime.ServerUpTime = ServerProgressBase::m_iSurverTimeUp;
					resultPack.PacTime.ServerTime = ServerProgressBase::m_fSurverTime;



					if (m_strLen == -1 || m_strLen == 0) //�ݱ� ��û
					{
						//����µ�?
						//Ŭ�������� ����ó��.
						/*ClientsProfile findclient = FindClientFromSock(m_cpyReads.fd_array[m_i]);
						findclient.UniqueNumber;
*/
						FD_CLR(m_reads.fd_array[m_i], &m_reads);
						closesocket(m_cpyReads.fd_array[m_i]);
						printf_s("%d ��Ĺ�� Ŭ���̾�Ʈ�� ���� �Ǿ����ϴ�.\n", (int)m_cpyReads.fd_array[m_i]);
						
					}
					else
					{
						send(m_reads.fd_array[m_i], (char*)(&resultPack), sizeof(CommonPacket), 0);//�����ϱ�.
					}
				}
			}
		}

	////}
	//closesocket(m_hServSock);
	//WSACleanup();
	//return;
		return 2;
}

bool ControllerServer::inst()
{
	if (nullptr == m_pinst)
	{
		m_pinst = new ControllerServer();
		return true;
	}

	//����ξȵ�.................
	return false;
}


void ControllerServer::EventSelectRealease()
{
	shutdown(m_hServSock, 2);
	closesocket(m_hServSock);
	return;
}


void ControllerServer::release()
{
	Clientslist.clear();
	m_Syscompack.clear();


	m_pinst->LogClearAll();
	shutdown(ServerSocket, 2);
	closesocket(ServerSocket);
	ServerSocket = NULL;
	WSACleanup();

	delete m_pinst;
	m_pinst = nullptr;

}

ControllerServer * ControllerServer::getSingle()
{
	return m_pinst;
}

const std::list<ClientsProfile>* ControllerServer::getClientlist()
{
	if (0 == Clientslist.size())
	{
		return (&Clientslist);
	}
	return nullptr;
}

void ControllerServer::AllSendComment(CommonPacket _compack)
{
	m_Syscompack.push_back(_compack);
}
void ControllerServer::AllSendclear()
{
	m_Syscompack.clear();
}

ClientsProfile ControllerServer::FindClientFromSock(SOCKET _sock)
{
	std::list<ClientsProfile>::iterator startiter = Clientslist.begin();
	std::list<ClientsProfile>::iterator enditer = Clientslist.end();

	for (;startiter != enditer; ++startiter)
	{
		if (startiter->ClientSocket == _sock)
		{
			return (*startiter);
		}
	}

	return ClientsProfile();
}

bool ControllerServer::init(schar * IP, u_short PORT)
{
	////////////////////////////////////////////////////////////////////////////////
	InitializeCriticalSection(&m_eCritical);
	Clientslist.clear();
	///////////////////////////////////////////////////////////////////////////////////

	if (0 != WSAStartup(MAKEWORD(2,2) ,&m_wsaData))
	{
		//�����޽���.
		return false;
	}

	m_hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&m_servAdr, 0, sizeof(m_servAdr));

	m_servAdr.sin_family = AF_INET;
	m_servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_servAdr.sin_port = htons(PORT);

	if (::bind(m_hServSock, (SOCKADDR*)&m_servAdr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		//���� �޽���
		return false;
	}
	if (listen(m_hServSock, 5) == SOCKET_ERROR)
	{
		//���� �޽���
		return false;
	}

	FD_ZERO(&m_reads);
	FD_SET(m_hServSock, &m_reads);



	//
	////////////////////////////////////////////////////////////////
	//int Server_sockfd = 0;



	////////////////////////////////////////////////////////////////

	//WSADATA wData;
	//if (0 != WSAStartup(MAKEWORD(2, 2), &wData))
	//{
	//	return false;
	//}

	//ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	////
	////Server_sockfd = ServerSocket;


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//SOCKADDR_IN Addr;
	//Addr.sin_family = AF_INET;
	//Addr.sin_addr.s_addr = htonl(INADDR_ANY);// ����� ������� ��Ƶ帳�ϴ�.
	//Addr.sin_port = htons(PORT);
	//if (-1 == ::bind(ServerSocket, (SOCKADDR*)&Addr, sizeof(SOCKADDR)))
	//{
	//	return false;
	//}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//if (-1 == listen(ServerSocket, SOMAXCONN))
	//{
	//	return false;
	//}
	////////////////////////////////////////////////////////////////////////////////////////////


	////FD_ZERO(&readfds);

	//FD_ZERO(&testfds);
	//FD_SET(ServerSocket, &testfds);
	//�ո����ΰ�. 

	//���߿� �α׳������
	return true;
}

void ControllerServer::reboot(schar * IP, u_short PORT)
{
	closesocket(ServerSocket);
	ServerSocket = NULL;
	WSACleanup();

	init(IP, PORT);
}


unsigned ControllerServer::AcceptClient(void * arg)
{
	//������ ����
	SOCKADDR_IN addr;
	int Size = sizeof(SOCKADDR_IN);
	while (m_bServerClose)
	{
		ClientsProfile pnewclient = ClientsProfile(m_iAllCountNumber);

		//fd_set allfds = 

		int client_len = 0;
		ServerLog(_T("[���� ����] "), m_iAllCountNumber, SL_SYS, SysM_UniqueNum, 0, 0);
		/*if (FD_ISSET((pnewclient.ClientSocket), &allfds))
		{
			client_len = sizeof(addr);
		}*/

			(pnewclient.ClientSocket) = accept(ServerSocket, (SOCKADDR*)&addr, &Size);


		/////////////////////////
		//LOG

		/////////////////////////

		
		
		pnewclient.EnterNumber = m_iAllCountNumber;


		//////////////////////////////////////////////////////////////////////////////
		//���߿� �������
		pnewclient.UniqueNumber = m_iAllCountNumber;
		//�������� �ѱ��
		//////////////////////////////////////////////////////////////////////////////

		CommonPacket FirstSend = CommonPacket();
		//memset(&FirstSend, 0, sizeof(CommonPacket));
		//ZeroMemory(&FirstSend, sizeof(CommonPacket));


		FirstSend.PacProp.iLocation1 = (int)SL_SYS;
		FirstSend.PacProp.iLocation2 = (int)SysM_UniqueNum;
		FirstSend.PacProp.iWork = (int)CC_SEND;
		FirstSend.PacProp.iItem = (int)SysI_Unique;
		memcpy(FirstSend.Comments, &m_iAllCountNumber, sizeof(int));
		memcpy(FirstSend.Comments, &ServerProgressBase::m_iSurverTimeUp, sizeof(int));
		memcpy(FirstSend.Comments, &ServerProgressBase::m_fSurverTime, sizeof(float));

		if (-1 == send(pnewclient.ClientSocket, (char*)(&FirstSend), sizeof(CommonPacket), 0))
		{
			continue;
		}
		

		memset(&FirstSend, 0, sizeof(CommonPacket));
		if (-1 == recv(pnewclient.ClientSocket, (char*)(&FirstSend), sizeof(CommonPacket), 0))
		{
			continue;
		}

		if (FirstSend.PacProp.iLocation1 == SL_Err)
		{
			continue;
		}

		/////////////////////////
		//LOG
		ServerLog(_T("[���� ����] "), m_iAllCountNumber, SL_SYS, SysM_IntologinScene, 0, 0);
		++m_iAllCountNumber;
		/////////////////////////

		Clientslist.push_back(pnewclient);

		//�ൿ�� ó���մϴ�.
		HANDLE DoRecv_Handle = (HANDLE)_beginthreadex(nullptr, 0, ControllerServer::DoRecv, (void*)(&pnewclient), 0, nullptr);
		WaitForSingleObject(DoRecv_Handle, 10);



	}
	return 1;
}

unsigned ControllerServer::DoRecv(void * arg)
{

	ClientsProfile clientprof = (ClientsProfile)(*((ClientsProfile*)(arg)));


	std::list<struct ClientsProfile>::iterator StartIter = Clientslist.begin();
	std::list<struct ClientsProfile>::iterator EndIter = Clientslist.end();
	for (;	StartIter != EndIter ; ++StartIter)
	{
		if ((*StartIter).BootSend == false)
		{
			if (clientprof.EnterNumber == 0)
			{
				HANDLE DoRecv_Handle = (HANDLE)_beginthreadex(nullptr, 0, ControllerServer::DoRecv, (void*)(&(*StartIter)), 0, nullptr);
				WaitForSingleObject(DoRecv_Handle, 10);
				return -1;
			}
			else
			{
				if (clientprof.EnterNumber == (*StartIter).EnterNumber)
				{
					(*StartIter).BootSend = true;
					break;
				}
			}
		}
	}
	

	//typedef struct fd_set {
	//	u_int   fd_count;               /* how many are SET? */
	//	SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
	//} fd_set;

	fd_set clientfds;
	FD_ZERO(&clientfds);


	while (true)
	{


		/*if (FD_ISSET(clientprof.ClientSocket, ))
		{
		}*/


		CommonPacket recvPack;
		if (-1 == recv(clientprof.ClientSocket, (schar*)(&recvPack), sizeof(CommonPacket), 0))
		{
			break;
			//MSG_OOB
		}

		CommonPacket resultPack; 
	
		if (recvPack.PacProp.LinkNumber != 0)
		{
			
			if (m_pProgress)
			{
				ServerProgressBase* copys = m_pProgress->Copy();
				resultPack = copys->Progress(recvPack);

				delete copys;
				copys = nullptr;

			}
			/////////////////////////////////////////////////////////
			////���� ����
			//ServerProgressBase Progress = ServerProgressBase();

			///////////////////////////////////////////////////////
			//resultPack = Progress.Progress(recvPack);

			/////////////////////////
			//LOG
			ServerLog(_T("[���� ���]"), resultPack.PacProp.LinkNumber, resultPack.PacProp.iLocation1, resultPack.PacProp.iLocation2, resultPack.PacProp.iWork, resultPack.PacProp.iItem);
			/////////////////////////



			
			/////////////////////////////////////////////////

			/////////////////////////////////////////////////
			//���� �뺸 ���ٰ͵�
			//if (0 != m_Syscompack.size())
			//{
			//	std::list<CommonPacket> SendMsg;
			//	SendMsg.assign(m_Syscompack.begin(), m_Syscompack.end());
			//	std::list<CommonPacket>::iterator StartIter = SendMsg.begin();
			//	std::list<CommonPacket>::iterator EndIter = SendMsg.end();
			//	for (; StartIter != EndIter; ++StartIter)
			//	{
			//		CommonPacket resultPack2 = (*StartIter);
			//		//std::cout << "[���� �뺸]" << resultPack2.Comments << std::endl;
			//		send(clientprof.ClientSocket, (TCHAR*)(&resultPack2), sizeof(CommonPacket), 0);
			//	}
			//}
			/////////////////////////////////////////////////
			//��¥�� �ʿ��Ѱ� 
			//// ���� ���� (�ε����� �����ϰ�ʹ�....)��¥�� ����� �����������ϱ� ũ�⸦ �ּ�ȭ�ϸ�? TCHAR�� 1���� ǥ���Ҽ� �ְ� �װ� int�ι������ֳ�? TCHAR 1 ==? int 1
			// ���� ����
			// ���� ����
			// Ư�� ȿ��
		}
		resultPack.PacTime.ServerUpTime = ServerProgressBase::m_iSurverTimeUp;
		resultPack.PacTime.ServerTime = ServerProgressBase::m_fSurverTime;
		send(clientprof.ClientSocket, (schar*)(&resultPack), sizeof(CommonPacket), 0);


		///////////�������
		if (resultPack.PacProp.iWork == EndClient || resultPack.PacProp.iWork == EndClientForIngame
			|| resultPack.PacProp.iWork == EndClientForLobby || resultPack.PacProp.iWork == EndClientForRoom
			||resultPack.PacProp.iWork == EndClientForLogin)
		{
			//��� ��ٷ�����.
			double Ticks = GetTickCount();
			double GetTicks = 2000.0;
			while (GetTicks <= 0)
			{
				GetTicks -= (GetTickCount() - Ticks);
				Ticks = GetTickCount();
				send(clientprof.ClientSocket, (schar*)(&resultPack), sizeof(CommonPacket), 0);
			}
			//ServerLog("[���� ���]", resultPack.PacProp.LinkNumber, resultPack.PacProp.iLocation1, resultPack.PacProp.iLocation2, resultPack.PacProp.iLocation2, "�� Ŭ���̾�Ʈ�� �����մϴ�.");
			break;
		}
	}


	return 1;
}
//
//unsigned ControllerServer::DoSend(void * arg)
//{
//	ClientsProfile clientprof = (ClientsProfile)(*((ClientsProfile*)(arg)));	s//	CommonPacket sysPack;
//	while (true)
//	{		//// (0 != clientprof.strSend.size())
////
//	//sPack = clientprof.strSend.front();
//	//d::cout << "[���� ����]" << sysPack.Comments << std::endl;
//	//nd(clientprof.ClientSocket, (TCHAR*)(&sysPack), sizeof(CommonPacket), 0);
//	//ientprof.strSend.pop_front();
////

//	}//

//

//	return 1;
//}
//



void ControllerServer::LogClear(int Num)
{
}

void ControllerServer::LogClearAll()
{
}