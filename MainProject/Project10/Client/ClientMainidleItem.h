#pragma once
#include "OBJItem.h"
#include "ClientIngameEnum.h"

class ClientMainidleItem : private OBJItem
{
private:
	friend class Layer;

private:
public:
	Maptile m_MapTile[Map_maxX][Map_maxY];
	class CurBlock* m_curblcok;
	int m_iMapIdx = 0;


protected:
	virtual int Input(float time)final;
	virtual int Update(float time)final;
	virtual int LateUpdate(float time)final;
	virtual int Transform(float time)final;
	virtual int Render(float time, HDC drow = NULL)final;
	virtual int DebugRender(float time)final;
	virtual int Collision(float time) final;

protected:
	virtual int Init() final;
	virtual int release() final;

public:
	int GetMapIDX() const
	{
		return m_iMapIdx;
	}
	void SetMapIDX(int _IDX)
	{
		m_iMapIdx = _IDX;
		//업데이트도 해야죵
		MapUpdate();
	}

private:
	void MapUpdate();

private:
	ClientMainidleItem();
	~ClientMainidleItem();
};

