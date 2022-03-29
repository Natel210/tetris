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
	//혹시 모를 죽음 체크
	for (int x = 0; x < Map_maxX; ++x)
	{
		if (m_MapTile[x][1].eType == MTC_NONATIVE)
		{
			//게임 오버 구간 처리를 해야겠습니다.
			//////////////
			//MessageBox(ClientCore::mainhWnd, L"죽었습니다.", L"죽었습니다.", MB_OK);
			m_bEnd = 2;

		}
		
	}
	std::vector<int> checklinevec;
	for (int y = 0; y < Map_maxY; ++y)
	{
		bool clear = true;
		//각자의 라인을 모두채크한다.
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
			//지워지는 인댁스번째.

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
	//이전위치를 알아내는게 중요할거같다.
	//이전 위치 초기화.
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
	//이동 조작후 변경사항
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
			//나의 중심점과 저기의 위치에 따라서 나눌것이다.
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
	//다운 업데이트 후
	m_curblcok->DownUpdate(time);
	CurBlockIdx FindIdx;
	m_curblcok->GetCurBlockIdx(FindIdx);
	/////////////////////////////////////////////////////////////////////
	//마지막 충돌 여부판정
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
	//충동을 했음으로 꺼버리고 다시 올려준다.
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

		//그리고 충돌했을 때 라인체크를해서 업다운시켜버린다.

		LineCheck();


		return 1;
	}
	//충돌아아님으로 아직은 엑티브상테이다.
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

	//이아이템은 그리기만 하면될거같은데? 가아니고 노드를 인제 그려줘야겠죠.
	if (drow)
	{
		/////////////////////////////////////////////////////////////////////
		//라인용
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
		//내부의 판들
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
		//여기서 타입별로 브러쉬를 받아쓸수있게 해야곘다.,

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


	//일단은 틀을 그린다..
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
	/////////////지우고 재할당

	

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
//저 엔드를 수정해야합니다.
