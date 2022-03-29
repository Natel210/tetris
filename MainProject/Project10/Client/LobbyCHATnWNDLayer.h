#pragma once
#include "Layer.h"

class LobbyCHATnWNDLayer : public Layer
{
private:
	friend class Scene;
private:
	class ChatEditBarItem* pChatBarItem;
private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int release() final;

private:
	LobbyCHATnWNDLayer();
	~LobbyCHATnWNDLayer();
};

