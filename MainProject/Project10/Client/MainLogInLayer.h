#pragma once
#include "Layer.h"

class MainLogInLayer : public Layer
{
private:
	friend class Scene;
private:
	class LoginID* pLoginID;
	class LoginPW* pLoginPW;
	class LoginToLobby* pLoginMove;
private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int release() final;

private:
	MainLogInLayer();
	~MainLogInLayer();
};

