#pragma once
#include "WND_BUTTON.h"
#include "ClientIngameEnum.h"

class StaticRoomBox : public WND_Button
{
private:
	friend class Layer;
protected:
	virtual int Input(float time) final;
	virtual int Update(float time) final;
	virtual int LateUpdate(float time) final;
	virtual int Transform(float time) final;
	virtual int Render(float time, HDC drow) final;
	virtual int DebugRender(float time) final;
	virtual int Collision(float time) final;

protected:
	virtual int Init() final;
	virtual int release() final;

private:
	bool m_bSelects = false;

private:
	RoomInfo m_eRoominfo;

private:
	void StateDrawText();
public:
	void CreateRoom(const TCHAR* _RoomName, int LimNum = -1, bool Publics = true);
	void SetStateRoom(const TCHAR* _RoomName, int LimNum = -1, int CurNum = -1, bool Publics = true);
	void SetStateRoom(const RoomInfoLobby& roominfos);
	void DelRoom();
	void SetGamesRoom(bool games);

	RoomInfo inline GetRoomInfo() const
	{
		return m_eRoominfo;
	}

	////±â´Ù·ÁºÁ
	//void UpdateRoom(int LimNum);
	//void PushUnit();

public:
	inline int GetSelect() const
	{
		if (!m_eRoominfo.m_bIsActive)
		{
			return false;
		}
		return m_bSelects;
	}
	inline void SetSelect(bool bools)
	{
		m_bSelects = bools;
		StateDrawText();
	}

protected:
	StaticRoomBox();
	~StaticRoomBox();
};

