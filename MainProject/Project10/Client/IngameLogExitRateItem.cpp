#include "stdafx.h"
#include "IngameLogExitRateItem.h"
#include "ClientHeader.h"
#include "ClientIngameEnum.h"
#include "ClientCore.h"

IngameLogExitRateItem::IngameLogExitRateItem()
{
	
}
	
	


IngameLogExitRateItem::~IngameLogExitRateItem()
{
}

int IngameLogExitRateItem::Input(float time)
{
	return 1;
}

int IngameLogExitRateItem::Update(float time)
{
	if (1 == CallButton)
	{
		if (m_bEXIT)
		{
			SetWindowText(m_hWnd, TEXT("������ ���� ���"));
		}
		else
		{
			SetWindowText(m_hWnd, TEXT("������ ����"));
		}
	}

	

	return 1;
}

int IngameLogExitRateItem::LateUpdate(float time)
{
	return 1;
}

int IngameLogExitRateItem::Transform(float time)
{
	return 1;
}

int IngameLogExitRateItem::Render(float time, HDC drow)
{
	if (true == DrowText)
	{
		//�߰� �۾��� �ʿ��ϴٸ� ���⼭ �ؾ���.
		DrowText = false;
	}

	return 1;
}

int IngameLogExitRateItem::DebugRender(float time)
{
	return 1;
}

int IngameLogExitRateItem::Collision(float time)
{
	if (1 == CallButton)
	{
		//��ư�� ���������ϴ�.
		// ó���� �ൿ�� �������ּ���.
	}

	if (m_bEXIT)
	{
		// �̰� Ʈ���̰� 
		// ���� ���¸� ���� ������ �ϰڴ�.
	}

	return 1;
}



int IngameLogExitRateItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("EXIT WAITINGS"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600 + (Map_maxX * 30) + 15, (Map_maxY * 28) + 50, 240, 75, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetWindowText(m_hWnd, TEXT("������ ����"));
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return 1;
}

int IngameLogExitRateItem::release()
{
	//�����־�߰ڴ�. �̳����ı��Ǹ�
	//BoxhWind;
	WNDItem::release(0);
	return 1;
}




LRESULT IngameLogExitRateItem::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ���ϰ��� 0�� ���� ����Ʈ ó���� �Ѵٴ� ���̰�
	// ���ϰ��� 1�� ��쿡�� ����Ʈ ó���� ���� �ʰڴٴ� ��.

	switch (message)
	{
	case BM_SETSTATE:
	{
		//HDC hDC = GetDC(hWnd);
		//BitBlt((m_MemoryDC), 0, 0, 1000, 1000, hDC, 0, 0, SRCCOPY);
		//1�� üũ�� ����
		//0�� üũ ������ ����
		CallButton = (int)wParam;
		if (1 == CallButton)
		{
			//InputManager
			if (KEY_KEY(MouseLB))
			{
				//�ٲ��� �ʴ´�.
			}
			else
			{
				m_bEXIT = !m_bEXIT;
			}
			
		}
		return 0;
	}
	case BM_GETSTATE:
	{
		return 0;
	}
	break;
	case WM_PAINT:
	{
		DrowText = true;
		return 0;
	}
	break;
	}
	return 0;
}



