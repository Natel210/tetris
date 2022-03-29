#pragma once
#include "Layer.h"

//���� �ٷ�� �κ��� �漱��â�� �ٷ�ϴ�.


class MainLobbyLayer : public Layer
{
private:
	friend class Scene;
private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int release() final;

private:
	int m_uSelectNum = -1;
	int m_iSearchstartpage = 1; //�ϴ���..
	float m_fSearchRate = 1.0f;
	bool m_bSearchMode = false;

private:
	class StaticRoomBox* pStaticArr[9] = {nullptr, };
	//class StaticRoomBox* pStatic2;
	//class StaticRoomBox* pStatic3;
	//class StaticRoomBox* pStatic4;
	//class StaticRoomBox* pStatic5;
	//class StaticRoomBox* pStatic6;
	//class StaticRoomBox* pStatic7;
	//class StaticRoomBox* pStatic8;
	//class StaticRoomBox* pStatic9;

private:
	MainLobbyLayer();
	~MainLobbyLayer();
};

