#include "stdafx.h"
#include "LobbyInfo.h"
#include "NetCore.h"
#include "Roominfo.h"

#include <algorithm>

bool LobbyInfo::CreateRoom(int idx)
{
	RoomInfo* pNewRoom = nullptr;
	pNewRoom = FindRoom(idx);
	if (pNewRoom)
	{
		return false;
	}
	pNewRoom = new RoomInfo;
	pNewRoom->m_iRoomNum = idx;
	
	m_RoomInfomap.insert(std::make_pair(idx, pNewRoom));
	//m_RoomInfomap.

	return true;
}

RoomInfo * LobbyInfo::FindRoom(int idx)
{
	std::map<int, RoomInfo *>::iterator FindIter;
	FindIter = m_RoomInfomap.find(idx);
	if (FindIter == m_RoomInfomap.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

bool LobbyInfo::DeleteRoom(int idx)
{
	std::map<int, RoomInfo  *>::iterator FindIter;
	FindIter = m_RoomInfomap.find(idx);
	if (FindIter == m_RoomInfomap.end())
	{
		return false;
	}
	delete FindIter->second;
	FindIter->second = nullptr;
	m_RoomInfomap.erase(FindIter);

	return true;
}

int LobbyInfo::EnterableRoom(int _Count)
{

	std::map<int, RoomInfo *>::iterator startter = m_RoomInfomap.begin();
	std::map<int, RoomInfo *>::iterator endter = m_RoomInfomap.end();

	if (m_RoomInfomap.size() <= _Count)
	{
		return _Count;
	}
	for (int a = 1; a < _Count; ++a)
	{
		if (endter == (++startter))
		{
			return _Count;
		}
	}


	int GetIdx = _Count;
	for (; (startter != endter) && (GetIdx <= m_RoomInfomap.size()); ++startter)
	{
		if (startter->second->m_bIsActive &&
			(startter->second->m_iLimNum > startter->second->m_iCurNum) &&
			!startter->second->IsIngame)
		{
			++GetIdx;
		}
	}

	if (m_RoomInfomap.size() == 0 || GetIdx == 0)
	{
		return -1;
	}
	else
	{
		//--startter;
		for (int i = 0 ; i < GetIdx-(_Count); ++i)
		{
			(--startter);
		}
		return (startter)->first;
	}



}

int LobbyInfo::RoomSize() const
{
	return (int)m_RoomInfomap.size();
}

void LobbyInfo::PlayerLobbyEnter(Player _pr)
{
	RoomInfo* pFindRoom = FindPlayRoom(_pr.eLoginfo.m_UniqueID);
	if (pFindRoom)
	{
		ExitRoom(pFindRoom->m_iRoomNum, _pr.eLoginfo.m_UniqueID);
	}
	m_Playermap.insert(std::make_pair(_pr.eLoginfo.m_UniqueID, _pr));
}

RoomInfo * LobbyInfo::FindIdleRoom(int PlayerNum)
{
	std::map<int, class RoomInfo *>::iterator StartIter = m_RoomInfomap.begin();
	std::map<int, class RoomInfo *>::iterator EndIter = m_RoomInfomap.end();
	for (;StartIter != EndIter; ++StartIter)
	{
		if (!StartIter->second->IsIngame)
		{ 
			continue;
		}
		for (int i = 0 ; i < 7 ; ++i)
		{
			if (PlayerNum == StartIter->second->PlayerId[i])
			{
				return StartIter->second;
			}
		}
	}
	return nullptr;
}

RoomInfo * LobbyInfo::FindPlayRoom(int PlayerNum)
{
	std::map<int, class RoomInfo *>::iterator StartIter = m_RoomInfomap.begin();
	std::map<int, class RoomInfo *>::iterator EndIter = m_RoomInfomap.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		for (int i = 0; i < 7; ++i)
		{
			if (PlayerNum == StartIter->second->PlayerId[i])
			{
				return StartIter->second;
			}
		}
	}
	return nullptr;
}

bool LobbyInfo::EnterRoom(int Room, int PlayerNum)
{
	RoomInfo* pRoom = FindRoom(Room);
	if (!pRoom)
	{
		return false;
	}
	for (int idx = 0 ; idx < 7; ++idx)
	{
		if (pRoom->PlayerId[idx] == 0)
		{
			pRoom->PlayerId[idx] = PlayerNum;
			//idx
			pRoom->m_PushMsg[idx] = _T("");

			return true;
		}
		
	}

	return false;
}

bool LobbyInfo::ExitRoom(int Room, int PlayerNum)
{
	RoomInfo* pRoom = FindRoom(Room);
	if (!pRoom)
	{
		return false;
	}
	for (int idx = 0; idx < 7; ++idx)
	{
		if (pRoom->PlayerId[idx] == PlayerNum)
		{
			pRoom->PlayerId[idx] = 0;
			pRoom->PlayerId[idx] = -1;
			pRoom->PlayerReady[idx] = 0;
			pRoom->PlayerGamescore[idx] = -1;
			pRoom->PlayerDeath[idx] = -1;
			for (int sec = 0; sec < 10; ++sec)
			{
				for (int thr = 0; thr < 23; ++thr)
				{
					pRoom->MapInfo[idx][sec][thr] = 0;
				}
			}
			pRoom->m_PushMsg[idx] = _T("");
			--pRoom->m_iCurNum;
			break;
		}
	}

	if (pRoom->m_iCurNum = 0)
	{
		DeleteRoom(pRoom->m_iRoomNum);

		//m_RoomInfomap.erase(pRoom->m_iRoomNum);
	}

	m_Playermap[PlayerNum].ePlayerStates.RoomNum = -1;
	m_Playermap[PlayerNum].ePlayerStates.States = playlobby;
	return true;
}

bool LobbyInfo::isPlayer(int PlayerNum)
{
	std::unordered_map<int, Player>::iterator StartIter = m_Playermap.find(PlayerNum);
	if (StartIter == m_Playermap.end())
	{
		return false;
	}

	return true;
}

Player LobbyInfo::FindPlayer(int PlayerNum)
{

	std::unordered_map<int, Player>::iterator StartIter = m_Playermap.find(PlayerNum);
	if (StartIter == m_Playermap.end())
	{
		return Player();
	}

	return StartIter->second;
}

void LobbyInfo::ClearRooms()
{
	std::map<int, RoomInfo *>::iterator startiter = m_RoomInfomap.begin();
	std::map<int, RoomInfo *>::iterator enditer = m_RoomInfomap.end();
	for (; startiter != enditer;)
	{
		if (startiter->second->m_iCurNum == 0)
		{
			startiter = m_RoomInfomap.erase(startiter);
		}
		else
		{
			++startiter;
		}
	}

}

LobbyInfo::LobbyInfo()
{
	m_RoomInfomap.clear();
}


LobbyInfo::~LobbyInfo()
{
	std::map<int, class RoomInfo *>::iterator StartIter = m_RoomInfomap.begin();
	std::map<int, class RoomInfo *>::iterator EndIter = m_RoomInfomap.end();
	for ( ; StartIter != EndIter; )
	{
		delete StartIter->second;
		StartIter->second = nullptr;
		StartIter = m_RoomInfomap.erase(StartIter);

	}
	m_RoomInfomap.clear();
}
