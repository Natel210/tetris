#include "stdafx.h"
#include "SubViewLayer.h"

#include "Scene.h"
#include "ClientIngameEnum.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "Render/RenderManager.h"

#include "SubViewItem.h"
#include "ClientRoomScene.h"
#include <map>
//#include "ClientIngmaeLayer.h"
//#include "ClientMainViewItem.h"
#include "ResultItem.h"

int SubViewLayer::Init()
{
	//ResultItem* pResult = Layer::CreateObj<ResultItem>("ResultItem");
	//pResult->
	int PivotX = 30 + 8;
	int PivotY = 50 + 220;
	int sizeX = 150;
	int sizeY = 100;

	SubResult[0] = Layer::CreateObj<ResultItem>(_T("ResultItem1"));
	SubResult[0]->MovePos(0 + PivotX, 0 + PivotY);
	SubResult[0]->SetSize(sizeX, sizeY);

	SubResult[1] = Layer::CreateObj<ResultItem>(_T("ResultItem2"));
	SubResult[1]->MovePos(0 + PivotX, (Map_maxY * 15) + 20 + PivotY);
	SubResult[1]->SetSize(sizeX, sizeY);

	SubResult[2] = Layer::CreateObj<ResultItem>(_T("ResultItem3"));
	SubResult[2]->MovePos(170 + PivotX, 0 + PivotY);
	SubResult[2]->SetSize(sizeX, sizeY);

	SubResult[3] = Layer::CreateObj<ResultItem>(_T("ResultItem4"));
	SubResult[3]->MovePos(170 + PivotX, (Map_maxY * 15) + 20 + PivotY);
	SubResult[3]->SetSize(sizeX, sizeY);

	SubResult[4] = Layer::CreateObj<ResultItem>(_T("ResultItem5"));
	SubResult[4]->MovePos(340 + PivotX, 0 + PivotY);
	SubResult[4]->SetSize(sizeX, sizeY);

	SubResult[5] = Layer::CreateObj<ResultItem>(_T("ResultItem6"));
	SubResult[5]->MovePos(340 + PivotX, (Map_maxY * 15) + 20 + PivotY);
	SubResult[5]->SetSize(sizeX, sizeY);

///////////////////////////////////////////////////////////////////////////////////
	SubView[0] = Layer::CreateObj<SubViewItem>(_T("SubViewItem1"));
	SubView[0]->SetPos(0, 0);
	SubView[1] = Layer::CreateObj<SubViewItem>(_T("SubViewItem2"));
	SubView[1]->SetPos(0, (Map_maxY * 15) + 20);

	SubView[2] = Layer::CreateObj<SubViewItem>(_T("SubViewItem3"));
	SubView[2]->SetPos(170, 0);
	SubView[3] = Layer::CreateObj<SubViewItem>(_T("SubViewItem4"));
	SubView[3]->SetPos(170, (Map_maxY * 15) + 20);

	SubView[4] = Layer::CreateObj<SubViewItem>(_T("SubViewItem5"));
	SubView[4]->SetPos(340, 0);
	SubView[5] = Layer::CreateObj<SubViewItem>(_T("SubViewItem6"));
	SubView[5]->SetPos(340, (Map_maxY * 15) + 20);



	WinDCManager::CreateHDC(_T("IngameSubDC"), IngameSubDC, 30, 50, 560, (Map_maxY * 30) + 30);
	LayerPosX = 30;
	LayerPosY = 50;
	LayerSizeX = 560;
	LayerSizeY = (Map_maxY * 30) + 30;
	LayerZ = IngameSubDC;
	m_LayerhDC = WinDCManager::FindDC(_T("IngameSubDC"));
	return 1;
}

