#include "stdafx.h"
#include "ClientMainViewItem.h"
#include "Render/RenderManager.h"
#include "Input/Input.h"
#include "ClientIngmaeBlock.h"




ClientMainViewItem::ClientMainViewItem() : m_curblcok(nullptr)
{
}


ClientMainViewItem::~ClientMainViewItem()
{
}

void ClientMainViewItem::LineCheck()
{
	//Ȥ�� �� ���� üũ
	for (int x = 0; x < Map_maxX; ++x)
	{
		if (m_MapTile[x][1].eType == MTC_NONATIVE)
		{
			//���� ���� ���� ó���� �ؾ߰ڽ��ϴ�.
			//////////////
			//MessageBox(ClientCore::mainhWnd, L"�׾����ϴ�.", L"�׾����ϴ�.", MB_OK);
			m_bEnd = 2;

		}
		
	}
	std::vector<int> checklinevec;
	for (int y = 0; y < Map_maxY; ++y)
	{
		bool clear = true;
		//������ ������ ���äũ�Ѵ�.
		for (int x = 0; x < Map_maxX; ++x)
		{
			if (m_MapTile[x][y].eType != MTC_NONATIVE)
			{
				clear = false;
				break;
			}
		}
		if (clear)
		{
			checklinevec.push_back(y);
		}
	}
	int Counts = (int)checklinevec.size();
	switch (Counts)
	{
	case 1:
		m_iMyScore += 1000;
		break;
	case 2:
		m_iMyScore += 3000;
		break;
	case 3:
		m_iMyScore += 6000;
		break;
	case 4:
		m_iMyScore += 10000;
		break;
	default:
		break;
	}
	
	if (0 != checklinevec.size())
	{
		for (int i = 0; i < (int)checklinevec.size(); ++i)
		{
			//�������� �δ콺��°.

			//
			for (int j = checklinevec[i]; j > 0; --j)
			{
				for (int x = 0; x < Map_maxX; ++x)
				{
					//m_MapTile[x][j].eType = MTC_ATIVE;
					m_MapTile[x][j].eType = m_MapTile[x][j - 1].eType;
				}
			}
		}
	}
}

int ClientMainViewItem::Input(float time)
{
	if (KEY_KEY(_T("LeftMove")) || 
		KEY_KEY(_T("RightMove")) || 
		KEY_KEY(_T("DownMove")) || 
		KEY_KEY(_T("ShutDown")) || 
		KEY_KEY(_T("Change")))
	{
		SetFocus(ClientCore::mainhWnd);
	}


	return 1;
}

