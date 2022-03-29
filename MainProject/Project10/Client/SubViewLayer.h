#pragma once
//여기서는 받아들이는 정보를 기반으로 업테이트를 실시한다.
#include "Layer.h"

class SubViewLayer : public Layer
{
private:
	friend class Scene;
	friend class ClientRoomScene;
private:
	class SubViewItem* SubView[6];
	class ResultItem* SubResult[6];
	float UpdateTime = 0.1f;

private:
	int issurverUptime = 0;
	float issurvertime = 0.0f;



public:
	//bool RecvMap();

private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int EndUp() final;
	virtual int release() final;

private:
	void RecvMaps();
public:
	SubViewLayer();
	~SubViewLayer();
};

