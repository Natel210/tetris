#include "stdafx.h"
#include "ResultItem.h"
#include "ClientIngameEnum.h"

int ResultItem::Input(float time)
{
	return PR_OK;
}

int ResultItem::Update(float time)
{
	return PR_OK;
}

void ResultItem::SetBackgraoundColor(COLORREF _Color)
{
	
}

int ResultItem::Init()
{
	WNDItem::Init(TEXT("static"), m_strName.c_str(), WS_CHILD | WS_VISIBLE | SS_CENTER, 0, 0, 100, 1000, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetWindowText(m_hWnd, TEXT(""));
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int ResultItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}

ResultItem::ResultItem()
{
}


ResultItem::~ResultItem()
{
}
