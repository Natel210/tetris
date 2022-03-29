#include "stdafx.h"
#include "MainLobbyLayer.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "StaticRoomBox.h"

#include "CreateRoomItem.h"
#include "EnterRoomItem.h"
#include "EnterRankingItem.h"
#include "EnterLogoutItem.h"
#include "EnterLobbyExitItem.h"

#include "FrameCore.h"
#include "ClientRoomScene.h"
#include "ClientLobbyScene.h"

#include "WaitSearchButton.h"
#include "AllSearchButton.h"
#include "LeftMoveButton.h"
#include "RightMoveButton.h"
#include "MovePageButton.h"


#include <assert.h>

int MainLobbyLayer::Init()
{
	LayerPosX = (int)(WindSizeX * 0.05f);
	LayerPosY = (int)(WindSizeY * 0.05f);
	LayerSizeX = (int)(WindSizeX * 0.60f);
	LayerSizeY = (int)(WindSizeY * 0.45f);

	WaitSearchButton* WaitSearch = CreateObj<WaitSearchButton>(_T("WaitSearch"));
	AllSearchButton* AllSearch = CreateObj<AllSearchButton>(_T("AllSearch"));
	LeftMoveButton* LeftMove = CreateObj<LeftMoveButton>(_T("LeftMove"));
	RightMoveButton* RightMove = CreateObj<RightMoveButton>(_T("RightMove"));
	MovePageButton* MovePage = CreateObj<MovePageButton>(_T("MovePage"));

	CreateRoomItem* pCreateRoomItem = CreateObj<CreateRoomItem>(_T("CreateRoomItem"));
	EnterRoomItem* pEnterRoom = CreateObj<EnterRoomItem>(_T("LobbytoRoom"));
	EnterRankingItem* pRankingItem = CreateObj<EnterRankingItem>(_T("RankingItem"));
	EnterLogoutItem* pLogoutItem = CreateObj<EnterLogoutItem>(_T("LogoutItem"));
	EnterLobbyExitItem* pExitItem = CreateObj<EnterLobbyExitItem>(_T("ExitItem"));

	////////////////

	pStaticArr[0] = CreateObj<StaticRoomBox>(_T("Staticbox1"));
	pStaticArr[1] = CreateObj<StaticRoomBox>(_T("Staticbox2"));
	pStaticArr[2] = CreateObj<StaticRoomBox>(_T("Staticbox3"));
	pStaticArr[3] = CreateObj<StaticRoomBox>(_T("Staticbox4"));
	pStaticArr[4] = CreateObj<StaticRoomBox>(_T("Staticbox5"));
	pStaticArr[5] = CreateObj<StaticRoomBox>(_T("Staticbox6"));
	pStaticArr[6] = CreateObj<StaticRoomBox>(_T("Staticbox7"));
	pStaticArr[7] = CreateObj<StaticRoomBox>(_T("Staticbox8"));
	pStaticArr[8] = CreateObj<StaticRoomBox>(_T("Staticbox9"));

	//////////////////

	pStaticArr[0]->MovePos(100, 60);
	pStaticArr[1]->MovePos(100, 170);
	pStaticArr[2]->MovePos(100, 280);
	pStaticArr[3]->MovePos(320, 60);
	pStaticArr[4]->MovePos(320, 170);
	pStaticArr[5]->MovePos(320, 280);
	pStaticArr[6]->MovePos(540, 60);
	pStaticArr[7]->MovePos(540, 170);
	pStaticArr[8]->MovePos(540, 280);

	WinDCManager::CreateHDC(_T("LobbyMainDC"), LobbyMainDC, LayerPosX, LayerPosY, LayerSizeX, LayerSizeY);
	LayerZ = LobbyMainDC;
	m_LayerhDC = WinDCManager::FindDC(_T("LobbyMainDC"));

	return PR_OK;
}

