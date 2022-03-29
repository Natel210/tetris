#pragma once
#include "WNDItem.h"
#include "ClientIngameEnum.h"

class IngameLogScoreItem : public WNDItem
{
private:
	friend class Layer;
	friend class ClientIngameLogLayer;
protected:
	virtual int Input(float time) final;
	virtual int Update(float time) final;
	virtual int LateUpdate(float time) final;
	virtual int Transform(float time) final;
	virtual int Render(float time, HDC drow)final;
	virtual int DebugRender(float time)final;
	virtual int Collision(float time)final;

protected:
	virtual int Init() final;
	virtual int release() final;

	virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


private:

private:
	std::list<HWND> m_PopupPlayerinfolist;
	float times = 0.5f;
	std::vector<IngameScore> m_Scorevec;
	int CurSel = 0;

	//bool EXIT = false;
	//bool DrowText = false;
	//int CallButton = 0;
public:
	//bool Init(IngameScore _1p, IngameScore _2p = IngameScore(), IngameScore _3p = IngameScore(), IngameScore _4p = IngameScore(), IngameScore _5p = IngameScore(), IngameScore _6p = IngameScore(), IngameScore _7p = IngameScore());
	void SetScore(IngameScoreSurver pScroesp[7]);
protected:
	IngameLogScoreItem();
	~IngameLogScoreItem();
};

