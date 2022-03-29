#pragma once
#include "WNDItem.h"
class WND_EditBox : public WNDItem
{
private:
	friend class Layer;
protected:
	bool isEnterCntl = false;

protected:
	virtual int Input(float time) = 0;
	virtual int Update(float time) = 0;
	virtual int LateUpdate(float time) override;
	virtual int Transform(float time) override;
	virtual int Render(float time, HDC drow) override;
	virtual int DebugRender(float time) override;
	virtual int Collision(float time) override;

protected:
	virtual int Init() = 0;
	virtual int release() = 0;
	virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
	void SetText(const TCHAR* str);
	const Tstring GetText() const;
	void SetFocusBox();
	bool GetFocusBox() const;
protected:



protected:
	WND_EditBox();
	~WND_EditBox();
};

