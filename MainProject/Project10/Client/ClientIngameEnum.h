#pragma once
#include <string>
#include "resource.h"
#include "LobbyPlayerlist.h"





static const int Map_maxY = 23;
static const int Map_maxX = 10;
static const int MyBlockSize = 30;
static const int OtherBlockSize = 15;
static const int NextBlockSize = 30;

#define LobbyMainDC 102
#define LobbyChatDC 101
#define LobbyplayDC 100



#define IngameMainDC 202
#define IngameSubDC 201
#define IngameLogDC 200


 

#define LB_C_UPDATE  WM_APP +0
#define LB_C_OPENSEL  WM_APP +1
#define LB_C_ALLCLEAR  WM_APP +2



#define DLG_C_UPDATE  WM_APP +100
#define  DLG_ONCREATES WM_APP +101



struct PlayerStates
{
	int States = 0; // 로비에서 대기중 / 방에 접속중 / 게임중
	int RoomNum = 0; // 몇번 방인지
};

struct PlayerLogInfo
{
	TCHAR m_ID[20] = {0, };
	TCHAR m_PW[60] = {0, };
	TCHAR m_Email[100] = {0, };
	int m_UniqueID = 0;
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

enum playerready
{
	PREADY_NO,
	PREADY_STAY,
	PREADY_READY,
	PREADY_WAIT,
	PREADY_START
};

enum playerstats
{
	playErr = 0,
	playLogin = 1,
	playlobby = 2,
	playroomidle = 3,
	playingmae = 4,
	playRanking = 5,
};

enum BlockType
{
	BT_ERR = -1,
	BT_4LA,
	BT_4LB,

	BT_22AA,
	BT_22AB,
	BT_22BA,
	BT_22BB,

	BT_22MM,

	BT_31LA,
	BT_31LB,
	BT_31LC,
	BT_31LD,

	BT_31RA,
	BT_31RB,
	BT_31RC,
	BT_31RD,

	BT_31MA,
	BT_31MB,
	BT_31MC,
	BT_31MD




};

enum BlockState
{
	BKS_NONE,
	BKS_CHANGE,
	BKS_LEFT,
	BKS_RIGHT,
	BKS_DOWN,
	BKS_SHUTDOWN
};

enum MapTileColors
{
	MTC_ERR,
	MTC_NONE,
	MTC_NONATIVE,
	MTC_ATIVE1,
	MTC_ATIVE2,
	MTC_ATIVE3,
	MTC_ATIVE4,
	MTC_ATIVE5,
	MTC_ATIVE6,
	MTC_ATIVE7
};


struct Maptile
{
public:
	MapTileColors eType = MTC_ERR;
	int x = 0;
	int y = 0;
	int Render(HDC drow = NULL);
	int RenderOthrer(int PosX, int PosY ,HDC drow = NULL);
	int RenderPivotSIze(int PosX, int PosY, HDC drow = NULL, int sizeX = NextBlockSize, int SizeY = NextBlockSize);
};


struct IngameScore
{
	Tstring m_Name = {0, };
	int m_PlayerIngameNum = -1;
	int m_Score = 0;
	//Tstring m_strmsg;
};

struct IngameScoreSurver
{
	TCHAR m_Name[20] = {0, };
	int m_PlayerIngameNum = -1;
	int m_Score = 0;
	//Tstring m_strmsg;

