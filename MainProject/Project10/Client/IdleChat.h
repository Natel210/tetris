#pragma once
#include "WND_LISTBOX.h"
class IdleChat : public WND_LISTBOX
{
private:
	friend class Layer;
	friend class SideView;
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
	//virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) final;

private:
	float ChatUpdate = 0.2f;

protected:
	IdleChat();
	~IdleChat();
};

