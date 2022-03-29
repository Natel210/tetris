#include "stdafx.h"
#include "ClientIngmaeBlock.h"
#include "input/Input.h"

void CurBlockIdx::Idx()
{
	x1 = m_blocknodeX[0];
	x2 = m_blocknodeX[1];
	x3 = m_blocknodeX[2];
	x4 = m_blocknodeX[3];

	y1 = m_blocknodeY[0];
	y2 = m_blocknodeY[1];
	y3 = m_blocknodeY[2];
	y4 = m_blocknodeY[3];
}

void CurBlock::ChangeBlock()
{
	switch (eType)
	{
	case BT_4LA:
		eType = BT_4LB;
		break;
	case BT_4LB:
		eType = BT_4LA;
		break;
	case BT_22AA:
		eType = BT_22AB;
		break;
	case BT_22AB:
		eType = BT_22AA;
		break;
	case BT_22BA:
		eType = BT_22BB;
		break;
	case BT_22BB:
		eType = BT_22BA;
		break;
	case BT_31LA:
		eType = BT_31LB;
		break;
	case BT_31LB:
		eType = BT_31LC;
		break;
	case BT_31LC:
		eType = BT_31LD;
		break;
	case BT_31LD:
		eType = BT_31LA;
		break;
	case BT_31RA:
		eType = BT_31RB;
		break;
	case BT_31RB:
		eType = BT_31RC;
		break;
	case BT_31RC:
		eType = BT_31RD;
		break;
	case BT_31RD:
		eType = BT_31RA;
		break;
	case BT_31MA:
		eType = BT_31MB;
		break;
	case BT_31MB:
		eType = BT_31MC;
		break;
	case BT_31MC:
		eType = BT_31MD;
		break;
	case BT_31MD:
		eType = BT_31MA;
		break;
	default:
		break;
	}
}

void CurBlock::ReChangeBlock()
{
	switch (eType)
	{
	case BT_4LA:
		eType = BT_4LB;
		break;
	case BT_4LB:
		eType = BT_4LA;
		break;
	case BT_22AA:
		eType = BT_22AB;
		break;
	case BT_22AB:
		eType = BT_22AA;
		break;
	case BT_22BA:
		eType = BT_22BB;
		break;
	case BT_22BB:
		eType = BT_22BA;
		break;
		//////////
	case BT_31LA:
		eType = BT_31LD;
		break;
	case BT_31LB:
		eType = BT_31LA;
		break;
	case BT_31LC:
		eType = BT_31LB;
		break;
	case BT_31LD:
		eType = BT_31LC;
		break;
	case BT_31RA:
		eType = BT_31RD;
		break;
	case BT_31RB:
		eType = BT_31RA;
		break;
	case BT_31RC:
		eType = BT_31RB;
		break;
	case BT_31RD:
		eType = BT_31RC;
		break;
	case BT_31MA:
		eType = BT_31MD;
		break;
	case BT_31MB:
		eType = BT_31MA;
		break;
	case BT_31MC:
		eType = BT_31MB;
		break;
	case BT_31MD:
		eType = BT_31MC;
		break;
	default:
		break;
	}
}

void CurBlock::SetNextBlock(int nextblock)
{
	eNextType = nextblock;
}

int CurBlock::GetNextBlock() const
{
	return eNextType;
}

void CurBlock::NextBlock()
{
	//if (eNextType == BT_ERR)
	//{
	//	//에러나면 랜덤입니다.
	//	eType = (BlockType)(rand() % BT_31MD +1);
	//	eNextType = BT_ERR;
	//}
	//else
	{
		eType = (BlockType)eNextType;
		eNextType = BT_ERR;
	}
}

