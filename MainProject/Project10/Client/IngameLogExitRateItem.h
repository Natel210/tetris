#pragma once
#include "WNDItem.h"

class IngameLogExitRateItem : public WNDItem
{
private:
	friend class Layer;
	friend class ClientIngameLogLayer;
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

	virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	bool m_bEXIT = false;
	bool DrowText = false;
	int CallButton = 0;


protected:
	IngameLogExitRateItem();
	~IngameLogExitRateItem();
};