	operator IngameScore()
	{
		IngameScore pdesc = IngameScore();
		//TCHAR wbuff[20] = {0, };
		//MultiByteToWideChar(CP_ACP, MB_COMPOSITE, m_Name, 20, wbuff, 20);
		pdesc.m_Name = m_Name;

		pdesc.m_PlayerIngameNum = m_PlayerIngameNum;
		pdesc.m_Score= m_Score;
		return pdesc;
	}

};


class RoomInfoLobby
{
public:
	int m_iRoomNum = 0;
	int m_iCurNum = 0;
	int m_iLimNum = 0;
	bool m_bPub = false;
	bool m_bIsActive = false;
	TCHAR m_RoomNameArr[30] = { 0, };
	int m_password = -1;
	bool IsIngame = false;

};

struct RoomInfo
{
public:
	//
	int m_iRoomNum = 0;
	int m_iCurNum = 0;
	int m_iLimNum = 0;
	bool m_bPub = false;
	bool m_bIsActive = false;
	TCHAR m_RoomNameArr[30] = { 0, };
	int m_password = -1;

public:
	bool IsIngame = false;;
	float m_fsecTime = 0.f;
	TCHAR MapInfo[7][10][23] = { 0, };
	int PlayerId[7] = { 0, };

public:
	//문자화 보관
	Tstring m_strRoomNum = L"";
	Tstring m_strRoomName = L"";
	Tstring m_strRoomLimNum = L"";
	Tstring m_strRoomCurNum = L"";

public:
	void UpdateString()
	{


		TCHAR strbuff[_MAX_PATH];
		if (m_iRoomNum >= 0)
		{
			memset(strbuff, 0, sizeof(TCHAR) * _MAX_PATH);
			_itow_s(m_iRoomNum, strbuff, 10);
			m_strRoomNum = strbuff;
		}

		if (m_strRoomName.size() > 30)
		{
			MessageBox(ClientCore::mainhWnd, TEXT("문자열 길이 초과, 30글자로 절삭 됩니다."), TEXT("방제 초과"), MB_OK);
		}
		
		for (int i = 0; i < 30; ++i)
		{
			m_RoomNameArr[i] = m_strRoomName.c_str()[i];
		}
		//WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, m_strRoomName.c_str(), (int)m_strRoomName.size(), m_RoomNameArr, 30, NULL, NULL);

		if (m_iLimNum >= 2)
		{
			memset(strbuff, 0, sizeof(TCHAR) * _MAX_PATH);
			_itow_s(m_iLimNum, strbuff, 10);
			m_strRoomLimNum = strbuff;
		}
		else
		{
			m_strRoomCurNum = L"Err";
		}

		if (m_iCurNum >= 1)
		{
			memset(strbuff, 0, sizeof(TCHAR) * _MAX_PATH);
			_itow_s(m_iCurNum, strbuff, 10);
			m_strRoomCurNum = strbuff;
		}
		else
		{
			m_strRoomCurNum = L"0";
		}
	}

	RoomInfoLobby toRoomInfoLobby() const
	{
		RoomInfoLobby Roomresult;
		Roomresult.m_iRoomNum = m_iRoomNum;
		Roomresult.m_iCurNum = m_iCurNum;
		Roomresult.m_iLimNum = m_iLimNum;
		Roomresult.m_bPub = m_bPub;
		Roomresult.m_bIsActive = m_bIsActive;
		memcpy(&Roomresult.m_RoomNameArr[0], &m_RoomNameArr[0], sizeof(TCHAR) * 30);
		Roomresult.m_password = m_password;
		Roomresult.IsIngame = IsIngame;
		return Roomresult;
	}
	void fromRoomInfoLobby(const RoomInfoLobby& Roomresult)
	{

		if (!Roomresult.m_bIsActive)
		{
			return;
		}

		m_iRoomNum = Roomresult.m_iRoomNum;
		m_iCurNum = Roomresult.m_iCurNum;
		m_iLimNum = Roomresult.m_iLimNum;
		m_bPub = Roomresult.m_bPub;
		m_bIsActive = Roomresult.m_bIsActive;





		memcpy(&m_RoomNameArr[0] , &Roomresult.m_RoomNameArr[0] , sizeof(TCHAR) * 30);
		TCHAR wnamearr[_MAX_PATH] = { 0, };
		//MultiByteToWideChar(CP_ACP, WC_COMPOSITECHECK, m_RoomNameArr, 30, &m_strRoomName.c_str()[0], 30, NULL, NULL);
		//MultiByteToWideChar(CP_ACP, MB_COMPOSITE, m_RoomNameArr, 30, wnamearr, 30);
		m_strRoomName = m_RoomNameArr;

		m_password = Roomresult.m_password;
		IsIngame = Roomresult.IsIngame;


		return;
	}
};




static std::unordered_map<int, Tstring> m_CurLobbyPlayermap;

inline static int FindIdx(const Tstring& _str)
{
	std::unordered_map<int, Tstring>::iterator finditer = m_CurLobbyPlayermap.begin();
	while (finditer != m_CurLobbyPlayermap.end())
	{
		if (finditer->second == _str)
		{
			return finditer->first;
		}
		++finditer;
	}
	return 0;
}











//다음에 수정합니다.
static BOOL CALLBACK PlayerinfostatsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (!IsWindowEnabled(hWnd))
		{
			break;
		}
		WINDOWINFO  mainwindesc;
		GetWindowInfo(ClientCore::mainhWnd, &mainwindesc);

