#include "stdafx.h"
#include "ReadyButton.h"
#include "ClientRoomScene.h"
#include "ClientHeader.h"

ReadyButton::ReadyButton()
{
}


ReadyButton::~ReadyButton()
{
}

int ReadyButton::Input(float time)
{
	return PR_OK;
}

int ReadyButton::Update(float time)
{

	if (m_bChanged)
	{
		if (ClientRoomScene::gethost())
		{
			if (m_bIsReady)
			{
				SetText(L" ���� �ϱ� ���");
			}
			else
			{
				SetText(L" ���� �ϱ�");
			}
		}
		else
		{
			if (m_bIsReady)
			{
				SetText(L" �غ� �ϱ� ���");
			}
			else
			{
				SetText(L" �غ� �ϱ�");
			}
		}
		m_bChanged = false;
	}
	

	return PR_OK;
}

int ReadyButton::LateUpdate(float time)
{
	return PR_OK;
}

int ReadyButton::Transform(float time)
{
	return PR_OK;
}

int ReadyButton::Render(float time, HDC drow)
{
	return PR_OK;
}

int ReadyButton::DebugRender(float time)
{
	return PR_OK;
}

int ReadyButton::Collision(float time)
{


	if (m_iCollButton)
	{
		//if (ClientRoomScene::m_fChangeCoolTime > 0.0f)
		//{
		//	m_iCollButton = false;
		//	return PR_OK;
		//}

		m_bChanged = true;
		m_bIsReady = !m_bIsReady;
		m_iCollButton = false;
	}
	return PR_OK;
}

int ReadyButton::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("ReadyButton"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600 + (Map_maxX * 15) + 5 -100, 50 + (Map_maxY * 15) + 15+ 100, 200, 100, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	if (ClientRoomScene::gethost())
	{
		SetText(L" ���� �ϱ� ");
	}
	else
	{
		SetText(L" �غ� �ϱ� ");
	}
	
	return PR_OK;
}

int ReadyButton::release()
{
	WNDItem::release(0);
	return PR_OK;
}