BlockState CurBlock::MoveUpdate(float time)
{
	//바뀌는게 최우선
	if (KEY_PUSH(_T("Change")))
	{
		ChangeBlock();
		m_fKeyStayCount = 0.0f;
		return BKS_CHANGE;
	}
	else if (KEY_STAY(_T("Change")))
	{
		if (m_fKeyStayCount > 0.3f)
		{
			ChangeBlock();
			m_fKeyStayCount -= 0.1f;
			return BKS_CHANGE;
		}
		else
		{
			m_fKeyStayCount += time;
		}

	}
	else if (KEY_UP(_T("Change")))
	{
		m_fKeyStayCount = 0.0f;
	}
	////////////////////////////////////////////////////

	if (KEY_PUSH(_T("LeftMove")))
	{
		x -= 1;
		m_fKeyStayCount = 0.0f;
		return BKS_LEFT;
	}
	else if (KEY_STAY(_T("LeftMove")))
	{
		if (m_fKeyStayCount > 0.3f)
		{
			x -= (time * 10.0f);
			return BKS_LEFT;
		}
		else
		{
			m_fKeyStayCount += time;
		}

	}
	else if (KEY_UP(_T("LeftMove")))
	{
		x = (float)((int)x);
		m_fKeyStayCount = 0.0f;
	}

	////////////////////////////////////////////////////
	if (KEY_PUSH(_T("RightMove")))
	{
		x += 1;
		m_fKeyStayCount = 0.0f;
		return BKS_RIGHT;
	}
	else if (KEY_STAY(_T("RightMove")))
	{
		if (m_fKeyStayCount > 0.3f)
		{
			x += (time * 10.0f);
			return BKS_RIGHT;
		}
		else
		{
			m_fKeyStayCount += time;
		}

	}
	else if (KEY_UP(_T("RightMove")))
	{
		x = (float)((int)x);
		m_fKeyStayCount = 0.0f;
	}

	////////////////////////////////////////////////////
	if (KEY_PUSH(_T("DownMove")))
	{
		y += 1;
		m_fDownTime = 1.0f;
		m_fKeyStayCount = 0.0f;
		return BKS_DOWN;
	}
	else if (KEY_STAY(_T("DownMove")))
	{
		if (m_fKeyStayCount > 0.3f)
		{
			y += (time * 10.0f);
			m_fDownTime = 1.0f;
			return BKS_DOWN;
		}
		else
		{
			m_fKeyStayCount += time;
		}

	}
	else if (KEY_UP(_T("DownMove")))
	{
		y = (float)((int)y);
		m_fKeyStayCount = 0.0f;
	}




	if (KEY_PUSH(_T("ShutDown")))
	{
		//인제 충돌을하러떠납니다.
		return BKS_SHUTDOWN;
	}

	return BKS_NONE;
}


void CurBlock::DownUpdate(float time)
{
	if (m_fDownTime < 0)
	{
		++y;
		//첫번째
		//y가 맥스가된다면?
		m_fDownTime = 1.0f;
	}
	else
	{
		m_fDownTime -= time;
	}
}

void CurBlock::GetCurBlockIdx(CurBlockIdx & _block)
{
	switch (eType)
	{
	case BT_4LA:
	{
		_block.m_blocknodeX[0] = (int)x - 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x + 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x + 2;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_4LB:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y - 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y + 1;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y + 2;
	}
	break;
	case BT_22AA:
	{
		_block.m_blocknodeX[0] = (int)x - 1;
		_block.m_blocknodeY[0] = (int)y - 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y - 1;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x + 1;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_22AB:
	{
		_block.m_blocknodeX[0] = (int)x + 1;
		_block.m_blocknodeY[0] = (int)y - 1;

		_block.m_blocknodeX[1] = (int)x + 1;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y + 1;
	}
	break;
	case BT_22BA:
	{
		_block.m_blocknodeX[0] = (int)x - 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y - 1;

		_block.m_blocknodeX[3] = (int)x + 1;
		_block.m_blocknodeY[3] = (int)y - 1;
	}
	break;
	case BT_22BB:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y - 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x + 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x + 1;
		_block.m_blocknodeY[3] = (int)y + 1;
	}
	break;
	case BT_22MM:
	{
		_block.m_blocknodeX[0] = (int)x - 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x - 1;
		_block.m_blocknodeY[2] = (int)y + 1;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y + 1;
	}
	break;
	case BT_31LA:
	{
		_block.m_blocknodeX[0] = (int)x - 1;
		_block.m_blocknodeY[0] = (int)y ;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y + 1;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y + 2;
	}
	break;
	case BT_31LB:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y - 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x - 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x - 2;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_31LC:
	{
		_block.m_blocknodeX[0] = (int)x + 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y - 1;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y - 2;
	}
	break;
	case BT_31LD:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y + 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x + 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x + 2;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_31RA:
	{
		_block.m_blocknodeX[0] = (int)x + 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y + 1;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y + 2;
	}
	break;
	case BT_31RB:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y + 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x - 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x - 2;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_31RC:
	{
		_block.m_blocknodeX[0] = (int)x - 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y - 1;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y - 2;
	}
	break;
	case BT_31RD:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y - 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x + 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x + 2;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_31MA:
	{
		_block.m_blocknodeX[0] = (int)x - 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y - 1;

		_block.m_blocknodeX[3] = (int)x + 1;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_31MB:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y - 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x + 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y + 1;
	}
	break;
	case BT_31MC:
	{
		_block.m_blocknodeX[0] = (int)x + 1;
		_block.m_blocknodeY[0] = (int)y;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x;
		_block.m_blocknodeY[2] = (int)y + 1;

		_block.m_blocknodeX[3] = (int)x - 1;
		_block.m_blocknodeY[3] = (int)y;
	}
	break;
	case BT_31MD:
	{
		_block.m_blocknodeX[0] = (int)x;
		_block.m_blocknodeY[0] = (int)y + 1;

		_block.m_blocknodeX[1] = (int)x;
		_block.m_blocknodeY[1] = (int)y;

		_block.m_blocknodeX[2] = (int)x - 1;
		_block.m_blocknodeY[2] = (int)y;

		_block.m_blocknodeX[3] = (int)x;
		_block.m_blocknodeY[3] = (int)y - 1;
	}
	break;
	default:
		break;
	}

	_block.Idx();
}
