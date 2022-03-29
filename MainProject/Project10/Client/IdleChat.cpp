#include "stdafx.h"
#include "IdleChat.h"
#include <windowsx.h>
#include "ClientHeader.h"

IdleChat::IdleChat()
{
}


IdleChat::~IdleChat()
{
}

int IdleChat::Input(float time)
{
	return PR_OK;
}

int IdleChat::Update(float time)
{
	///////////////나는 확인 해야한다.//////////////
	//업데이트 로그가 있는지를.


	if (ChatUpdate < 0.0f)
	{
		CommonPacket packets;
		//memset(&packets, 0, sizeof(CommonPacket));
		//ZeroMemory(&packets, sizeof(CommonPacket));
		/////////
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_ROOM;
		packets.PacProp.iLocation2 = RM_CHAT;
		packets.PacProp.iWork = CC_FIND;
		packets.PacProp.iItem = LB_CHATCHECK;
		packets.SetComment(_T("찾아라!"));



		ClientCore::pServer->PushSend(packets);

		packets = CommonPacket();
		packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_ROOM, RM_CHAT, CC_FIND, LB_CHATCHECK);
		if (packets.PacProp.iLocation1 == SL_ROOM && packets.PacProp.iItem == LB_CHATCHECK)
		{
			int idx = 0;
			Tstring m_savestr = _T("");
			while (idx < 8048)
			{
				if (packets.Comments[idx] == -52)
				{
					break;
				}
				if (packets.Comments[idx] == '\0')
				{
					break;
				}
				if (packets.Comments[idx] == '\n')
				{
					int Count = ListBox_GetCount(m_hWnd);
					if (Count >= 15)
					{
						SCROLLINFO einfo;
						GetScrollInfo(m_hWnd, SB_VERT, &einfo);

						AddString(m_savestr.c_str());
						//;
						ListBox_SetCurSel(m_hWnd, ListBox_GetCount(m_hWnd) - 1);
						UpdateWindow(m_hWnd);
						m_savestr.clear();
						//int a = ListBox_GetCurSel(m_hWnd);

						//einfo.nPos = Count - 14;
						//int b = SetScrollInfo(m_hWnd, SB_VERT, &einfo, TRUE);
					}
					else
					{
						AddString(m_savestr.c_str());
						m_savestr.clear();
					}


					//m_savestr = "";

					//int     nMin;
					//int     nMax;
					//UINT    nPage;
					//int     nPos;
				}
				else
				{
					m_savestr += packets.Comments[idx];
				}
				++idx;
			}
		}
		

		//////////////////////////////////채팅 수신을 완료했음을 보내주는 신호가 필요하다.
		//packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		//packets.PacProp.iLocation1 = SL_ROOM;
		//packets.PacProp.iLocation2 = RM_CHAT;
		//packets.PacProp.iWork = CC_FIND;
		//packets.PacProp.iItem = LB_CHATEND;
		//packets.SetComment(_T("채팅이 정상적으로 적용되었습니다."));

		//ClientCore::pServer->PushSend(packets);

		//int count = 0;

		//packets = CommonPacket();
		//packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_ROOM, RM_CHAT, CC_FIND, LB_CHATEND);
		//if (packets.PacProp.iLocation1 == SL_ROOM && packets.PacProp.iItem == LB_CHATEND)
		//{
		//}
		//else if (packets == DisConnected)
		//{
		//	return PR_RECONECTSURVER;
		//}
		ChatUpdate = 0.2f;
	}
	else
	{
		ChatUpdate -= time;
	}


	return PR_OK;
}

int IdleChat::LateUpdate(float time)
{
	return PR_OK;
}

int IdleChat::Transform(float time)
{
	return PR_OK;
}

int IdleChat::Render(float time, HDC drow)
{
	return PR_OK;
}

int IdleChat::DebugRender(float time)
{
	return PR_OK;
}

int IdleChat::Collision(float time)
{
	return PR_OK;
}

int IdleChat::Init()
{
	WNDItem::Init(TEXT("listbox"), TEXT("idlechatLog"), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL /*| LBS_NOSEL*/, 600 + (Map_maxX * 30) + 15, (Map_maxY * 15) + 50, 240, 265, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	//600 + (Map_maxX * 30) + 15, (Map_maxY * 15) + 50, 240, 300,
	AllClear();
	AddString(_T("채팅을 시작합니다."));

	//Tstring m_addstring;
	//TCHAR addstringbuff[_MAX_PATH] = { 0, };

	//int a = 0;
	//for (size_t i = 0; i < 40; ++i)
	//{
	//	m_addstring = L"";
	//	++a;
	//	_itow_s(a, addstringbuff, 10);
	//	m_addstring = L"테스트 [";
	//	m_addstring += addstringbuff;
	//	m_addstring += L"] 입니다.";
	//	SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)m_addstring.c_str());
	//}

	UpdateWindow(m_hWnd);
	return PR_OK;
}

int IdleChat::release()
{
	WNDItem::release(0);
	return PR_OK;
}
