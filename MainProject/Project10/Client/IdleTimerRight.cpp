#include "stdafx.h"
#include "IdleTimerRight.h"
#include <windowsx.h>
#include "ClientHeader.h"

int IdleTimerRight::Input(float time)
{
	return PR_OK;
}

int IdleTimerRight::Update(float time)
{
	return PR_OK;
}

int IdleTimerRight::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("IdleTimerRight"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600 + (Map_maxX * 30) + 10 + 5 + 125, 50 + 10 + 50, 115, 40, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);

	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));

	SetText(L" => ");
	//Button_Enable(m_hWnd, false);
	return PR_OK;
}

int IdleTimerRight::release()
{
	WNDItem::release(0);
	return PR_OK;
}

IdleTimerRight::IdleTimerRight()
{
}


IdleTimerRight::~IdleTimerRight()
{
}
