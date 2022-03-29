#include "stdafx.h"
#include "MovePageButton.h"


int MovePageButton::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("movepage"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 528 + 20, 390, 70, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 0 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int MovePageButton::release()
{
	WNDItem::release(0);
	return PR_OK;
}

MovePageButton::MovePageButton()
{
}


MovePageButton::~MovePageButton()
{
}

int MovePageButton::Input(float time)
{
	return PR_OK;
}

int MovePageButton::Update(float time)
{
	return PR_OK;
}

int MovePageButton::LateUpdate(float time)
{
	return PR_OK;
}

int MovePageButton::Transform(float time)
{
	return PR_OK;
}

int MovePageButton::Render(float time, HDC drow)
{
	return PR_OK;
}

int MovePageButton::DebugRender(float time)
{
	return PR_OK;
}

int MovePageButton::Collision(float time)
{
	if (m_iCollButton)
	{
		m_iCollButton = false;
	}
	return PR_OK;
}
