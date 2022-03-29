#include "stdafx.h"
#include "EnterLobbyExitItem.h"
#include "ClientHeader.h"

EnterLobbyExitItem::EnterLobbyExitItem()
{
}


EnterLobbyExitItem::~EnterLobbyExitItem()
{
}

int EnterLobbyExitItem::Input(float time)
{
	return PR_OK;
}

int EnterLobbyExitItem::Update(float time)
{
	return PR_OK;
}

int EnterLobbyExitItem::LateUpdate(float time)
{
	return PR_OK;
}

int EnterLobbyExitItem::Transform(float time)
{
	return PR_OK;
}

int EnterLobbyExitItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int EnterLobbyExitItem::DebugRender(float time)
{
	return PR_OK;
}

int EnterLobbyExitItem::Collision(float time)
{
	if (m_iCollButton)
	{
		ClientCore::ClientRun = false;
		m_iCollButton = false;
		

	

	}

	return PR_OK;
}

int EnterLobbyExitItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("LobbyExit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (int)(WindSizeX * 0.06f + 860), (int)(WindSizeY * 0.85f), 200, 50, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" Á¾ ·á ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int EnterLobbyExitItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}
