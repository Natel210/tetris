#include "stdafx.h"
#include "ClientLogInScene.h"


#include "MainLogInLayer.h"

int ClientLogInScene::Init()
{
	pMainLoginLayer = Scene::CreateLayer<MainLogInLayer>(_T("LogIn"));
	return 1;
}

int ClientLogInScene::release()
{
	pMainLoginLayer = nullptr;
	return 1;
}

ClientLogInScene::ClientLogInScene() : Scene()
{
}


ClientLogInScene::~ClientLogInScene()
{
}