int MainLobbyLayer::LayerUpdate(float time)
{
	HBRUSH Backbrush = ColorManager::FindBrush(_T("BackMapBrush"));
	HBRUSH oldbrush = (HBRUSH)SelectObject(m_LayerhDC, Backbrush);
	HPEN oldPen = (HPEN)SelectObject(m_LayerhDC, GetStockObject(NULL_PEN));
	Rectangle(m_LayerhDC, 0, 0, LayerSizeX, LayerSizeY);
	(HBRUSH)SelectObject(m_LayerhDC, oldbrush);
	(HPEN)SelectObject(m_LayerhDC, oldPen);

	////////////////////////
	/////////////////////////////////////////////////////////////////////////
	WaitSearchButton* WaitSearch = FindObj<WaitSearchButton>(_T("WaitSearch"));
	AllSearchButton* AllSearch = FindObj<AllSearchButton>(_T("AllSearch"));
	LeftMoveButton* LeftMove = FindObj<LeftMoveButton>(_T("LeftMove"));
	RightMoveButton* RightMove = FindObj<RightMoveButton>(_T("RightMove"));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��������
	std::vector<RoomInfoLobby> Searchrooms;



	CommonPacket packets_l = CommonPacket();
	packets_l = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_LOBBY, LB_FINDROOM, CC_FIND, packets_l.PacProp.iItem);

	if (packets_l.PacProp.iLocation1 == SL_LOBBY && packets_l.PacProp.iItem == LB_ROOMSEARCHENTERS)
	{
		Searchrooms.clear();
		Searchrooms.resize(9);
		memcpy(&Searchrooms[0], &packets_l.Comments[0], sizeof(RoomInfoLobby) * 9);

		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->SetStateRoom(Searchrooms[i]);
			if (m_uSelectNum == i)
			{
				pStaticArr[i]->SetSelect(false);
			}
			else
			{
				pStaticArr[i]->SetSelect(true);
			}

		}

	}
	if (packets_l.PacProp.iLocation1 == SL_LOBBY && packets_l.PacProp.iItem == LB_ROOMSEARCHALL)
	{
		Searchrooms.clear();
		Searchrooms.resize(9);
		memcpy(&Searchrooms[0], &packets_l.Comments[0], sizeof(RoomInfoLobby) * 9);

		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->SetStateRoom(Searchrooms[i]);
			if (m_uSelectNum == i)
			{
				pStaticArr[i]->SetSelect(false);
			}
			else
			{
				pStaticArr[i]->SetSelect(true);
			}

		}

	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//CommonPacket packets_r = CommonPacket();
	//packets_r = ClientCore::pServer->PopRecv(packets_r.PacProp.LinkNumber, SL_LOBBY, LB_FINDROOM, CC_FIND, packets_r.PacProp.iItem);
	//if (packets_r.PacProp.iLocation1 == SL_LOBBY && packets_r.PacProp.iItem == LB_ROOMSEARCHENTERS)
	//{
	//	Searchrooms.clear();
	//	Searchrooms.resize(9);
	//	memcpy(&Searchrooms[0], &packets_r.Comments[0], sizeof(RoomInfoLobby) * 9);

	//	for (int i = 0; i < 9; ++i)
	//	{
	//		pStaticArr[i]->SetStateRoom(Searchrooms[i]);
	//		if (m_uSelectNum == i)
	//		{
	//			pStaticArr[i]->SetSelect(false);
	//		}
	//		else
	//		{
	//			pStaticArr[i]->SetSelect(true);
	//		}

	//	}
	//}
	//if (packets_r.PacProp.iLocation1 == SL_LOBBY && packets_r.PacProp.iItem == LB_ROOMSEARCHALL)
	//{
	//	Searchrooms.clear();
	//	Searchrooms.resize(9);
	//	memcpy(&Searchrooms[0], &packets_r.Comments[0], sizeof(RoomInfoLobby) * 9);

	//	for (int i = 0; i < 9; ++i)
	//	{
	//		pStaticArr[i]->SetStateRoom(Searchrooms[i]);
	//		if (m_uSelectNum == i)
	//		{
	//			pStaticArr[i]->SetSelect(false);
	//		}
	//		else
	//		{
	//			pStaticArr[i]->SetSelect(true);
	//		}

	//	}
	//}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//CommonPacket packets = CommonPacket();
	//packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_FINDROOM, CC_FIND, packets.PacProp.iItem);
	//if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_ROOMSEARCHENTERS)
	//{
	//	memcpy(&Searchrooms[0], &packets.Comments[0], sizeof(RoomInfoLobby) * 9);

	//	for (int i = 0; i < 9; ++i)
	//	{
	//		pStaticArr[i]->SetStateRoom(Searchrooms[i]);
	//		if (m_uSelectNum == i)
	//		{
	//			pStaticArr[i]->SetSelect(false);
	//		}
	//		else
	//		{
	//			pStaticArr[i]->SetSelect(true);
	//		}

	//	}
	//}
	//if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_ROOMSEARCHALL)
	//{
	//	memcpy(&Searchrooms[0], &packets.Comments[0], sizeof(RoomInfoLobby) * 9);

	//	for (int i = 0; i < 9; ++i)
	//	{
	//		pStaticArr[i]->SetStateRoom(Searchrooms[i]);
	//		if (m_uSelectNum == i)
	//		{
	//			pStaticArr[i]->SetSelect(false);
	//		}
	//		else
	//		{
	//			pStaticArr[i]->SetSelect(true);
	//		}

	//	}
	//}




	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����
	if (LeftMove->m_iCollButton)
	{
		m_iSearchstartpage -= 3;
		if (m_iSearchstartpage <= 1)
		{
			m_iSearchstartpage = 1;
		}
		LeftMove->m_iCollButton = false;


		//////////////////////////////////////////////////////////////////////
		//�������� ���ſ�û
		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->DelRoom();
		}


		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_FINDROOM;
		packets.PacProp.iWork = CC_FIND;
		if (m_bSearchMode)
		{
			packets.PacProp.iItem = LB_ROOMSEARCHALL;
		}
		else
		{
			packets.PacProp.iItem = LB_ROOMSEARCHENTERS;
		}


		int SeachPage = 1;
		if (m_iSearchstartpage <= 1)
		{
			SeachPage = 1;
		}
		else
		{
			SeachPage = m_iSearchstartpage;
		}




		memcpy(&packets.Comments[0], &SeachPage, sizeof(int));

		ClientCore::pServer->PushSend(packets);

		m_fSearchRate = 5.0f;
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//������
	if (RightMove->m_iCollButton)
	{
		m_iSearchstartpage += 3;
		RightMove->m_iCollButton = false;
		//////////////////////////////////////////////////////////////////////
		//�������� ���ſ�û
		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->DelRoom();
		}


		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_FINDROOM;
		packets.PacProp.iWork = CC_FIND;
		if (m_bSearchMode)
			{
				packets.PacProp.iItem = LB_ROOMSEARCHALL;
			}
		else
			{
				packets.PacProp.iItem = LB_ROOMSEARCHENTERS;
			}


		int SeachPage = 1;
		if (m_iSearchstartpage <= 0)
			{
				SeachPage = 1;
			}
		else
			{
				SeachPage = m_iSearchstartpage;
			}




		memcpy(&packets.Comments[0], &SeachPage, sizeof(int));

		ClientCore::pServer->PushSend(packets);

		///////////////////////////////////////////////////////////////////////
		m_fSearchRate = 5.0f;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��ü ����
	if (AllSearch->m_iCollButton)
	{
		m_bSearchMode = true;
		AllSearch->m_iCollButton = false;

		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->DelRoom();
		}


		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_FINDROOM;
		packets.PacProp.iWork = CC_FIND;
		if (m_bSearchMode)
		{
			packets.PacProp.iItem = LB_ROOMSEARCHALL;
		}
		else
		{
			packets.PacProp.iItem = LB_ROOMSEARCHENTERS;
		}


		int SeachPage = 1;
		if (m_iSearchstartpage <= 1)
		{
			SeachPage = 1;
		}
		else
		{
			SeachPage = m_iSearchstartpage;
		}




		memcpy(&packets.Comments[0], &SeachPage, sizeof(int));

		ClientCore::pServer->PushSend(packets);


		///////////////////////////////////////////////////////////////////////
		m_fSearchRate = 5.0f;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//��� ����
	if (WaitSearch->m_iCollButton)
	{
		m_bSearchMode = false;
		WaitSearch->m_iCollButton = false;

		std::vector<RoomInfoLobby> Searchrooms;
		Searchrooms.clear();
		Searchrooms.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->DelRoom();
		}


		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_FINDROOM;
		packets.PacProp.iWork = CC_FIND;
		if (m_bSearchMode)
		{
			packets.PacProp.iItem = LB_ROOMSEARCHALL;
		}
		else
		{
			packets.PacProp.iItem = LB_ROOMSEARCHENTERS;
		}


		int SeachPage = 1;
		if (m_iSearchstartpage <= 1)
		{
			SeachPage = 1;
		}
		else
		{
			SeachPage = m_iSearchstartpage;
		}




		memcpy(&packets.Comments[0], &SeachPage, sizeof(int));

		ClientCore::pServer->PushSend(packets);

