#include "stdafx.h"
#include "RankingListItem.h"

#include "Input/Input.h"

#include <algorithm>

static bool SortPlayer(RankSaveList _src, RankSaveList _dest)
{
	if (_src.name[0] == 0 || _src.name[0] == -52)
	{
		return false;
	}
	for (size_t i = 0; i < 20; ++i)
	{
		if (_src.name[i] == _dest.name[i])
		{
			continue;
		}
		else
		{
			if (_src.name[i] < _dest.name[i])
			{
				return true;
			}
			else if (_dest.name[i] == 0 || _dest.name[i] == -52)
			{
				return false;
			}
			break;
		}
	
	}
	
	return false;
}


static bool SortHighScore(RankSaveList _src, RankSaveList _dest)
{
	if (_src.Score > _dest.Score)
	{
		return true;
	}
	return false;
}

static bool SortRating(RankSaveList _src, RankSaveList _dest)
{
	float srcRat = 0.f;
	float desRat = 0.f;
	if (_src.Loses == 0)
	{
		srcRat = 1.0f;
	}
	else
	{
		srcRat = _src.Wins / (float)(_src.Loses + _src.Wins);
	}
	if (_dest.Loses == 0)
	{
		desRat = 1.0f;
	}
	else
	{
		desRat = _dest.Wins / (float)(_dest.Loses + _dest.Wins);
	}


	if (srcRat <= desRat)
	{
		return false;
	}
	return true;
}


static bool SortManyWins(RankSaveList _src, RankSaveList _dest)
{
	if (_src.Wins <= _dest.Wins)
	{
		return false;
	}
	return true;
}


//
//int RankingListItem::insertCategory(const TCHAR * pstr)
//{
//	LVCOLUMN COL;
//	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
//	COL.fmt = LVCFMT_CENTER;
//	COL.cx = 0;
//	//COL.cxMin = 00;
//	COL.pszText = (LPWSTR)pstr;
//	COL.iSubItem = (int)m_categoryvec.size();
//	ListView_InsertColumn(m_hWnd, 0, (LPARAM)&COL);
//	m_categoryvec.push_back(pstr);
//	return COL.iSubItem;
//}

void RankingListItem::SortList(ButtonState type)
{
	switch (type)
	{
	case RankingListItem::BS_ERR:
		break;
	case RankingListItem::BS_NO:
		break;
	case RankingListItem::BS_NAME:
		std::sort(m_saveScoresvec.begin(), m_saveScoresvec.end(), SortPlayer);
		break;
	case RankingListItem::BS_SCORE:
		std::sort(m_saveScoresvec.begin(), m_saveScoresvec.end(), SortHighScore);
		break;
	case RankingListItem::BS_RATE:
		std::sort(m_saveScoresvec.begin(), m_saveScoresvec.end(), SortRating);
		break;
	case RankingListItem::BS_WINS:
		std::sort(m_saveScoresvec.begin(), m_saveScoresvec.end(), SortManyWins);
		break;
	default:
		break;
	}
	m_bColSort = false;
	return;
}

int RankingListItem::UpdateList()
{
	//서버에서 정보를 받아와야한다.
	//내가 원하는게수.
	CommonPacket packets;
	//memset(&packets, 0, sizeof(CommonPacket));
	//ZeroMemory(&packets, sizeof(CommonPacket));
	/////////
	packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
	packets.PacProp.iLocation1 = SL_RANKING;
	packets.PacProp.iLocation2 = RK_UPDATE;
	packets.PacProp.iWork = CC_UPDATE;
	packets.PacProp.iItem = RG_UPDATE;

	//2가지 정보
	memcpy(&packets.Comments[0], (void*)&m_eButtonType, sizeof(int));
	memcpy(&packets.Comments[4], (void*)&m_iListSizeCounter, sizeof(int));

	ClientCore::pServer->PushSend(packets);



	return 0;
}

int RankingListItem::UpdatePlayerStates()
{
	if (PR_RECONECTSURVER == UpdateList())
	{
		return PR_RECONECTSURVER;
	}
	return 0;
}

int RankingListItem::ExpandFinds(int num)
{
	m_iListSizeCounter += num;
	if (m_iListSizeCounter > 20 )
	{
		m_iListSizeCounter = 20;
	}
	if (PR_RECONECTSURVER == UpdateList())
	{
		return PR_RECONECTSURVER;
	}
	return 0;
}

