#pragma once
#include "OBJItem.h"
#include "ClientIngameEnum.h"

class IngameLogNextBlockItem : public OBJItem
{
private:
	friend class Layer;
protected:
	virtual int Input(float time) final;
	virtual int Update(float time) final;
	virtual int LateUpdate(float time) final;
	virtual int Transform(float time) final;
	virtual int Render(float time, HDC drow)final;
	virtual int DebugRender(float time)final;
	virtual int Collision(float time)final;

protected:
	virtual int Init() final;
	virtual int release() final;
private:
	Maptile m_NextViewTile[4][4] = { Maptile (),};
	int m_iNextIDX = 0;

public:
	void SetNextNode(int _idx)
	{
		m_iNextIDX = _idx;
	}


protected:
	IngameLogNextBlockItem();
	~IngameLogNextBlockItem();
};

