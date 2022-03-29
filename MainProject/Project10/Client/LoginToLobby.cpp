#include "stdafx.h"
#include "LoginToLobby.h"

#include "ClientHeader.h"
#include "ClientIngameEnum.h"
#include "ClientCore.h"

#include "FrameCore.h"
//#include "ClientRoomScene.h"
#include "ClientLogInScene.h"
#include "ClientLobbyScene.h"

#include <assert.h>

void LoginToLobby::LoginSet(const Tstring & Id, const Tstring & pw)
{
	m_Id = Id;
	m_Pw = pw;
}

LoginToLobby::LoginToLobby()
{
}


LoginToLobby::~LoginToLobby()
{
}

int LoginToLobby::Input(float time)
{
	return PR_OK;
}

int LoginToLobby::Update(float time)
{
	CommonPacket packets = CommonPacket();

	////////////////////////////////////서버 수신확인
	packets.PacProp.iLocation1 = SL_Err;
	packets = ClientCore::pServer->PopRecv(ClientCore::pServer->MyUniqueNum, SL_LOG_IN, LI_SIGNIN, CC_CHECK);
	if (packets == DisConnected)
	{
		return PR_RECONECTSURVER;
	}

	if (packets.PacProp.iLocation1 == SL_LOG_IN && packets.PacProp.iWork == CC_CHECK)
	{
		if (packets.PacProp.iItem == LI_LoginOk)
		{
			//이때 서버에게 내가 들어간다고 알아야하고 나도 내정보를 알고있어야한다.
			memcpy(&ClientCore::ClientPlayer, packets.Comments, sizeof(Player));

			if (ClientCore::ClientPlayer.eLoginfo.m_UniqueID == 0)
			{
				MessageBox(ClientCore::mainhWnd, TEXT("정보가 정확하게 들오지 못했습니다."), TEXT("로그인 실패"), MB_OK);
				assert(true);
				return PR_OK;
			}


			MessageBox(ClientCore::mainhWnd, TEXT("정상적으로 접속되었습니다."), TEXT("로그인 성공"), MB_OK);
			///////////////////어떠한 조건들을 완료하고 나서,
			ClientLobbyScene* pNextScene = FrameCore::CreateScene<ClientLobbyScene>(GameLobbyScene);
			pNextScene->SetActive(false);
			WNDItem::ALLHIDE();
			Sleep(10);
			ClientLogInScene* pCurScene = FrameCore::FindScene<ClientLogInScene>(GameLoginScene);

			pNextScene->SetActive(true);
			pCurScene->SetActive(false);
			pCurScene->Delete();

			return PR_SCENECHNAGE;
		}
		else if (packets.PacProp.iItem == LI_AllreadyLogin)
		{
			MessageBox(ClientCore::mainhWnd, TEXT("이미 접속 중입니다."), TEXT("로그인 실패"), MB_OK);
		}
		else if (packets.PacProp.iItem == LI_NonLogin)
		{
			MessageBox(ClientCore::mainhWnd, TEXT("아이디와 비밀번호를 다시 한번 확인 해주세요."), TEXT("로그인 실패"), MB_OK);
		}
		else
		{
			MessageBox(ClientCore::mainhWnd, TEXT("아이디와 비밀번호를 다시 한번 확인 해주세요."), TEXT("로그인 실패"), MB_OK);
		}
		return PR_OK;
	}

	return PR_OK;
}

int LoginToLobby::LateUpdate(float time)
{
	return PR_OK;
}

int LoginToLobby::Transform(float time)
{
	return PR_OK;
}

int LoginToLobby::Render(float time, HDC drow)
{
	return PR_OK;
}

int LoginToLobby::DebugRender(float time)
{
	return PR_OK;
}

int LoginToLobby::Collision(float time)
{
	CommonPacket packets;

	//////////////////////////////////////서버 수신확인
	//packets.PacProp.iLocation1 = SL_Err;
	//packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOG_IN, LI_SIGNIN, CC_CHECK);
	//if (packets == DisConnected)
	//{
	//	return PR_RECONECTSURVER;
	//}
	//if (packets.PacProp.iLocation1 == SL_LOG_IN && packets.PacProp.iWork == CC_CHECK)
	//{
	//	if (packets.PacProp.iItem == LI_LoginOk)
	//	{
	//		//이때 서버에게 내가 들어간다고 알아야하고 나도 내정보를 알고있어야한다.
	//		memcpy(&ClientCore::ClientPlayer, packets.Comments, sizeof(Player));
	//		if (ClientCore::ClientPlayer.eLoginfo.m_UniqueID == 0)
	//		{
	//			return PR_OK;
	//		}
	//		MessageBox(NULL, TEXT("정상적으로 접속되었습니다."), TEXT("로그인 성공"), MB_OK);
	//		///////////////////어떠한 조건들을 완료하고 나서,
	//		ClientLobbyScene* pNextScene = FrameCore::CreateScene<ClientLobbyScene>(GameLobbyScene);
	//		pNextScene->SetActive(false);
	//		WNDItem::ALLHIDE();
	//		ClientLogInScene* pCurScene = FrameCore::FindScene<ClientLogInScene>(GameLoginScene);

	//		pNextScene->SetActive(true);
	//		pCurScene->SetActive(false);
	//		pCurScene->Delete();
	//		return PR_SCENECHNAGE;
	//	}
	//	else
	//	{
	//		MessageBox(NULL, TEXT("아이디와 비밀번호를 다시 한번 확인 해주세요."), TEXT("로그인 실패"), MB_OK);
	//	}
	//	return PR_OK;
	//}


	if (m_iCollButton)
	{
		//레이어의 속성을 움직이게 하겠다.
		//memset(&packets, 0, sizeof(CommonPacket));
		//ZeroMemory(&packets, sizeof(CommonPacket));
		/////////
		packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
		packets.PacProp.iLocation1 = SL_LOG_IN;
		packets.PacProp.iLocation2 = LI_SIGNIN;
		packets.PacProp.iWork = CC_CHECK;
		packets.PacProp.iItem = LI_IDPW;


		PlayerLogInfo m_LoginInfo;
		memcpy(m_LoginInfo.m_ID, m_Id.c_str(), sizeof(TCHAR) * 20);
		memcpy(m_LoginInfo.m_PW, m_Pw.c_str(), sizeof(TCHAR) * 60);
		
		memcpy(packets.Comments, (void*)&m_LoginInfo, sizeof(PlayerLogInfo));

		ClientCore::pServer->PushSend(packets);

		
		m_iCollButton = false;
	}


	

	return PR_OK;
}

int LoginToLobby::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("LoginEnter"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (WindSizeX/2) + 180, 350,160 ,150, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 접속 하기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int LoginToLobby::StartUp()
{
	return 0;
}

int LoginToLobby::release()
{
	WNDItem::release(0);
	return PR_OK;
}
