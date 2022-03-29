#pragma once
#include <unordered_map>

enum playerstats
{
	playErr = 0,
	playLogin = 1,
	playlobby  = 2,
	playroomidle = 3,
	playingmae = 4,
	playRanking = 5,
};


struct PlayerLogInfo
{
	TCHAR m_ID[20] = {0, };
	TCHAR m_PW[60] = {0, };
	TCHAR m_Email[100] = { 0, };
	int m_UniqueID = 0;
};

struct PlayerStates
{
	int States = 1; // 로비에서 대기중 / 방에 접속중 / 게임중
	int RoomNum = 0; // 몇번 방인지
};


struct PayerGameInfo
{
	int m_Win = 0;
	int m_Lose = 0;
	int m_MostScore = 0;
};


struct Player
{
	PlayerLogInfo eLoginfo = PlayerLogInfo();
	PlayerStates ePlayerStates = PlayerStates();
	PayerGameInfo eGameinfo = PayerGameInfo();
};
////////////////////////////////////////////////


class NetCore
{
private:
	static std::vector<Tstring> m_AllPlaterID;
	static std::unordered_map<Tstring, Player*> m_Players;
	//내부적으로 돌리기위해서 필요한 함수
	static std::unordered_map<int, Tstring> m_PushMsg;



	//static 
	static std::unordered_map<int, class LobbyInfo *> m_LobbyInfomap;

public:
	static bool CreateLobby(int idx);
	static class LobbyInfo* FindLobby(int idx);
	static bool DeleteLobby(int idx);
public:
	static bool Init();
	static bool release();

public:
	static class RoomInfo* FindIdleRoom(int PlayerIdx);
	static class RoomInfo* FindPlayRoom(int PlayerIdx);
	static class LobbyInfo* FindPlayerLobby(int PlayerIdx);
	static Tstring getLobbySendMsg(int Playeridx);
	static void ClearLobbySendMsg(int Playeridx);
	static void SetLobbySendMsg(int Playeridx, const Tstring& _str);

public:
	static Player* FindPlayer(const Tstring _strID);

	static void SavePlayer();
	static void LoadPlayer();
	static void AddPlayer(const PlayerLogInfo& Info);


	static Tstring FindPlayerID(int _unNum);
	static bool isPlayerId(const  Tstring& _pstr);
	static int isLogin(const  Tstring& id, const  Tstring& pw);
	static Tstring FindID(const  Tstring& em);
	static Tstring FindPW(const  Tstring& em, const  Tstring& id);


	//소팅된 어떠한 값
	static bool FindPlayers(int _sortenum, int _count, std::vector<Player>& _Result);

	static void ClearRooms();

private:
	NetCore();
	~NetCore();
};


