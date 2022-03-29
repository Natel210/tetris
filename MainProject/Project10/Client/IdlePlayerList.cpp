#include "stdafx.h"
#include "IdlePlayerList.h"

#include "ClientHeader.h"
#include <windowsx.h>
#include "ClientRoomScene.h"

LRESULT IdlePlayerList::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ���ϰ��� 0�� ���� ����Ʈ ó���� �Ѵٴ� ���̰�
	// ���ϰ��� 1�� ��쿡�� ����Ʈ ó���� ���� �ʰڴٴ� ��.

	switch (message)
	{
	case WM_KEYDOWN:
	{
		//Ű������ �����ϴ�.
		return 1;
	}
	case WM_KEYUP:
	{
		//Ű������ �����ϴ�.
		return 1;
	}
	case WM_KEYLAST:
	{
		//Ű������ �����ϴ�.
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
		//////////////////////////////////���ٶ� 
		//�������� Ư���ο��� ������ �����ش޶�� ��û�Ѵ�.
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

		//�̰� Ŀ���� ������ ���ؼ� ã�ƾ߰���?
		//������ �̰� �Ѱ��ݽô� �̸��� �ְ�..........................................
		///////////////////////
		//findplayername = "Natel";

		//���޷� �̾ƾ߰ڴ�.
		//lParam�� �޽����� �������� �����մϴ�.
		HWND popLog = CreateDialog(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_PLAYERINFO), ClientCore::mainhWnd, DLGPROC(PlayerinfostatsProc));

		SetDlgItemText(popLog, IDC_PLAYERIDLIST1, findplayername.c_str());

		ShowWindow(popLog, true);
		//InvalidateRect(popLog, NULL, TRUE);


		SendMessage(popLog, DLG_C_UPDATE, 0, 0);

		//DLG_C_UPDATE

		//m_PopupPlayerinfolist.push_back(popLog);

		//MessageBox(NULL, TEXT("111"), TEXT("1111"), MB_OK);
		//�̰Ŵ� ������ �������� �����ְ��Ұ̴ϴ�.
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
	AddString(L"���� ���� �÷��̾�");



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
			AddString(L"���� ���� �÷��̾�");
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
