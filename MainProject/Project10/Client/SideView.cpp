#include "stdafx.h"
#include "SideView.h"

#include "Scene.h"
#include "ClientIngameEnum.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "RoomToRobby.h"
#include "IdleTimeBox.h"

#include "IdleTimerleft.h"
#include "IdleTimerRight.h"

#include "IdlePlayerList.h"
#include "ClientRoomScene.h"

#include "IdleChat.h"
#include "IdleChatBar.h"

const static float IngmaeTimeScale = 5.0f;


int SideView::Init()
{
	WinDCManager::CreateHDC(_T("IdleSidViewDC"), IngameLogDC, 600 + (Map_maxX * 30) + 10, 50, 250, (Map_maxY * 30) + 30);
	m_LayerhDC = WinDCManager::FindDC(_T("IdleSidViewDC"));


	//CreateItem
	pRooomToRobby = CreateObj<RoomToRobby>(_T("RoomToRobby"));


	pIdleTimeBox = CreateObj<IdleTimeBox>(_T("IdleTimeBox"));
	pIdleTimerleft = CreateObj<IdleTimerleft>(_T("IdleTimerleft"));
	pIdleTimerRight = CreateObj<IdleTimerRight>(_T("IdleTimerRight"));

	pIdlePlayerList = CreateObj<IdlePlayerList>(_T("IdlePlayerList"));

	pIdleChat = CreateObj<IdleChat>(_T("IdleChat"));
	pIdleChatBar = CreateObj<IdleChatBar>(_T("IdleChatBar"));

	return PR_OK;
}

int SideView::LayerUpdate(float time)
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
	/////////////////////////////////////////////////////////
	//호스트이 유무를 받아야겠군요.



	if (ClientRoomScene::gethost())
	{
		if (m_fTimeUpdate <= 0.0f)
		{
			m_fTimeUpdate = 0.1f;

			if (pIdleTimerleft->getState() == 1 && pIdleTimerleft->m_iCollButton == false)
			{
				ClientRoomScene::m_fSec -= IngmaeTimeScale;
				m_bchanged = true;
			}

			if (pIdleTimerRight->getState() == 1 && pIdleTimerleft->m_iCollButton == false)
			{
				ClientRoomScene::m_fSec += IngmaeTimeScale;
				m_bchanged = true;
			}

		}
		else
		{
			m_fTimeUpdate -= time;
		}


		////////////////////////////////////////////////////////////////////////////////////////////////

		if (pIdleTimerleft->m_iCollButton)
		{
			ClientRoomScene::m_fSec -= IngmaeTimeScale;
		
			m_bchanged = true;
			pIdleTimerleft->m_iCollButton = false;

		}
		if (pIdleTimerRight->m_iCollButton)
		{
			ClientRoomScene::m_fSec += IngmaeTimeScale;
			
			m_bchanged = true;
			pIdleTimerRight->m_iCollButton = false;
		}
		/////////////////////////////////////////////////////////////////////////////




		///////////////////////////////////////////////////////////////////////////처리파트
		//업
		while (ClientRoomScene::m_fSec < 0.0f)
		{
			ClientRoomScene::m_fSec += 60.0f;
			--ClientRoomScene::m_iMin;
			m_bchanged = true;
		}
		//다운
		while (ClientRoomScene::m_fSec >= 60.0f)
		{
			ClientRoomScene::m_fSec -= 60.0f;
			++ClientRoomScene::m_iMin;
			m_bchanged = true;
		}

		if (ClientRoomScene::m_iMin <= 0 && ClientRoomScene::m_fSec < 30.0f)
		{
			ClientRoomScene::m_iMin = 0;
			ClientRoomScene::m_fSec = 30.0f;
			m_bchanged = true;
		}

		if (ClientRoomScene::m_iMin >= 100)
		{
			ClientRoomScene::m_iMin = 99;
			ClientRoomScene::m_fSec = 59.99f;
			m_bchanged = true;
		}

	}
	else
	{
		//m_bchanged = true;
	}

	////////////////////////////////////////////////
	//호스트의 경우에
	

	/////////////////////////////////////////////////////////
	//호스트가 아닌 경우.


	if (m_bchanged == true)
	{
		TCHAR timerbuff[_MAX_PATH];
		if (ClientRoomScene::m_iMin < 10)		// 분이 10이하일때
		{
			if (ClientRoomScene::m_fSec < 10.0f) //초가 10이하일때.
			{
				_stprintf_s(timerbuff, _T(" 0%i : 0%.2f "), ClientRoomScene::m_iMin, ClientRoomScene::m_fSec);
			}
			else //아닐때.,
			{
				_stprintf_s(timerbuff, _T(" 0%i : %.2f "), ClientRoomScene::m_iMin, ClientRoomScene::m_fSec);
			}
			
		}
		else		// 아닐떄.
		{
			if (ClientRoomScene::m_fSec < 10.0f) //초가 10이하일때.
			{
				_stprintf_s(timerbuff, _T(" %i : 0%.2f "), ClientRoomScene::m_iMin, ClientRoomScene::m_fSec);
			}
			else //아닐때.,
			{
				_stprintf_s(timerbuff, _T(" %i : %.2f "), ClientRoomScene::m_iMin, ClientRoomScene::m_fSec);
			}
		}
		pIdleTimeBox->SetText(timerbuff);
		m_bchanged = false;
	}



	return PR_OK;
}

int SideView::StartUp()
{
	pRooomToRobby->SetActive(true);
	pRooomToRobby->WndShow();
	pIdleTimeBox->SetActive(true);
	pIdleTimeBox->WndShow();
	pIdleTimerleft->SetActive(true);
	pIdleTimerleft->WndShow();
	pIdleTimerRight->SetActive(true);
	pIdleTimerRight->WndShow();
	pIdlePlayerList->SetActive(true);
	pIdlePlayerList->WndShow();
	pIdleChat->SetActive(true);
	pIdleChat->WndShow();
	pIdleChatBar->SetActive(true);
	pIdleChatBar->WndShow();
	return PR_OK;
}

int SideView::EndUp()
{
	pRooomToRobby->SetActive(false);
	pRooomToRobby->WndHide();
	pIdleTimeBox->SetActive(false);
	pIdleTimeBox->WndHide();
	pIdleTimerleft->SetActive(false);
	pIdleTimerleft->WndHide();
	pIdleTimerRight->SetActive(false);
	pIdleTimerRight->WndHide();
	pIdlePlayerList->SetActive(false);
	pIdlePlayerList->WndHide();
	pIdleChat->SetActive(false);
	pIdleChat->WndHide();
	pIdleChatBar->SetActive(false);
	pIdleChatBar->WndHide();

	return PR_OK;
}

int SideView::release()
{
	return 0;
}

void SideView::SetPrevExit(bool _Exit)
{
	if (true == _Exit)
	{
		pRooomToRobby->PrevSetExit();
	}
}

SideView::SideView()
{
}


SideView::~SideView()
{
}
