#include "stdafx.h"
#include "RoomToRobby.h"

#include "ClientCore.h"
#include "ClientHeader.h"
#include "ClientIngameEnum.h"

#include "FrameCore.h"
#include "ClientRoomScene.h"
#include "ClientLobbyScene.h"


void RoomToRobby::PrevSetExit()
{
	m_iCollButton = true;
}

RoomToRobby::RoomToRobby()
{
}


RoomToRobby::~RoomToRobby()
{
}

int RoomToRobby::Input(float time)
{
	return PR_OK;
}

int RoomToRobby::Update(float time)
{
	CommonPacket packets = CommonPacket();
	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_ROOM, RM_EXIT, RC_EXIT);
	if (packets == DisConnected)
	{
		return PR_RECONECTSURVER;
	}
	if (packets.PacProp.iLocation1 == SL_ROOM)
	{
		if (packets.PacProp.iLocation1 == SL_ROOM && packets.PacProp.iItem == RM_EXITOK)
		{
			////////////////////////////////////////////////////////////////////////////////////
			ClientLobbyScene* pNextScene = FrameCore::CreateScene<ClientLobbyScene>(GameLobbyScene);
			pNextScene->SetActive(false);
			Sleep(10);
			ClientRoomScene* pCurScene = FrameCore::FindScene<ClientRoomScene>(GameRoomScene);
			pNextScene->SetActive(true);
			pCurScene->SetActive(false);
			pCurScene->Delete();


			return PR_SCENECHNAGE;
		}
	}
	return PR_OK;
}

int RoomToRobby::LateUpdate(float time)
{
	return PR_OK;
}

int RoomToRobby::Transform(float time)
{
	return PR_OK;
}

int RoomToRobby::Render(float time, HDC drow)
{
	return PR_OK;
}

int RoomToRobby::DebugRender(float time)
{
	return PR_OK;
}

int RoomToRobby::Collision(float time)
{
	if (m_iCollButton)
	{
		////////////////////////////////////////////////////////////////////////////////////
		//서버에게 전달하고 OK받으면할거다.,
		CommonPacket packets = CommonPacket();;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_ROOM;
		packets.PacProp.iLocation2 = RM_EXIT;
		packets.PacProp.iWork = RC_EXIT;
		packets.PacProp.iItem = RM_EXITQ;
		packets.SetComment(_T("방에서 로비로 이동합니다."));


		ClientCore::pServer->PushSend(packets);

		//packets = CommonPacket();
		//packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_ROOM, RM_EXIT, RC_EXIT);
		//if (packets == DisConnected)
		//{
		//	return PR_RECONECTSURVER;
		//}
		//if (packets.PacProp.iLocation1 == SL_ROOM)
		//{
		//	if (packets.PacProp.iLocation1 == SL_ROOM && packets.PacProp.iItem == RM_EXITOK)
		//	{
		//		////////////////////////////////////////////////////////////////////////////////////
		//		ClientLobbyScene* pNextScene = FrameCore::CreateScene<ClientLobbyScene>(GameLobbyScene);
		//		pNextScene->SetActive(false);
		//		ClientRoomScene* pCurScene = FrameCore::FindScene<ClientRoomScene>(GameRoomScene);
		//		pNextScene->SetActive(true);
		//		pCurScene->SetActive(false);
		//		pCurScene->Delete();


		//		return PR_SCENECHNAGE;
		//	}
		//}
		
		m_iCollButton = false;
	}

	return PR_OK;
}

int RoomToRobby::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("IdleExit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600 + (Map_maxX * 30) + 15, (Map_maxY * 28) + 50, 240, 75, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 나가기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int RoomToRobby::release()
{
	WNDItem::release(0);
	return PR_OK;
}
