#pragma once
#include "WND_STATIC.h"
class ResultItem : public WND_STATIC
{
private:
	friend class Layer;
	friend class SubViewLayer;
	friend class ClientIngmaeLayer;
protected:
	virtual int Input(float time);
	virtual int Update(float time);
	//	virtual int LateUpdate(float time);
	//	virtual int Transform(float time);
	//	virtual int Render(float time, HDC drow);
	//	virtual int DebugRender(float time);
	//	virtual int Collision(float time);

private:

public:
	//int GetReady() const;
	//void SetReady(int readys);
	void SetBackgraoundColor(COLORREF _Color);
protected:
	virtual int Init();
	virtual int release();
	//virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	ResultItem();
	~ResultItem();
};

