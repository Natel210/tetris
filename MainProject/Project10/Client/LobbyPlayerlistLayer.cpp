#include "stdafx.h"
#include "LobbyPlayerlistLayer.h"
#include "ClientHeader.h"
#include "ClientCore.h"
#include "LobbyPlayerlist.h"


int LobbyPlayerlistLayer::Init()
{
	LayerPosX =		(int)(WindSizeX * 0.65f);
	LayerPosY =		(int)(WindSizeY * 0.05f);
	LayerSizeX =	(int)(WindSizeX * 0.30f);
	LayerSizeY =	(int)(WindSizeY * 0.45f);


	WinDCManager::CreateHDC(_T("LobbyPlayDC"), LobbyplayDC, LayerPosX, LayerPosY, LayerSizeX, LayerSizeY);
	LayerZ = LobbyplayDC;
	m_LayerhDC = WinDCManager::FindDC(_T("LobbyPlayDC"));

	LobbyPlayerlist* pList = CreateObj<LobbyPlayerlist>(_T("LobbyPlayerlist"));
	pList->MovePos(LayerPosX +10, LayerPosY +10);
	pList->SetSize(LayerSizeX - 20, LayerSizeY -20);
	//pList->m_bContKey/
	return 2;
}

int LobbyPlayerlistLayer::LayerUpdate(float time)
{
	HBRUSH Backbrush = ColorManager::FindBrush(_T("BackMapBrush"));
	HBRUSH oldbrush = (HBRUSH)SelectObject(m_LayerhDC, Backbrush);
	HPEN oldPen = (HPEN)SelectObject(m_LayerhDC, GetStockObject(NULL_PEN));
	Rectangle(m_LayerhDC, 0, 0, LayerSizeX, LayerSizeY);
	(HBRUSH)SelectObject(m_LayerhDC, oldbrush);
	(HPEN)SelectObject(m_LayerhDC, oldPen);





	return 2;
}

int LobbyPlayerlistLayer::StartUp()
{
	LobbyPlayerlist* pList = FindObj<LobbyPlayerlist>(_T("LobbyPlayerlist"));
	if (pList)
	{
		pList->WndShow();
		return false;
	}
	
	return 2;
}

int LobbyPlayerlistLayer::release()
{
	return 2;
}

LobbyPlayerlistLayer::LobbyPlayerlistLayer()
{
}


LobbyPlayerlistLayer::~LobbyPlayerlistLayer()
{
}
