#pragma once
#include "Scene.h"

class ClientLogInScene : public Scene
{
	friend class FrameCore;
private:
	class MainLogInLayer* pMainLoginLayer = nullptr;

protected:
	virtual int Init() final;
	virtual int release() final;

protected:
	ClientLogInScene();
	~ClientLogInScene();
};

