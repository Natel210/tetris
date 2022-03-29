#include "stdafx.h"
#include "IngameLogTimerItme.h"
#include "ClientHeader.h"
#include "ClientRoomScene.h"

IngameLogTimerItme::IngameLogTimerItme()
{
}


IngameLogTimerItme::~IngameLogTimerItme()
{
}

int IngameLogTimerItme::Input(float time)
{
	return PR_OK;
}

int IngameLogTimerItme::Update(float time)
{
	if (!ClientRoomScene::m_bIsGameEnd)
	{
		ClientRoomScene::m_fIngameCurSec -= time;
	}
	
	///////////////////////////////////////////////////////////////////////////처리파트
	//업
	while (ClientRoomScene::m_fIngameCurSec < 0.0f)
	{
		ClientRoomScene::m_fIngameCurSec += 60.0f;
		--ClientRoomScene::m_iIngameCurMin;
		if (ClientRoomScene::m_iIngameCurMin < 0)
		{
			ClientRoomScene::m_iIngameCurMin = 0;
			ClientRoomScene::m_fIngameCurSec = 0.0f;
			break;
		}
	}
	//다운
	while (ClientRoomScene::m_fIngameCurSec >= 60.0f)
	{
		ClientRoomScene::m_fIngameCurSec -= 60.0f;
		++ClientRoomScene::m_iIngameCurMin;
		if (ClientRoomScene::m_iIngameCurMin > 99)
		{
			ClientRoomScene::m_iIngameCurMin = 99;
			ClientRoomScene::m_fIngameCurSec = 59.99f;
			break;
		}
	}





	
	TCHAR timerbuff[_MAX_PATH];
	if (ClientRoomScene::m_iIngameCurMin < 10)		// 분이 10이하일때
	{
		if (ClientRoomScene::m_fIngameCurSec < 10.0f) //초가 10이하일때.
		{
			swprintf_s(timerbuff, L" 0%i : 0%.2f ", ClientRoomScene::m_iIngameCurMin, ClientRoomScene::m_fIngameCurSec);
		}
		else //아닐때.,
		{
			swprintf_s(timerbuff, L" 0%i : %.2f ", ClientRoomScene::m_iIngameCurMin, ClientRoomScene::m_fIngameCurSec);
		}

	}
	else		// 아닐떄.
	{
		if (ClientRoomScene::m_fIngameCurSec < 10.0f) //초가 10이하일때.
		{
			swprintf_s(timerbuff, L" %i : 0%.2f ", ClientRoomScene::m_iIngameCurMin, ClientRoomScene::m_fIngameCurSec);
		}
		else //아닐때.,
		{
			swprintf_s(timerbuff, L" %i : %.2f ", ClientRoomScene::m_iIngameCurMin, ClientRoomScene::m_fIngameCurSec);
		}
	}

	SetText(timerbuff);


	return PR_OK;
}


int IngameLogTimerItme::Init()
{
	WNDItem::Init(TEXT("static"), TEXT("intgameTimer"), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 600 + (Map_maxX * 30) + 10 + 5, 50 + 10, 240, (Map_maxY * 5) - 20 - 50, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	SetText(_T(" 01 : 00.00 "));
	return PR_OK;
}

int IngameLogTimerItme::release()
{
	WNDItem::release(0);
	return PR_OK;
}
