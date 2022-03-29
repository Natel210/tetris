#pragma once
#include <commctrl.h>

#include "WNDItem.h"
#include "ClientIngameEnum.h"

class RankingListItem : public WNDItem
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
	virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) final;

public:
	//void SetText(const TCHAR* str);
	//const Tstring GetText() const;


private:


private:
	//�¸�, �й�, ���̽��ھ�, ���� ����
	std::vector<RankSaveList> m_saveScoresvec;
private:
	enum ButtonState
	{
		BS_ERR,
		BS_NO,
		BS_NAME,
		BS_SCORE,
		BS_RATE,
		BS_WINS
	};
	ButtonState m_eButtonType = BS_ERR;
	bool m_bFirstPush = false;
	bool m_bColSort = false;
	int m_iListSizeCounter = 10;
private:
	void SortList(ButtonState type);


private:
	int UpdateList();

public:
	int UpdatePlayerStates();//�̰ɿ�û�ϸ� �������� �޾ƿ;��Ѵ�,

	int ExpandFinds(int num);//���̾�� �ϴ� ���Ÿ�.
	int ReduceFinds(int num);//���̾�� �ϴ� ���Ÿ�.


protected:
RankingListItem();
~RankingListItem();
};

