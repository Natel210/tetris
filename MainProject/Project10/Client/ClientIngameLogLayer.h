#pragma once
#include "Layer.h"
#include "ClientIngameEnum.h"

class ClientIngameLogLayer : public Layer
{
private:
	friend class Scene;
	friend class ClientRoomScene;
private:
	class IngameLogExitRateItem* m_pExits = nullptr;
	class IngameLogNextBlockItem* m_pNextBolck = nullptr;
	class IngameLogScoreItem* m_pScores = nullptr;
	class IngameLogTimerItme* m_pTimer = nullptr;
public:

private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int EndUp() final;
	virtual int release() final;

private:
	bool m_bReturnLobby = false;
private:
	inline bool ReturnLobby() const
	{
		return m_bReturnLobby;
	}

public:
	void SetNextNode(int _idx);
	void SetScore(IngameScoreSurver pScroesp[7]);
	//int GetScore() const;


public:
	ClientIngameLogLayer();
	~ClientIngameLogLayer();
};

