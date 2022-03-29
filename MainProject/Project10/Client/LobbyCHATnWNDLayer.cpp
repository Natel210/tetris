#include "stdafx.h"
#include "LobbyCHATnWNDLayer.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "ChatEditBarItem.h"
#include "ChatingLog.h"




int LobbyCHATnWNDLayer::Init()
{
	//pMainViewItem = Layer::CreateObj<ClientMainViewItem>("MainViewItem");
	//pMainViewItme = pMainViewItem;




	pChatBarItem = CreateObj<ChatEditBarItem>(_T("LobbyChattinbar"));
	ChatingLog* pChatingLog = CreateObj<ChatingLog>(_T("ChatingLog"));

	LayerPosX =		(int)(WindSizeX * 0.05f);
	LayerPosY =		(int)(WindSizeY * 0.5f);
	LayerSizeX =	(int)(WindSizeX * 0.9f);
	LayerSizeY =	(int)(WindSizeY * 0.43f);


	WinDCManager::CreateHDC(_T("LobbyChatDC"), LobbyChatDC, LayerPosX, LayerPosY, LayerSizeX, LayerSizeY);
	LayerZ = LobbyChatDC;
	m_LayerhDC = WinDCManager::FindDC(_T("LobbyChatDC"));

	return PR_OK;
}

int LobbyCHATnWNDLayer::LayerUpdate(float time)
{


	HBRUSH Backbrush = ColorManager::FindBrush(_T("BackMapBrush"));
	HBRUSH oldbrush = (HBRUSH)SelectObject(m_LayerhDC, Backbrush);
	HPEN oldPen = (HPEN)SelectObject(m_LayerhDC, GetStockObject(NULL_PEN));
	Rectangle(m_LayerhDC, 0, 0, LayerSizeX, LayerSizeY);
	(HBRUSH)SelectObject(m_LayerhDC, oldbrush);
	(HPEN)SelectObject(m_LayerhDC, oldPen);


	/////////////////////////////////////////////////////////////////////////////////////////

	return PR_OK;
}

int LobbyCHATnWNDLayer::StartUp()
{


	ChatingLog* pChatingLog = FindObj<ChatingLog>(_T("ChatingLog"));
	pChatBarItem->WndShow();
	pChatingLog->WndShow();


	return PR_OK;
}

int LobbyCHATnWNDLayer::release()
{
	pChatBarItem = nullptr;

	return PR_OK;
}

LobbyCHATnWNDLayer::LobbyCHATnWNDLayer() : pChatBarItem (nullptr)
{
}


LobbyCHATnWNDLayer::~LobbyCHATnWNDLayer()
{
}
