#include "stdafx.h"
#include "IdleTimerleft.h"
#include <windowsx.h>
#include "ClientHeader.h"

int IdleTimerleft::Input(float time)
{
	return PR_OK;
}

int IdleTimerleft::Update(float time)
{
	return PR_OK;
}

int IdleTimerleft::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("IdleTimerleft"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600 + (Map_maxX * 30) + 10 + 5, 50 + 10 + 50, 115, 40,ClientCore::mainhWnd, ClientCore::mainhInst, NULL);


	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));

	SetText(L" <= ");

	//Button_Enable(m_hWnd, true);
	//Button_SetStyle
	return PR_OK;
}

int IdleTimerleft::release()
{
	WNDItem::release(0);
	return PR_OK;
}

IdleTimerleft::IdleTimerleft()
{
}


IdleTimerleft::~IdleTimerleft()
{
}