/*

		packets = CommonPacket();
		packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_FINDROOM, CC_FIND, packets.PacProp.iItem);
		if (packets.PacProp.iLocation1 != SL_LOBBY)
		{
			return PR_OK;
		}
		if (packets.PacProp.iItem != LB_ROOMSEARCHENTERS && packets.PacProp.iItem != LB_ROOMSEARCHALL)
		{
			return PR_OK;
		}

		memcpy(&Searchrooms[0], &packets.Comments[0], sizeof(RoomInfoLobby) * 9);

		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->SetStateRoom(Searchrooms[i]);
			if (m_uSelectNum == i)
			{
				pStaticArr[i]->SetSelect(false);
			}
			else
			{
				pStaticArr[i]->SetSelect(true);
			}

		}*/

		///////////////////////////////////

		////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		m_fSearchRate = 5.0f;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////








	//////////////////////////////////////////////////////////////////////////
	//�ֱ��� ����
	//std::vector<RoomInfoLobby> Searchrooms;
	Searchrooms.clear();
	Searchrooms.resize(9);
	if (m_fSearchRate < 0.f)
	{
		//////////////////////////////////////////////////////////////////////
		//�������� ���ſ�û
		for (int i = 0; i < 9; ++i)
		{
			pStaticArr[i]->DelRoom();
		}


		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_FINDROOM;
		packets.PacProp.iWork = CC_FIND;
		if (m_bSearchMode)
		{
			packets.PacProp.iItem = LB_ROOMSEARCHALL;
		}
		else
		{
			packets.PacProp.iItem = LB_ROOMSEARCHENTERS;
		}


		int SeachPage = 1;
		if (m_iSearchstartpage <= 0)
		{
			SeachPage = 1;
		}
		else
		{
			SeachPage = m_iSearchstartpage;
		}




		memcpy(&packets.Comments[0], &SeachPage, sizeof(int));

		ClientCore::pServer->PushSend(packets);
/*


		packets = CommonPacket();
		packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_FINDROOM, CC_FIND, packets.PacProp.iItem);
		if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_ROOMSEARCHENTERS)
		{
			memcpy(&Searchrooms[0], &packets.Comments[0], sizeof(RoomInfoLobby) * 9);

			for (int i = 0; i < 9; ++i)
			{
				pStaticArr[i]->SetStateRoom(Searchrooms[i]);
				if (m_uSelectNum == i)
				{
					pStaticArr[i]->SetSelect(false);
				}
				else
				{
					pStaticArr[i]->SetSelect(true);
				}

			}
		}
		if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_ROOMSEARCHALL)
		{
			memcpy(&Searchrooms[0], &packets.Comments[0], sizeof(RoomInfoLobby) * 9);

			for (int i = 0; i < 9; ++i)
			{
				pStaticArr[i]->SetStateRoom(Searchrooms[i]);
				if (m_uSelectNum == i)
				{
					pStaticArr[i]->SetSelect(false);
				}
				else
				{
					pStaticArr[i]->SetSelect(true);
				}

			}
		}*/

		///////////////////////////////////////////////////////////////////////

		m_fSearchRate = 5.0f;
	}
	else
	{
		int icounts = 0;
		m_fSearchRate -= time;
		for (int i = 0; i < 9; ++i)
		{
			if (pStaticArr[i]->GetSelect())
			{
				if (m_uSelectNum == i)
				{
					continue;
				}
				else
				{
					if (m_uSelectNum == -1)
					{
						m_uSelectNum = i;
						return PR_OK;
					}
					pStaticArr[m_uSelectNum]->SetSelect(true);
					m_uSelectNum = i;

				}
			}
			else
			{
				++icounts;
			}
		}
		if (icounts == 9)
		{
			m_uSelectNum = -1;
		}
	}

	/////////////////////////////////////////////////////
	MovePageButton* FindMovePage = FindObj<MovePageButton>(_T("MovePage"));
	Tstring CurPagetx = FindMovePage->GetText();
	int CurPage = _ttoi(CurPagetx.c_str());
	int ChangePage = (m_iSearchstartpage / 3);

	if (CurPage != ChangePage)
	{
		FindMovePage->Setidx(ChangePage);
	}
	////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//on create or in enter 
	CommonPacket packets = CommonPacket();
	packets.PacProp.iLocation1 = SL_Err;
	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_ENTER, CC_ENTER);
	if (packets == DisConnected)
	{
		assert(true);
		return PR_RECONECTSURVER;
	}
	if (packets.PacProp.iLocation1 == SL_LOBBY)
	{
		if (packets.PacProp.iItem == LB_ROOMENTER)
		{
			int ireturn = 0;
			memcpy(&ireturn, packets.Comments, sizeof(int));

			//�̰��� ������ 
			ClientRoomScene* pNextScene = FrameCore::CreateScene<ClientRoomScene>(GameRoomScene);
			pNextScene->SetActive(false);
			//WNDItem::ALLHIDE();

			//MessageBox(NULL, TEXT("���������� �α׾ƿ� �Ǿ����ϴ�. \n�α��� ȭ������ �̵��մϴ�."), TEXT("�α� �ƿ�"), MB_OK);
			//Sleep(10);
			ClientLobbyScene* pCurScene = FrameCore::FindScene<ClientLobbyScene>(GameLobbyScene);
			pNextScene->SetActive(true);
			pCurScene->SetActive(false);
			pCurScene->Delete();

			return PR_SCENECHNAGE;
		}
		else if (packets.PacProp.iItem == LB_ROOMLIMITNUM)
		{
			//�ִ� ����� �� ã���ϴ�.
			MessageBox(ClientCore::mainhWnd, TEXT("�ο��� ���� ã���ϴ�."), TEXT("���� �Ұ�"), MB_OK);

		}
		else if (packets.PacProp.iItem == LB_ROOMISGAMMING)
		{
			//���� ���� ���Դϴ�.
			MessageBox(ClientCore::mainhWnd, TEXT("���� ���� ���Դϴ�."), TEXT("���� �Ұ�"), MB_OK);
		}
		else if (packets.PacProp.iItem == LB_ROOMPWFALSE)
		{
			//��� ��ȣ�� Ʋ�Ƚ��ϴ�.
			MessageBox(ClientCore::mainhWnd, TEXT("���� ��й�ȣ�� Ʋ�Ƚ��ϴ�."), TEXT("���� �Ұ�"), MB_OK);

		}
		else if (packets.PacProp.iItem == LB_ENTER)
		{
			//�ִ� ����� �� ã���ϴ�.
			MessageBox(ClientCore::mainhWnd, TEXT("�˼����� �ַ��Դϴ�.\n�ٽ� �ѹ� �� ������ �ּ���."), TEXT("���� �Ұ�"), MB_OK);
		}
	}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	EnterRoomItem* pEnterRoom = FindObj<EnterRoomItem>(_T("LobbytoRoom"));
	if (!pEnterRoom)
	{
		return PR_OK;
	}
	if (pEnterRoom->m_iCollButton)
	{
		//1. ��������
		//2. ��й�ȣ�� �´���
		if (m_uSelectNum < 9 && m_uSelectNum >= 0)
		{
			//��й�ȣ�� �´���
			////////////////////////////////////
			//���Ǵ޼�
			CommonPacket packets;
			//memset(&packets, 0, sizeof(CommonPacket));
			//ZeroMemory(&packets, sizeof(CommonPacket));
			/////////
			packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
			packets.PacProp.iLocation1 = SL_LOBBY;
			packets.PacProp.iLocation2 = LB_ENTER;
			packets.PacProp.iWork = CC_ENTER;
			packets.PacProp.iItem = LB_ROOM;
			// ���濡 ���� �;��.
			// int �ָ�ɰŰ�
			int iroomnum = pStaticArr[m_uSelectNum]->GetRoomInfo().m_iRoomNum;
			memcpy(packets.Comments, &iroomnum, sizeof(int));
			// �ױ⿡ �ݿ��Ǿ��� ���� ��ȣ�� 0~6�̾�.
			ClientCore::pServer->PushSend(packets);
		}
		pEnterRoom->m_iCollButton = false;	
	}
	if (CreateRoomItem::m_bisCreate)
	{
		//�̰��� ������ 
		ClientRoomScene* pNextScene = FrameCore::CreateScene<ClientRoomScene>(GameRoomScene);
		pNextScene->SetActive(false);
		ClientLobbyScene* pCurScene = FrameCore::FindScene<ClientLobbyScene>(GameLobbyScene);
		//Sleep(10);
		pNextScene->SetActive(true);
		pCurScene->SetActive(false);
		pCurScene->Delete();
		CreateRoomItem::m_bisCreate = false;
		return PR_SCENECHNAGE;
	}
	return PR_OK;
}

