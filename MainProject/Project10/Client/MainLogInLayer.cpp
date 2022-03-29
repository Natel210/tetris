#include "stdafx.h"
#include "MainLogInLayer.h"

#include "ClientCore.h"
#include "ClientHeader.h"
#include "Render/Rendermanager.h"

#include "LoginID.h"
#include "LoginPW.h"
#include "LoginSignup.h"
#include "LoginFindIDPW.h"
#include "LogInEXITItem.h"
#include "LoginToLobby.h"

int MainLogInLayer::Init()
{
	pLoginID = CreateObj<LoginID>(_T("LoginID"));
	pLoginPW = CreateObj<LoginPW>(_T("LoginPW"));
	pLoginMove = CreateObj<LoginToLobby>(_T("LoginMove"));
	LogInEXITItem* pExit = CreateObj<LogInEXITItem>(_T("LoginEXIT"));
	LoginFindIDPW* pFindIDPW = CreateObj<LoginFindIDPW>(_T("LoginFindIDPW"));
	LoginSignup* pSignin = CreateObj<LoginSignup>(_T("LoginSignin"));
	return PR_OK;
}

int MainLogInLayer::LayerUpdate(float time)
{
#ifdef _DEBUG
	Rectangle(m_LayerhDC, 0, 0, 700, 400);
#endif // _DEBUG
	Tstring GetId = pLoginID->GetText();
	Tstring GetPw = pLoginPW->GetText();
	pLoginMove->LoginSet(GetId, GetPw);
	return PR_OK;
}

int MainLogInLayer::StartUp()
{
	pLoginID->WndShow();
	pLoginPW->WndShow();
	pLoginMove->WndShow();
	LogInEXITItem* pExit2 = FindObj<LogInEXITItem>(_T("LoginEXIT"));
	pExit2->WndShow();
	LoginFindIDPW* pFindIDPW2 = FindObj<LoginFindIDPW>(_T("LoginFindIDPW"));
	pFindIDPW2->WndShow();
	LoginSignup* pSignin2 = FindObj<LoginSignup>(_T("LoginSignin"));
	pSignin2->WndShow();
	return PR_OK;
}

int MainLogInLayer::release()
{
	WinDCManager::DelDC(_T("LoginDC"));
	return PR_OK;
}

MainLogInLayer::MainLogInLayer()
{
}


MainLogInLayer::~MainLogInLayer()
{
}
