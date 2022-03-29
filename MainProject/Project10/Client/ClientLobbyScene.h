#pragma once
#include "Scene.h"

class ClientLobbyScene : public Scene
{
	friend class FrameCore;
private:
	class MainLobbyLayer* pMainLobbyLayer = nullptr;
protected:
	virtual int Init() final;
	virtual int release() final;

protected:
	ClientLobbyScene();
	~ClientLobbyScene();
};

