#pragma once
#include "ClientIngameEnum.h"

#define StartBlockType BT_4LA  

struct  CurBlockIdx
{
	int m_blocknodeX[4] = { 0, };
	int m_blocknodeY[4] = { 0, };
	int x1, x2, x3, x4 = 0;
	int y1, y2, y3, y4 = 0;
	void Idx();
};

class CurBlock
{
private:
	friend class ClientMainViewItem;
public:
	BlockType eType = StartBlockType;
public:
	float x = 10;
	float y = 0;
	float m_fDownTime = 0.5f;
	float m_fKeyStayCount = 0.0f;

public:
	void ChangeBlock();
	void ReChangeBlock();
private:
	int eNextType = BT_ERR;

private:
	void SetNextBlock(int nextblock);
	int GetNextBlock() const;
public:
	void NextBlock();
	BlockState MoveUpdate(float time);
	void DownUpdate(float time);
	void GetCurBlockIdx(CurBlockIdx& _block);
	
};