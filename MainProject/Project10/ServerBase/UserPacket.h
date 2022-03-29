#pragma once
#include "UserDefines.h"

#pragma pack(push, 1)
struct PacketTime
{
	int ServerUpTime = 0;
	float ServerTime = 0.0f;

	bool operator ==(int _dest)
	{
		if (ServerUpTime == _dest
			&& ServerTime == (float)_dest)
		{
			return true;
		}
		return false;
	}
	bool operator ==(float _dest)
	{
		if (ServerUpTime == (int)_dest
			&& ServerTime == _dest)
		{
			return true;
		}
		return false;
	}

	bool operator ==(const PacketTime& _dest)
	{
		if (ServerUpTime == _dest.ServerUpTime 
			&& ServerTime == _dest.ServerTime)
		{
			return true;
		}
		return false;
	}

	bool operator !=(const PacketTime& _dest) const
	{
		if (ServerUpTime != _dest.ServerUpTime
			|| ServerTime != _dest.ServerTime)
		{
			return true;
		}
		return false;
	}

	bool operator >(const PacketTime& _dest)
	{
		if (ServerUpTime < _dest.ServerUpTime)
		{
			return false;
		}
		else if (ServerTime <= _dest.ServerTime)
		{
			return false;
		}
		return true;
	}
	bool operator <(const PacketTime& _dest)
	{
		if (ServerUpTime > _dest.ServerUpTime)
		{
			return false;
		}
		else if (ServerTime > _dest.ServerTime)
		{
			return false;
		}
		return true;
	}
	bool operator >=(const PacketTime& _dest)
	{
		if (ServerUpTime < _dest.ServerUpTime)
		{
			return false;
		}
		else if (ServerTime < _dest.ServerTime)
		{
			return false;
		}
		return true;
	}
	bool operator <=(const PacketTime& _dest)
	{
		if (ServerUpTime > _dest.ServerUpTime)
		{
			return false;
		}
		else if (ServerTime > _dest.ServerTime)
		{
			return false;
		}
		return true;
	}

	/////////특수한기능


	/// <param name="_dest">특수기능: 상위 버전의 인트와 비교 대상이 될 int 자료형입니다.</param>		
	bool operator <<= (int _dest)
	{

		if (ServerUpTime == _dest)
		{
			return true;
		}
		return false;
	}

	/// <param name="_dest">특수기능: 하위 버전의 플롯와 비교 대상이 될 float 자료형입니다.</param>		
	bool operator >>= (float _dest)
	{
		if (ServerTime == _dest)
		{
			return true;
		}
		return false;
	}

	PacketTime()
	{}
	PacketTime(int up, float time) :ServerUpTime(up), ServerTime(time)
	{}
};

struct PacketProperty
{

	// 연결 번호 : 자신이 부여받은 번호
	int LinkNumber;
	// 큰위치
	int iLocation1;
	// 위치안에서 구역
	int iLocation2;
	// 하는일
	int iWork;
	// 주체
	int iItem;
	PacketProperty() : LinkNumber(0), iLocation1(SL_Err), iLocation2(0), iWork(0), iItem(0)
	{}
	PacketProperty(int num, int loc1, int loc2 = 0, int work = 0, int item = 0) : LinkNumber(num), iLocation1(loc1), iLocation2(loc2), iWork(work), iItem(item)
	{}

	bool operator== (const PacketProperty& _dest)
	{
		if (this->LinkNumber != _dest.LinkNumber)
		{
			return false;
		}

		if (this->iLocation1 != _dest.iLocation1)
		{
			return false;
		}

		if (this->iLocation2 != _dest.iLocation2)
		{
			return false;
		}

		if (this->iWork != _dest.iWork)
		{
			return false;
		}

		if (this->iItem != _dest.iItem)
		{
			return false;
		}

		return true;
	}

	bool operator!= (const PacketProperty& _dest) const
	{
		if (this->LinkNumber == _dest.LinkNumber)
		{
			return false;
		}

		if (this->iLocation1 == _dest.iLocation1)
		{
			return false;
		}

		if (this->iLocation2 == _dest.iLocation2)
		{
			return false;
		}

		if (this->iWork == _dest.iWork)
		{
			return false;
		}

		if (this->iItem == _dest.iItem)
		{
			return false;
		}

		return true;
	}
};


