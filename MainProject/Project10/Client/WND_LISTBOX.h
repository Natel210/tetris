#pragma once
#include "WNDItem.h"
class WND_LISTBOX : public WNDItem
{
private:
	friend class Layer;
protected:
	bool m_bContKey = false;
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


protected:
	virtual int GetSel() const;
	virtual void SetSel(int Sel);
protected:
	virtual int AddString(const TCHAR* pstr) final;
	//virtual int aAddString(const TCHAR* pstr) final;
	virtual int AllClear() final;
protected:
	WND_LISTBOX();
	~WND_LISTBOX();
};

