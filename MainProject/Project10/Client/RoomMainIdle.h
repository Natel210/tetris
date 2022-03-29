#pragma once
#include "Layer.h"



//메인은 같아....


class RoomMainIdle : public Layer
{
private:
	friend class Scene;
	friend class ClientRoomScene;
private:
	class ReadyButton* pReady = nullptr;
	class ClientMainidleItem* pMainViewItem = nullptr;
private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int EndUp() final;
	virtual int release() final;

public:
	int GetMapIDX() const;
	void SetMapIDX(int _IDX);
	bool GetReady() const;
	void ResetReady();
public:
	RoomMainIdle();
	~RoomMainIdle();
};

