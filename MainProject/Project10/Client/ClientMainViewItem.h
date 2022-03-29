#pragma once
#include "ObjItem.h"
#include "ClientIngameEnum.h"
//#include "ClientIngmaeBlock.h"

class ClientMainViewItem : private OBJItem
{
private:
	friend class Layer;

private:
public:
	Maptile m_MapTile[Map_maxX][Map_maxY];
	class CurBlock* m_curblcok = nullptr;

private:
	void LineCheck();
private:
	int m_iMyScore = 0;
	int m_bEnd = 0;//0�̾��³�  1�� �������γ� 2�� ������ 3�� �ִ³�

protected:
	virtual int Input(float time)final;
	virtual int Update(float time)final;
	virtual int LateUpdate(float time)final;
	virtual int Transform(float time)final;
	virtual int Render(float time , HDC drow = NULL)final;
	virtual int DebugRender(float time)final;
	virtual int Collision(float time) final;

protected:
	virtual int Init() final;
	virtual int release() final;
	
public:
	void SetNextBlock(int nextblock);
	int GetNextBlock() const;
	int GetScore() const;
	void GameClear(int MapIdx);
	int GetEnd() const;
	void GameEnd();
private:
	ClientMainViewItem();
	~ClientMainViewItem();
};

