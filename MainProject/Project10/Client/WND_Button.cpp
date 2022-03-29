#include "stdafx.h"
#include "WND_Button.h"
#include "Input/Input.h"

LRESULT WND_Button::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 리턴값이 0인 경우는 디폴트 처리를 한다는 것이고
	// 리턴값이 1인 경우에는 디폴트 처리를 하지 않겠다는 뜻.

	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		return (LRESULT)CreateSolidBrush(RGB(0, 0, 0));
	}
	case WM_CTLCOLORBTN:
	{
		return (LRESULT)CreateSolidBrush(RGB(0, 0, 0));
	}
	case BM_SETSTATE:
	{


		//내가생각하는 그 구조임.
		if (1 == m_bCurState  && m_bCurState != (int)wParam)
		{
			POINT mycursor;
			GetCursorPos(&mycursor);
			ScreenToClient(m_hWnd, &mycursor);
			//mycursor.x;
			//mycursor.y;

			if ( mycursor.x  < 0 || mycursor.y  < 0 || 
				mycursor.x  > m_Rect.right || 
				mycursor.y  > m_Rect.bottom )
			{
				m_iCollButton = false;
			}
			else
			{
				m_iCollButton = true;
			}

			
		}
		else
		{
			m_iCollButton = false;
		}
		m_bCurState = (int)wParam;

		//1이 체크된 상태
		//0이 체크 해제된 상태
		return 0;
	}
	case BM_GETSTATE:
	{
		return 0;
	}
	break;
	case WM_PAINT:
	{
		m_bDrowText = true;
		return 0;
	}
	break;
	}
	return 0;
}

void WND_Button::SetText(const TCHAR * str)
{
	if (m_hWnd  == NULL)
	{
		return;
	}
	m_strText.clear();
	m_strText = str;
	SetWindowText(m_hWnd, str);
	return;
}

void WND_Button::Setidx(int str)
{
	if (m_hWnd == NULL)
	{
		return;
	}
	m_strText.clear();
	TCHAR buf[100] = { 0, };
	_itot_s(str, buf, 10);
	m_strText = buf;
	SetWindowText(m_hWnd, buf);
	return;
}

const Tstring WND_Button::GetText() const
{
	return m_strText;
}

WND_Button::WND_Button()
{
}


WND_Button::~WND_Button()
{
	
}

int WND_Button::LateUpdate(float time)
{
	return 0;
}

int WND_Button::Transform(float time)
{
	return 0;
}

int WND_Button::Render(float time, HDC drow)
{
	return 0;
}

int WND_Button::DebugRender(float time)
{
	return 0;
}

int WND_Button::Collision(float time)
{
	return 0;
}