const static int CommentSize = 4096;

typedef struct CommonPacket
{
	PacketTime PacTime;
	PacketProperty PacProp;
	//내용
	TCHAR Comments[CommentSize];
	CommonPacket() :PacTime(0, 0), PacProp(0, 0, 0, 0, 0)
	{
		for (int i = 0; i < CommentSize; ++i)
		{
			Comments[i] = 0;
		}
	}
	void SetComment(const Tstring& _str)
	{
		for (int i = 0; i < CommentSize; ++i)
		{
			Comments[i] = 0;
		}
		memcpy(Comments, _str.c_str(), sizeof(_str));
	}
	void SetComment(const TCHAR* _str, int size)
	{
		for (int i = 0; i < CommentSize; ++i)
		{
			Comments[i] = 0;
		}
		memcpy(Comments, _str, sizeof(TCHAR) * size);
	}
	//void SetComment(const TCHAR* _str, int size)
	//{
	//	TCHAR buff[_MAX_PATH] = {0,};
	//	//MultiByteToWideChar()
	//	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, _str, size, buff, _MAX_PATH, NULL, NULL);

	//	for (int i = 0; i < CommentSize; ++i)
	//	{
	//		Comments[i] = 0;
	//	}
	//	memcpy(Comments, buff, sizeof(TCHAR) * size);
	//}
	//void SetComment(const std::wstring& _str)
	//{
	//	TCHAR buff[_MAX_PATH] = { 0, };
	//	//MultiByteToWideChar()
	//	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, _str.c_str(), (int)_str.size(), buff, _MAX_PATH, NULL, NULL);

	//	for (int i = 0; i < CommentSize; ++i)
	//	{
	//		Comments[i] = 0;
	//	}
	//	
	//	memcpy(Comments, buff, sizeof(TCHAR) * _str.size());
	//}
	void SetCommentinChating(const Tstring& _str)
	{
		for (int i = 0; i < CommentSize; ++i)
		{
			Comments[i] = 0;
		}

		memcpy(Comments, _str.c_str(), sizeof(TCHAR) * _str.size());
	}

	CommonPacket(PacketTime time, PacketProperty pack) :PacTime(time), PacProp(pack)
	{
		for (int i = 0; i < CommentSize; ++i)
		{
			Comments[i] = 0;
		}
	}

	bool operator== (const CommonPacket& _dest) const
	{
		if (PacTime != _dest.PacTime)
		{
			return false;
		}
		if (PacProp != _dest.PacProp)
		{
			return false;
		}
		for (int idx = 0; idx < 2048; ++idx)
		{
			if (Comments[idx] != _dest.Comments[idx])
			{
				return false;
			}
		}
		return true;
	}
	bool operator== (CommonPacket& _dest) const
	{
		if (PacTime != _dest.PacTime)
		{
			return false;
		}
		if (PacProp != _dest.PacProp)
		{
			return false;
		}
		for (int idx = 0; idx < 2048; ++idx)
		{
			if (Comments[idx] != _dest.Comments[idx])
			{
				return false;
			}
		}
		return true;
	}

}COMPAC;

static const CommonPacket DisConnected = CommonPacket(PacketTime(0,0), PacketProperty{-1,-1,-1,-1,-1});






#pragma pack(pop)



//클라이언트들의 인적사항.
//서버가 예네들을 관할때 필요한 정보들
typedef struct ClientsProfile
{
	bool BootSend = false;
	///////////////////////////////////////////////////////////////
	int EnterNumber = 0;						//고유 번호
	SceneLocation CurLocation = SL_Err;			//자신의 위치
	int CurLobby = -1;							//자신의 로비
	int CurRoom = -1;							//자신의 방
	///////////////////////////////////////////////////////////////
	SOCKET ClientSocket;						//소켓
	std::vector<Tstring> strLogvec;			//개인로그
	std::list<CommonPacket> strSend;			//보내기용 팩
	///////////////////////////////////////////////////////////////
	//미변동사항이고 저장되는것들
	int UniqueNumber = 0;//이건 로그인때 파싱으로 찾는기능으로 할것이다.
	Tstring ID;
	Tstring PW;
	Tstring MAIL;
	/////////////

	////파일이름, 디렉토리
	//bool SaveProfile(const TCHAR* _str)
	//{
	//	/////////////////////////////////////
	//	//그냥 열어서 강제 쓰기할겨
	//	//int UniqueNumber;
	//	//Tstring ID;
	//	//Tstring PW;
	//	//Tstring MAIL;

	//}

	//bool LoadProfile()
	//{
	//	/////////////////////////////////////
	//	//
	//}

	//내부에서 만들어줄겁니다.
	void MakeUniqueNumber()
	{
		//랜덤으로 생성해서 부여함... 이건 메르센트위스터를 사용하는것이 좋겠군요....
	}

	void PushPack(CommonPacket _compack)
	{
		strSend.push_back(_compack);

	}

	ClientsProfile(int EnterNum) : EnterNumber(EnterNum)
	{

	}

	ClientsProfile() {
	
	}


}CNTPF;







