#include "stdafx.h"
#include "ReFrashButton.h"
#include "ClientHeader.h"

bool ReFrashButton::isRefrash() 
{
	bool returnbool = false;
	if (UpdateOK == true)
	{
		returnbool = true;
		UpdateOK = false;
	}
	return returnbool;
}

ReFrashButton::ReFrashButton()
{
}


ReFrashButton::~ReFrashButton()
{
}

int ReFrashButton::Input(float time)
{
	return PR_OK;
}

int ReFrashButton::Update(float time)
{
	//if (cooltime < 0.0f)
	//{
	//	SetText(L"갱신 하기");
	//}
	//else
	//{
	//	TCHAR buff[_MAX_PATH];

	//	swprintf_s(buff, L"적용 중 %.1F초 ", cooltime);
	//	SetText(buff);
	//}



	return PR_OK;
}

int ReFrashButton::LateUpdate(float time)
{
	return PR_OK;
}

int ReFrashButton::Transform(float time)
{
	return PR_OK;
}

int ReFrashButton::Render(float time, HDC drow)
{
	return PR_OK;
}

int ReFrashButton::DebugRender(float time)
{
	return PR_OK;
}

int ReFrashButton::Collision(float time)
{
	if (cooltime < 0.0f)
	{
		if (m_iCollButton)
		{
			UpdateOK = true;
			m_iCollButton = 0;
			cooltime = 2.0f;
		}

	}
	else
	{
		if (m_iCollButton)
		{
			m_iCollButton = 0;
		}

		cooltime -= time;
	}


	return PR_OK;
}

int ReFrashButton::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("reFrash"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (int)(WindSizeX * 0.06f + 550), int(WindSizeY * 0.82f), 200, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);

	SetText(L"갱신 하기");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int ReFrashButton::release()
{
	WNDItem::release(0);
	return PR_OK;
}
