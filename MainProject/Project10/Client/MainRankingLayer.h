#pragma once
#include "Layer.h"
class MainRankingLayer : public Layer
{
private:
	friend class Scene;
private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int release() final;

private:
	MainRankingLayer();
	~MainRankingLayer();
};

