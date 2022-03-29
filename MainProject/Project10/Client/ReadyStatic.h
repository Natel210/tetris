#pragma once
#include "WND_STATIC.h"
class ReadyStatic : public WND_STATIC
{
private:
	friend class Layer;
	friend class OtherView;
protected:
	virtual int Input(float time);
	virtual int Update(float time);
	//	virtual int LateUpdate(float time);
	//	virtual int Transform(float time);
	//	virtual int Render(float time, HDC drow);
	//	virtual int DebugRender(float time);
	//	virtual int Collision(float time);

private:
	bool m_bchanged = false;
	int m_iplayerready = 0;

	//float m_testtime = 3.0f;
	//bool m_btest = false;
public:
	int GetReady() const;
	void SetReady(int readys);

protected:
	virtual int Init();
	virtual int release();
	//virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

protected:
	ReadyStatic();
	~ReadyStatic();
};

