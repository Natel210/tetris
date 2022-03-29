#include "stdafx.h"
#include "LoginID.h"
#include "ClientCore.h"

int LoginID::Init()
{
	WNDItem::Init(TEXT("edit"), TEXT("LoginID"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 300, 350, 230, 70, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L"");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));

	return PR_OK;
}

int LoginID::release()
{
	WNDItem::release(1);
	return PR_OK;
}


LoginID::LoginID()
{
}


LoginID::~LoginID()
{
}

int LoginID::Input(float time)
{

	return PR_OK;
}

int LoginID::Update(float time)
{
	return PR_OK;
}

int LoginID::LateUpdate(float time)
{
	return PR_OK;
}

int LoginID::Transform(float time)
{
	return PR_OK;
}

int LoginID::Render(float time, HDC drow)
{
	return PR_OK;
}

int LoginID::DebugRender(float time)
{
	return PR_OK;
}

int LoginID::Collision(float time)
{


	return PR_OK;
}