int SubViewLayer::LayerUpdate(float time)
{
	RecvMaps();




	//////////////////////////////////////
	//나의 기록을 합니다.
	if (ClientRoomScene::m_bIsGameEnd && ClientRoomScene::m_fEndCoolTime > 0.2f)
	{
		for (int i = 0; i < 6; ++i)
		{
			SubResult[i]->WndShow();
			SubResult[i]->SetActive(true);
		}
	}
	else
	{
		for (int i = 0; i < 6; ++i)
		{
			SubResult[i]->WndHide();
			SubResult[i]->SetActive(false);
		}
	}







	////////////////////////////////////////////////////////

	Tstring Setstring;
	std::map <int, Tstring>::iterator startiter = ClientRoomScene::m_RoomPlayermap.begin();
	std::map <int, Tstring>::iterator enditer = ClientRoomScene::m_RoomPlayermap.end();

	//m_RoomPlayerScore
	bool checkplayer = false;
	for (int i = 0; (i < ClientRoomScene::m_RoomPlayermap.size()) && (startiter != enditer) ; ++i, ++startiter)
	{
		if (startiter->first == ClientCore::ClientPlayer.eLoginfo.m_UniqueID)
		{
			checkplayer = true;
			if (startiter == enditer)
			{
				break;
			}
			continue;
		}

		Setstring = L"";

		if (ClientRoomScene::m_isWinPlayer != 0)
		{
			if (startiter->first == ClientRoomScene::m_isWinPlayer)
			{
				//SubResult[i]->SetChangeBK(true, RGB(110, 110, 200));
				Setstring += _T(" 승 리 ");
				Setstring += _T("\n");
			}
			else
			{
				//SubResult[i]->SetChangeBK(true, RGB(200, 110, 110));
				Setstring += _T(" 패 배 ");
				Setstring += _T("\n");
			}
		}
		else
		{
			Setstring += _T(" ");
			Setstring += _T("\n");
		}
		
		Tstring buff = _T("");
		buff.append(startiter->second.begin(), startiter->second.end());
		Setstring += buff;
		Setstring += _T("\n");


		int scores = 0;
		std::map <int, int>::iterator finditer =  ClientRoomScene::m_RoomPlayerScore.find(startiter->first);
		if (finditer == ClientRoomScene::m_RoomPlayerScore.end())
		{
			scores = -1;
		}
		else
		{
			scores = finditer->second;
		}
		TCHAR TCHARbuff[MAX_PATH];
		if (checkplayer)
		{
			_itow_s(ClientRoomScene::m_RoomPlayerScore[i-1], TCHARbuff, 10);
		}
		else
		{
			_itow_s(ClientRoomScene::m_RoomPlayerScore[i], TCHARbuff, 10);
		}
		

		Setstring += TCHARbuff;
		Setstring += _T("\n");

	/*	Tstring buff = L"";
		buff.append(ClientRoomScene::m_RoomPlayermap[i].begin(), ClientRoomScene::m_RoomPlayermap[i].end());
		Setstring += buff;
		Setstring += L"\n";*/

		//TCHAR TCHARbuff[MAX_PATH];
		//_itow_s(ClientRoomScene::m_RoomPlayerScore[i], TCHARbuff, 10);

		//Setstring += TCHARbuff;
		//Setstring += L"\n";
		//승리
		//플레이어
		//점수

		//Setstring


		if (checkplayer)
		{
			SubResult[i-1]->SetText(Setstring.c_str());
		}
		else
		{
			SubResult[i]->SetText(Setstring.c_str());
		}
		
	}
	



	///////////////////////////////////////



	//작업 범위
#ifdef DEBUG
	HPEN dwebugpaens = ColorManager::FindPen(_T("DebugRect"));
	HPEN OldPens = (HPEN)SelectObject(m_LayerhDC, dwebugpaens);
	Rectangle(m_LayerhDC, 0, 0, 560, (Map_maxY * 30) + 30);
	(HPEN)SelectObject(m_LayerhDC, OldPens);
#endif // DEBUG


	if (UpdateTime <= 0.f)
	{
		UpdateTime = 0.2f;
	}
	else
	{
		UpdateTime -= time;
		return PR_OK;
	}
	

	if (!ClientCore::pServer)
	{
		return 1;
	}

	//ClientRoomScene::m_RoomPlayermap.clear();
	//CommonPacket packets;
	////memset(&packets, 0, sizeof(CommonPacket));
	////ZeroMemory(&packets, sizeof(CommonPacket));
	///////////
	//packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	//packets.PacProp.iLocation1 = SL_ROOM;
	//packets.PacProp.iLocation2 = RM_LISTUPDATE;
	//packets.PacProp.iWork = RC_PLAYER;
	//packets.PacProp.iItem = RM_CHAEKPLAYER;
	//packets.SetComment("찾아라!");
	//ClientCore::pServer->PushSend(packets);
	//packets = CommonPacket();
	//packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_ROOM, packets.PacProp.iLocation2, packets.PacProp.iWork, packets.PacProp.iItem);
	//if (packets.PacProp.iLocation1 == SL_ROOM)
	//{
	//	ClientRoomScene::m_RoomPlayermap.clear();
	//	int maxidx = 0;
	//	memcpy(&maxidx, &packets.Comments[0], sizeof(int));
	//	TCHAR savebuff[20];
	//	int saveIDnum;
	//	for (int idx = 0; idx < maxidx; ++idx)
	//	{
	//		memcpy(&saveIDnum, &packets.Comments[idx * 24 + 8], sizeof(int));
	//		memcpy(savebuff, &packets.Comments[idx * 24 + 4 + 8], sizeof(TCHAR) * 20);
	//		ClientRoomScene::m_RoomPlayermap.insert(std::make_pair(saveIDnum, savebuff));
	//	}
	//}
	return 1;
}

