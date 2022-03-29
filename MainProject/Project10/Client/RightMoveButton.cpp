#include "stdafx.h"
#include "RightMoveButton.h"


RightMoveButton::RightMoveButton()
{
}


RightMoveButton::~RightMoveButton()
{
}

int RightMoveButton::Input(float time)
{
	return PR_OK;
}

int RightMoveButton::Update(float time)
{
	return PR_OK;
}

int RightMoveButton::LateUpdate(float time)
{
	return PR_OK;
}

int RightMoveButton::Transform(float time)
{
	return PR_OK;
}

int RightMoveButton::Render(float time, HDC drow)
{
	return PR_OK;
}

int RightMoveButton::DebugRender(float time)
{
	return PR_OK;
}

int RightMoveButton::Collision(float time)
{
	if (m_iCollButton)
	{
		m_iCollButton = false;
	}
	return PR_OK;
}

int RightMoveButton::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("Rightmove"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 592+46, 390, 100, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" ==> ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int RightMoveButton::release()
{
	WNDItem::release(0);
	return PR_OK;
}
