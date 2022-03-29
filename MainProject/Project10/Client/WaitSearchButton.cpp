#include "stdafx.h"
#include "WaitSearchButton.h"


WaitSearchButton::WaitSearchButton()
{
}


WaitSearchButton::~WaitSearchButton()
{
}

int WaitSearchButton::Input(float time)
{
	return PR_OK;
}

int WaitSearchButton::Update(float time)
{
	return PR_OK;
}

int WaitSearchButton::LateUpdate(float time)
{
	return PR_OK;
}

int WaitSearchButton::Transform(float time)
{
	return PR_OK;
}

int WaitSearchButton::Render(float time, HDC drow)
{
	return PR_OK;
}

int WaitSearchButton::DebugRender(float time)
{
	return PR_OK;
}

int WaitSearchButton::Collision(float time)
{
	if (m_iCollButton)
	{
		m_iCollButton = false;
	}
	return PR_OK;
}

int WaitSearchButton::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("WaitSearchRoom"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 390, 144, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 대기방 보기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int WaitSearchButton::release()
{
	WNDItem::release(0);
	return PR_OK;
}
