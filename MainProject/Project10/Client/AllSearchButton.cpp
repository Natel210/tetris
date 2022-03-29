#include "stdafx.h"
#include "AllSearchButton.h"


AllSearchButton::AllSearchButton()
{
}


AllSearchButton::~AllSearchButton()
{
}

int AllSearchButton::Input(float time)
{
	return PR_OK;
}

int AllSearchButton::Update(float time)
{
	return PR_OK;
}

int AllSearchButton::LateUpdate(float time)
{
	return PR_OK;
}

int AllSearchButton::Transform(float time)
{
	return PR_OK;
}

int AllSearchButton::Render(float time, HDC drow)
{
	return PR_OK;
}

int AllSearchButton::DebugRender(float time)
{
	return PR_OK;
}

int AllSearchButton::Collision(float time)
{
	if (m_iCollButton)
	{
		m_iCollButton = false;
	}

	return PR_OK;
}

int AllSearchButton::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("AllRooms"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 264, 390, 144, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 모든방 보기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int AllSearchButton::release()
{
	WNDItem::release(0);
	return PR_OK;
}
