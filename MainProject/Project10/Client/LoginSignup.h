#pragma once
#include "WND_Button.h"
class LoginSignup : public WND_Button
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
	LoginSignup();
	~LoginSignup();
};

