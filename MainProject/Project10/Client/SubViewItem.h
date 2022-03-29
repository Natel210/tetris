#pragma once
#include "OBJItem.h"
#include "ClientIngameEnum.h"

class SubViewItem :private OBJItem
{
private:
	friend class Layer;
private:
	//필요한것..
	Maptile m_RenderMapTile[Map_maxX][Map_maxY];//출력용
	Maptile m_ChangeMapTile[Map_maxX][Map_maxY];//업데이트용
private:
	int PosX = 100;
	int PosY = 100;
public:
	void SetPos(int _x, int _y);
	int GetPosX() const;
	int GetPosY() const;
	void SendMapTile(TCHAR _pMapArr[Map_maxX][Map_maxY]);
protected:
	virtual int Input(float time) final;
	virtual int Update(float time) final;
	virtual int LateUpdate(float time) final;
	virtual int Transform(float time) final;
	virtual int Render(float time, HDC drow) final;
	virtual int DebugRender(float time) final;
	virtual int Collision(float time) final;

protected:
	virtual int Init() final;
	virtual int release() final;
private:
	SubViewItem();
	~SubViewItem();
};

