#include "stdafx.h"
#include "LogInEXITItem.h"

#include "ClientHeader.h"
#include "ClientIngameEnum.h"
#include "ClientCore.h"

LogInEXITItem::LogInEXITItem()
{
}


LogInEXITItem::~LogInEXITItem()
{
}

int LogInEXITItem::Input(float time)
{
	return PR_OK;
}

int LogInEXITItem::Update(float time)
{
	return PR_OK;
}

int LogInEXITItem::LateUpdate(float time)
{
	return PR_OK;
}

int LogInEXITItem::Transform(float time)
{
	return PR_OK;
}

int LogInEXITItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int LogInEXITItem::DebugRender(float time)
{
	return PR_OK;
}

int LogInEXITItem::Collision(float time)
{
	if (m_iCollButton)
	{
		ClientCore::ClientRun = false;
	}

	return PR_OK;
}

int LogInEXITItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("LoginExit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 550, 240, 75, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" Á¾ ·á ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int LogInEXITItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}
