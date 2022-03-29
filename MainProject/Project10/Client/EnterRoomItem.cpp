#include "stdafx.h"
#include "EnterRoomItem.h"
#include "ClientHeader.h"

#include "FrameCore.h"
#include "ClientLobbyScene.h"
#include "ClientRoomScene.h"

EnterRoomItem::EnterRoomItem()
{
}


EnterRoomItem::~EnterRoomItem()
{
}

int EnterRoomItem::Input(float time)
{
	return PR_OK;
}

int EnterRoomItem::Update(float time)
{
	return PR_OK;
}

int EnterRoomItem::LateUpdate(float time)
{
	return PR_OK;
}

int EnterRoomItem::Transform(float time)
{
	return PR_OK;
}

int EnterRoomItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int EnterRoomItem::DebugRender(float time)
{
	return PR_OK;
}

int EnterRoomItem::Collision(float time)
{
	//if (m_iCallButton)
	//{
	//	////어떠한 판단을 하고 그 다음에
	//	//////////////////////////// 서버에게 나는 어디로 이동한다고 메시지를 보낸다.



	//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	//이것이 끝나면 
	//	ClientRoomScene* pNextScene = FrameCore::CreateScene<ClientRoomScene>(GameRoomScene);
	//	pNextScene->SetActive(false);
	//	//WNDItem::ALLHIDE();

	//	//MessageBox(NULL, TEXT("정상적으로 로그아웃 되었습니다. \n로그인 화면으로 이동합니다."), TEXT("로그 아웃"), MB_OK);


	//	ClientLobbyScene* pCurScene = FrameCore::FindScene<ClientLobbyScene>(GameLobbyScene);

	//	pNextScene->SetActive(true);
	//	pCurScene->SetActive(false);
	//	pCurScene->Delete();

	//	m_iCallButton = false;

	//}


	return PR_OK;
}

int EnterRoomItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("EnterRoom"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (int)(WindSizeX * 0.06f + 215), (int)(WindSizeY * 0.85f), 200, 50, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 입장하기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int EnterRoomItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}