int MainLobbyLayer::StartUp()
{
	CreateRoomItem* pCreateRoomItem = FindObj<CreateRoomItem>(_T("CreateRoomItem"));
	EnterRoomItem* pEnterRoom = FindObj<EnterRoomItem>(_T("LobbytoRoom"));
	EnterRankingItem* pRankingItem = FindObj<EnterRankingItem>(_T("RankingItem"));
	EnterLogoutItem* pLogoutItem = FindObj<EnterLogoutItem>(_T("LogoutItem"));
	EnterLobbyExitItem* pExitItem = FindObj<EnterLobbyExitItem>(_T("ExitItem"));
	pCreateRoomItem->WndShow();
	pEnterRoom->WndShow();
	pRankingItem->WndShow();
	pLogoutItem->WndShow();
	pExitItem->WndShow();

	WaitSearchButton* WaitSearch = FindObj<WaitSearchButton>(_T("WaitSearch"));
	AllSearchButton* AllSearch = FindObj<AllSearchButton>(_T("AllSearch"));
	LeftMoveButton* LeftMove = FindObj<LeftMoveButton>(_T("LeftMove"));
	RightMoveButton* RightMove = FindObj<RightMoveButton>(_T("RightMove"));
	MovePageButton* MovePage = FindObj<MovePageButton>(_T("MovePage"));
	WaitSearch->WndShow();
	AllSearch->WndShow();
	LeftMove->WndShow();
	RightMove->WndShow();
	MovePage->WndShow();

	for (int i = 0 ; i < 9  ; ++i)
	{
		pStaticArr[i]->WndShow();
	}
	return 2;
}

int MainLobbyLayer::release()
{
	return PR_OK;
}

MainLobbyLayer::MainLobbyLayer()
{
}


MainLobbyLayer::~MainLobbyLayer()
{
}
