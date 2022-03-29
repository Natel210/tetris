#include "stdafx.h"
#include "SubViewItem.h"



#include "Render/RenderManager.h"

SubViewItem::SubViewItem()
{
}


SubViewItem::~SubViewItem()
{
}

void SubViewItem::SetPos(int _x, int _y)
{
	PosX = _x;
	PosY = _y;
}

int SubViewItem::GetPosX() const
{
	return PosX;
}

int SubViewItem::GetPosY() const
{
	return PosY;
}

void SubViewItem::SendMapTile(TCHAR _pMapArr[Map_maxX][Map_maxY])
{
	if (!_pMapArr)
	{
		return;
	}
	for (int x = 0 ; x < Map_maxX; ++x)
	{
		for (int y = 0 ; y < Map_maxY; ++y)
		{
			m_ChangeMapTile[x][y].eType = (MapTileColors)_pMapArr[x][y];
		}
	}
	return;
}

int SubViewItem::Input(float time)
{
	return 1;
}

int SubViewItem::Update(float time)
{
	return 1;
}

int SubViewItem::LateUpdate(float time)
{
	//마지막 업데이트에서 고속 복사릃 한다.
	 //m_MapTile[Map_maxX][Map_maxY]
	return 1;
}

int SubViewItem::Transform(float time)
{
	return 1;
}

int SubViewItem::Render(float time, HDC drow)
{
	/////////////////////////////////////////////////////////////////////
	//라인용
	HBRUSH oldbrush = (HBRUSH)SelectObject(drow, GetStockObject(DKGRAY_BRUSH));
	HPEN oldPen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));
	Rectangle(drow, PosX, PosY, PosX + (Map_maxX * 15) + 12, PosY + (Map_maxY * 15) + 12);
	(HBRUSH)SelectObject(drow, oldbrush);
	(HPEN)SelectObject(drow, oldPen);

	HBRUSH Backbrush = ColorManager::FindBrush(_T("BackMapBrush"));
	oldbrush = (HBRUSH)SelectObject(drow, Backbrush);

	oldPen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));
	/////////////////////////////////////////////////////////////////////
	//내부의 판들
	Rectangle(drow, PosX+ 5, PosY+ 5, PosX+ (Map_maxX * 15) + 6/* 455*/, PosY+ (Map_maxY * 15) + 5/* 695*/);

	(HPEN)SelectObject(drow, oldPen);
	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	HPEN BackPen = ColorManager::FindPen(_T("BackMapPen"));
	oldPen = (HPEN)SelectObject(drow, BackPen);


	POINT ReturnPT;
	MoveToEx(drow, PosX +20, PosY+ 5, &ReturnPT);
	LineTo(drow, PosX+ 20, PosY + (Map_maxY * 15) + 5);
	for (int i = 1; i < Map_maxX - 1; ++i)
	{
		MoveToEx(drow, PosX +(20 + (i * 15)), PosY+ 5, NULL);
		LineTo(drow, PosX +(20 + (i * 15)), PosY+(Map_maxY * 15) + 5);
	}
	for (int i = 1; i < Map_maxY; ++i)
	{
		MoveToEx(drow, PosX +5, PosY +(5 + (i * 15)), NULL);
		LineTo(drow, PosX +(Map_maxX * 15) + 5, PosY+(5 + (i * 15)));
	}
	MoveToEx(drow, ReturnPT.x, ReturnPT.y, NULL);

	(HBRUSH)SelectObject(drow, oldbrush);
	(HPEN)SelectObject(drow, oldPen);

	/////////////////////////////////////////////////////////////////////


	if (m_ChangeMapTile)
	{
		memcpy(m_RenderMapTile, m_ChangeMapTile, sizeof(Maptile)*Map_maxX*Map_maxY);

		//ClientIngmaeLayer::pMainViewItme->m_MapTile[][];
	}

	for (int y = 0; y < Map_maxY; ++y)
	{
		for (int x = 0; x < Map_maxX; ++x)
		{
			m_RenderMapTile[x][y].RenderOthrer(PosX+5, PosY+5,drow);
		}
	}

	return 1;
}

int SubViewItem::DebugRender(float time)
{
	return 1;
}

int SubViewItem::Collision(float time)
{
	return 1;
}

int SubViewItem::Init()
{

	for (int y = 0; y < Map_maxY; ++y)
	{
		for (int x = 0; x < Map_maxX; ++x)
		{
			//m_RenderMapTile[x][y].eType = MTC_NONE;
			//m_RenderMapTile[x][y].x = x;
			//m_RenderMapTile[x][y].y = y;

			m_ChangeMapTile[x][y].eType = MTC_NONE;
			m_ChangeMapTile[x][y].x = x;
			m_ChangeMapTile[x][y].y = y;
		}
	}
	return 1;
}

int SubViewItem::release()
{
	return 1;
}
