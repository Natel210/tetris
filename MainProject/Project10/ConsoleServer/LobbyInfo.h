#pragma once
#include <unordered_map>
#include <map>
#include "NetCore.h"
//#include "Roominfo.h"
//class NetCore;
class LobbyInfo
{
private:
	friend static bool NetCore::CreateLobby(int idx);
	friend static bool NetCore::DeleteLobby(int idx);
private:
	//방의 정보를 알고 있어야 겠다.
	std::map<int, class RoomInfo *> m_RoomInfomap;
	//해당 로비에 위치한 플레이어들을 알아야 겠다.
	std::unordered_map<int, Player> m_Playermap;
public:
	bool CreateRoom(int idx);
	class RoomInfo* FindRoom(int idx);
	bool DeleteRoom(int idx);
	int EnterableRoom(int _Count);
	int RoomSize() const;
public:
	std::unordered_map<int, Player> getLobbyPlayers()
	{
		return m_Playermap;
	}


	const std::map<int, class RoomInfo *>* getLobbyRooms()
	{
		return &m_RoomInfomap;
	}


	void PlayerLobbyEnter(Player _pr);


	inline void PlayerLobbyleave(Player _pr)
	{
		m_Playermap.erase(_pr.eLoginfo.m_UniqueID);
	}


public:
	class RoomInfo* FindIdleRoom(int PlayerNum);
	class RoomInfo* FindPlayRoom(int PlayerNum);
	bool EnterRoom(int Room,int PlayerNum);
	bool ExitRoom(int Room, int PlayerNum);

	bool isPlayer(int PlayerNum);
	Player FindPlayer(int PlayerNum);

	void ClearRooms();

private:
	LobbyInfo();
	~LobbyInfo();
};

