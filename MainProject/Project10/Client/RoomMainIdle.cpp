#include "stdafx.h"
#include "RoomMainIdle.h"

#include "Scene.h"
#include "ClientIngameEnum.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "ClientMainidleItem.h"

#include "ReadyButton.h"
#include "ClientRoomScene.h"

int RoomMainIdle::Init()
{
	
	//pMainViewItme = pMainViewItem;
	WinDCManager::CreateHDC(_T("IdleMainDC"), IngameMainDC, 600, 50, (Map_maxX * 30) + 10, (Map_maxY * 30) + 30);
	LayerPosX = 600;
	LayerPosY = 50;
	LayerSizeX = (Map_maxX * 30) + 10;
	LayerSizeY = (Map_maxY * 30) + 10;
	LayerZ = IngameMainDC;
	m_LayerhDC = WinDCManager::FindDC(_T("IdleMainDC"));

	pMainViewItem = Layer::CreateObj<ClientMainidleItem>(_T("MainViewItem"));
	pMainViewItem->SetMapIDX(6);
	pReady = CreateObj<ReadyButton>(_T("ReadyButton"));







	return PR_OK;
}

int RoomMainIdle::LayerUpdate(float time)
{
#ifdef DEBUG
	HPEN dwebugpaens = ColorManager::FindPen(_T("DebugRect"));
	HPEN OldPens = (HPEN)SelectObject(m_LayerhDC, dwebugpaens);
	Rectangle(m_LayerhDC, 0, 0, (Map_maxX * 30) + 10, (Map_maxY * 30) + 30);
	(HPEN)SelectObject(m_LayerhDC, OldPens);
#endif // DEBUG


	//if (testtime < 0.f)
	//{
	//	testtime = 0.1f;
	//}
	//else
	//{
	//	testtime -= time;
	//	return 1;
	//}

	//if (ClientCore::pServer)
	//{
	//	//레이어의 속성을 움직이게 하겠다.
	//	CommonPacket packets;
	//	//memset(&packets, 0, sizeof(CommonPacket));
	//	//ZeroMemory(&packets, sizeof(CommonPacket));
	//	/////////
	//	packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	//	packets.PacProp.iLocation1 = SL_INGAME;
	//	packets.PacProp.iLocation2 = IG_PLAYPANEL;
	//	packets.PacProp.iWork = IC_SEND;
	//	packets.PacProp.iItem = IG_MAP;
	//	TCHAR recvMap[Map_maxX][Map_maxY];
	//	for (int x = 0; x < Map_maxX; ++x)
	//	{
	//		for (int y = 0; y < Map_maxY; ++y)
	//		{
	//			recvMap[x][y] = pMainViewItem->m_MapTile[x][y].eType;
	//		}
	//	}
	//	memcpy(packets.Comments, recvMap, sizeof(TCHAR)*Map_maxX*Map_maxY);
	//	ClientCore::pServer->PushSend(packets);
	//}


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


	return PR_OK;
}

int RoomMainIdle::StartUp()
{
	pReady->SetActive(true);
	pReady->WndShow();
	return PR_OK;
}

int RoomMainIdle::EndUp()
{
	pReady->SetActive(false);
	pReady->WndHide();
	return PR_OK;
}

int RoomMainIdle::release()
{
	WinDCManager::DelDC(_T("IngameMainDC"));
	Layer::RemoveObj(_T("MainViewItem"));
	return PR_OK;
}

int RoomMainIdle::GetMapIDX() const
{
	return pMainViewItem->GetMapIDX();
}
void RoomMainIdle::SetMapIDX(int _IDX)
{
	pMainViewItem->SetMapIDX(_IDX);
}

bool RoomMainIdle::GetReady() const
{
	return pReady->GetReady();
}

void RoomMainIdle::ResetReady()
{
	if (ClientRoomScene::gethost())
	{
		pReady->SetText(L" 시작 하기");
	}
	else
	{
		pReady->SetText(L" 준비 하기");
	}
	pReady->m_bIsReady = false;
	pReady->m_iCollButton = false;
	pReady->m_bChanged = false;
}

//pReady->m_bIsReady = false;
//pReady->m_bChanged = true;
//pReady->m_iCollButton = false;

RoomMainIdle::RoomMainIdle()
{
}


RoomMainIdle::~RoomMainIdle()
{
}
