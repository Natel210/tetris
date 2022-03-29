#include "stdafx.h"
#include "MainRankingLayer.h"

#include "RankingExit.h"
#include "RankingListItem.h"
#include "ReFrashButton.h"
#include "StaticRankTitle.h"

int MainRankingLayer::Init()
{
//	RankingListItem* RankList = CreateObj<RankingListItem>("RankingListItem");
	RankingExit* pExit = CreateObj<RankingExit>(_T("RankingExit"));
	RankingListItem* pRankingList = CreateObj<RankingListItem>(_T("RankingListItem"));
	ReFrashButton* pReFrashButton = CreateObj<ReFrashButton>(_T("ReFrashButton"));
	StaticRankTitle* pStaticRankTitle = CreateObj<StaticRankTitle>(_T("StaticRankTitle"));

	return PR_OK;
}

int MainRankingLayer::LayerUpdate(float time)
{
	ReFrashButton* pReFrashButton = FindObj<ReFrashButton>(_T("ReFrashButton"));
	if (pReFrashButton)
	{
		if (pReFrashButton->isRefrash())
		{
			RankingListItem* pRankingList = FindObj<RankingListItem>(_T("RankingListItem"));
			if (pRankingList)
			{
				pRankingList->UpdatePlayerStates();
			}
		}
	}
	

	return PR_OK;
}

int MainRankingLayer::StartUp()
{
	//	RankingListItem* RankList = CreateObj<RankingListItem>("RankingListItem");

	RankingExit* pExit = FindObj<RankingExit>(_T("RankingExit"));
	if (pExit)
	{
		pExit->WndShow();
	}
	RankingListItem* pRankingList = FindObj<RankingListItem>(_T("RankingListItem"));
	if (pRankingList)
	{
		pRankingList->WndShow();
	}

	ReFrashButton* pReFrashButton = FindObj<ReFrashButton>(_T("ReFrashButton"));
	if (pReFrashButton)
	{
		pReFrashButton->WndShow();
	}
	StaticRankTitle* pStaticRankTitle = FindObj<StaticRankTitle>(_T("StaticRankTitle"));
	if (pStaticRankTitle)
	{
		pStaticRankTitle->WndShow();
	}
	return PR_OK;
}

int MainRankingLayer::release()
{
	RankingExit* pExit = FindObj<RankingExit>(_T("RankingExit"));
	if (pExit)
	{
		pExit->WndHide();
	}
	RankingListItem* pRankingList = FindObj<RankingListItem>(_T("RankingListItem"));
	if (pRankingList)
	{
		pRankingList->WndHide();
	}
	ReFrashButton* pReFrashButton = FindObj<ReFrashButton>(_T("ReFrashButton"));
	if (pReFrashButton)
	{
		pReFrashButton->WndHide();
	}
	StaticRankTitle* pStaticRankTitle = FindObj<StaticRankTitle>(_T("StaticRankTitle"));
	if (pStaticRankTitle)
	{
		pStaticRankTitle->WndHide();
	}

	return PR_OK;
}

MainRankingLayer::MainRankingLayer()
{
}


MainRankingLayer::~MainRankingLayer()
{
}
