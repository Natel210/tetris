#include "stdafx.h"
#include "IngameLogNextBlockItem.h"
#include "ClientHeader.h"

IngameLogNextBlockItem::IngameLogNextBlockItem()
{
}


IngameLogNextBlockItem::~IngameLogNextBlockItem()
{
}

int IngameLogNextBlockItem::Input(float time)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; ++x)
		{
			m_NextViewTile[x][y].eType = MTC_NONATIVE;
			m_NextViewTile[x][y].x = x;
			m_NextViewTile[x][y].y = y;
		}
	}



	

	switch (m_iNextIDX)
	{
	case BT_4LA:
	{
		m_NextViewTile[0][1].eType = MTC_ATIVE1;
		m_NextViewTile[1][1].eType = MTC_ATIVE1;
		m_NextViewTile[2][1].eType = MTC_ATIVE1;
		m_NextViewTile[3][1].eType = MTC_ATIVE1;
	}
	break;
	case BT_4LB:
	{
		m_NextViewTile[1][0].eType = MTC_ATIVE1;
		m_NextViewTile[1][1].eType = MTC_ATIVE1;
		m_NextViewTile[1][2].eType = MTC_ATIVE1;
		m_NextViewTile[1][3].eType = MTC_ATIVE1;
	}
	break;
	case BT_22AA:
	{
		m_NextViewTile[0][1].eType = MTC_ATIVE2;
		m_NextViewTile[1][1].eType = MTC_ATIVE2;
		m_NextViewTile[1][2].eType = MTC_ATIVE2;
		m_NextViewTile[2][2].eType = MTC_ATIVE2;
	}
	break;
	case BT_22AB:
	{
		m_NextViewTile[2][0].eType = MTC_ATIVE2;
		m_NextViewTile[1][1].eType = MTC_ATIVE2;
		m_NextViewTile[2][1].eType = MTC_ATIVE2;
		m_NextViewTile[1][2].eType = MTC_ATIVE2;
	}
	break;
	case BT_22BA:
	{
		m_NextViewTile[1][1].eType = MTC_ATIVE3;
		m_NextViewTile[2][1].eType = MTC_ATIVE3;
		m_NextViewTile[1][2].eType = MTC_ATIVE3;
		m_NextViewTile[0][2].eType = MTC_ATIVE3;
	}
	break;
	case BT_22BB:
	{
		m_NextViewTile[1][0].eType = MTC_ATIVE3;
		m_NextViewTile[1][1].eType = MTC_ATIVE3;
		m_NextViewTile[2][1].eType = MTC_ATIVE3;
		m_NextViewTile[2][2].eType = MTC_ATIVE3;
	}
	break;
	case BT_22MM:
	{
		m_NextViewTile[1][1].eType = MTC_ATIVE4;
		m_NextViewTile[1][2].eType = MTC_ATIVE4;
		m_NextViewTile[2][2].eType = MTC_ATIVE4;
		m_NextViewTile[2][1].eType = MTC_ATIVE4;
	}
	break;

	case BT_31LA:
	{
		m_NextViewTile[1][0].eType = MTC_ATIVE5;
		m_NextViewTile[2][0].eType = MTC_ATIVE5;
		m_NextViewTile[2][1].eType = MTC_ATIVE5;
		m_NextViewTile[2][2].eType = MTC_ATIVE5;
	}
		break;
	case BT_31LB:
	{
		m_NextViewTile[0][2].eType = MTC_ATIVE5;
		m_NextViewTile[1][2].eType = MTC_ATIVE5;
		m_NextViewTile[2][2].eType = MTC_ATIVE5;
		m_NextViewTile[2][1].eType = MTC_ATIVE5;
	}
		break;
	case BT_31LC:
	{
		m_NextViewTile[1][0].eType = MTC_ATIVE5;
		m_NextViewTile[1][1].eType = MTC_ATIVE5;
		m_NextViewTile[1][2].eType = MTC_ATIVE5;
		m_NextViewTile[2][2].eType = MTC_ATIVE5;
	}
		break;
	case BT_31LD:
	{
		m_NextViewTile[0][1].eType = MTC_ATIVE5;
		m_NextViewTile[1][1].eType = MTC_ATIVE5;
		m_NextViewTile[2][1].eType = MTC_ATIVE5;
		m_NextViewTile[0][2].eType = MTC_ATIVE5;
	}
		break;
	case BT_31RA:
	{
		m_NextViewTile[1][0].eType = MTC_ATIVE6;
		m_NextViewTile[1][1].eType = MTC_ATIVE6;
		m_NextViewTile[1][2].eType = MTC_ATIVE6;
		m_NextViewTile[2][0].eType = MTC_ATIVE6;
	}
		break;
	case BT_31RB:
	{
		m_NextViewTile[0][1].eType = MTC_ATIVE6;
		m_NextViewTile[1][1].eType = MTC_ATIVE6;
		m_NextViewTile[2][1].eType = MTC_ATIVE6;
		m_NextViewTile[2][2].eType = MTC_ATIVE6;
	}
		break;
	case BT_31RC:
	{
		m_NextViewTile[2][0].eType = MTC_ATIVE6;
		m_NextViewTile[2][1].eType = MTC_ATIVE6;
		m_NextViewTile[2][2].eType = MTC_ATIVE6;
		m_NextViewTile[1][2].eType = MTC_ATIVE6;
	}
		break;
	case BT_31RD:
	{
		m_NextViewTile[0][2].eType = MTC_ATIVE6;
		m_NextViewTile[1][2].eType = MTC_ATIVE6;
		m_NextViewTile[2][2].eType = MTC_ATIVE6;
		m_NextViewTile[0][1].eType = MTC_ATIVE6;
	}
		break;
	case BT_31MA:
	{
		m_NextViewTile[0][2].eType = MTC_ATIVE7;
		m_NextViewTile[1][2].eType = MTC_ATIVE7;
		m_NextViewTile[2][2].eType = MTC_ATIVE7;
		m_NextViewTile[1][1].eType = MTC_ATIVE7;
	}
		break;
	case BT_31MB:
	{
		m_NextViewTile[1][0].eType = MTC_ATIVE7;
		m_NextViewTile[1][1].eType = MTC_ATIVE7;
		m_NextViewTile[1][2].eType = MTC_ATIVE7;
		m_NextViewTile[2][1].eType = MTC_ATIVE7;
	}
		break;
	case BT_31MC:
	{
		m_NextViewTile[0][1].eType = MTC_ATIVE7;
		m_NextViewTile[1][1].eType = MTC_ATIVE7;
		m_NextViewTile[2][1].eType = MTC_ATIVE7;
		m_NextViewTile[1][2].eType = MTC_ATIVE7;
	}
		break;
	case BT_31MD:
	{	
		m_NextViewTile[2][0].eType = MTC_ATIVE7;
		m_NextViewTile[2][1].eType = MTC_ATIVE7;
		m_NextViewTile[2][2].eType = MTC_ATIVE7;
		m_NextViewTile[1][1].eType = MTC_ATIVE7;
	}
		break;

	break;
	default:
		break;
	}

	//m_iNextIDX

