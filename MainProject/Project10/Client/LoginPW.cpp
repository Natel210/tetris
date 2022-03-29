#include "stdafx.h"
#include "LoginPW.h"
#include "ClientCore.h"

LoginPW::LoginPW()
{
}


LoginPW::~LoginPW()
{
}

int LoginPW::Input(float time)
{
	return PR_OK;
}

int LoginPW::Update(float time)
{
	return PR_OK;
}

int LoginPW::LateUpdate(float time)
{
	return PR_OK;
}

int LoginPW::Transform(float time)
{
	return PR_OK;
}

int LoginPW::Render(float time, HDC drow)
{
	return PR_OK;
}

int LoginPW::DebugRender(float time)
{
	return PR_OK;
}

int LoginPW::Collision(float time)
{
	return PR_OK;
}

int LoginPW::Init()
{
	WNDItem::Init(TEXT("edit"), TEXT("LoginPW"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_PASSWORD, 540, 350, 230, 70, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L"");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int LoginPW::release()
{
	WNDItem::release(1);
	return PR_OK;
}
