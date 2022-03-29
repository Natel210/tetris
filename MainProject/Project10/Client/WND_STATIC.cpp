#include "stdafx.h"
#include "WND_STATIC.h"
#include <windowsx.h>

WND_STATIC::WND_STATIC()
{
}


WND_STATIC::~WND_STATIC()
{
}

int WND_STATIC::LateUpdate(float time)
{
	return PR_OK;
}

int WND_STATIC::Transform(float time)
{
	return PR_OK;
}

int WND_STATIC::Render(float time, HDC drow)
{
	return PR_OK;
}

int WND_STATIC::DebugRender(float time)
{
	return PR_OK;
}

int WND_STATIC::Collision(float time)
{
	return PR_OK;
}

int WND_STATIC::Init()
{
	return PR_OK;
}

int WND_STATIC::release()
{
	return PR_OK;
}

LRESULT WND_STATIC::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//switch (message)
	//{
	//default:
	//	break;
	//}

	return 0;
}

void WND_STATIC::SetText(const TCHAR * str)
{
	SetWindowText(m_hWnd, str);
}

const Tstring WND_STATIC::GetText() const
{
	UpdateWindow(m_hWnd);
	TCHAR savebuff[_MAX_PATH];
	Tstring strTex;
	GetWindowText(m_hWnd, savebuff, _MAX_PATH);
	strTex = savebuff;
	return strTex;
}

void WND_STATIC::SetBackgraoundColor(COLORREF _Color)
{

}