int ClientMainViewItem::Update(float time)
{
	if (m_bEnd == 2)
	{
		return PR_OK;
	}

	/////////////////////////////////////////////////////////////////////
	//������ġ�� �˾Ƴ��°� �߿��ҰŰ���.
	//���� ��ġ �ʱ�ȭ.
	CurBlockIdx prevIdx;
	m_curblcok->GetCurBlockIdx(prevIdx);
	for (int i = 0; i < 4; ++i)
	{
		if (prevIdx.m_blocknodeY[i] <= -1 || prevIdx.m_blocknodeY[i] >= Map_maxY || prevIdx.m_blocknodeX[i] <= -1 || prevIdx.m_blocknodeX[i] >= Map_maxX)
		{
			continue;
		}
		m_MapTile[prevIdx.m_blocknodeX[i]][prevIdx.m_blocknodeY[i]].eType = MTC_NONE;
	}
	/////////////////////////////////////////////////////////////////////
	//�̵� ������ �������
	BlockState Blockresult = m_curblcok->MoveUpdate(time);
	CurBlockIdx MoveIdx;
	m_curblcok->GetCurBlockIdx(MoveIdx);
	for (int i = 0; i < 4; ++i)
	{
		if ( MoveIdx.m_blocknodeX[i] <= -1 )
		{
			++m_curblcok->x;
			break;
		}
		else if (MoveIdx.m_blocknodeX[i] >= Map_maxX)
		{
			--m_curblcok->x;
			break;
		}
		else if (m_MapTile[MoveIdx.m_blocknodeX[i]][MoveIdx.m_blocknodeY[i]].eType == MTC_NONATIVE)
		{
			if (BKS_CHANGE == Blockresult)
			{
				m_curblcok->ReChangeBlock();
			}
			if (BKS_LEFT == Blockresult)
			{
				if (MoveIdx.m_blocknodeX[i] < 0 || MoveIdx.m_blocknodeY[i] < 0)
				{

				}
				else
				{
					++m_curblcok->x;
				}
				
			}
			if (BKS_RIGHT == Blockresult)
			{
				if (MoveIdx.m_blocknodeX[i] < 0 || MoveIdx.m_blocknodeY[i] < 0)
				{
					//--m_curblcok->x;
				}
				else
				{
					--m_curblcok->x;
				}
				
			}
			//���� �߽����� ������ ��ġ�� ���� �������̴�.
			break;
		}
	}
	if (BKS_SHUTDOWN == Blockresult)
	{
		int DownY = 0;
		bool FindDrop = false; 
		CurBlockIdx FindIdx;
 		m_curblcok->GetCurBlockIdx(FindIdx);

		while (!FindDrop)
		{
			++DownY;
			for (int i = 0; i < 4; ++i)
			{
				if (FindIdx.m_blocknodeY[i]+DownY <= 0)
				{
					continue;
				}
				if (FindIdx.m_blocknodeY[i]+DownY >= (Map_maxY - 1))
				{
					FindDrop = true;
					break;
				}
			}
			for (int i = 0; i < 4; ++i)
			{
				if (FindIdx.m_blocknodeY[i] + DownY <= 0 || FindIdx.m_blocknodeY[i] + DownY >= Map_maxY + 1 || FindIdx.m_blocknodeX[i] <= -1 || FindIdx.m_blocknodeX[i] >= Map_maxX)
				{
					continue;
				}
				if (m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i] + 1 + DownY].eType == MTC_NONATIVE)
 				{
					FindDrop = true;
					break;
				}
			}

		}
		for (int i = 0; i < 4; ++i)
		{
 			m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i] + DownY].eType = MTC_NONATIVE;
		}
		m_curblcok->y = 0;
		m_curblcok->NextBlock();
		LineCheck();
		return 1;
	}
	/////////////////////////////////////////////////////////////////////
	//�ٿ� ������Ʈ ��
	m_curblcok->DownUpdate(time);
	CurBlockIdx FindIdx;
	m_curblcok->GetCurBlockIdx(FindIdx);
	/////////////////////////////////////////////////////////////////////
	//������ �浹 ��������
	bool NonActiveBlock = false;
	for (int i = 0; i < 4; ++i)
	{
		if (FindIdx.m_blocknodeY[i] <= 0)
		{
			continue;
		}
		if (FindIdx.m_blocknodeY[i] >= (Map_maxY - 1))
		{
			NonActiveBlock = true;
			break;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		if (FindIdx.m_blocknodeY[i] <= 0 || FindIdx.m_blocknodeY[i] >= Map_maxY +1 || FindIdx.m_blocknodeX[i] <= -1 || FindIdx.m_blocknodeX[i] >= Map_maxX)
		{
			continue;
		}
		if (m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i] + 1].eType == MTC_NONATIVE)
		{
			NonActiveBlock = true;
			break;
		}
	}
	//�浿�� �������� �������� �ٽ� �÷��ش�.
	if (NonActiveBlock)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (FindIdx.m_blocknodeY[i] <= -1 || FindIdx.m_blocknodeY[i] >= Map_maxY || FindIdx.m_blocknodeX[i] <= -1 || FindIdx.m_blocknodeX[i] >= Map_maxX)
			{
				continue;
			}

			m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_NONATIVE;
		}
		m_curblcok->y = 0;
		m_curblcok->NextBlock();

		//�׸��� �浹���� �� ����üũ���ؼ� ���ٿ���ѹ�����.

		LineCheck();


		return 1;
	}
	//�浹�ƾƴ����� ������ ��Ƽ������̴�.
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			if (FindIdx.m_blocknodeY[i] <= -1 || FindIdx.m_blocknodeY[i] >= Map_maxY || FindIdx.m_blocknodeX[i] <= -1 || FindIdx.m_blocknodeX[i] >= Map_maxX)
			{
				continue;
			}
			switch (m_curblcok->eType)
			{	
			case BT_ERR:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_NONE;
				break;
			case BT_4LA:
			case BT_4LB:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_ATIVE1;
				break;
			case BT_22AA:
			case BT_22AB:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_ATIVE2;
				break;
			case BT_22BA:
			case BT_22BB:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_ATIVE3;
				break;
			case BT_22MM:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_ATIVE4;
				break;
			case BT_31LA:
			case BT_31LB:
			case BT_31LC:
			case BT_31LD:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_ATIVE5;
				break;
			case BT_31RA:
			case BT_31RB:
			case BT_31RC:
			case BT_31RD:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_ATIVE6;
				break;
			case BT_31MA:
			case BT_31MB:
			case BT_31MC:
			case BT_31MD:
				m_MapTile[FindIdx.m_blocknodeX[i]][FindIdx.m_blocknodeY[i]].eType = MTC_ATIVE7;
				break;
			default:
				break;
			}
		}
		return 1;
	}





	return 1;
}

