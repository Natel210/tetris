#pragma once
#include "WND_STATIC.h"
// �� ����ƽ�̴�... 
// �׸��� ���������� �ð� ������־�߰ڴ�.....
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

