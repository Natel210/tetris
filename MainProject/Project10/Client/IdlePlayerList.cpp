#include "stdafx.h"
#include "IdlePlayerList.h"

#include "ClientHeader.h"
#include <windowsx.h>
#include "ClientRoomScene.h"

LRESULT IdlePlayerList::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

		//MessageBox(NULL, TEXT("111"), TEXT("1111"), MB_OK);
		//이거는 상대방의 프로필을 볼수있게할겁니다.
		break;
	}


	default:
		break;
	}
	return 0;
}

IdlePlayerList::IdlePlayerList()
{
}


IdlePlayerList::~IdlePlayerList()
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

int IdlePlayerList::Init()
{
	WNDItem::Init(TEXT("listbox"), TEXT("idleplayerLog"), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL, 600 + (Map_maxX * 30) + 15, (Map_maxY * 7) + 50, 240, 140, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	//Tstring m_addstring;
	//TCHAR addstringbuff[_MAX_PATH] = { 0, };
	//Adds
	//Rectangle(m_LayerhDC, 0, (Map_maxY * 5), 250, (Map_maxY * 13));
	AddString(L"접속 중인 플레이어");



	return PR_OK;
}

int IdlePlayerList::release()
{
	std::list<HWND>::iterator startiter = m_PopupPlayerinfolist.begin();
	std::list<HWND>::iterator enditer = m_PopupPlayerinfolist.end();
	for (; startiter != enditer; ++startiter)
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

int IdlePlayerList::Input(float time)
{
	return PR_OK;
}

int IdlePlayerList::Update(float time)
{
	CurSel = GetSel();
	//if (CurSel > 0)
	//{
	//	int a = 0;
	//}

	if (UpdateTime <= 0.f)
	{
		if (ClientRoomScene::m_RoomPlayermap.size())
		{
			AllClear();
			m_CurLobbyPlayermap.clear();
			AddString(L"접속 중인 플레이어");
			std::map <int, Tstring> copymap = ClientRoomScene::m_RoomPlayermap;
			std::map <int, Tstring>::iterator startiter = copymap.begin();
			std::map <int, Tstring>::iterator endtiter = copymap.end();
			for (; startiter != endtiter; ++startiter)
			{
				m_CurLobbyPlayermap.insert(std::make_pair(startiter->first, startiter->second));
				AddString(startiter->second.c_str());
			}

			/*if (CurSel > 0)
			{
				int a = 0;
			}*/
			SetSel(CurSel);

		}

		
		UpdateTime = 0.5f;
	}
	else
	{
		UpdateTime -= time;
	}

	return PR_OK;
}

int IdlePlayerList::LateUpdate(float time)
{
	return PR_OK;
}

int IdlePlayerList::Transform(float time)
{
	return PR_OK;
}

int IdlePlayerList::Render(float time, HDC drow)
{
	return PR_OK;
}

int IdlePlayerList::DebugRender(float time)
{
	return PR_OK;
}

int IdlePlayerList::Collision(float time)
{
	return PR_OK;
}