int SubViewLayer::StartUp()
{
	for (int i = 0 ; i < 6 ; ++i)
	{
		SubResult[i]->WndShow();
	}
	return PR_OK;
}

int SubViewLayer::EndUp()
{
	for (int i = 0; i < 6; ++i)
	{
		SubResult[i]->WndHide();
	}
	return PR_OK;
}

int SubViewLayer::release()
{
	return PR_OK;
}

void SubViewLayer::RecvMaps()
{
	if (ClientRoomScene::m_bIsGameEnd && ClientRoomScene::m_fEndCoolTime > 0.2f)
	{
		return;
	}


	CommonPacket recvpack = CommonPacket();
	recvpack = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_INGAME, IG_PLAYPANEL, IC_SEND, IG_MAP);
	
	
	//while (recvpack.PacProp.iLocation1 != SL_INGAME)
	//{
	//	recvpack = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_INGAME, IG_PLAYPANEL, IC_SEND, IG_MAP);
	//}
	//CommonPacket recvpack = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_INGAME, IG_PLAYPANEL, IC_SEND, IG_MAP);


	if (IG_MAP == recvpack.PacProp.iItem && IC_SEND == recvpack.PacProp.iWork)
	{
		int Uptime = 0;
		memcpy(&Uptime, &recvpack.Comments[0], sizeof(int));
		if (issurverUptime > Uptime)
		{
			return;
		}
		issurverUptime = Uptime;

		float servertime = 0.0f;
		memcpy(&servertime, &recvpack.Comments[sizeof(int)], sizeof(float));
		if (issurvertime >servertime)
		{
			return;
		}
		issurvertime = servertime;

		TCHAR recvmap[6][Map_maxX][Map_maxY];
		memcpy(recvmap, &recvpack.Comments[sizeof(int)+ sizeof(float)], sizeof(TCHAR) *Map_maxX *Map_maxY * 6);

		std::map<int, Tstring>copymap = ClientRoomScene::m_RoomPlayermap;
		std::map<int, Tstring>::iterator startiter = copymap.begin();
		std::map<int, Tstring>::iterator enditer = copymap.end();

		for (int idx = 0; startiter != enditer; ++idx, ++startiter)
		{
			SubView[idx]->SendMapTile(recvmap[idx]);
		}
	}
}

SubViewLayer::SubViewLayer()
{
}


SubViewLayer::~SubViewLayer()
{
}
