#pragma once

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

class CurIngameinfo
{
public:
	float m_fTime = 0.0f;
	TCHAR MapInfo[7][10][23] = { 0, };
	int PlayerId[7] = { 0, };
};



struct IngameScoreSurver
{
	TCHAR m_Name[20];
	int m_PlayerIngameNum = -1;
	int m_Score = 0;
	//Tstring m_strmsg;
};








class RoomInfo
{
public:
	int m_iWinIDNum = 0;

	int m_iRoomNum = 0;
	int m_iCurNum = 0;
	int m_iLimNum = 0;
	bool m_bPub = false;
	bool m_bIsActive = false;
	TCHAR m_RoomNameArr[30] = { 0, };
	int m_password = -1;
	int m_imapidx = 0;


public:
	bool IsIngame = false;
	int m_min = 0;
	float m_fsecTime = 0.0f;
	TCHAR MapInfo[7][10][23] = { 0, };
	int PlayerId[7] = { 0, };
	int PlayerReady[7] = { 0, };
	int PlayerGamescore[7] = { 0, };
	int PlayerDeath[7] = { -1, };
	int hostid = 0;

public:
	Tstring m_PushMsg[7] = { _T(""), };
public:
	Tstring getRoomSendMsg(int Playeridx);
	void ClearRoomSendMsg(int Playeridx);
	void SetRoomSendMsg(const Tstring& _str);
public:
	//문자화 보관
	Tstring m_strRoomNum = _T("");
	Tstring m_strRoomName = _T("");
	Tstring m_strRoomLimNum = _T("");
	Tstring m_strRoomCurNum = _T("");


public:
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

		return Roomresult;
	}
	void fromRoomInfoLobby(const RoomInfoLobby& Roomresult)
	{
		m_iRoomNum = Roomresult.m_iRoomNum;
		m_iCurNum = Roomresult.m_iCurNum;
		m_iLimNum = Roomresult.m_iLimNum;
		m_bPub = Roomresult.m_bPub;
		m_bIsActive = Roomresult.m_bIsActive;
		memcpy(&m_RoomNameArr[0], &Roomresult.m_RoomNameArr[0], sizeof(TCHAR) * 30);
		m_password = Roomresult.m_password;

		return;
	}

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
			MessageBox(NULL, TEXT("문자열 길이 초과, 30글자로 절삭 됩니다."), TEXT("방제 초과"), MB_OK);
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

public:
	RoomInfo();
	~RoomInfo();
};

