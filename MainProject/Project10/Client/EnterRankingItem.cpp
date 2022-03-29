#include "stdafx.h"
#include "EnterRankingItem.h"
#include "ClientHeader.h"

#include "FrameCore.h"
#include "ClientRankingScene.h"
#include "ClientLobbyScene.h"


EnterRankingItem::EnterRankingItem()
{
}


EnterRankingItem::~EnterRankingItem()
{
}

int EnterRankingItem::Input(float time)
{
	return PR_OK;
}

int EnterRankingItem::Update(float time)
{
	return PR_OK;
}

int EnterRankingItem::LateUpdate(float time)
{
	return PR_OK;
}

int EnterRankingItem::Transform(float time)
{
	return PR_OK;
}

int EnterRankingItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int EnterRankingItem::DebugRender(float time)
{
	return PR_OK;
}

int EnterRankingItem::Collision(float time)
{
	if (m_iCollButton)
	{
		///////////////////어떠한 조건들을 완료하고 나서,

		ClientRankingScene* pNextScene = FrameCore::CreateScene<ClientRankingScene>(GameRankinScene);
		pNextScene->SetActive(false);
		WNDItem::ALLHIDE();

		ClientLobbyScene* pCurScene = FrameCore::FindScene<ClientLobbyScene>(GameLobbyScene);
		pCurScene->SetActive(false);
		pCurScene->Delete();
		pNextScene->SetActive(true);
		m_iCollButton = false;
		//Sleep(10);
		return PR_SCENECHNAGE;
	}

	return PR_OK;
}

int EnterRankingItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("EnterRank"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (int)(WindSizeX * 0.06f + 430),int( WindSizeY * 0.85f), 200, 50, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 랭킹 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	//SendMessage(m_hWnd, WM_SHOWWINDOW, 1, 1);
	//WM_SHOWWINDOW
	return PR_OK;
}

int EnterRankingItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}
