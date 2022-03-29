#include "stdafx.h"
#include "WND_LISTBOX.h"
#include "ClientHeader.h"
#include "windowsx.h"

int WND_LISTBOX::GetSel() const
{
	int retruens = ListBox_GetCurSel(m_hWnd);
	return retruens;
}

void WND_LISTBOX::SetSel(int Sel)
{
	ListBox_SetCurSel(m_hWnd, Sel);
}

int WND_LISTBOX::AddString(const TCHAR * pstr)
{
	SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)pstr);
	//UpdateWindow(m_hWnd);
	return PR_OK;
}

//int WND_LISTBOX::aAddString(const TCHAR * pstr)
//{
//	SendMessageA(m_hWnd, LB_ADDSTRING, 0, (LPARAM)pstr);
//	//UpdateWindow(m_hWnd);
//	return PR_OK;
//}

int WND_LISTBOX::AllClear()
{
	ListBox_ResetContent(m_hWnd);
	//int count = (int)SendMessage(m_hWnd, LB_GETCOUNT, (WPARAM)0, (LPARAM)0);
	//for (int i = 0 ; i < count ; ++i)
	//{
	//	ListBox_DeleteString(m_hWnd, i);
	////	SendMessage(m_hWnd, LB_DELETESTRING, a, (LPARAM)1);
	//}
	
	return 0;
}

WND_LISTBOX::WND_LISTBOX()
{
}


WND_LISTBOX::~WND_LISTBOX()
{
}

int WND_LISTBOX::Update(float time)
{
	return PR_OK;
}

int WND_LISTBOX::LateUpdate(float time)
{
	return PR_OK;
}

int WND_LISTBOX::Transform(float time)
{
	return PR_OK;
}

int WND_LISTBOX::Render(float time, HDC drow)
{
	return PR_OK;
}

int WND_LISTBOX::DebugRender(float time)
{
	return PR_OK;
}

int WND_LISTBOX::Collision(float time)
{
	return PR_OK;
}

int WND_LISTBOX::Init()
{
	return PR_OK;
}

int WND_LISTBOX::release()
{
	return PR_OK;
}

LRESULT WND_LISTBOX::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		//키조작을 막습니다.
		if (m_bContKey)
		{
			return 1;
		}
		return 0;
	}
	case WM_KEYUP:
	{
		//키조작을 막습니다.
		if (m_bContKey)
		{
			return 1;
		}
		return 0;
	}
	case WM_KEYLAST:
	{
		//키조작을 막습니다.
		if (m_bContKey)
		{
			return 1;
		}
		return 0;
	}
	case LB_C_ALLCLEAR:
	{

		

		return 0;
	}
	}
	return 0;
}
