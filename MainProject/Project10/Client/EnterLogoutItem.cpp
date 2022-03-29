#include "stdafx.h"
#include "EnterLogoutItem.h"
#include "ClientHeader.h"

#include "FrameCore.h"
#include "ClientLogInScene.h"
#include "ClientLobbyScene.h"

EnterLogoutItem::EnterLogoutItem()
{
}


EnterLogoutItem::~EnterLogoutItem()
{
}

int EnterLogoutItem::Input(float time)
{
	return PR_OK;
}

int EnterLogoutItem::Update(float time)
{
	

	CommonPacket packets = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_LOBBY, LB_LOGOUT, CC_ENTER, LB_RETURNTOLOGIN);
	if (packets.PacProp.iLocation1 == SL_LOBBY &&packets.PacProp.iItem == LB_RETURNTOLOGIN)
	{
		ClientLogInScene* pNextScene = FrameCore::CreateScene<ClientLogInScene>(GameLoginScene);
		pNextScene->SetActive(false);
		WNDItem::ALLHIDE();
		//로그아웃시에는 내정보는 날라간다.
		ClientCore::ClientPlayer = Player();
		MessageBox(ClientCore::mainhWnd, TEXT("정상적으로 로그아웃 되었습니다. \n로그인 화면으로 이동합니다."), TEXT("로그 아웃"), MB_OK);
		ClientLobbyScene* pCurScene = FrameCore::FindScene<ClientLobbyScene>(GameLobbyScene);
		pNextScene->SetActive(true);
		pCurScene->SetActive(false);
		pCurScene->Delete();
		return PR_SCENECHNAGE;
	}






	return PR_OK;
}

int EnterLogoutItem::LateUpdate(float time)
{
	return PR_OK;
}

int EnterLogoutItem::Transform(float time)
{
	return PR_OK;
}

int EnterLogoutItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int EnterLogoutItem::DebugRender(float time)
{
	return PR_OK;
}

int EnterLogoutItem::Collision(float time)
{
	if (m_iCollButton)
	{
		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_LOGOUT;
		packets.PacProp.iWork = CC_ENTER;
		packets.PacProp.iItem = LB_RETURNTOLOGIN;

		//memcpy(&packets.Comments[0], &SeachPage, sizeof(int));

		ClientCore::pServer->PushSend(packets);

		m_iCollButton = false;
	}
	return PR_OK;
}

int EnterLogoutItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("Logout"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (int)(WindSizeX * 0.06f + 645), int(WindSizeY * 0.85f), 200, 50, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 로그 아웃 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int EnterLogoutItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}
