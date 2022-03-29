#include "stdafx.h"
#include "LobbyPlayerlist.h"
#include "ClientCore.h"
#include "ClientHeader.h"
#include "resource.h"
#include "windowsx.h"
//b#include ""

//std::unordered_map<int, Tstring> LobbyPlayerlist::m_CurLobbyPlayermap;










LobbyPlayerlist::LobbyPlayerlist()
{
}


LobbyPlayerlist::~LobbyPlayerlist()
{
	std::list<HWND>::iterator startiter = m_PopupPlayerinfolist.begin();
	std::list<HWND>::iterator enditer = m_PopupPlayerinfolist.end();
	for (; startiter != enditer; ++startiter)
	{
		CloseHandle((*startiter));
		(*startiter) = NULL;
	}
	m_PopupPlayerinfolist.clear();

}

int LobbyPlayerlist::Input(float time)
{
	//if (KEY_PUSH(MouseRB))
	//{
	//
	//}
	return PR_OK;
}

int LobbyPlayerlist::Update(float time)
{
	// 1. 서버에게 자료를 지금 존제하는 유저들을 전송 받는다.
	// 2, 그걸 다시 분석해서 넣어준다.

	if (m_fUpdateCount < 0.0f)
	{
		if (!ClientCore::pServer)
		{
			return 1;
		}
		//레이어의 속성을 움직이게 하겠다.
		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_CHECKPLAYER;
		packets.PacProp.iWork = CC_FIND;
		packets.PacProp.iItem = LB_PLAYERLIST;
		packets.SetComment(_T("찾아라!"));

		ClientCore::pServer->PushSend(packets);
	}
	else
	{
		m_fUpdateCount -= time;
	}


	CommonPacket packets = CommonPacket();
	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_CHECKPLAYER, CC_FIND, LB_PLAYERLIST);
	if (packets == DisConnected)
	{
		return PR_RECONECTSURVER;
	}
	if (packets.PacProp.iLocation1 == SL_LOBBY)
	{
		int allidx;
		memcpy(&allidx, &packets.Comments[0], sizeof(int));

		if (is_Update == false)
		{
			CurSel = ListBox_GetCurSel(m_hWnd);
			ListBox_ResetContent(m_hWnd);
			is_Update = true;
		}
		m_CurLobbyPlayermap.clear();
		AddString(L"접속 중인 플레이어");

		int inext1 = 0;
		TCHAR next1[20];
		for (int i = 1; i < allidx + 1; ++i)
		{
			memcpy(&inext1, &packets.Comments[(24 * i) - 20], sizeof(int));
			memcpy(next1, &packets.Comments[(24 * i) - 16], sizeof(char) * 20);
			m_CurLobbyPlayermap.insert(std::make_pair(inext1, next1));
			AddString(next1);
		}
		m_fUpdateCount = 3.0f;
		is_Update = false;
		ListBox_SetCurSel(m_hWnd, CurSel);
		CurSel = ListBox_GetCurSel(m_hWnd);
	}
	return PR_OK;
}

int LobbyPlayerlist::LateUpdate(float time)
{
	return PR_OK;
}

int LobbyPlayerlist::Transform(float time)
{
	return PR_OK;
}

int LobbyPlayerlist::Render(float time, HDC drow)
{
	return PR_OK;
}

int LobbyPlayerlist::DebugRender(float time)
{
	return PR_OK;
}

int LobbyPlayerlist::Collision(float time)
{

	//SendMessage(m_hWnd, LB_C_OPENSEL, (WPARAM)0, (LPARAM)CurSel);
	return PR_OK;
}

int LobbyPlayerlist::Init()
{
	WNDItem::Init(TEXT("listbox"), TEXT("Playerlog"), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL , (int)(0), (int)(0), 100, 200, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	AddString(L"접속 중인 플레이어");
	return PR_OK;
}

int LobbyPlayerlist::release()
{
	std::list<HWND>::iterator startiter = m_PopupPlayerinfolist.begin();
	std::list<HWND>::iterator enditer = m_PopupPlayerinfolist.end();
	for (; startiter != enditer	; ++startiter)
	{
		ShowWindow((*startiter), SW_HIDE);
		DestroyWindow(*startiter);
		
		//(*startiter) = NULL;
	}
	//
	//CloseHandle((*startiter));
	m_PopupPlayerinfolist.clear();
	WNDItem::release(0);
	return PR_OK;
}



LRESULT LobbyPlayerlist::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 리턴값이 0인 경우는 디폴트 처리를 한다는 것이고
	// 리턴값이 1인 경우에는 디폴트 처리를 하지 않겠다는 뜻.

	switch (message)
	{
	case WM_KEYDOWN:
	{
		//키조작을 막습니다.
		return 1;
	}
	case WM_KEYUP:
	{
		//키조작을 막습니다.
		return 1;
	}
	case WM_KEYLAST:
	{
		//키조작을 막습니다.
		return 1;
	}

	case WM_LBUTTONDBLCLK:
	{
		SendMessage(m_hWnd, LB_C_OPENSEL, (WPARAM)0, (LPARAM)CurSel);
		return 1;
	}

	case LB_C_UPDATE:
	{
		if (!lParam)
		{
			UpdateWindow(NULL);
		}
		else
		{
			UpdateWindow(m_hWnd);
		}
		break;
	}

	case LBN_KILLFOCUS:
	{
		//CurSel = -1;
		//SendMessage(m_hWnd, LB_SETCURSEL, (WPARAM)CurSel, (LPARAM)0);
		break;
	}

	case LB_C_OPENSEL:
	{
		//////////////////////////////////자줄때 
		//서버에게 특정인원의 정보를 제공해달라고 요청한다.
		//m_CurLobbyPlayermap
		CurSel = ListBox_GetCurSel(m_hWnd);
		if (CurSel <= 0)
		{
			break;
		}

		TCHAR buff[_MAX_PATH];
		//GetSeltext
		ListBox_GetText(hWnd, (WPARAM)(int)CurSel, (LPARAM)(LPCTSTR)buff);

		Tstring strbuff = buff;
		Tstring findplayername;
		findplayername.append(strbuff.begin(), strbuff.end());
		///////////////////////

		//이건 커셀과 서버를 통해서 찾아야겠죠?
		//하지만 이건 넘겨줍시다 이름만 주고..........................................
		///////////////////////
		//findplayername = "Natel";

		//듀모달로 뽑아야겠다.
		//lParam의 메시지를 바탕으로 조작합니다.
		HWND popLog = CreateDialog(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_PLAYERINFO), ClientCore::mainhWnd, DLGPROC(PlayerinfostatsProc));

		SetDlgItemText(popLog, IDC_PLAYERIDLIST1, findplayername.c_str());

		ShowWindow(popLog, true);
		//InvalidateRect(popLog, NULL, TRUE);


		SendMessage(popLog, DLG_C_UPDATE, 0, 0);

		//DLG_C_UPDATE

		//m_PopupPlayerinfolist.push_back(popLog);

		//MessageBox(hWnd, TEXT("111"), TEXT("1111"), MB_OK);
		//이거는 상대방의 프로필을 볼수있게할겁니다.
		break;
	}


	default:
		break;
	}
	return 0;
}