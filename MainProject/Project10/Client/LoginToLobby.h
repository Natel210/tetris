#pragma once
#include "WND_Button.h"
class LoginToLobby :	public WND_Button
{
private:
	friend class Layer;
private:
	Tstring m_Id = _T("");
	Tstring m_Pw = _T("");
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
	virtual int StartUp() final;
	virtual int release() final;
	//virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
public:
	void LoginSet(const Tstring& Id, const Tstring& pw);
protected:
	LoginToLobby();
	~LoginToLobby();
};