		//SetTimer(hWnd, 11, 10, nullptr);

		int Topsize = mainwindesc.rcClient.top + 300;
		int Leftsize = mainwindesc.rcClient.left + 700;


		WINDOWINFO curWind;
		GetWindowInfo(hWnd, &curWind);
		int SizeY = curWind.rcWindow.bottom - curWind.rcWindow.top;
		int SizeX = curWind.rcWindow.right - curWind.rcWindow.left;

		SetWindowPos(hWnd, HWND_TOP, Leftsize, Topsize, SizeX, SizeY, NULL);

		return TRUE;
	}
	case WM_DESTROY:
	{
		//KillTimer(hWnd, 11);
		return TRUE;
	}
	case WM_TIMER:
	{
		//CommonPacket packets;
		//packets.PacProp.iLocation1 = SL_Err;
		//packets = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_LOBBY, LB_CHECKPLAYER, CC_FIND, LB_PLAYER);
		//if (packets == DisConnected)
		//{
		//	return PR_RECONECTSURVER;
		//}

		//if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_PLAYER)
		//{
		//	//////////플레이어 구조체 자체를 줄 것이다.
		//	Player playerinfo = Player();
		//	memcpy(&playerinfo, packets.Comments, sizeof(Player));

		//	SetDlgItemText(hWnd, IDC_PLAYERIDLIST1, (LPTSTR)playerinfo.eLoginfo.m_ID);
		//	//SetDlgItemText(hWnd, IDC_CURSTATS, (LPSTR)playerinfo.ePlayerStates.States);
		//	SetDlgItemInt(hWnd, IDC_WINSSCORE, (UINT)playerinfo.eGameinfo.m_Win, TRUE);
		//	SetDlgItemInt(hWnd, IDC_LOSESCORE, (UINT)playerinfo.eGameinfo.m_Lose, TRUE);

		//	if ((playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose) == 0)
		//	{
		//		SetDlgItemText(hWnd, IDC_RATTING, (LPTSTR)_T("0%"));
		//	}
		//	else
		//	{
		//		TCHAR rattnglog[_MAX_PATH];

		//		//swprintf_s(MainTimerBuff, TEXT("[MainTime : %.9f][FPS : %.2f]"), fMainTimer, fMainFPS);
		//		//swprintf_s()
		//		_stprintf_s(rattnglog, _T("%.2f %%"), (float)(playerinfo.eGameinfo.m_Win / (float)(playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose) * 100.0f));
		//		//sprintf_s(rattnglog, "%.2f %%", (float)(playerinfo.eGameinfo.m_Win / (float)(playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose) * 100.0f));
		//		SetDlgItemText(hWnd, IDC_RATTING, (LPTSTR)rattnglog);
		//		//SetDlgItemInt(hWnd, IDC_RATTING, (UINT)playerinfo.eGameinfo.m_Win / playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose, TRUE);
		//	}

		//	TCHAR poslog[_MAX_PATH];
		//	switch (playerinfo.ePlayerStates.States)
		//	{
		//	case playlobby:
		//	{
		//		SetDlgItemText(hWnd, IDC_CURSTATS, _T("로비에서 대기중"));
		//		break;
		//	}
		//	case playroomidle:
		//	{
		//		_stprintf_s(poslog, _T("%d 방에서 대기중"), playerinfo.ePlayerStates.RoomNum);
		//		//sprintf_s(poslog, "%d 방에서 대기중", playerinfo.ePlayerStates.RoomNum);
		//		SetDlgItemText(hWnd, IDC_CURSTATS, (LPTSTR)poslog);
		//		break;
		//	}
		//	case playingmae:
		//	{
		//		_stprintf_s(poslog, _T("%d 방에서 게임중"), playerinfo.ePlayerStates.RoomNum);
		//		//sprintf_s(poslog, "%d 방에서 게임중", playerinfo.ePlayerStates.RoomNum);
		//		SetDlgItemText(hWnd, IDC_CURSTATS, (LPTSTR)poslog);
		//		break;
		//	}
		//	default:
		//		break;
		//	}
		//}

		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_PLAYERMOVE1:
		{
			/////////처리하고 끝냅니다.




			EndDialog(hWnd, ID_PLAYERMOVE1);
			break;
		}
		case ID_PALYERINFOOK:
		{
			EndDialog(hWnd, ID_PALYERINFOOK);
			break;
		}
		default:
			break;
		}
		return TRUE;
	}

	case DLG_C_UPDATE:
	{
		TCHAR playernamebuff[30];

		GetDlgItemText(hWnd, IDC_PLAYERIDLIST1, (LPTSTR)playernamebuff, 30);

		if (!FindIdx(playernamebuff))
		{
			//MessageBox(NULL, TEXT("사용자 정보가 손상되었습니다."), TEXT("정보 출력 오류"), MB_OK);
			SetDlgItemText(hWnd, IDC_PLAYERIDLIST1, _T("N / A"));
			SetDlgItemText(hWnd, IDC_CURSTATS, _T(" 플레이어 정보가 손상 되었습니다. "));
			//SetDlgItemText(hWnd, IDC_CURSTATS, (LPSTR)playerinfo.ePlayerStates.States);
			SetDlgItemText(hWnd, IDC_WINSSCORE, _T("N / A"));
			SetDlgItemText(hWnd, IDC_LOSESCORE, _T("N / A"));
			SetDlgItemText(hWnd, IDC_RATTING, _T("N / A"));
			break;
		}

		//////////////////////////////////////////////////////////////////////////////
		//레이어의 속성을 움직이게 하겠다.
		/////////



		CommonPacket packets;
		//memset(&packets, 0, sizeof(CommonPacket));
		//ZeroMemory(&packets, sizeof(CommonPacket));
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_LOBBY;
		packets.PacProp.iLocation2 = LB_CHECKPLAYER;
		packets.PacProp.iWork = CC_FIND;
		packets.PacProp.iItem = LB_PLAYER;

		packets.SetComment(playernamebuff);

		ClientCore::pServer->PushSend(packets);



		packets = CommonPacket();
		packets.PacProp.iLocation1 = SL_Err;
		int count = 0;
		while (true)
		{
			packets = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_LOBBY, LB_CHECKPLAYER, CC_FIND, LB_PLAYER);
			if (packets == DisConnected)
			{
				return PR_RECONECTSURVER;
			}
			if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_PLAYER)
			{
				break;
			}
			if (count >= 10000)
			{
				SetDlgItemText(hWnd, IDC_PLAYERIDLIST1, _T("N / A"));
				SetDlgItemText(hWnd, IDC_CURSTATS, _T(" 플레이어 정보가 손상 되었습니다. "));
				SetDlgItemText(hWnd, IDC_WINSSCORE, _T("N / A"));
				SetDlgItemText(hWnd, IDC_LOSESCORE, _T("N / A"));
				SetDlgItemText(hWnd, IDC_RATTING, _T("N / A"));
				return 0;
			}
			++count;
		}


		if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_PLAYER)
		{
			//////////플레이어 구조체 자체를 줄 것이다.
			Player playerinfo = Player();
			memcpy(&playerinfo, packets.Comments, sizeof(Player));

			SetDlgItemText(hWnd, IDC_PLAYERIDLIST1, (LPTSTR)playerinfo.eLoginfo.m_ID);
			//SetDlgItemText(hWnd, IDC_CURSTATS, (LPSTR)playerinfo.ePlayerStates.States);
			SetDlgItemInt(hWnd, IDC_WINSSCORE, (UINT)playerinfo.eGameinfo.m_Win, TRUE);
			SetDlgItemInt(hWnd, IDC_LOSESCORE, (UINT)playerinfo.eGameinfo.m_Lose, TRUE);





			if ((playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose) == 0)
			{
				SetDlgItemText(hWnd, IDC_RATTING, (LPTSTR)_T("0%"));
			}
			else
			{
				TCHAR rattnglog[_MAX_PATH];

				//swprintf_s(MainTimerBuff, TEXT("[MainTime : %.9f][FPS : %.2f]"), fMainTimer, fMainFPS);
				//swprintf_s()
				_stprintf_s(rattnglog, _T("%.2f %%"), (float)(playerinfo.eGameinfo.m_Win / (float)(playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose) * 100.0f));
				//sprintf_s(rattnglog, "%.2f %%", (float)(playerinfo.eGameinfo.m_Win / (float)(playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose) * 100.0f));
				SetDlgItemText(hWnd, IDC_RATTING, (LPTSTR)rattnglog);
				//SetDlgItemInt(hWnd, IDC_RATTING, (UINT)playerinfo.eGameinfo.m_Win / playerinfo.eGameinfo.m_Win + playerinfo.eGameinfo.m_Lose, TRUE);
			}


			if (-1 == playerinfo.ePlayerStates.RoomNum)
			{
				SetDlgItemText(hWnd, IDC_CURSTATS, _T("로비에서 대기중"));
				break;
			}
			else
			{
				TCHAR poslog[_MAX_PATH];
				switch (playerinfo.ePlayerStates.States)
				{
				case playlobby:
				{
					SetDlgItemText(hWnd, IDC_CURSTATS, _T("로비에서 대기중"));
					break;
				}
				case playroomidle:
				{
					_stprintf_s(poslog, _T("%d 방에서 대기중"), playerinfo.ePlayerStates.RoomNum);
					//sprintf_s(poslog, "%d 방에서 대기중", playerinfo.ePlayerStates.RoomNum);
					SetDlgItemText(hWnd, IDC_CURSTATS, (LPTSTR)poslog);
					break;
				}
				case playingmae:
				{
					_stprintf_s(poslog, _T("%d 방에서 게임중"), playerinfo.ePlayerStates.RoomNum);
					//sprintf_s(poslog, "%d 방에서 게임중", playerinfo.ePlayerStates.RoomNum);
					SetDlgItemText(hWnd, IDC_CURSTATS, (LPTSTR)poslog);
					break;
				}
				default:
					break;
				}
			}


		
		}


		/////////////////////////////////////////////////////////////////////////////////////




		//playernamebuff
		//이것의 이름으로

		//활동중
		//승리
		//패배를 획득한다.
		

		


		



		return TRUE;
	}
	//case WM_TIMER:
	//{

	//}




	default:
		break;
	}


	return FALSE;
}

