#include "stdafx.h"
#include "NetCore.h"
#include "LobbyInfo.h"
#include "RoomInfo.h"
#include <algorithm>
#include <iostream>

//내림차순
static bool SortPlayer(Player _src, Player _dest)
{
	if (_src.eLoginfo.m_ID[0] ==0 || _src.eLoginfo.m_ID[0] == -52)
	{
		return false;
	}
	for (size_t i = 0; i < 20; ++i)
	{
		if (_src.eLoginfo.m_ID[i] == _dest.eLoginfo.m_ID[i])
		{
			continue;
		}
		else
		{
			if (_src.eLoginfo.m_ID[i] < _dest.eLoginfo.m_ID[i])
			{
				return true;
			}
			else if (_dest.eLoginfo.m_ID[i] == 0 || _dest.eLoginfo.m_ID[i] == -52)
			{
				return false;
			}
			break;
		}

	}

	return false;
}
static bool SortHighScore(Player _src, Player _dest)
{
	if (_src.eGameinfo.m_MostScore> _dest.eGameinfo.m_MostScore)
	{
		return true;
	}
	return false;
}
static bool SortRating(Player _src, Player _dest)
{
	float srcRat = 0.f;
	float desRat = 0.f;
	if (_src.eGameinfo.m_Lose == 0)
	{
		srcRat = 1.0f;
	}
	else
	{
		srcRat = _src.eGameinfo.m_Win / (float)(_src.eGameinfo.m_Lose + _src.eGameinfo.m_Win);
	}
	if (_dest.eGameinfo.m_Lose == 0)
	{
		desRat = 1.0f;
	}
	else
	{
		desRat = _dest.eGameinfo.m_Win / (float)(_dest.eGameinfo.m_Lose + _dest.eGameinfo.m_Win);
	}


	if (srcRat <= desRat)
	{
		return false;
	}
	return true;
}
static bool SortManyWins(Player _src, Player _dest)
{
	if (_src.eGameinfo.m_Win <= _dest.eGameinfo.m_Win)
	{
		return false;
	}
	return true;
}

















std::unordered_map<int, class LobbyInfo *> NetCore::m_LobbyInfomap;
std::unordered_map<Tstring, Player*> NetCore::m_Players;
std::unordered_map<int, Tstring> NetCore::m_PushMsg;
std::vector<Tstring> NetCore::m_AllPlaterID;

bool NetCore::CreateLobby(int idx)
{
	LobbyInfo* pNewLobby = nullptr;
	pNewLobby = FindLobby(idx);
	if (pNewLobby)
	{
		return false;
	}
	pNewLobby = new LobbyInfo;
	
	
	m_LobbyInfomap.insert(std::make_pair(idx, pNewLobby));
	return true;
}

