#pragma once
#include "WND_STATIC.h"
// 넌 스테틱이다... 
// 그리고 독립적으로 시간 계산해주어야겠다.....
class inGameTimers : public WND_STATIC
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
public:
	inGameTimers();
	~inGameTimers();
};

