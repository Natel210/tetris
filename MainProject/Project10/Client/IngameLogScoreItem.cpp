#include "stdafx.h"
#include "IngameLogScoreItem.h"

#include "ClientHeader.h"
#include "ClientIngameEnum.h"
#include "ClientCore.h"

#include "windowsx.h"
#include "resource.h"

#include "ClientRoomScene.h"
#include <algorithm>

static bool isScoreSort(IngameScore _src, IngameScore _dest)
{
	if (_src.m_Score > _dest.m_Score)
	{
		return true;
	}
	return false;
}


void IngameLogScoreItem::SetScore(IngameScoreSurver pScroesp[7])
{
	m_Scorevec.clear();
	m_Scorevec.resize(7);

	for (int i = 0 ; i < 7 ; ++i)
	{
		m_Scorevec[i] = pScroesp[i];
	}
	

}

IngameLogScoreItem::IngameLogScoreItem()
{
}


IngameLogScoreItem::~IngameLogScoreItem()
{
}

int IngameLogScoreItem::Input(float time)
{
	//if (KEY_DOUBLE(MouseLB))
	//{
	//	SendMessage(m_hWnd, LB_C_OPENSEL, (WPARAM)0, (LPARAM)CurSel);
	//}

	return PR_OK;
}

int IngameLogScoreItem::Update(float time)
{
	///////////////////////////////////////////////////////////////
	//���� ���� ���ھ �ְ� �޾ƾ߰ڴ�. ������ �ٲ���ֵ���.
	///////////////////////////////////////////////////////////////
	//���� ������ �ش�.,









	/////////////////////////////////////////////////////////////////
	//��Ʈ�� �����߰ڴ�.
	//std::sort(m_Scorevec.begin(), m_Scorevec.end(), isScoreSort);


	SendMessage(m_hWnd, LB_C_UPDATE, 0, 0);

	CurSel = (int)SendMessage(m_hWnd, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);


	if (times < 0.f)
	{
		times = 0.5f;
		SendMessage(m_hWnd, LB_SETCURSEL, (WPARAM)CurSel, (LPARAM)0);
	}
	else
	{
		times -= time;
		SendMessage(m_hWnd, LB_SETCURSEL, (WPARAM)CurSel, (LPARAM)0);
		return 1;
	}
	Tstring m_addstring;
	TCHAR addstringbuff[_MAX_PATH] = { 0, };
	for (size_t i = 0; i < m_Scorevec.size(); ++i)
	{
		if (m_Scorevec[i].m_Name == L"")
		{
			continue;
		}
		if (m_Scorevec[i].m_PlayerIngameNum == 0)
		{
			continue;
		}


		//++m_Scorevec[i].m_Score;
		///////////////////////////////////
		//�޾Ƽ� �����ؾ߰ڴ�.
		///////////////////////////////////

		// ������ ����ð��� �޾ƿͼ� �����Ѵ�?
		// 1�������� float���� �ش�.
		// 0.05�������� ������ �ð��� �������Ѵ�.
		// �̰� �ð�������Ʈ�� �� �����ϰŰ�����.
		// Ư���ð��̵Ǹ� �����ϵ��� �ϴ� ���� �´� �Ű���.
		// �׷��ٸ�. ü������ �Ǵ� �ð��� ��ŸŸ���� �����̵� ���ɼ��� ����.
		// ������ ������ ��������� ������ �ð��� �ʿ��ϰڳ�?
		// ������ ���� Ÿ���� ����������.
		// �װ� �ٽ� ������ �ð���ŭ �� ���ְ�
		// ������ ���ϴ� Ư���ð��̵Ǹ� Ư���� �̺�Ʈ�� �����ϵ��� �������Ѵ�.
		// �����Ǵ� �ð��� ����


		m_addstring = m_Scorevec[i].m_Name;
		m_addstring += L" : ";
		_itow_s(m_Scorevec[i].m_Score, addstringbuff, 10);
		m_addstring += addstringbuff;

		SendMessage(m_hWnd, LB_DELETESTRING, i, (LPARAM)1);
		SendMessage(m_hWnd, LB_INSERTSTRING, i, (LPARAM)m_addstring.c_str());
		//LB_CUSTOMUPDATE
		//UpdateWindow(m_hWnd);
		//int b = SetDlgItemText(m_hWnd, i, (LPCWSTR)m_addstring.c_str());
		//int c = 0;
		//SetWindowText()
	}

	SendMessage(m_hWnd, LB_SETCURSEL, (WPARAM)CurSel, (LPARAM)0);

	SendMessage(m_hWnd, LB_C_UPDATE, 0, 1);

	return PR_OK;
}