LobbyInfo * NetCore::FindLobby(int idx)
{
	std::unordered_map<int, class LobbyInfo *>::iterator FindIter;
	FindIter = m_LobbyInfomap.find(idx);
	if (FindIter == m_LobbyInfomap.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

bool NetCore::DeleteLobby(int idx)
{
	std::unordered_map<int, class LobbyInfo *>::iterator FindIter;
	FindIter = m_LobbyInfomap.find(idx);
	if (FindIter == m_LobbyInfomap.end())
	{
		return false;
	}
	delete FindIter->second;
	FindIter->second = nullptr;
	m_LobbyInfomap.erase(FindIter);

	return true;

}

bool NetCore::Init()
{
	m_LobbyInfomap.clear();

	LoadPlayer();
	CreateLobby(0);





	//FindLobby(1)->CreateRoom(1);
	/*FindLobby(1)->FindRoom(1)->IsIngame = true;
	FindLobby(1)->FindRoom(1)->PlayerId[0] = 1;
	FindLobby(1)->FindRoom(1)->PlayerId[1] = 2;
	FindLobby(1)->FindRoom(1)->PlayerId[2] = 3;
	FindLobby(1)->FindRoom(1)->PlayerId[3] = 4;
	FindLobby(1)->FindRoom(1)->PlayerId[4] = 5;
	FindLobby(1)->FindRoom(1)->PlayerId[5]  =6;
	FindLobby(1)->FindRoom(1)->PlayerId[6] = 7;*/


	//SavePlayer();
	LoadPlayer();

	return true;
}

bool NetCore::release()
{
	//SavePlayer();

	std::unordered_map<int, LobbyInfo *>::iterator StartIter = m_LobbyInfomap.begin();
	std::unordered_map<int, LobbyInfo *>::iterator EndIter = m_LobbyInfomap.end();
	for (; StartIter != EndIter;)
	{
		StartIter = m_LobbyInfomap.erase(StartIter);
	}
	//m_Players
	std::unordered_map<Tstring, Player*>::iterator playerstartiter = m_Players.begin();
	std::unordered_map<Tstring, Player*>::iterator playerenditer = m_Players.end();

	for (; StartIter != EndIter;)
	{
		delete playerstartiter->second;
		playerstartiter->second = nullptr;
		playerstartiter = m_Players.erase(playerstartiter);
	}

	return true;
}

RoomInfo * NetCore::FindIdleRoom(int PlayerIdx)
{
	std::unordered_map<int, LobbyInfo *>::iterator StartIter = m_LobbyInfomap.begin();
	std::unordered_map<int, LobbyInfo *>::iterator EndIter = m_LobbyInfomap.end();
	RoomInfo * pFindRoom = nullptr;

	for (; StartIter != EndIter; ++StartIter)
	{
		pFindRoom = StartIter->second->FindIdleRoom(PlayerIdx);
		if (pFindRoom)
		{
			return pFindRoom;
		}
		continue;
	}
	return nullptr;
}

RoomInfo * NetCore::FindPlayRoom(int PlayerIdx)
{
	std::unordered_map<int, LobbyInfo *>::iterator StartIter = m_LobbyInfomap.begin();
	std::unordered_map<int, LobbyInfo *>::iterator EndIter = m_LobbyInfomap.end();
	RoomInfo * pFindRoom = nullptr;

	for (; StartIter != EndIter; ++StartIter)
	{
		pFindRoom = StartIter->second->FindPlayRoom(PlayerIdx);
		if (pFindRoom)
		{
			return pFindRoom;
		}
		continue;
	}
	return nullptr;
}

LobbyInfo * NetCore::FindPlayerLobby(int PlayerIdx)
{
	std::unordered_map<int, LobbyInfo *>::iterator StartIter = m_LobbyInfomap.begin();
	std::unordered_map<int, LobbyInfo *>::iterator EndIter = m_LobbyInfomap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (StartIter->second->isPlayer(PlayerIdx))
		{
			return StartIter->second;
		}
		continue;
	}
	return nullptr;
}

Tstring NetCore::getLobbySendMsg(int Playeridx)
{
	Tstring strtext;
	strtext = _T("");
	std::unordered_map<int, Tstring>::iterator finditer = m_PushMsg.find(Playeridx);
	if (finditer != m_PushMsg.end())
	{
		strtext = finditer->second;
		finditer->second = _T("");
	}
	return strtext;

}

void NetCore::ClearLobbySendMsg(int Playeridx)
{
	std::unordered_map<int, Tstring>::iterator finditer = m_PushMsg.find(Playeridx);
	if (finditer != m_PushMsg.end())
	{
		//strtext = finditer->second;
		finditer->second = _T("");
	}
	return;
}




void NetCore::SetLobbySendMsg(int Playeridx, const Tstring & _str)
{
	std::unordered_map<int, Player> Copymap =  FindPlayerLobby(Playeridx)->getLobbyPlayers();
	std::unordered_map<int, Player>::iterator startiter = Copymap.begin();
	std::unordered_map<int, Player>::iterator enditer = Copymap.end();
	for (;startiter != enditer; ++startiter)
	{
		if (startiter->second.ePlayerStates.States != playlobby)
		{
			continue;
		}
		if (m_PushMsg[startiter->first][0] == (TCHAR)(-52))
		{
			m_PushMsg[startiter->first].clear();
		}
		m_PushMsg[startiter->first] += _str;
		m_PushMsg[startiter->first] += _T("\n");
	}

}

Player* NetCore::FindPlayer(const Tstring _strID)
{
	Player* mplay = nullptr;
	std::unordered_map<Tstring, Player*>::iterator FindIter;
	FindIter = m_Players.find(_strID);
	if (FindIter == m_Players.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void NetCore::SavePlayer()
{
	//문단으로 구분해서 세이브하고 읽어들인다.
	char MaxBuffer[_MAX_PATH] = {0, };
	GetCurrentDirectoryA(sizeof(char) * _MAX_PATH, MaxBuffer);
	char Drive[_MAX_DRIVE] = {0,};
	char Direc[_MAX_DIR] = {0,};
	_splitpath_s(MaxBuffer, Drive, _MAX_DRIVE, Direc, _MAX_DIR, NULL, 0, NULL, 0);


	////////////////////////////////////////////////////////////////////////////////////////
	//값형 복사를 해야한다.
	//충돌방지.
	std::unordered_map<std::string, Player*> copyPlayers;
	std::unordered_map<Tstring, Player*>::iterator startitert = m_Players.begin();
	std::unordered_map<Tstring, Player*>::iterator enditert = m_Players.end();
	for (; startitert != enditert; ++startitert)
	{
		Player* copyplayer = new Player;
		copyplayer->eGameinfo = startitert->second->eGameinfo;
		copyplayer->eLoginfo = startitert->second->eLoginfo;
		copyplayer->ePlayerStates = startitert->second->ePlayerStates;

		std::string savestr = "";
		savestr.append(startitert->first.begin(), startitert->first.end());
		copyPlayers.insert(std::make_pair(savestr, copyplayer));
	}

	///////////////////////////////////////////////////////////////////////////////////////
	std::unordered_map<std::string, Player*>::iterator startiter = copyPlayers.begin();
	std::unordered_map<std::string, Player*>::iterator enditer = copyPlayers.end();

	for (; startiter != enditer; ++startiter)
	{
		std::string stCurPath = Drive;
		stCurPath += Direc;

		stCurPath += "DATA\\";
		if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
		{
			CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
		}
		stCurPath += "PLAYERDATA\\";
		if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
		{
			CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
		}

		char iduf[20] = {0, };
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, startiter->second->eLoginfo.m_ID, 20, iduf, 20, NULL, NULL);
		stCurPath += iduf;

		stCurPath += ".payerdatas";

		char savebuff[_MAX_PATH] = { 0, };
		HANDLE FileHandle = CreateFileA(stCurPath.c_str(), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
		if (FileHandle != NULL)
		{
			std::string Saveinfos = "";
			char idbuf[20] = {0, };
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, startiter->second->eLoginfo.m_ID, 20, idbuf, 20, NULL, NULL);
			Saveinfos += idbuf;
			Saveinfos += "\r";
			char pwbuf[60] = {0, };
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, startiter->second->eLoginfo.m_PW, 60, pwbuf, 60, NULL, NULL);
			Saveinfos += pwbuf;
			Saveinfos += "\r";
			char embuf[100] = {0, };
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, startiter->second->eLoginfo.m_Email, 100, embuf, 100, NULL, NULL);
			Saveinfos += embuf;
			Saveinfos += "\r";

			_itoa_s(startiter->second->eLoginfo.m_UniqueID, savebuff, 10);
			Saveinfos += savebuff;//여기서부터 숫자를 문자열로만듬
			Saveinfos += "\r";

			_itoa_s(startiter->second->eGameinfo.m_Win, savebuff, 10);
			Saveinfos += savebuff;
			Saveinfos += "\r";

			_itoa_s(startiter->second->eGameinfo.m_Lose, savebuff, 10);
			Saveinfos += savebuff;
			Saveinfos += "\r";

			_itoa_s(startiter->second->eGameinfo.m_MostScore, savebuff, 10);
			Saveinfos += savebuff;
			Saveinfos += "\r";

			if (0 == WriteFile(FileHandle, Saveinfos.c_str(), (DWORD)Saveinfos.size(), NULL, NULL))
			{
				MessageBox(NULL, TEXT("파일을 읽는데 있어 WriteFile이 0이 반환되어 실패했습니다."), TEXT("저장 애러"), MB_OK);
				int err = GetLastError();
			}

			CloseHandle(FileHandle);
			FileHandle = NULL;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//std::unordered_map<std::string, Player*> copyPlayers;
	startiter = copyPlayers.begin();
	enditer = copyPlayers.end();
	while (startiter != enditer)
	{
		delete startiter->second;
		startiter->second = nullptr;
		startiter = copyPlayers.erase(startiter);

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	std::string stCurPath = Drive;
	stCurPath += Direc;

	stCurPath += "DATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	stCurPath += "PLAYERDATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	stCurPath += "PlayerList.lists";


	std::string strPlayervecs;
	for (size_t i = 0; i < m_AllPlaterID.size(); ++i)
	{
		char allidbuf[20] = {0, };
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, m_AllPlaterID[i].c_str(), (int)m_AllPlaterID[i].size(), allidbuf, 20, NULL, NULL);
		strPlayervecs += allidbuf;
		strPlayervecs += "\r";
	}


	HANDLE FilelistHandle = CreateFileA(stCurPath.c_str(), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	WriteFile(FilelistHandle, strPlayervecs.c_str(), (DWORD)strPlayervecs.size(), NULL, NULL);

	CloseHandle(FilelistHandle);
	FilelistHandle = NULL;


	//자인제 상대좌표가 완성되었다.



	//일단 그전에 상대 좌표를 구해서 해야겠다.
	//CreateFile()
}

void NetCore::LoadPlayer()
{
	//문단으로 구분해서 세이브하고 읽어들인다.
	char MaxBuffer[_MAX_PATH] = {0, };
	GetCurrentDirectoryA(sizeof(char) * _MAX_PATH, MaxBuffer);
	char Drive[_MAX_DRIVE] = {0, };
	char Direc[_MAX_DIR] = {0, };
	_splitpath_s(MaxBuffer, Drive, _MAX_DRIVE, Direc, _MAX_DIR, NULL, 0, NULL, 0);


	std::string stCurPath = Drive;
	stCurPath += Direc;

	stCurPath += "DATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	stCurPath += "PLAYERDATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	stCurPath += "PlayerList.lists";

	HANDLE FilelistHandle = CreateFileA(stCurPath.c_str(), GENERIC_ALL, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	HRESULT rs = GetLastError();
	m_AllPlaterID.clear();

	char MaxBuffer2[300000] = {0, };
	DWORD readsize = NULL;
	ReadFile(FilelistHandle, MaxBuffer2, sizeof(char) * 300000, &readsize, NULL);


	std::string savestr;
	for (int i = 0; i < (int)readsize; ++i)
	{
		if (MaxBuffer2[i] == -52)
		{
			break;
		}
		if (MaxBuffer2[i] == '\r')
		{
			//넣어주는 부분에서 Wide로
			TCHAR Loadidbuf[20] = {0, };
			MultiByteToWideChar(CP_ACP, MB_COMPOSITE, savestr.c_str(), (int)savestr.size(), Loadidbuf, 20);
			m_AllPlaterID.push_back(Loadidbuf);
			savestr = "";
			continue;
		}
		savestr += MaxBuffer2[i];
	}

	CloseHandle(FilelistHandle);
	FilelistHandle = NULL;




	/////////////////////////////////
	for (size_t i = 0; i < m_AllPlaterID.size(); ++i)
	{
		std::string stCurPath = Drive;
		stCurPath += Direc;
		stCurPath += "DATA\\";
		if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
		{
			CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
		}
		stCurPath += "PLAYERDATA\\";
		if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
		{
			CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
		}

		char allpid[20] = {0, };
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, m_AllPlaterID[i].c_str(), (int)m_AllPlaterID[i].size(), allpid, 20, NULL, NULL);
		stCurPath += allpid;
		stCurPath += ".payerdatas";
		readsize = NULL;
		HANDLE FileHandle = CreateFileA(stCurPath.c_str(), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
		ReadFile(FileHandle, MaxBuffer2, sizeof(char) * 300000, &readsize, NULL);

		Player* NewPlayer = new Player;

		std::string savestr;
		int counts = 1;
		for (int i = 0; i < (int)readsize; ++i)
		{
			if (MaxBuffer2[i] == -52)
			{
				break;
			}
			if (MaxBuffer2[i] == '\r')
			{
				char savebuff[_MAX_PATH] = { 0, };
				switch (counts)
				{
				case 1:
				{
					TCHAR byff[20] = {0, };
					MultiByteToWideChar(CP_ACP, MB_COMPOSITE, savestr.c_str(), (int)savestr.size(), byff, 20);
					memcpy(&NewPlayer->eLoginfo.m_ID, byff, 20);
					break;
				}
				case 2:
				{
					TCHAR byff[60] = { 0, };
					MultiByteToWideChar(CP_ACP, MB_COMPOSITE, savestr.c_str(), (int)savestr.size(), byff, 60);
					memcpy(&NewPlayer->eLoginfo.m_PW, byff, 60);
					break;
				}

				case 3:
				{
					TCHAR byff[100] = { 0, };
					MultiByteToWideChar(CP_ACP, MB_COMPOSITE, savestr.c_str(), (int)savestr.size(), byff, 100);
					memcpy(&NewPlayer->eLoginfo.m_Email, byff, 100);
					break;
				}
					
				case 4:
					NewPlayer->eLoginfo.m_UniqueID = atoi(&savestr[0]);
					//memcpy(&NewPlayer.eLoginfo.m_UniqueID, &savestr[0], sizeof(int));
					break;
				case 5:
					NewPlayer->eGameinfo.m_Win = atoi(&savestr[0]);
					//memcpy(&NewPlayer.eGameinfo.m_Win, &savestr[0], sizeof(int));
					break;
				case 6:
					NewPlayer->eGameinfo.m_Lose = atoi(&savestr[0]);
					//memcpy(&NewPlayer.eGameinfo.m_Lose, &savestr[0], sizeof(int));
					break;
				case 7:
					NewPlayer->eGameinfo.m_MostScore = atoi(&savestr[0]);
					//memcpy(&NewPlayer.eGameinfo.m_MostScore, &savestr[0], sizeof(int));
					break;
				default:
					break;
				}
				++counts;
				savestr = "";
				continue;
			}
			savestr += MaxBuffer2[i];
		}

		//인썰트는 와이드문자로

		m_Players.insert(std::make_pair(NewPlayer->eLoginfo.m_ID, NewPlayer));
		m_PushMsg.insert(std::make_pair(NewPlayer->eLoginfo.m_UniqueID, _T("")));

		CloseHandle(FileHandle);
		FileHandle = NULL;
	}
}

void NetCore::AddPlayer(const PlayerLogInfo& Info)
{
	Player* newplayer = new Player;
	newplayer->eLoginfo = Info;
	newplayer->ePlayerStates.States = playLogin;

	m_Players.insert(std::make_pair(newplayer->eLoginfo.m_ID, newplayer));
	m_PushMsg.insert(std::make_pair(newplayer->eLoginfo.m_UniqueID, _T("")));
	m_AllPlaterID.push_back(newplayer->eLoginfo.m_ID);


	/////////////////////////////////////////
	//문단으로 구분해서 세이브하고 읽어들인다.
	char MaxBuffer[_MAX_PATH] = {0, };
	GetCurrentDirectoryA(sizeof(char) * _MAX_PATH, MaxBuffer);
	char Drive[_MAX_DRIVE] = {0, };
	char Direc[_MAX_DIR] = {0, };
	_splitpath_s(MaxBuffer, Drive, _MAX_DRIVE, Direc, _MAX_DIR, NULL, 0, NULL, 0);
	//////////////////////////////////////////

	std::string stCurPath = Drive;
	stCurPath += Direc;
	stCurPath += "DATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	stCurPath += "PLAYERDATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	//이걸 다시 멀티 문자열로
	char logid[20] = {0, };
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, newplayer->eLoginfo.m_ID, 20, logid, 20, NULL, NULL);
	stCurPath += logid;

	stCurPath += ".payerdatas";


	char savebuff[_MAX_PATH] = { 0, };

	HANDLE FileHandle = CreateFileA(stCurPath.c_str(), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	if (FileHandle != NULL)
	{
		std::string Saveinfos = "";
		char idbuf[20] = {0, };
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, newplayer->eLoginfo.m_ID, 20, idbuf, 20, NULL, NULL);
		Saveinfos += idbuf;
		Saveinfos += "\r";
		char pwbuf[60] = {0, };
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, newplayer->eLoginfo.m_PW, 60, pwbuf, 60, NULL, NULL);
		Saveinfos += pwbuf;
		Saveinfos += "\r";
		char embuf[100] = {0, };
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, newplayer->eLoginfo.m_Email, 100, embuf, 100, NULL, NULL);
		Saveinfos += embuf;
		Saveinfos += "\r";

		////////////////////////
		_itoa_s(newplayer->eLoginfo.m_UniqueID, savebuff, 10);
		Saveinfos += savebuff;//여기서부터 숫자를 문자열로만듬
		Saveinfos += "\r";

		_itoa_s(newplayer->eGameinfo.m_Win, savebuff, 10);
		Saveinfos += savebuff;
		Saveinfos += "\r";

		_itoa_s(newplayer->eGameinfo.m_Lose, savebuff, 10);
		Saveinfos += savebuff;
		Saveinfos += "\r";

		_itoa_s(newplayer->eGameinfo.m_MostScore, savebuff, 10);
		Saveinfos += savebuff;
		Saveinfos += "\r";

		//버퍼를 만들어보자!

		if (0 != WriteFile(FileHandle, Saveinfos.c_str(), (DWORD)Saveinfos.size(), NULL, NULL))
		{
			//strPlayervecs += startiter->second.eLoginfo.m_ID;
			//strPlayervecs += "\r";
		}

		CloseHandle(FileHandle);
		FileHandle = NULL;
	}

	/////////////////////////////////////////////
	stCurPath = Drive;
	stCurPath += Direc;

	stCurPath += "DATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	stCurPath += "PLAYERDATA\\";
	if (GetFileAttributesA((LPCSTR)stCurPath.c_str()) == 0xFFFFFFFF)
	{
		CreateDirectoryA((LPCSTR)stCurPath.c_str(), NULL);
	}
	stCurPath += "PlayerList.lists";


	std::string strPlayervecs = "";
	for (size_t i = 0; i < m_AllPlaterID.size(); ++i)
	{
		char allbuf[20] = {0, };
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, m_AllPlaterID[i].c_str(), (int)m_AllPlaterID[i].size(), allbuf, 20, NULL, NULL);
		strPlayervecs += allbuf;
		strPlayervecs += "\r";
	}


	HANDLE FilelistHandle = CreateFileA(stCurPath.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	WriteFile(FilelistHandle, strPlayervecs.c_str(), (DWORD)strPlayervecs.size(), NULL, NULL);

	CloseHandle(FilelistHandle);
	FilelistHandle = NULL;
}

Tstring NetCore::FindPlayerID(int _unNum)
{
	Tstring strretult = _T("");
	std::unordered_map<Tstring, Player*>::iterator startiter = m_Players.begin();
	std::unordered_map<Tstring, Player*>::iterator enditer = m_Players.end();
	for (; startiter != enditer; ++startiter)
	{
		if (_unNum == startiter->second->eLoginfo.m_UniqueID)
		{
			strretult = startiter->second->eLoginfo.m_ID;
			break;
		}
	}
	return strretult;
}

bool NetCore::isPlayerId(const  Tstring& _pstr)
{
	for (size_t i = 0; i < m_AllPlaterID.size(); ++i)
	{
		if (m_AllPlaterID[i] == _pstr)
		{
			return true;
		}
	}
	return false;
}

int NetCore::isLogin(const Tstring & id, const Tstring & pw)
{
	std::unordered_map<Tstring, Player*>::iterator Finditer;
	Finditer = m_Players.find(id);
	if (Finditer == m_Players.end())
	{
		return 0;
	}
	LobbyInfo* curlobby = FindPlayerLobby(Finditer->second->eLoginfo.m_UniqueID);
	if (curlobby)
	{
		return 1;
	}
	if (Finditer->second->eLoginfo.m_PW == pw)
	{
		return 2;
	}
	return false;
}

Tstring NetCore::FindID(const Tstring & em)
{
	std::unordered_map<Tstring, Player*>::iterator startiter = m_Players.begin();
	std::unordered_map<Tstring, Player*>::iterator enditer = m_Players.end();

	for (; startiter != enditer; ++startiter)
	{
		if (startiter->second->eLoginfo.m_Email == em)
		{
			return	startiter->second->eLoginfo.m_ID;
		}
	}
	return _T("");
}

Tstring NetCore::FindPW(const Tstring & em, const Tstring & id)
{
	std::unordered_map<Tstring, Player*>::iterator Finditer;
	Finditer = m_Players.find(id);
	if (Finditer == m_Players.end())
	{
		return _T("");
	}
	if (Finditer->second->eLoginfo.m_Email == em)
	{
		return Finditer->second->eLoginfo.m_PW;
	}
	return _T("");
}

bool NetCore::FindPlayers(int _sortenum, int _count, std::vector<Player>& _Result)
{
	_Result.clear();
	std::unordered_map<Tstring, Player*>::iterator startiter = m_Players.begin();
	std::unordered_map<Tstring, Player*>::iterator enditer = m_Players.end();
	for ( ;startiter != enditer ; ++startiter)
	{
		if (!startiter->second)
		{
			continue;
		}

		_Result.push_back(*startiter->second);
	}

	switch (_sortenum)
	{
	case 0://bs_err
		break;
	case 1://bs_no
		break;
	case 2://bs_name
	{
		std::sort(_Result.begin(), _Result.end(), SortPlayer);
	}
		break;
	case 3://bs_scroe
	{
		std::sort(_Result.begin(), _Result.end(), SortHighScore);
	}
		break;
	case 4://bs_rate
	{
		std::sort(_Result.begin(), _Result.end(), SortRating);
	}
		break;
	case 5://bs_wins
	{
		std::sort(_Result.begin(), _Result.end(), SortManyWins);
	}
		break;
	default:
		break;
	}
	//소팅 완료

	//_Result.resize(_count);
	return true;
}

void NetCore::ClearRooms()
{
	std::unordered_map<int, LobbyInfo *>::iterator startiter = m_LobbyInfomap.begin();
	std::unordered_map<int, LobbyInfo *>::iterator enditer = m_LobbyInfomap.end();
	for ( ; startiter != enditer; ++startiter)
	{
		startiter->second->ClearRooms();
	}
	
}

NetCore::NetCore()
{

}


NetCore::~NetCore()
{

}
