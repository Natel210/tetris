#pragma once
#include "WND_STATIC.h"
class StaticRankTitle :
	public WND_STATIC
{
private:
	friend class Layer;
protected:
	virtual int Input(float time) final;
	virtual int Update(float time) final;

protected:
	virtual int Init() final;
	virtual int release() final;
	//virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	StaticRankTitle();
	~StaticRankTitle();
};

