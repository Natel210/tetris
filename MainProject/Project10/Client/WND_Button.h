#pragma once
#include "WNDItem.h"

class WND_Button :	public WNDItem
{
private:
	friend class Layer;
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

private:
	int m_bCurState = false;
	Tstring	m_strText = _T("");
public:
	inline int getState()const
	{
		return m_bCurState;
	}


protected:
	bool m_bDrowText = false;		// 텍스트가 갱신되어야 할지 말지.
	int m_iCollButton = false;		// 버튼이 눌러졌는 지 안눌러 졌는지.
	bool m_bNextWork = false;		// 다음일을 수행해야할지 안해야할지.

protected:
	void SetText(const TCHAR* str);
	void Setidx(int str);
	const Tstring GetText() const;

protected:
	WND_Button();
	virtual ~WND_Button() = 0;
};

