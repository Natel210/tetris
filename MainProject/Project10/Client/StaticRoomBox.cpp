#include "stdafx.h"
#include "StaticRoomBox.h"
#include "ClientHeader.h"
#include "windowsx.h"
#include "resource.h"

StaticRoomBox::StaticRoomBox()
{
}


StaticRoomBox::~StaticRoomBox()
{
}

int StaticRoomBox::Input(float time)
{
	return PR_OK;
}

int StaticRoomBox::Update(float time)
{
	return PR_OK;
}

int StaticRoomBox::LateUpdate(float time)
{
	return PR_OK;
}

int StaticRoomBox::Transform(float time)
{
	return PR_OK;
}

int StaticRoomBox::Render(float time, HDC drow)
{


	return PR_OK;
}

int StaticRoomBox::DebugRender(float time)
{
	return PR_OK;
}

int StaticRoomBox::Collision(float time)
{
	if (!m_eRoominfo.m_bIsActive)
	{
		Tstring m_str;
		SetText(m_str.c_str());
		m_iCollButton = false;
		//HDC dc =GetDC(m_hWnd);
		//Button_Enable(m_hWnd, false);
		//SendMessage(ClientCore::mainhWnd, WM_CTLCOLORBTN, (WPARAM)dc, (LPARAM)m_hWnd);
		//ReleaseDC(m_hWnd, dc);


		return PR_OK;
	}

	if (m_iCollButton)
	{
		StateDrawText();
		
		//testswich = !testswich;
		m_iCollButton = false;
	}
	//if (testswich)
	//{
	//	WNDItem::SetActive(false);

	//}
	//else
	//{
	//	WNDItem::SetActive(true);

	//}
/*

	if (GetAsyncKeyState(VK_ADD) & 0x8000)
	{
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
	}
	else
	{
		ShowWindow(m_hWnd, SW_HIDE);
	}*/


	return PR_OK;
}

int StaticRoomBox::Init()
{

	WNDItem::Init(TEXT("button"), TEXT("Roominfo"), WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON/*| BS_3STATE*/ | BS_LEFT | BS_MULTILINE /*|BS_BITMAP */|BS_TEXT /*|BS_ICON*/, 100, 100, 200, 100, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	//StateDrawText();


	Button_SetText(m_hWnd, L"");
	return PR_OK;
}

int StaticRoomBox::release()
{
	WNDItem::release(0);
	return PR_OK;
}

void StaticRoomBox::StateDrawText()
{
	if (m_eRoominfo.m_iRoomNum == 0)
	{

		return;
	}
	if (m_bSelects)
	{
		Tstring m_str;
		m_str += L"\n    ";

		m_str += L"방번호 : ";
		m_str += m_eRoominfo.m_strRoomNum;
		m_str += L"\n    ";

		m_str += L"방이름 : ";
		m_str += m_eRoominfo.m_strRoomName;
		m_str += L"\n    ";

		m_str += L"인원수 : ";
		m_str += m_eRoominfo.m_strRoomCurNum;
		m_str += L" / ";
		m_str += m_eRoominfo.m_strRoomLimNum;
		m_str += L"\n    ";

		if (!m_eRoominfo.m_bPub)
		{
			m_str += L"비밀방";
			m_str += L"\n";
		}
		else
		{
			m_str += L"공개방";
			m_str += L"\n";
		}
		SetText(m_str.c_str());
		m_bSelects = false;
	}
	else
	{
		Tstring m_str;
		m_str += L"                [  선 택  ]";
		m_str += L"\n    ";

		m_str += L"방번호 : ";
		m_str += m_eRoominfo.m_strRoomNum;
		m_str += L"\n    ";

		m_str += L"방이름 : ";
		m_str += m_eRoominfo.m_strRoomName;
		m_str += L"\n    ";

		m_str += L"인원수 : ";
		m_str += m_eRoominfo.m_strRoomCurNum;
		m_str += L" / ";
		m_str += m_eRoominfo.m_strRoomLimNum;
		m_str += L"\n    ";

		if (!m_eRoominfo.m_bPub)
		{
			m_str += L"비밀방";
			m_str += L"\n";
		}
		else
		{
			m_str += L"공개방";
			m_str += L"\n";
		}
		SetText(m_str.c_str());
		m_bSelects = true;
	}
}

void StaticRoomBox::CreateRoom(const TCHAR * _RoomName, int LimNum, bool Publics)
{
	if (1 >= LimNum)
	{
		return;
	}

	m_eRoominfo.m_iCurNum = 0;
	m_eRoominfo.m_bIsActive = true;

	SetStateRoom(_RoomName, LimNum, Publics);
}

void StaticRoomBox::SetStateRoom(const TCHAR * _RoomName, int LimNum, int CurNum, bool Publics)
{
	//TCHAR strbuff[_MAX_PATH];

	//넘버를 할당 받고

	m_eRoominfo.m_strRoomName = _RoomName;

	if (LimNum >= 1)
	{
		m_eRoominfo.m_iLimNum = LimNum;
	}

	if (LimNum >= 1)
	{
		m_eRoominfo.m_iCurNum = CurNum;
	}
	
	m_eRoominfo.m_bPub = Publics;

	m_eRoominfo.UpdateString();
	StateDrawText();
	
}

void StaticRoomBox::SetStateRoom(const RoomInfoLobby & roominfos)
{
	m_eRoominfo.fromRoomInfoLobby(roominfos);
	m_eRoominfo.UpdateString();
	StateDrawText();
}

void StaticRoomBox::DelRoom()
{
	m_eRoominfo.m_bIsActive = false;
}

void StaticRoomBox::SetGamesRoom(bool games)
{
	m_eRoominfo.IsIngame = games;
}
