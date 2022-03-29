#pragma once
#include "WND_LISTBOX.h"
#include "ClientHeader.h"

class LobbyPlayerlist : public WND_LISTBOX
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

private:
	int CurSel = 0;
	float m_fUpdateCount = 3.0f;
	bool is_Update = false;



	//std::vector<Player> m_CurLobbyPlayervec;
	std::list<HWND> m_PopupPlayerinfolist;

public:



public:
	virtual LRESULT CALLBACK LobbyPlayerlist::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	//std::vector

protected:
	LobbyPlayerlist();
	~LobbyPlayerlist();
};

