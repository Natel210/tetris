#include "stdafx.h"
#include "Scene.h"
#include "ClientIngmaeLayer.h"
#include "ClientMainViewItem.h"
#include "Render/RenderManager.h"
#include "ClientIngameEnum.h"
#include "ClientHeader.h"
#include "ClientCore.h"
#include "ClientRoomScene.h"
#include "ResultItem.h"


//ClientMainViewItem* ClientIngmaeLayer::pMainViewItme = nullptr;


int ClientIngmaeLayer::Init()
{
	//WinDCManager::CreateHDC("IngameMainDC2", IngameMainDC  + 100, 0, 0/*,450,700*/);
	pMainViewItem = Layer::CreateObj<ClientMainViewItem>(_T("MainViewItem"));
	pResultItem = Layer::CreateObj<ResultItem>(_T("ResultItem"));
	pResultItem->MovePos(650, 400);
	pResultItem->SetSize(250, 150);
	//pMainViewItme = pMainViewItem;

	WinDCManager::CreateHDC(_T("IngameMainDC"), IngameMainDC, 600,50, (Map_maxX * 30) + 10, (Map_maxY * 30) + 30);
	LayerPosX = 600;
	LayerPosY = 50;
	LayerSizeX = (Map_maxX * 30) + 10;
	LayerSizeY = (Map_maxY * 30) + 10;
	LayerZ = IngameMainDC;
	m_LayerhDC = WinDCManager::FindDC(_T("IngameMainDC"));


	return 1;
}

int ClientIngmaeLayer::LayerUpdate(float time)
{

	if (ClientRoomScene::m_bIsGameEnd && ClientRoomScene::m_fEndCoolTime > 0.2f )
	{
		if (true == GetActive())
		{
			pResultItem->WndShow();
			pResultItem->SetActive(true);
		}
		//pResultItem->SetActive(true);
	}
	else
	{
		if (true == GetActive())
		{
			pResultItem->WndHide();
			pResultItem->SetActive(false);
		}
		
	}

	Tstring Setstring;
	std::map <int, Tstring>::iterator startiter = ClientRoomScene::m_RoomPlayermap.begin();
	std::map <int, Tstring>::iterator enditer = ClientRoomScene::m_RoomPlayermap.end();

	//m_RoomPlayerScore
	for (int i = 0; (startiter != enditer); ++i ,++startiter)
	{
		if (startiter->first == ClientCore::ClientPlayer.eLoginfo.m_UniqueID)
		{
			Setstring = L"";

			if (ClientRoomScene::m_isWinPlayer != 0)
			{
				if (startiter->first == ClientRoomScene::m_isWinPlayer)
				{
					Setstring += L" 승 리 ";
					Setstring += L"\n";
				}
				else
				{
					Setstring += L" 패 배 ";
					Setstring += L"\n";
				}
			}
			else
			{
				Setstring += L" ";
				Setstring += L"\n";
			}

			//int scores = 0;
			//std::map <int, int>::iterator finditer = ClientRoomScene::m_RoomPlayerScore.find(ClientCore::ClientPlayer.eLoginfo.m_UniqueID);
			//if (finditer == ClientRoomScene::m_RoomPlayerScore.end())
			//{
			//	scores = -1;
			//}
			//else
			//{
			//	scores = finditer->second;
			//}
			//TCHAR TCHARbuff[MAX_PATH] = {0,};
			//_itow_s(ClientRoomScene::m_RoomPlayerScore[i], TCHARbuff, 10);

			//Setstring += TCHARbuff;
			//Setstring += L"\n";
			
			//
			TCHAR TCHARbuff2[MAX_PATH] = { 0, };
			swprintf_s(TCHARbuff2, L" %d초 남았습니다.  ", (int)ClientRoomScene::m_fEndCoolTime);
			Setstring += TCHARbuff2;


			if (wcscmp(m_saavestr.c_str(), Setstring.c_str()))
			{
				pResultItem->SetText(Setstring.c_str());
				m_saavestr = Setstring;
			}


			//
			


		}
	}

/*
	for (int i = 0; (i < 6) && (startiter != enditer); ++i, ++startiter)
	{
		if (startiter->first == ClientCore::ClientPlayer.eLoginfo.m_UniqueID)
		{
			++startiter;
			if (startiter == enditer)
			{
				break;
			}

		}
		Setstring = L"";

		if (ClientRoomScene::m_isWinPlayer != 0)
		{
			if (startiter->first == ClientRoomScene::m_isWinPlayer)
			{
				Setstring += L" 승 리 ";
				Setstring += L"\n";
			}
			else
			{
				Setstring += L" 패 배 ";
				Setstring += L"\n";
			}
		}
		else
		{
			Setstring += L" ";
			Setstring += L"\n";
		}

		Tstring buff = L"";
		buff.append(startiter->second.begin(), startiter->second.end());
		Setstring += buff;
		Setstring += L"\n";


		int scores = 0;
		std::map <int, int>::iterator finditer = ClientRoomScene::m_RoomPlayerScore.find(startiter->first);
		if (finditer == ClientRoomScene::m_RoomPlayerScore.end())
		{
			scores = -1;
		}
		else
		{
			scores = finditer->second;
		}
		TCHAR TCHARbuff[MAX_PATH];
		_itow_s(ClientRoomScene::m_RoomPlayerScore[i], TCHARbuff, 10);

		Setstring += TCHARbuff;
		Setstring += L"\n";

		SubResult[i]->SetText(Setstring.c_str());
	}

*/






#ifdef DEBUG
	HPEN dwebugpaens = ColorManager::FindPen(_T("DebugRect"));
	HPEN OldPens = (HPEN)SelectObject(m_LayerhDC, dwebugpaens);
	Rectangle(m_LayerhDC, 0, 0, (Map_maxX * 30) + 10, (Map_maxY * 30) + 30);
	(HPEN)SelectObject(m_LayerhDC, OldPens);
#endif // DEBUG


	if (testtime < 0.f)
	{
		testtime = 0.1f;
	}
	else
	{
		testtime -= time;
		return 1;
	}




	/*for (UINT i = 0; i <= strChat.size(); ++i)
	{
		packets.Comments[i] = strChat.c_str()[i];
	}
	pServer->PushSend(packets);

	CommonPacket recvpackets = pServer->PopRecv();
	if (recvpackets.PacProp.LinkNumber != 0)
	{
		std::cout << recvpackets.Comments << std::endl;
	}*/

	return 0;
}

