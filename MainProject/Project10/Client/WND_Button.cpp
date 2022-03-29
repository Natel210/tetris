#include "stdafx.h"
#include "WND_Button.h"
#include "Input/Input.h"

LRESULT WND_Button::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ���ϰ��� 0�� ���� ����Ʈ ó���� �Ѵٴ� ���̰�
	// ���ϰ��� 1�� ��쿡�� ����Ʈ ó���� ���� �ʰڴٴ� ��.

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


		//���������ϴ� �� ������.
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

		//1�� üũ�� ����
		//0�� üũ ������ ����
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