enum MAPIDX
{
	MAPERR,
	MAP1,
	MAP2,
	MAP3,
	MAP4,
	MAP5,
	MAP6,

};


//미리 구성된 정보를 만들어도 되겠구나.
class AdvanceMap
{
	static const TCHAR AdvanceMap::pMapErr[Map_maxX][Map_maxY];
	static const TCHAR pMapArr1[Map_maxX][Map_maxY];
	static const TCHAR pMapArr2[Map_maxX][Map_maxY];
	static const TCHAR pMapArr3[Map_maxX][Map_maxY];
	static const TCHAR pMapArr4[Map_maxX][Map_maxY];
	static const TCHAR pMapArr5[Map_maxX][Map_maxY];
	static const TCHAR pMapArr6[Map_maxX][Map_maxY];

public:
	static const TCHAR* SelectMap(int idx)
	{
		switch (idx)
		{
		case MAPERR:
			return &(pMapErr[0][0]);
			break;
		case MAP1:
			return &(pMapArr1[0][0]);
			break;
		case MAP2:
			return &(pMapArr2[0][0]);
			break;
		case MAP3:
			return &(pMapArr3[0][0]);
			break;
		case MAP4:
			return &(pMapArr4[0][0]);
			break;
		case MAP5:
			return &(pMapArr5[0][0]);
			break;
		case MAP6:
			return &(pMapArr6[0][0]);
			break;
		default:
			//return &(pMapErr[0][0]);
			break;
		}

		return &(pMapErr[0][0]);
	}
};





//패킷
struct RankSaveList
{
	TCHAR name[20] = {0,};
	int Score = 0;
	int Wins = 0;
	int Loses = 0;
};