int RankingListItem::ReduceFinds(int num)
{
	m_iListSizeCounter -= num;
	if (m_iListSizeCounter < 4)
	{
		m_iListSizeCounter = 4;
	}
	if (PR_RECONECTSURVER == UpdateList())
	{
		return PR_RECONECTSURVER;
	}
	return 0;
}

RankingListItem::RankingListItem()
{
}


RankingListItem::~RankingListItem()
{
}

int RankingListItem::Input(float time)
{
	return PR_OK;
}

int RankingListItem::Update(float time)
{
	CommonPacket packets;
	packets.PacProp.iLocation1 = SL_Err;
	packets = ClientCore::pServer->PopRecv(ClientCore::pServer->MyUniqueNum, SL_RANKING, RK_UPDATE, CC_UPDATE, RG_UPDATE);
	if (packets == DisConnected)
	{
		return PR_RECONECTSURVER;
	}
	if (packets.PacProp.iLocation1 == SL_RANKING && packets.PacProp.iItem == RG_UPDATE)
	{
		int RoopCount = 0;
		memcpy(&RoopCount, &packets.Comments[0], sizeof(int));


		m_saveScoresvec.resize(RoopCount);
		for (int i = 0; i < RoopCount; ++i)
		{
			memcpy(&m_saveScoresvec[i].name[0], &packets.Comments[4 + (i * 32) + 0], sizeof(TCHAR) * 20);
			memcpy(&m_saveScoresvec[i].Score, &packets.Comments[4 + (i * 32) + 20], sizeof(int));
			memcpy(&m_saveScoresvec[i].Wins, &packets.Comments[4 + (i * 32) + 24], sizeof(int));
			memcpy(&m_saveScoresvec[i].Loses, &packets.Comments[4 + (i * 32) + 28], sizeof(int));
		}

		SortList(m_eButtonType);

		/////////////////////////
		//출력세팅
		LVITEM LI;

		LI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		LI.state = 0;

		LI.iSubItem = 1;
		for (size_t i = 0; i < m_saveScoresvec.size(); ++i)
		{
			LI.iItem = (int)i;

			Tstring convscr = m_saveScoresvec[i].name;
			Tstring convwstr;
			convwstr.append(convscr.begin(), convscr.end());
			LI.pszText = (LPWSTR)(convwstr.c_str());
			ListView_SetItem(m_hWnd, &LI);
		}
		//////////////////////////////////////////기본 10개

		LI.iSubItem = 2;

		for (size_t i = 0; i < m_saveScoresvec.size(); ++i)
		{
			TCHAR scorebuff[_MAX_PATH];
			LI.iItem = (int)i;
			//m_saveScoresvec[i].Score;
			_itow_s(m_saveScoresvec[i].Score, scorebuff, 10);
			LI.pszText = (LPWSTR)scorebuff;
			ListView_SetItem(m_hWnd, &LI);
		}
		//////////////////////////////////////////기본 10개
		LI.iSubItem = 3;

		for (size_t i = 0; i < m_saveScoresvec.size(); ++i)
		{
			TCHAR Ratebuff[_MAX_PATH];
			LI.iItem = (int)i;
			//m_saveScoresvec[i].Score;
			float lates = 0.0f;
			if (m_saveScoresvec[i].Loses == 0)
			{
				if (m_saveScoresvec[i].Wins == 0)
				{
					lates = 0.0f;
				}
				else
				{
					lates = 100.0f;
				}

			}
			else
			{
				lates = (m_saveScoresvec[i].Wins / (float)(m_saveScoresvec[i].Loses + m_saveScoresvec[i].Wins)) * 100.0f;
			}
			swprintf_s(Ratebuff, _MAX_PATH, L"%.3f%%", lates);

			LI.pszText = (LPWSTR)Ratebuff;
			ListView_SetItem(m_hWnd, &LI);
		}
		/////////////////////
		LI.iSubItem = 4;
		for (size_t i = 0; i < m_saveScoresvec.size(); ++i)
		{
			TCHAR Winsbuff[_MAX_PATH];
			LI.iItem = (int)i;
			swprintf_s(Winsbuff, _MAX_PATH, L"%d", m_saveScoresvec[i].Wins);
			LI.pszText = (LPWSTR)Winsbuff;
			ListView_SetItem(m_hWnd, &LI);
		}
	}
	// m_iListSizeCounter
	// 서순을 보려는 것들
	// 하나의 폼  RankSaveList
	// 최대 20







	/////////////////////////////////////////////////////////////////
	int CategorX = 0;
	CategorX = ListView_GetColumnWidth(m_hWnd, 0);
	if (CategorX != 0)
	{
		ListView_SetColumnWidth(m_hWnd, 0, 0);
	}
	CategorX = ListView_GetColumnWidth(m_hWnd, 1);
	if (CategorX != 350)
	{
		ListView_SetColumnWidth(m_hWnd, 1, 350);
	}
	CategorX = ListView_GetColumnWidth(m_hWnd, 2);
	if (CategorX != 200)
	{
		ListView_SetColumnWidth(m_hWnd, 2, 200);
	}
	CategorX = ListView_GetColumnWidth(m_hWnd, 3);
	if (CategorX != 200)
	{
		ListView_SetColumnWidth(m_hWnd, 3, 200);
	}
	CategorX = ListView_GetColumnWidth(m_hWnd, 4);
	if (CategorX != 200)
	{
		ListView_SetColumnWidth(m_hWnd, 4, 200);
	}
	///////////////////////////////////////////////////////////////////

	//마우스 정보를 직접받자
	//
	POINT cursorpoint;
	if (!GetCursorPos(&cursorpoint))
	{
		return PR_ERRER;
	}
	if (!ScreenToClient(m_hWnd, &cursorpoint))
	{
		return PR_ERRER;
	}
	


	if (KEY_PUSH(MouseLB))
	{
		m_bFirstPush = true;
	}



	if (KEY_UP(MouseLB) && m_bFirstPush == true)
	{
		//m_eButtonType = BS_ERR;
		if (cursorpoint.y > 50 || cursorpoint.y < 0)
		{
			//m_eButtonType = BS_NO;
			return PR_OK;
		}
		else if (cursorpoint.x < 0)
		{
			//m_eButtonType = BS_NO;
			return PR_OK;
		}
		else if (cursorpoint.x > 950)
		{
			//m_eButtonType = BS_NO;
			return PR_OK;
		}
		else if (cursorpoint.x >= 0 && cursorpoint.x < 350)
		{
			m_eButtonType = BS_NAME;
		}
		else if (cursorpoint.x >= 350 && cursorpoint.x < 550)
		{
			m_eButtonType = BS_SCORE;
		}
		else if (cursorpoint.x >= 550 && cursorpoint.x < 750)
		{
			m_eButtonType = BS_RATE;
		}
		else if (cursorpoint.x >= 750 && cursorpoint.x < 950)
		{
			m_eButtonType = BS_WINS;
		}
		//소트처리를한다.
		m_bFirstPush = false;
		m_bColSort = true;
		UpdateList();
	}
	

	//SortList(m_eButtonType);


	/////////////////////////////////////////////////////////////////
	return PR_OK;
}

