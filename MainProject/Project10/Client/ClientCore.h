#pragma once
#include "UseServer.h"

#define GameLoginScene _T("LogIn")
#define GameLobbyScene _T("Lobby")
#define GameRoomScene _T("Room")
#define GameRankinScene _T("Ranking")


class ClientCore
{
private:
	static class ClientLogInScene* pLoginScene;
	static class ClientLobbyScene* pLobbyScene;
	static class ClientRoomScene* pRoomScene;
	static class ClientRankingScene* pRankingScene;
public:
	static UseServer* pServer;
	static int CurIngmaeNumber;
	static bool ClientRun;
	static HWND mainhWnd;
	static HINSTANCE mainhInst;
	static HDC PrintDC;
	static WNDPROC mainProc;
	static struct Player ClientPlayer;

public:
	static bool init();
	static bool Update(float time);
	static bool release();



public:



	//µð¹ö±ë¿ë
	static std::vector<int> testmap;



};

