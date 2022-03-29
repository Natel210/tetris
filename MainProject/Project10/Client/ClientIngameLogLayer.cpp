#include "stdafx.h"
#include "ClientIngameLogLayer.h"

#include "Scene.h"
#include "ClientIngameEnum.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "Render/RenderManager.h"

#include "IngameLogTimerItme.h"
#include "IngameLogNextBlockItem.h"
#include "IngameLogScoreItem.h"
#include "IngameLogExitRateItem.h"
#include "IngameLogTimerItme.h"

int ClientIngameLogLayer::Init()
{
	m_pExits = CreateObj<IngameLogExitRateItem>(_T("IngameExit"));
	//exits->SetActive(false);
	m_pScores = CreateObj<IngameLogScoreItem>(_T("IngameLogScore"));
	//Scores->SetActive(false);
	m_pNextBolck = CreateObj<IngameLogNextBlockItem>(_T("IngameLogNextBlockItem"));
	m_pTimer = CreateObj<IngameLogTimerItme>(_T("IngameLogTimerItme"));


	LayerPosX = 600 + (Map_maxX * 30) + 10;
	LayerPosY = 50;
	LayerSizeX = 250;
	LayerSizeY = (Map_maxY * 30) + 30;
	LayerZ = IngameLogDC;
	WinDCManager::CreateHDC(_T("IngameLogDC"), IngameLogDC, 600 + (Map_maxX * 30) + 10, 50, 250	, (Map_maxY * 30) + 30);
	m_LayerhDC = WinDCManager::FindDC(_T("IngameLogDC"));

	return PR_OK;
}

int ClientIngameLogLayer::LayerUpdate(float time)
{
#ifdef DEBUG
	HPEN dwebugpaens = ColorManager::FindPen(_T("DebugRect"));
	HPEN OldPens = (HPEN)SelectObject(m_LayerhDC, dwebugpaens);
	Rectangle(m_LayerhDC, 0, 0, 250, (Map_maxY * 30) + 30);

	// 타이머 할당공간
	Rectangle(m_LayerhDC, 0, 0, 250, (Map_maxY * 5));
	// 다음노드 할당공간
	Rectangle(m_LayerhDC, 0, (Map_maxY * 5), 250, (Map_maxY * 13));
	// 스코어 로그 할당공간
	Rectangle(m_LayerhDC, 0, (Map_maxY * 13), 250, (Map_maxY * 28));


	(HPEN)SelectObject(m_LayerhDC, OldPens);
#endif // DEBUG

	m_bReturnLobby = m_pExits->m_bEXIT;

	//받아온다.

	return PR_OK;
}

int ClientIngameLogLayer::StartUp()
{
	//IngameLogExitRateItem* exits = FindObj<IngameLogExitRateItem>("IngameExit");
	m_pExits->SetActive(true);
	m_pExits->WndShow();
	//Scores = FindObj<IngameLogScoreItem>("IngameLogScore");
	m_pScores->SetActive(true);
	m_pScores->WndShow();
	m_pTimer->SetActive(true);
	m_pTimer->WndShow();
	return PR_OK;
}

int ClientIngameLogLayer::EndUp()
{
	//IngameLogExitRateItem* exits = FindObj<IngameLogExitRateItem>("IngameExit");
	m_pExits->SetActive(false);
	m_pExits->WndHide();
	//IngameLogScoreItem* Scores = FindObj<IngameLogScoreItem>("IngameLogScore");
	
	m_pScores->SetActive(false);
	m_pScores->WndHide();
	m_pTimer->SetActive(false);
	m_pTimer->WndHide();
	return PR_OK;
}

int ClientIngameLogLayer::release()
{
	return PR_OK;
}

void ClientIngameLogLayer::SetNextNode(int _idx)
{
	m_pNextBolck->SetNextNode(_idx);
}

void ClientIngameLogLayer::SetScore(IngameScoreSurver pScroesp[7])
{
	m_pScores->SetScore(pScroesp);
	//void SetScore(IngameScore pScroesp[7]);
}

ClientIngameLogLayer::ClientIngameLogLayer()
{
}


ClientIngameLogLayer::~ClientIngameLogLayer()
{
}