int RankingListItem::LateUpdate(float time)
{
	return PR_OK;
}

int RankingListItem::Transform(float time)
{
	return PR_OK;
}

int RankingListItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int RankingListItem::DebugRender(float time)
{
	return PR_OK;
}

int RankingListItem::Collision(float time)
{
	return PR_OK;
}

int RankingListItem::Init()
{
	WNDItem::Init(WC_LISTVIEW, TEXT("MyClass1"), WS_CHILD | WS_VISIBLE | WS_BORDER |/* LVS_AUTOARRANGE |*/ LVS_REPORT, 100, 130, 950, 600, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	//m_hWnd = CreateWindow(WC_LISTVIEW, NULL, /* | LVS_OWNERDRAWFIXED *//*| LVS_NOSORTHEADER*/, ClientCore::mainhWnd, NULL, ClientCore::mainhInst, NULL);
	
	//폰트 설정
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));

	// 패널 라인을 만듭니다.
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM /*| LVCF_MINWIDTH*/;
	COL.fmt = LVCFMT_CENTER;//| LVCFMT_FIXED_WIDTH;
	COL.cx = 0;
	COL.pszText = TEXT("");
	COL.iSubItem = 0;
	ListView_InsertColumn(m_hWnd, 0, (LPARAM)&COL);
	//2
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	COL.fmt = LVCFMT_CENTER | LVCFMT_FIXED_WIDTH;
	COL.cx = 350;
	COL.cxMin = 350;
	COL.pszText = TEXT(" 플 레 이 어  아 이 디");
	COL.iSubItem = 1;
	ListView_InsertColumn(m_hWnd, 1, (LPARAM)&COL);
	//3
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	COL.fmt = LVCFMT_CENTER | LVCFMT_FIXED_WIDTH;
	COL.cx = 200;
	COL.cxMin = 200;
	COL.pszText = TEXT(" 최 고  점 수 ");
	COL.iSubItem = 2;
	ListView_InsertColumn(m_hWnd, 2, (LPARAM)&COL);
	//4
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	COL.fmt = LVCFMT_CENTER | LVCFMT_FIXED_WIDTH;
	COL.cx = 200;
	COL.cxMin = 200;
	COL.pszText = TEXT(" 최 고  승 률 ");
	COL.iSubItem = 3;
	ListView_InsertColumn(m_hWnd, 3, (LPARAM)&COL);
	//5
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	COL.fmt = LVCFMT_CENTER | LVCFMT_FIXED_WIDTH;
	COL.cx = 200;
	COL.cxMin = 200;
	COL.pszText = TEXT(" 최 고  승 수 ");
	COL.iSubItem = 4;
	
	ListView_InsertColumn(m_hWnd, 4, (LPARAM)&COL);

	////////////////////////////////////////////////////////////////////////////////////////////
	//Item을 넣어줍니다.
	LVITEM LI;

	LI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 0;
	LI.pszText = L"1";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 1;
	LI.pszText = L"2";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 2;
	LI.pszText = L"3";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 3;
	LI.pszText = L"4";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 4;
	LI.pszText = L"5";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 5;
	LI.pszText = L"6";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 6;
	LI.pszText = L"7";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 7;
	LI.pszText = L"8";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 8;
	LI.pszText = L"9";
	ListView_InsertItem(m_hWnd, &LI);
	LI.iItem = 9;
	LI.pszText = L"10";
	ListView_InsertItem(m_hWnd, &LI);
	//////////////////////////////////////////기본 10개

	LI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 1;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 1;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 2;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 3;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 4;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 5;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 6;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 7;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 8;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 9;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	///////////////////////////////////////////////////////////////

	LI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 2;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 1;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 2;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 3;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 4;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 5;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 6;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 7;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 8;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 9;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);

	/////////////////////////////////////////////////////////////////

	LI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 3;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 1;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 2;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 3;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 4;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 5;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 6;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 7;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 8;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 9;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	/////////////////////////////////////////////////////////////
	LI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 4;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 1;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 2;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 3;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 4;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 5;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 6;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 7;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 8;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);
	LI.iItem = 9;
	LI.pszText = L"";
	ListView_SetItem(m_hWnd, &LI);

	/////////////////////////////////////////////////////////////////









	//RankSaveList RSL;
	//for (size_t i = 0; i < 10; ++i)
	//{
	//	RSL.name[i] = (TCHAR)'A';
	//	RSL.Score += (int)(i * 1000);
	//	RSL.Wins = (int)(10 - i);
	//	RSL.Loses = (int)(i);

	//	m_saveScoresvec.push_back(RSL);
	//}


	//업데이트 매시지를 보내준다.
	UpdatePlayerStates();
	///////////////////////////////////////////////////////////////////
	return PR_OK;
}

int RankingListItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}

LRESULT RankingListItem::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_MOUSEMOVE:
	{

		//int x = (int)(short)LOWORD(lParam);
		//int y = (int)(short)HIWORD(lParam);
		break;
	}
	case WM_NCRBUTTONDOWN:
	{
		//int x = (int)(short)LOWORD(lParam);
		//int y = (int)(short)HIWORD(lParam);
		break;
	}
	case WM_LBUTTONUP:
	{
		//int x = (int)(short)LOWORD(lParam);
		//int y = (int)(short)HIWORD(lParam);
		return 0;
	}
	//case LVM_HITTEST:
	//{
	//	return 1;
	//}

	//case NM_CLICK:
	//{
	//	int a = 0;
	//}
	//	break;
	//case NM_DBLCLK:
	//{
	//	int a = 0;
	//}
	//break;
	//case LVN_COLUMNDROPDOWN:
	//{
	//	int a = 0;
	//}
	break;
	default:
		break;
	}
	return 0;
}
