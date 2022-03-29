#pragma once
#include "Layer.h"
class SideView : public Layer
{
private:
	friend class Scene;
	friend class ClientRoomScene;
public:

	

private:
	class RoomToRobby* pRooomToRobby = nullptr;
	
	class IdleTimeBox* pIdleTimeBox = nullptr;
	class IdleTimerleft* pIdleTimerleft = nullptr;
	class IdleTimerRight* pIdleTimerRight = nullptr;

	class IdlePlayerList* pIdlePlayerList = nullptr;

	class IdleChat* pIdleChat = nullptr;
	class IdleChatBar* pIdleChatBar = nullptr;

private:
	bool m_bchanged = true;

private:
	float m_fTimeUpdate = 0.1f;

private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int EndUp() final;
	virtual int release() final;


private:
	//void Update
	void SetPrevExit(bool _Exit);
public:
	SideView();
	~SideView();
};