int IngameLogScoreItem::LateUpdate(float time)
{



	return PR_OK;
}

int IngameLogScoreItem::Transform(float time)
{
	return PR_OK;
}

int IngameLogScoreItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int IngameLogScoreItem::DebugRender(float time)
{
	return PR_OK;
}

int IngameLogScoreItem::Collision(float time)
{
	return PR_OK;
}

int IngameLogScoreItem::Init()
{
	//WNDItem::Init(TEXT("button"), TEXT("EXIT"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600 + (Map_maxX * 30) + 15, (Map_maxY * 28), 240, 75, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	WNDItem::Init(TEXT("listbox"), TEXT("Ingamescorelist"), WS_CHILD | WS_VISIBLE |  WS_BORDER, 600 + (Map_maxX * 30) + 15, (Map_maxY * 15) + 50, 240, 300, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	//SetWindowText(m_hWnd, TEXT("������ ����"));

	m_Scorevec.resize(7);
	//TCHAR* items[] = { TEXT("new1"),TEXT("new1") ,TEXT("new1") ,TEXT("new1") ,TEXT("new1") ,TEXT("new1") ,TEXT("new1") };
	//Tstring add
	//
	//m_strmsg

	Tstring m_addstring;
	TCHAR addstringbuff[_MAX_PATH] = { 0, };

	std::map <int, Tstring> copymap = ClientRoomScene::m_RoomPlayermap;
	std::map <int, Tstring>::iterator startiter = copymap.begin();
	std::map <int, Tstring>::iterator enditer = copymap.end();	
	
	for (size_t i = 0; startiter != enditer; ++startiter,++i)
	{
		m_Scorevec[i].m_Name.assign(startiter->second.begin(), startiter->second.end());
		m_Scorevec[i].m_Score = 0;

		if (m_Scorevec[i].m_Name != L"")
		{
			m_addstring = m_Scorevec[i].m_Name;
			m_addstring += L" : ";
			_itow_s(m_Scorevec[i].m_Score, addstringbuff, 10);
			m_addstring += addstringbuff;
			//SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)m_addstring.c_str());
			PostMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)m_addstring.c_str());
		}
		
	}


	return PR_OK;
}

int IngameLogScoreItem::release()
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

LRESULT IngameLogScoreItem::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
		if (CurSel <= 0)
		{
			break;
		}

		TCHAR buff[_MAX_PATH];
		//GetSeltext
		ListBox_GetText(hWnd, (WPARAM)(int)CurSel, (LPARAM)(LPCTSTR)buff);
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//2���� �����̽��ٿ� �����ָ�ǰڱ�
		//int 32
		int counts = 0;
		while (true)
		{
			if (buff[counts] == 32)
			{
				break;
			}
			++counts;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		Tstring strbuff = buff;
		strbuff.erase(counts, strbuff.size() - 1);
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

		m_PopupPlayerinfolist.push_back(popLog);

		////���޷� �̾ƾ߰ڴ�.
		////lParam�� �޽����� �������� �����մϴ�.
		//HWND popLog = CreateDialog(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_PLAYERINFO), ClientCore::mainhWnd, DLGPROC(PlayerinfostatsProc));
		//ShowWindow(popLog, true);
		//InvalidateRect(popLog, NULL, TRUE);
		////MessageBox(NULL, TEXT("111"), TEXT("1111"), MB_OK);
		////�̰Ŵ� ������ �������� �����ְ��Ұ̴ϴ�.
		break;
	}

		
	default:
		break;
	}
	return 0;
}


//���⼭������Ұ̴ϴ�.

