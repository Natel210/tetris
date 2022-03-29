#include "stdafx.h"
#include "ClientCore.h"
#include "ClientHeader.h"
#include "FrameCore.h"

#include "ClientLogInScene.h"
#include "ClientLobbyScene.h"
#include "ClientRoomScene.h"
#include "ClientRankingScene.h"

#include "WNDItem.h"

std::vector<int> ClientCore::testmap;

UseServer* ClientCore::pServer;

bool ClientCore::ClientRun = true;
HWND ClientCore::mainhWnd = NULL;
HINSTANCE ClientCore::mainhInst = NULL;
HDC ClientCore::PrintDC = NULL;
WNDPROC ClientCore::mainProc = NULL;
Player ClientCore::ClientPlayer;

//
//ClientCore::ClientCore()
//{
//}
//
//
//ClientCore::~ClientCore()
//{
//}

ClientLogInScene* ClientCore::pLoginScene = nullptr;
ClientLobbyScene* ClientCore::pLobbyScene = nullptr;
ClientRoomScene* ClientCore::pRoomScene = nullptr;
ClientRankingScene* ClientCore::pRankingScene = nullptr;

bool ClientCore::init()
{
	/////////////////////////////////////////////////////////////
	ClientCore::testmap.clear();
	ClientCore::testmap.push_back(-1);//디버그용
	//////////////////////////////////////////////////////////////

#ifdef _DEBUG
	//pRankingScene = FrameCore::CreateScene<ClientRankingScene>(GameRankinScene);
	//pRankingScene->SetActive(false);
	//WNDItem::ALLHIDE();
	//pRankingScene->SetActive(true);

	//실제 실행될 로직입니다.
	pLoginScene = FrameCore::CreateScene<ClientLogInScene>(GameLoginScene);
	pLoginScene->SetActive(false);
	WNDItem::ALLHIDE();
	pLoginScene->SetActive(true);
#else

	//실제 실행될 로직입니다.
	pLoginScene = FrameCore::CreateScene<ClientLogInScene>(GameLoginScene);
	pLoginScene->SetActive(false);
	WNDItem::ALLHIDE();
	pLoginScene->SetActive(true);
#endif // _DEBUG



	/*pLobbyScene = FrameCore::CreateScene<ClientLobbyScene>(GameLobbyScene);
	pLobbyScene->SetActive(false);
	pRoomScene = FrameCore::CreateScene<ClientRoomScene>(GameRoomScene);
	pRoomScene->SetActive(false);*/
	//pRankingScene = FrameCore::CreateScene<ClientRankingScene>(GameRankinScene);
	//pRankingScene->SetActive(false);

	/////////////////////////////
	
	//pRankingScene->SetActive(true);

	//pScene = nullptr;
	//FrameCore::RemoveScene("LogIn");
	//FrameCore::RemoveScene("Lobby");
	//FrameCore::RemoveScene("Room");
	//pRoomScene->SetActive(false);
	return true;
}
static float m_testtime = 5.0f;
bool ClientCore::Update(float time)
{
	FrameCore::Logic(time);
	//if (m_testtime < 0.f)
	//{
	//	m_testtime = 5.0f;
	//	pRoomScene->SetActive(!pRoomScene->GetActive());
	//}
	//else
	//{
	//	m_testtime -= time;
	//}



	return true;
}

bool ClientCore::release()
{
	FrameCore::RemoveScene(_T("Room"));
	FrameCore::RemoveScene(_T("LogIn"));
	FrameCore::RemoveScene(_T("Lobby"));
	FrameCore::RemoveScene(_T("Ranking"));
	return true;
}
