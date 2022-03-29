#pragma once
#include "OBJItem.h"
class LobbyChatBK : private OBJItem
{
private:
	friend class Layer;

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

private:
	LobbyChatBK();
	~LobbyChatBK();
};

