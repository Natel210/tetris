#include "stdafx.h"
#include "StaticRankTitle.h"


int StaticRankTitle::Input(float time)
{
	return PR_OK;
}

int StaticRankTitle::Update(float time)
{
	return PR_OK;
}

int StaticRankTitle::Init()
{
	WNDItem::Init(TEXT("static"), TEXT("LankTitle"), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 370, 20, 400, 80, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L"¼ø À§");
	HFONT font = CreateFont(70, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int StaticRankTitle::release()
{
	WNDItem::release(0);
	return PR_OK;
}

StaticRankTitle::StaticRankTitle()
{
}


StaticRankTitle::~StaticRankTitle()
{
}