int ClientMainViewItem::LateUpdate(float time)
{
	return 1;
}

int ClientMainViewItem::Transform(float time)
{
	return 1;
}

int ClientMainViewItem::Render(float time, HDC drow)
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
		Rectangle(drow, 5, 5, (Map_maxX*30 )+5/* 455*/, (Map_maxY * 30) + 5/* 695*/);

		(HPEN)SelectObject(drow, oldPen);

		/////////////////////////////////////////////////////////////////////////////
		HPEN BackPen = ColorManager::FindPen(_T("BackMapPen"));
		oldPen = (HPEN)SelectObject(drow, BackPen);


		POINT ReturnPT;
		MoveToEx(drow, 35, 5, &ReturnPT);
		LineTo(drow, 35, 695);
		for (int i = 1; i < Map_maxX -1; ++i)
		{
			MoveToEx(drow, (35 + (i*30)), 5, NULL);
			LineTo(drow, (35 + (i * 30)), (Map_maxY * 30) + 5);
		}
		for (int i = 1; i < Map_maxY; ++i)
		{
			MoveToEx(drow, 5, (5 + (i * 30)), NULL);
			LineTo(drow, (Map_maxX * 30) + 5, (5 + (i * 30)));
		}
		MoveToEx(drow, ReturnPT.x, ReturnPT.y, NULL);

		(HBRUSH)SelectObject(drow, oldbrush);
		(HPEN)SelectObject(drow, oldPen	);

		/////////////////////////////////////////////////////////////////////
		//���⼭ Ÿ�Ժ��� �귯���� �޾ƾ����ְ� �ؾ߁ٴ�.,

		for (int y = 0; y < Map_maxY; ++y)
		{
			for (int x = 0; x < Map_maxX; ++x)
			{
				m_MapTile[x][y].Render(drow);
			}
		}
		/////////////////////////////////////////////////////////////////////
	}

	return 1;
}

int ClientMainViewItem::DebugRender(float time)
{
	return 1;
}

int ClientMainViewItem::Collision(float time)
{
	return 1;
}

int ClientMainViewItem::Init()
{
	InputManager::CreateInput(_T("LeftMove"), VK_LEFT);
	InputManager::CreateInput(_T("RightMove"), VK_RIGHT);
	InputManager::CreateInput(_T("DownMove"), VK_DOWN);
	InputManager::CreateInput(_T("ShutDown"), VK_SPACE);
	InputManager::CreateInput(_T("Change"), VK_UP);


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
	
	m_curblcok = new CurBlock;
	return 1;
}
int ClientMainViewItem::release()
{
	delete m_curblcok;
	m_curblcok = nullptr;	
	return 1;
}

void ClientMainViewItem::SetNextBlock(int nextblock)
{
	m_curblcok->SetNextBlock(nextblock);
}

int ClientMainViewItem::GetNextBlock() const
{
	return m_curblcok->GetNextBlock();
}

int ClientMainViewItem::GetScore() const
{
	return m_iMyScore;
}

void ClientMainViewItem::GameClear(int MapIdx)
{
	m_iMyScore = 0;
	m_bEnd = 1;


	delete m_curblcok;
	m_curblcok = nullptr;
	/////////////����� ���Ҵ�

	

	//for (int y = 0; y < Map_maxY; ++y)
	//{
	//	for (int x = 0; x < Map_maxX; ++x)
	//	{
	//		m_MapTile[x][y].eType = MTC_NONE;
	//		m_MapTile[x][y].x = x;
	//		m_MapTile[x][y].y = y;
	//	}
	//}

	TCHAR pMapArr[Map_maxX][Map_maxY];
	const TCHAR* pMap = AdvanceMap::SelectMap(MapIdx);
	memcpy(pMapArr, pMap, sizeof(TCHAR)*Map_maxX*Map_maxY);
	for (int y = 0; y < Map_maxY; ++y)
	{
		for (int x = 0; x < Map_maxX; ++x)
		{
			m_MapTile[x][y].eType = (MapTileColors)pMapArr[x][y];
		}
	}



	m_curblcok = new CurBlock;
	m_bEnd = 1;
}

int ClientMainViewItem::GetEnd() const
{
	return m_bEnd;
}

void ClientMainViewItem::GameEnd()
{
	m_bEnd = 2;
	//////////////
}
//�� ���带 �����ؾ��մϴ�.