int ClientIngmaeLayer::StartUp()
{
	//pResultItem->WndShow();
	return PR_OK;
}

int ClientIngmaeLayer::EndUp()
{
	if (pResultItem->GetActive() == true)
	{
		pResultItem->WndHide();
		pResultItem->SetActive(false);
	}
	
	return PR_OK;
}

int ClientIngmaeLayer::release()
{
	WinDCManager::DelDC(_T("IngameMainDC"));
	Layer::RemoveObj(_T("MainViewItem"));
	return 1;
}

void ClientIngmaeLayer::SendMaps()
{
	if (ClientCore::pServer)
	{
		//레이어의 속성을 움직이게 하겠다.
		CommonPacket packets;
		//memset(&packets, 0, sizeof(CommonPacket));
		//ZeroMemory(&packets, sizeof(CommonPacket));
		/////////
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_INGAME;
		packets.PacProp.iLocation2 = IG_PLAYPANEL;
		packets.PacProp.iWork = IC_SEND;
		packets.PacProp.iItem = IG_MAP;
		TCHAR recvMap[Map_maxX][Map_maxY];
		for (int x = 0; x < Map_maxX; ++x)
		{
			for (int y = 0; y < Map_maxY; ++y)
			{
				recvMap[x][y] = (TCHAR)pMainViewItem->m_MapTile[x][y].eType;
			}
		}
		memcpy(packets.Comments, recvMap, sizeof(TCHAR)*Map_maxX*Map_maxY);
		ClientCore::pServer->PushSend(packets);
		//Sleep((10);
	}
}

void ClientIngmaeLayer::SetNextBlock(int nextblock)
{
	pMainViewItem->SetNextBlock(nextblock);
}

int ClientIngmaeLayer::GetNextBlock() const
{
	return pMainViewItem->GetNextBlock();
}

int ClientIngmaeLayer::GetScore() const
{
	return pMainViewItem->GetScore();
}

int ClientIngmaeLayer::GetEnd() const
{
	return pMainViewItem->GetEnd();
}

void ClientIngmaeLayer::ClearGame(int MapIdx)
{
	pMainViewItem->GameClear(MapIdx);
	//
	return;
}

void ClientIngmaeLayer::GameEnd()
{
	pMainViewItem->GameEnd();
}

ClientIngmaeLayer::ClientIngmaeLayer() : pMainViewItem(nullptr)
{
}


ClientIngmaeLayer::~ClientIngmaeLayer()
{
}
