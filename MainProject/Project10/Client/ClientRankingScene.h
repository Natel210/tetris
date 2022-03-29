#pragma once
#include "Scene.h"

class ClientRankingScene : public Scene
{
	friend class FrameCore;
private:

	class MainRankingLayer* pMainLankingLayer = nullptr;
protected:
	virtual int Init() final;
	virtual int release() final;




protected:
	ClientRankingScene();
	~ClientRankingScene();
};

