#include "stdafx.h"
#include "ReadyStatic.h"
#include "ClientIngameEnum.h"

int ReadyStatic::Input(float time)
{
	return PR_OK;
}

int ReadyStatic::Update(float time)
{
	//if (m_testtime <= 0.0f)
	//{
	//	m_btest = !m_btest;
	//	m_testtime = 3.0f;
	//	this->SetChangeBK(m_btest, RGB(50, 50, 50));
	//}
	//else
	//{
	//	m_testtime -= time;
	//}
	


	if (m_bchanged)
	{
		switch ((playerready)m_iplayerready)
		{
		case PREADY_NO:
			SetText(L" 비어 있음 ");
			break;
		case PREADY_STAY:
			SetText(L" 대 기 ");
			break;
		case PREADY_READY:
			SetText(L" 준 비 ");
			break;
		case PREADY_WAIT:
			SetText(L" 방 장 ");
			break;
		case PREADY_START:
			SetText(L" 시 작 ");
			break;
		default:
			break;
		}
		m_bchanged = false;
	}
	

	return PR_OK;
}

int ReadyStatic::Init()
{
	WNDItem::Init(TEXT("static"), m_strName.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 264, 390, 144, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	//this->SetChangeBK(true, RGB(50, 50, 50));
	//264, 390, 144, 60,
	//SetText(L" 대 기 ");
	m_bchanged = true;
	//m_btest = true;
	return PR_OK;
}

int ReadyStatic::GetReady() const
{
	return m_iplayerready;
}

void ReadyStatic::SetReady(int readys)
{
	if (m_iplayerready == readys)
	{
		m_bchanged = false;
	}
	else
	{
		m_bchanged = true;
	}
	m_iplayerready = readys;
}

int ReadyStatic::release()
{
	WNDItem::release(0);
	return PR_OK;
}

ReadyStatic::ReadyStatic()
{
}


ReadyStatic::~ReadyStatic()
{
}
