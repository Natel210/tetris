#pragma once
#include "WND_STATIC.h"
class IdleTimeBox : public WND_STATIC
{
private:
	friend class Layer;
	friend class SideView;
protected:
	virtual int Input(float time);
	virtual int Update(float time);
//	virtual int LateUpdate(float time);
//	virtual int Transform(float time);
//	virtual int Render(float time, HDC drow);
//	virtual int DebugRender(float time);
//	virtual int Collision(float time);

protected:
	virtual int Init();
	virtual int release();
	//virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	IdleTimeBox();
	~IdleTimeBox();
};

