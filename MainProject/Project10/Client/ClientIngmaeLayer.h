#pragma once
#include "Layer.h"

class ClientIngmaeLayer : public Layer
{
private:
private:
	float testtime = 0.1f;
private:
	friend class ClientRoomScene;
	friend class Scene;
public:
	//static class ClientMainViewItem* pMainViewItme;
	class ClientMainViewItem* pMainViewItem = nullptr;
	class ResultItem* pResultItem = nullptr;
private:
	Tstring m_saavestr = L"";

private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int EndUp() final;
	virtual int release() final;

private:
	void SendMaps();
	void SetNextBlock(int nextblock);
	int GetNextBlock() const;

public:
	int GetScore() const;
	int GetEnd() const;
	void ClearGame(int MapIdx);
	void GameEnd();

private:
	ClientIngmaeLayer();
	~ClientIngmaeLayer();
};

