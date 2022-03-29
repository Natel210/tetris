#pragma once
#include "WND_EditBox.h"
class LoginPW : public WND_EditBox
{
private:
	friend class Layer;
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

protected:
	LoginPW();
	~LoginPW();
};

