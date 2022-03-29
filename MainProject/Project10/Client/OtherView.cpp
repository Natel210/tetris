#include "stdafx.h"
#include "OtherView.h"

#include "Scene.h"
#include "ClientIngameEnum.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "SubViewItem.h"
#include "ReadyStatic.h"


int OtherView::Init()
{
	LayerPosX = 30;
	LayerPosY = 50;
	LayerSizeX = 560;
	LayerSizeY = (Map_maxY * 30) + 30;
	LayerZ = IngameSubDC;
	WinDCManager::CreateHDC(_T("OtherView"), IngameSubDC, 30, 50, 560, (Map_maxY * 30) + 30);

	m_LayerhDC = WinDCManager::FindDC(_T("OtherView"));

	ppSubView[0] = Layer::CreateObj<SubViewItem>(_T("SubViewItem1"));
	ppSubView[0]->SetPos(0, 0);
	ppSubView[1] = Layer::CreateObj<SubViewItem>(_T("SubViewItem2"));
	ppSubView[1]->SetPos(0, (Map_maxY * 15) + 20);

	ppSubView[2] = Layer::CreateObj<SubViewItem>(_T("SubViewItem3"));
	ppSubView[2]->SetPos(170, 0);
	ppSubView[3] = Layer::CreateObj<SubViewItem>(_T("SubViewItem4"));
	ppSubView[3]->SetPos(170, (Map_maxY * 15) + 20);

	ppSubView[4] = Layer::CreateObj<SubViewItem>(_T("SubViewItem5"));
	ppSubView[4]->SetPos(340, 0);
	ppSubView[5] = Layer::CreateObj<SubViewItem>(_T("SubViewItem6"));
	ppSubView[5]->SetPos(340, (Map_maxY * 15) + 20);


	int PivotX = 30+8;
	int PivotY = 50+220;

	ppSubViewReady[0] = Layer::CreateObj<ReadyStatic>(_T("SubViewReadyItem1"));
	ppSubViewReady[0]->MovePos(0+ PivotX, 0+ PivotY);
	ppSubViewReady[1] = Layer::CreateObj<ReadyStatic>(_T("SubViewReadyItem2"));
	ppSubViewReady[1]->MovePos(0+ PivotX, (Map_maxY * 15) + 20+ PivotY);

	ppSubViewReady[2] = Layer::CreateObj<ReadyStatic>(_T("SubViewReadyItem3"));
	ppSubViewReady[2]->MovePos(170+ PivotX, 0+PivotY);
	ppSubViewReady[3] = Layer::CreateObj<ReadyStatic>(_T("SubViewReadyItem4"));
	ppSubViewReady[3]->MovePos(170+ PivotX, (Map_maxY * 15) + 20+ PivotY);

	ppSubViewReady[4] = Layer::CreateObj<ReadyStatic>(_T("SubViewReadyItem5"));
	ppSubViewReady[4]->MovePos(340+ PivotX, 0+ PivotY);
	ppSubViewReady[5] = Layer::CreateObj<ReadyStatic>(_T("SubViewReadyItem6"));
	ppSubViewReady[5]->MovePos(340+ PivotX, (Map_maxY * 15) + 20+ PivotY);






	return PR_OK;
}

int OtherView::LayerUpdate(float time)
{
	//작업 범위
#ifdef DEBUG
	HPEN dwebugpaens = ColorManager::FindPen(_T("DebugRect"));
	HPEN OldPens = (HPEN)SelectObject(m_LayerhDC, dwebugpaens);
	Rectangle(m_LayerhDC, 0, 0, 560, (Map_maxY * 30) + 30);
	(HPEN)SelectObject(m_LayerhDC, OldPens);
#endif // DEBUG

	return PR_OK;
}

int OtherView::StartUp()
{
	ppSubViewReady[0]->SetActive(true);
	ppSubViewReady[0]->WndShow();
	ppSubViewReady[1]->SetActive(true);
	ppSubViewReady[1]->WndShow();
	ppSubViewReady[2]->SetActive(true);
	ppSubViewReady[2]->WndShow();
	ppSubViewReady[3]->SetActive(true);
	ppSubViewReady[3]->WndShow();
	ppSubViewReady[4]->SetActive(true);
	ppSubViewReady[4]->WndShow();
	ppSubViewReady[5]->SetActive(true);
	ppSubViewReady[5]->WndShow();
	return PR_OK;
}

int OtherView::EndUp()
{
	ppSubViewReady[0]->SetActive(false);
	ppSubViewReady[0]->WndHide();
	ppSubViewReady[1]->SetActive(false);
	ppSubViewReady[1]->WndHide();
	ppSubViewReady[2]->SetActive(false);
	ppSubViewReady[2]->WndHide();
	ppSubViewReady[3]->SetActive(false);
	ppSubViewReady[3]->WndHide();
	ppSubViewReady[4]->SetActive(false);
	ppSubViewReady[4]->WndHide();
	ppSubViewReady[5]->SetActive(false);
	ppSubViewReady[5]->WndHide();
	return PR_OK;
}

int OtherView::release()
{
	
	return PR_OK;
}

void OtherView::SetOtherReady(int _Readys[6])
{
	for (int i = 0; i < 6 ; ++i)
	{
		ppSubViewReady[i]->SetReady(_Readys[i]);
	}
}

void OtherView::SetOtherMap(int IDX)
{
	TCHAR pMapArr[Map_maxX][Map_maxY];
	const TCHAR* pMap = AdvanceMap::SelectMap(IDX);


	memcpy(pMapArr, pMap, sizeof(TCHAR)*Map_maxX*Map_maxY);

	for (int idx = 0; idx < 6 ; ++idx)
	{
		ppSubView[idx]->SendMapTile(pMapArr);
	}


	//TCHAR _pMapArr[Map_maxX][Map_maxY];
	//AdvanceMap::SelectMap(IDX, _pMapArr);
	//for (int i = 0; i < 6; ++i)
	//{
	//	if (ppSubView[i])
	//	{
	//		ppSubView[i]->SendMapTile(_pMapArr);
	//	}
	//	
	//}
}


OtherView::OtherView()
{
}


OtherView::~OtherView()
{
}
