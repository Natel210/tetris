#pragma once
#include "WND_Button.h"
class ReadyButton :
	public WND_Button
{
private:
	friend class Layer;
	friend class RoomMainIdle;
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
public:
	inline bool GetReady() const
	{
		return m_bIsReady;
	}
private:
	bool m_bIsReady = false;
	bool m_bChanged = false;
protected:
	ReadyButton();
	~ReadyButton();
};

