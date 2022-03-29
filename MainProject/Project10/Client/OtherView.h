#pragma once
#include "Layer.h"
class OtherView : public Layer
{
private:
	friend class Scene;
	friend class ClientRoomScene;
public:
private:
	class SubViewItem* ppSubView[6];
	class ReadyStatic* ppSubViewReady[6];

private:
	virtual int Init() final;
	virtual int LayerUpdate(float time) final;
	virtual int StartUp() final;
	virtual int EndUp() final;
	virtual int release() final;

public:
	void SetOtherReady(int _Readys[6]);
	void SetOtherMap(int IDX);

public:
	OtherView();
	~OtherView();
};

