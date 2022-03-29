#include "stdafx.h"
#include "ChatingLog.h"
#include "ClientHeader.h"
#include <windowsx.h>

#include <vector>

ChatingLog::ChatingLog()
{
}


ChatingLog::~ChatingLog()
{
}

int ChatingLog::Input(float time)
{
	return PR_OK;
}

int ChatingLog::Update(float time)
{
	///////////////나는 확인 해야한다.//////////////
	//업데이트 로그가 있는지를.
	int count = 0;

	CommonPacket packets = CommonPacket();
	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_CHAT, CC_FIND, LB_CHATCHECK);
	if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_CHATCHECK)
	{
		int idx = 0;
		bool applyok = false;
		Tstring m_savestr = _T("");
		while (idx < 2048)
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
				int coloncount = 0;
				for (int i = 0 ; i < m_savestr.size() ; ++i )
				{
					if (m_savestr.c_str()[i] == (TCHAR)':')
					{
						++coloncount;
					}
					if (coloncount >= 2)
					{
						int a = 0;
					}
				}

				

				int Count = ListBox_GetCount(m_hWnd);
				if (Count >= 15)
				{
					SCROLLINFO einfo;
					GetScrollInfo(m_hWnd, SB_VERT, &einfo);
					AddString(m_savestr.c_str());
					m_savestr.clear();
					ListBox_SetCurSel(m_hWnd, ListBox_GetCount(m_hWnd) - 1);
					UpdateWindow(m_hWnd);
				}
				else
				{
					AddString(m_savestr.c_str());
					m_savestr.clear();
				}
				applyok = true;
			}
			else
			{
				m_savestr += packets.Comments[idx];
			}
			++idx;

			
		}
		//packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		//packets.PacProp.iLocation1 = SL_LOBBY;
		//packets.PacProp.iLocation2 = LB_CHAT;
		//packets.PacProp.iWork = CC_FIND;
		//packets.PacProp.iItem = LB_CHATEND;
		//packets.SetComment(_T("채팅이 정상적으로 적용되었습니다."));
		//count = 0;
		//ClientCore::pServer->PushSend(packets);

		//packets = CommonPacket();
		//packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_CHAT, CC_FIND, LB_CHATEND);
		//if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_CHATEND)
		//{

		//}
	}
	else if (packets == DisConnected)
	{
		return PR_RECONECTSURVER;
	}


	if (ChatUpdate < 0.0f)
	{
		CommonPacket packet2s;
		packet2s.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packet2s.PacProp.iLocation1 = SL_LOBBY;
		packet2s.PacProp.iLocation2 = LB_CHAT;
		packet2s.PacProp.iWork = CC_FIND;
		packet2s.PacProp.iItem = LB_CHATCHECK;
		packet2s.SetComment(_T("찾아라!"));
		ClientCore::pServer->PushSend(packet2s);
		ChatUpdate = 0.2f;
	}
	else
	{
		ChatUpdate -= time;
	}

	
	return PR_OK;
}

int ChatingLog::LateUpdate(float time)
{
	return PR_OK;
}

int ChatingLog::Transform(float time)
{
	return PR_OK;
}

int ChatingLog::Render(float time, HDC drow)
{
	return PR_OK;
}

int ChatingLog::DebugRender(float time)
{
	return PR_OK;
}

int ChatingLog::Collision(float time)
{
	return PR_OK;
}

int ChatingLog::Init()
{
	WNDItem::Init(TEXT("listbox"), TEXT("chatLog"), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL /*| LBS_NOSEL*/, (int)(WindSizeX * 0.06f), (int)(WindSizeY * 0.52f), (int)(WindSizeX * 0.88f), 255, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	
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

int ChatingLog::release()
{
	WNDItem::release(0);
	return PR_OK;
}
