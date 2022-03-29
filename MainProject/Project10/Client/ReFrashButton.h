#pragma once
#include "WND_Button.h"
class ReFrashButton :
	public WND_Button
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
	//virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	float cooltime = 2.0f;
	bool UpdateOK = false;

public:
	bool isRefrash();


protected:
	ReFrashButton();
	~ReFrashButton();
};

