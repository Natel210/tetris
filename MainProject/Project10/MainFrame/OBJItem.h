#pragma once
#include "GameObj.h"
class OBJItem :	public GameObj
{
private:
	friend class Layer;
private:
	class Layer* pLayer = nullptr;
public:
	virtual bool GetActive();

protected:
	virtual int Input(float time) =0;
	virtual int Update(float time) = 0;
	virtual int LateUpdate(float time) = 0;
	virtual int Transform(float time);
	virtual int Render(float time, HDC drow);
	virtual int DebugRender(float time);
	virtual int Collision(float time);

protected:
	virtual int Init() = 0;
	virtual int release() = 0;
protected:
	OBJItem();
	~OBJItem();
};

