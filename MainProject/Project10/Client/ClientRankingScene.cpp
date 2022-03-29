#include "stdafx.h"
#include "ClientRankingScene.h"

//
#include "MainRankingLayer.h"

/////////////////////////////////////////////
#include <commctrl.h>
#pragma comment (lib, "comctl32.lib")

#include "ClientCore.h"

int ClientRankingScene::Init()
{
	pMainLankingLayer = Scene::CreateLayer<MainRankingLayer>(_T("Lanking"));




	return 1;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//WC_LISTVIEW;
	HWND hWnd = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_EDITLABELS /*| LVS_LIST *//*|LVS_OWNERDRAWFIXED*/, 10, 10, 500, 500, ClientCore::mainhWnd, NULL, ClientCore::mainhInst, NULL);
	//폰트를 키워서 만들어야겠다.

	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));

	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM /*| LVCF_MINWIDTH*/;
	COL.fmt = LVCFMT_CENTER;//| LVCFMT_FIXED_WIDTH;
	COL.cx = 0;
	//COL.cxMin = 00;
	COL.pszText = TEXT("");
	COL.iSubItem = 0;
	ListView_InsertColumn(hWnd, 0, (LPARAM)&COL);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	COL.fmt = LVCFMT_CENTER | LVCFMT_FIXED_WIDTH;
	COL.cx = 100;
	COL.cxMin = 100;
	COL.pszText = TEXT("NAME");
	COL.iSubItem = 1;
	SendMessage(hWnd, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	COL.fmt = LVCFMT_CENTER | LVCFMT_FIXED_WIDTH;
	COL.cx = 100;
	COL.cxMin = 100;
	COL.pszText = TEXT("TEST1");
	COL.iSubItem = 2;
	SendMessage(hWnd, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	////////////////////////////////////////////////////////////////////////////////////////////////

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
	COL.fmt = LVCFMT_CENTER | LVCFMT_FIXED_WIDTH;
	COL.cx = 100;
	COL.cxMin = 100;
	COL.pszText = TEXT("2TEST2");
	COL.iSubItem = 3;
	SendMessage(hWnd, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	LVITEM LI;

	LI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 0;
	LI.pszText = L"0";
	ListView_InsertItem(hWnd, &LI);
	LI.iItem = 1;
	LI.pszText = L"1";
	ListView_InsertItem(hWnd, &LI);
	LI.iItem = 2;
	LI.pszText = L"2";
	ListView_InsertItem(hWnd, &LI);
	LI.iItem = 3;
	LI.pszText = L"3";
	ListView_InsertItem(hWnd, &LI);
	/////////////////////////////////////////////////////////////////////////////////////////////////////


	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 1;
	LI.pszText = L"라군";
	ListView_SetItem(hWnd, &LI);
	//ListView
	LI.iItem = 1;
	LI.pszText = L"다군";
	ListView_SetItem(hWnd, &LI);
	LI.iItem = 2;
	LI.pszText = L"나군";
	ListView_SetItem(hWnd, &LI);
	LI.iItem = 3;
	LI.pszText = L"가군";
	ListView_SetItem(hWnd, &LI);



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	LI.state = 0;
	LI.iItem = 0;
	LI.iSubItem = 3;
	LI.pszText = L"3";
	ListView_SetItem(hWnd,&LI);


	LI.iItem = 1;
	LI.iSubItem = 3;
	LI.pszText = L"3333";
	ListView_SetItem(hWnd,&LI);


	LI.iItem = 2;
	LI.iSubItem = 3;
	LI.pszText = L"333";
	ListView_SetItem(hWnd,&LI);


	LI.iItem = 3;
	LI.iSubItem = 3;
	LI.pszText = L"33";
	ListView_SetItem(hWnd,&LI);
	//////////////////////////////////////////////////////////////////////////////////////////




	ListView_SetColumnWidth(hWnd, 0, 0);
	ListView_SetColumnWidth(hWnd, 1, 60);
	ListView_SetColumnWidth(hWnd, 2, 60);
	ListView_SetColumnWidth(hWnd, 3, 60);


	ListView_SetColumnWidth(hWnd, 4, 60);
	ListView_SetColumnWidth(hWnd, 5, 60);


	//SendMessage(hWnd, LVM_, 1, (LPARAM)&COL);

	return 1;
}

int ClientRankingScene::release()
{
	return 1;
}

ClientRankingScene::ClientRankingScene()
{
}


ClientRankingScene::~ClientRankingScene()
{
}