//	BlockType
	//if ()
	//{
	//}

	return 1;
}

int IngameLogNextBlockItem::Update(float time)
{

	return 1;
}

int IngameLogNextBlockItem::LateUpdate(float time)
{
	return 1;
}

int IngameLogNextBlockItem::Transform(float time)
{
	return 1;
}

int IngameLogNextBlockItem::Render(float time, HDC drow)
{
	//Rectangle(drow, 5, (Map_maxY * 7), 240, 140);
	//Rectangle(drow, 0, 0, 100, 100);
	
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; ++x)
		{
			m_NextViewTile[x][y].RenderPivotSIze(5+ 70, (Map_maxY * 7),drow);
		}
	}


	return 1;
}

int IngameLogNextBlockItem::DebugRender(float time)
{
	return 1;
}

int IngameLogNextBlockItem::Collision(float time)
{
	return 1;
}

int IngameLogNextBlockItem::Init()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; ++x)
		{
			m_NextViewTile[x][y].eType = MTC_NONE;
			//
			//m_NextViewTile[x][y].Render(drow);
			m_NextViewTile[x][y].x = x;
			m_NextViewTile[x][y].y = y;
		}
	}
	//int m_iNextIDX;
	return 1;
}

int IngameLogNextBlockItem::release()
{
	return 1;
}
