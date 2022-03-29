#include "stdafx.h"
#include "LeftMoveButton.h"


LeftMoveButton::LeftMoveButton()
{
}


LeftMoveButton::~LeftMoveButton()
{
}

int LeftMoveButton::Input(float time)
{
	return PR_OK;
}

int LeftMoveButton::Update(float time)
{
	return PR_OK;
}

int LeftMoveButton::LateUpdate(float time)
{
	return PR_OK;
}

int LeftMoveButton::Transform(float time)
{
	return PR_OK;
}

int LeftMoveButton::Render(float time, HDC drow)
{
	return PR_OK;
}

int LeftMoveButton::DebugRender(float time)
{
	return PR_OK;
}

int LeftMoveButton::Collision(float time)
{
	if (m_iCollButton)
	{
		m_iCollButton = false;
	}
	return PR_OK;
}

int LeftMoveButton::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("LeftMove"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 428, 390, 100, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" <== ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int LeftMoveButton::release()
{
	WNDItem::release(0);
	return PR_OK;
}
