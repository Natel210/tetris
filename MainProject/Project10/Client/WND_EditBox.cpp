#include "stdafx.h"
#include "WND_EditBox.h"
#include <CommCtrl.h>

WND_EditBox::WND_EditBox()
{
}


WND_EditBox::~WND_EditBox()
{
}

int WND_EditBox::LateUpdate(float time)
{
	return 0;
}

int WND_EditBox::Transform(float time)
{
	return 0;
}

int WND_EditBox::Render(float time, HDC drow)
{
	return 0;
}

int WND_EditBox::DebugRender(float time)
{
	return 0;
}

int WND_EditBox::Collision(float time)
{
	return 0;
}

LRESULT WND_EditBox::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT edit_result = NULL;
	switch (message)
	{
	case EM_GETSEL:
	{
		break;
	}
	case EM_SETSEL:
	{
		break;
	}
	/*case EN_SETFOCUS:
	{
		int a = 0;
		int b = 0;
		break;
	}*/
	case EN_KILLFOCUS:
	{
		break;
	}
	case WM_KEYDOWN:
	{
	/*	switch (wParam)
		{
		case VK_RETURN:
		{
			if (isEnterCntl && GetFocusBox())
			{
				SetWindowText(hWnd, TEXT(""));
			}
			edit_result = 0;
			break;
		}
		default:
			break;
		}
		break;*/
	}

	//SetText(L"");


	default:
		break;
	}



	return edit_result;
}

void WND_EditBox::SetText(const TCHAR * str)
{
	if (m_hWnd == NULL)
	{
		return;
	}
	
	SetWindowText(m_hWnd, str);
	return;
}

const Tstring WND_EditBox::GetText() const
{
	UpdateWindow(m_hWnd);
	TCHAR savebuff[_MAX_PATH];
	Tstring strTex;
	GetWindowText(m_hWnd, savebuff, _MAX_PATH);
	strTex = savebuff;
	return strTex;
}

void WND_EditBox::SetFocusBox()
{
	//SendMessage(m_hWnd, WM_IME_SETCONTEXT, 0, 0);
	//WM_IME_SETCONTEXT

	//SendMessage(m_hWnd, EM_TAKEFOCUS, 0, 0);
	SetFocus(NULL);
	SetFocus(m_hWnd);
	//SetFocus(ClientCore::mainhWnd);
}

bool WND_EditBox::GetFocusBox() const
{
	if (m_hWnd == GetFocus())
	{
		return true;
	}
	return false;
}
