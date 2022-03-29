#include "stdafx.h"
#include "ClientLobbyScene.h"


#include "MainLobbyLayer.h"
#include "LobbyCHATnWNDLayer.h"
#include "LobbyPlayerlistLayer.h"

int ClientLobbyScene::Init()
{
	pMainLobbyLayer = Scene::CreateLayer<MainLobbyLayer>(_T("LobbyMain"));
	LobbyCHATnWNDLayer* pChatLobbyLayer = Scene::CreateLayer<LobbyCHATnWNDLayer>(_T("LobbyChat"));
	LobbyPlayerlistLayer* pPlayLobbyLayer = Scene::CreateLayer<LobbyPlayerlistLayer>(_T("LobbyPlay"));
	return 1;
}


int ClientLobbyScene::release()
{
	return 1;
}

ClientLobbyScene::ClientLobbyScene()
{
}


ClientLobbyScene::~ClientLobbyScene()
{
}
