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
			SetWindowText(m_hWnd, TEXT("나가기 예약 취소"));
		}
		else
		{
			SetWindowText(m_hWnd, TEXT("나가기 예약"));
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
		//추가 작업이 필요하다면 여기서 해야함.
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
		//버튼이 눌러졌습니다.
		// 처리할 행동을 선택해주세요.
	}

	if (m_bEXIT)
	{
		// 이게 트루이고 
		// 게임 상태를 봐서 나가게 하겠다.
	}

	return 1;
}



int IngameLogExitRateItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("EXIT WAITINGS"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600 + (Map_maxX * 30) + 15, (Map_maxY * 28) + 50, 240, 75, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetWindowText(m_hWnd, TEXT("나가기 예약"));
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return 1;
}

int IngameLogExitRateItem::release()
{
	//난해주어야겠다. 이놈이파괴되면
	//BoxhWind;
	WNDItem::release(0);
	return 1;
}




LRESULT IngameLogExitRateItem::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 리턴값이 0인 경우는 디폴트 처리를 한다는 것이고
	// 리턴값이 1인 경우에는 디폴트 처리를 하지 않겠다는 뜻.

	switch (message)
	{
	case BM_SETSTATE:
	{
		//HDC hDC = GetDC(hWnd);
		//BitBlt((m_MemoryDC), 0, 0, 1000, 1000, hDC, 0, 0, SRCCOPY);
		//1이 체크된 상태
		//0이 체크 해제된 상태
		CallButton = (int)wParam;
		if (1 == CallButton)
		{
			//InputManager
			if (KEY_KEY(MouseLB))
			{
				//바꾸지 않는다.
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



