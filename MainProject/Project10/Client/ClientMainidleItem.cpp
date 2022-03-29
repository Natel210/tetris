#include "stdafx.h"
#include "ClientMainidleItem.h"


void ClientMainidleItem::MapUpdate()
{
	TCHAR pMapArr[Map_maxX][Map_maxY];
	const TCHAR* pMap = AdvanceMap::SelectMap(m_iMapIdx);
	memcpy(pMapArr, pMap, sizeof(TCHAR)*Map_maxX*Map_maxY);
	for (int y = 0; y < Map_maxY; ++y)
	{
		for (int x = 0; x < Map_maxX; ++x)
		{
			m_MapTile[x][y].eType = (MapTileColors)pMapArr[x][y];
		}
	}
	//m_MapTile->
}

ClientMainidleItem::ClientMainidleItem()
{
}


ClientMainidleItem::~ClientMainidleItem()
{
}

int ClientMainidleItem::Input(float time)
{
	return PR_OK;
}

int ClientMainidleItem::Update(float time)
{
	return PR_OK;
}

int ClientMainidleItem::LateUpdate(float time)
{
	return PR_OK;
}

int ClientMainidleItem::Transform(float time)
{
	return PR_OK;
}

int ClientMainidleItem::Render(float time, HDC drow)
{
	//�̾������� �׸��⸸ �ϸ�ɰŰ�����? ���ƴϰ� ��带 ���� �׷���߰���.
	if (drow)
	{
		/////////////////////////////////////////////////////////////////////
		//���ο�
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, GetStockObject(DKGRAY_BRUSH));
		HPEN oldPen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));
		Rectangle(drow, 0, 0, (Map_maxX * 30) + 10, (Map_maxY * 30) + 10);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldPen);


		/////////////////////////////////////////////////////////////////////////////////////////
		HBRUSH Backbrush = ColorManager::FindBrush(_T("BackMapBrush"));
		oldbrush = (HBRUSH)SelectObject(drow, Backbrush);

		oldPen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));
		/////////////////////////////////////////////////////////////////////
		//������ �ǵ�
		Rectangle(drow, 5, 5, (Map_maxX * 30) + 5/* 455*/, (Map_maxY * 30) + 5/* 695*/);

		(HPEN)SelectObject(drow, oldPen);

		/////////////////////////////////////////////////////////////////////////////
		HPEN BackPen = ColorManager::FindPen(_T("BackMapPen"));
		oldPen = (HPEN)SelectObject(drow, BackPen);


		POINT ReturnPT;
		MoveToEx(drow, 35, 5, &ReturnPT);
		LineTo(drow, 35, 695);
		for (int i = 1; i < Map_maxX - 1; ++i)
		{
			MoveToEx(drow, (35 + (i * 30)), 5, NULL);
			LineTo(drow, (35 + (i * 30)), (Map_maxY * 30) + 5);
		}
		for (int i = 1; i < Map_maxY; ++i)
		{
			MoveToEx(drow, 5, (5 + (i * 30)), NULL);
			LineTo(drow, (Map_maxX * 30) + 5, (5 + (i * 30)));
		}
		MoveToEx(drow, ReturnPT.x, ReturnPT.y, NULL);

		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldPen);

		/////////////////////////////////////////////////////////////////////
		//���⼭ Ÿ�Ժ��� �귯���� �޾ƾ����ְ� �ؾ߁ٴ�.,

		//���⼭ Ÿ�������� �����Ѵ�.
		for (int y = 0; y < Map_maxY; ++y)
		{
			for (int x = 0; x < Map_maxX; ++x)
			{
				m_MapTile[x][y].Render(drow);
			}
		}
		/////////////////////////////////////////////////////////////////////
	}
	return PR_OK;
}

int ClientMainidleItem::DebugRender(float time)
{
	return PR_OK;
}

int ClientMainidleItem::Collision(float time)
{
	return PR_OK;
}

int ClientMainidleItem::Init()
{
	//�ϴ��� Ʋ�� �׸���..
	//m_MapTile[Map_maxX][Map_maxY];
	for (int y = 0; y < Map_maxY; ++y)
	{
		for (int x = 0; x < Map_maxX; ++x)
		{
			m_MapTile[x][y].eType = MTC_NONE;
			m_MapTile[x][y].x = x;
			m_MapTile[x][y].y = y;
		}
	}

	return PR_OK;
}

int ClientMainidleItem::release()
{
	return PR_OK;
}