static bool ServerLog(Tstring tex1, int ClientNum, int Location1, /*정보*/int Location2, int Work, int Item, TCHAR* comments = nullptr)
{
	Tstring intex1 = tex1;
	int inClientNum = ClientNum;
	TCHAR buffL1[_MAX_PATH];
	_itot_s(Location1, buffL1, 10);
	Tstring  inLocation1 = buffL1;
	//
	TCHAR buffL2[_MAX_PATH];
	_itot_s(Location2, buffL2, 10);
	Tstring  inLocation2 = buffL2;
	//
	TCHAR BuffWork[_MAX_PATH];
	_itot_s(Work, BuffWork, 10);
	Tstring  inWork = BuffWork;
	//
	TCHAR BuffItem[_MAX_PATH];
	_itot_s(Item, BuffItem, 10);
	Tstring  inItem = BuffItem;

	TCHAR* incomments = comments;

	switch (Location1)
	{
	case SL_SYS:
	{
		inLocation1 = _T("시스템");
		switch (Location2)
		{
		case SysM_UniqueNum:
		{
			inLocation2 = _T("접속 대기중 입니다.");
			inWork = _T("");
			inItem = _T("");
		}
			break;
		case SysM_IntologinScene:
		{
			inLocation2 = _T("접속 되었고 로그인 화면으로 이동했습니다.");
			inWork = _T("");
			inItem = _T("");
		}
			break;
		case SysM_EXIT:
		{
			inLocation2 = _T("종료 여부");
			//종료 명령 내렸습니다.
			if (Item == SysI_EXITOK)
			{
				inItem = _T("에서 클라이언트가 종료 했습니다.");

				switch (Work)
				{
				case EndClientForLogin:
				{
					inWork = _T("로그인");
				}
				break;
				case EndClientForLobby:
				{
					inWork = _T("로비");
				}
				break;
				case EndClientForRoom:
				{
					inWork = _T("룸");
				}
				break;
				case EndClientForIngame:
				{
					inWork = _T("게임 도중");
				}
				break;
				default:
					break;
				}
			}
		}
			break;
		default:
			break;
		}
		//접속 제어



		


	}
	break;
	default:
		break;
	}

#ifdef _UNICODE
	std::wcout << (intex1.c_str()) << L"클라넘버 : [" << (inClientNum) << L"]  위치 : [" << (inLocation1.c_str()) << L"]  정보 : [" << (inLocation2.c_str()) << L"] / [" << (inWork.c_str()) << L"] / [" << (inItem.c_str()) << L"]" << std::endl;
#else
	std::cout << (intex1.c_str()) << "클라넘버 : [" << (inClientNum) << "]  위치 : [" << (inLocation1.c_str()) << "]  정보 : [" << (inLocation2.c_str()) << "] / [" << (inWork.c_str()) << "] / [" << (inItem.c_str()) << "]" << std::endl;
#endif // _UNICODE

	

	
	return true;
}








struct RoomScenedata
{

};

//
struct IngameSceneData
{
	enum GameResult
	{
		AllDie,
		TimeOver,
		Playing,
		Stay,
	};
	

	TCHAR m_bIsGamming;			//실제로 게임 중인지.

	//주인
	TCHAR m_iHost;				//

	//시간
	int m_iMaxTimeUp;
	float m_fMaxTimeDw;
	int m_iCurTimeUp;
	float m_fCurTimeDw;

	//


};