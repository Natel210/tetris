#include "stdafx.h"
#include "ClientIngameEnum.h"
#include "Render/RenderManager.h"


int Maptile::Render(HDC drow)
{
	switch (eType)
	{
	case MTC_ERR:
		break;
	case MTC_NONE:
	{
		//브러쉬랑
		//팬둘다 널인것으로만든다.
		//GetStockObject(NULL_BRUSH);
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, GetStockObject(NULL_BRUSH));

		HPEN oldpen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));

		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);

		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_NONATIVE:
	{
		HBRUSH nullbrush = ColorManager::FindBrush(_T("NonActiveBrush"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, nullbrush);
		HPEN oldpen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE1:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush1"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen1"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		//HPEN oldpen = (HPEN)SelectObject(drow, (HPEN)GetStockObject(BLACK_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE2:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush2"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen2"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		//HPEN oldpen = (HPEN)SelectObject(drow, (HPEN)GetStockObject(BLACK_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE3:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush3"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen3"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		//HPEN oldpen = (HPEN)SelectObject(drow, (HPEN)GetStockObject(BLACK_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE4:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush4"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen4"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		//HPEN oldpen = (HPEN)SelectObject(drow, (HPEN)GetStockObject(BLACK_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE5:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush5"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen5"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		//HPEN oldpen = (HPEN)SelectObject(drow, (HPEN)GetStockObject(BLACK_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE6:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush6"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen6"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		//HPEN oldpen = (HPEN)SelectObject(drow, (HPEN)GetStockObject(BLACK_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE7:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush7"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen7"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		//HPEN oldpen = (HPEN)SelectObject(drow, (HPEN)GetStockObject(BLACK_PEN));
		Rectangle(drow, 5 + (x * MyBlockSize) + 1, 5 + (y * MyBlockSize) + 1, 5 + MyBlockSize + (x * MyBlockSize) + 1, 5 + MyBlockSize + (y * MyBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	default:
		break;
	}
	return 1;
}

int Maptile::RenderOthrer(int PosX, int PosY, HDC drow)
{
	switch (eType)
	{
	case MTC_ERR:
		break;
	case MTC_NONE:
	{
		//브러쉬랑
		//팬둘다 널인것으로만든다.
		//GetStockObject(NULL_BRUSH);
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, GetStockObject(NULL_BRUSH));

		HPEN oldpen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));

		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);

		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_NONATIVE:
	{
		HBRUSH nullbrush = ColorManager::FindBrush(_T("NonActiveBrush"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, nullbrush);
		HPEN oldpen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE1:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush1"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen1"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE2:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush2"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen2"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE3:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush3"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen3"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE4:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush4"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen4"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE5:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush5"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen5"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE6:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush6"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen6"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE7:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush7"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen7"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * OtherBlockSize) + 1, PosY + (y * OtherBlockSize) + 1, PosX + OtherBlockSize + (x * OtherBlockSize) + 1, PosY + OtherBlockSize + (y * OtherBlockSize) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	
	default:
		break;
	}
	return 1;
}

int Maptile::RenderPivotSIze(int PosX, int PosY, HDC drow, int sizeX, int SizeY)
{
	switch (eType)
	{
	case MTC_ERR:
		break;
	case MTC_NONE:
	{
		//브러쉬랑
		//팬둘다 널인것으로만든다.
		//GetStockObject(NULL_BRUSH);
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, GetStockObject(NULL_BRUSH));

		HPEN oldpen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));

		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);

		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_NONATIVE:
	{
		HBRUSH nullbrush = ColorManager::FindBrush(_T("NonActiveBrush"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, nullbrush);
		HPEN oldpen = (HPEN)SelectObject(drow, GetStockObject(NULL_PEN));
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE1:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush1"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen1"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE2:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush2"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen2"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE3:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush3"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen3"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE4:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush4"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen4"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE5:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush5"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen5"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE6:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush6"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen6"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	case MTC_ATIVE7:
	{
		HBRUSH ActiveBrush = ColorManager::FindBrush(_T("ActiveBrush7"));
		HPEN ActivePen = ColorManager::FindPen(_T("ActivePen7"));
		HBRUSH oldbrush = (HBRUSH)SelectObject(drow, ActiveBrush);
		HPEN oldpen = (HPEN)SelectObject(drow, ActivePen);
		Rectangle(drow, PosX + (x * sizeX) + 1, PosY + (y * SizeY) + 1, PosX + sizeX + (x * sizeX) + 1, PosY + SizeY + (y * SizeY) + 1);
		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldpen);
	}
	break;
	default:
		break;
	}
	return 1;
}







const TCHAR AdvanceMap::pMapErr[Map_maxX][Map_maxY] = { 0, };
const TCHAR AdvanceMap::pMapArr1[Map_maxX][Map_maxY] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },// X 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2 },// X 9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2 },// X 8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2 },// X 7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2 },// X 6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2 },// X 5
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2 },// X 4
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2 },// X 3
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0 },// X 2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2 },// X 1
//Y - 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 - Y
 };
const TCHAR AdvanceMap::pMapArr2[Map_maxX][Map_maxY] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2 },// X 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2 },// X 9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0 },// X 8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0 },// X 7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0 },// X 6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 0 },// X 5
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0 },// X 4
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0 },// X 3
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2 },// X 2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2 },// X 1
//Y - 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 - Y
 };
const TCHAR AdvanceMap::pMapArr3[Map_maxX][Map_maxY] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },// X 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2 },// X 9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2 },// X 8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2 },// X 7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2 },// X 6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2 },// X 5
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2 },// X 4
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2 },// X 3
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2 },// X 2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },// X 1
//Y - 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 - Y
 };
const TCHAR AdvanceMap::pMapArr4[Map_maxX][Map_maxY] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },// X 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },// X 9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2 },// X 8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2 },// X 7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0 },// X 6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0 },// X 5
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },// X 4
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },// X 3
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },// X 2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },// X 1
//Y - 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 - Y
 };;
const TCHAR AdvanceMap::pMapArr5[Map_maxX][Map_maxY] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2 },// X 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2 },// X 9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 2 },// X 8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 2 },// X 7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0 },// X 6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0 },// X 5
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0 },// X 4
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 0 },// X 3
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0 },// X 2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 },// X 1
//Y - 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 - Y
 };
const TCHAR AdvanceMap::pMapArr6[Map_maxX][Map_maxY] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2 },// X 10
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2 },// X 9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0 },// X 8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0 },// X 7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0 },// X 6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0 },// X 5
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0 },// X 4
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2 },// X 3
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2 },// X 2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2 },// X 1
//Y - 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 - Y
 };














