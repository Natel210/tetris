#include "stdafx.h"
#include "RankingExit.h"
#include "ClientHeader.h"


#include "FrameCore.h"
#include "ClientRankingScene.h"
#include "ClientLobbyScene.h"


RankingExit::RankingExit()
{
}


RankingExit::~RankingExit()
{
}

int RankingExit::Input(float time)
{
	return PR_OK;
}

int RankingExit::Update(float time)
{
	return PR_OK;
}

int RankingExit::LateUpdate(float time)
{
	return PR_OK;
}

int RankingExit::Transform(float time)
{
	return PR_OK;
}

int RankingExit::Render(float time, HDC drow)
{
	return PR_OK;
}

int RankingExit::DebugRender(float time)
{
	return PR_OK;
}

int RankingExit::Collision(float time)
{
	if (m_iCollButton)
	{
		ClientLobbyScene* pNextScene = FrameCore::CreateScene<ClientLobbyScene>(GameLobbyScene);
		pNextScene->SetActive(false);
		//WNDItem::ALLHIDE();

		//MessageBox(NULL, TEXT("정상적으로 로그아웃 되었습니다. \n로그인 화면으로 이동합니다."), TEXT("로그 아웃"), MB_OK);

		Sleep(10);
		ClientRankingScene* pCurScene = FrameCore::FindScene<ClientRankingScene>(GameRankinScene);

		pNextScene->SetActive(true);
		pCurScene->SetActive(false);
		pCurScene->Delete();


		m_iCollButton = false;

		return PR_SCENECHNAGE;
	}

	return PR_OK;
}

int RankingExit::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("returnlobby"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (int)(WindSizeX * 0.06f + 780), int(WindSizeY * 0.82f), 200, 60, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 로비로 돌아 가기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int RankingExit::release()
{
	WNDItem::release(0);
	return PR_OK;
}
