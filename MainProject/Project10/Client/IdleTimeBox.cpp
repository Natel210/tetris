#include "stdafx.h"
#include "IdleTimeBox.h"

#include "ClientHeader.h"


int IdleTimeBox::Input(float time)
{
	return PR_OK;
}

int IdleTimeBox::Update(float time)
{
	return PR_OK;
}

int IdleTimeBox::Init()
{
	WNDItem::Init(TEXT("static"), TEXT("RoomTimer"), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 600 + (Map_maxX * 30) + 10 +5, 50 + 10, 240, (Map_maxY * 5) - 20 - 50, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	SetText(TEXT(" 01 : 00.00"));
	return PR_OK;
}

int IdleTimeBox::release()
{
	WNDItem::release(0);
	return PR_OK;
}

IdleTimeBox::IdleTimeBox()
{
}


IdleTimeBox::~IdleTimeBox()
{
}
