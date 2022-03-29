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

	/////////Ư���ѱ��


	/// <param name="_dest">Ư�����: ���� ������ ��Ʈ�� �� ����� �� int �ڷ����Դϴ�.</param>		
	bool operator <<= (int _dest)
	{

		if (ServerUpTime == _dest)
		{
			return true;
		}
		return false;
	}

	/// <param name="_dest">Ư�����: ���� ������ �÷Կ� �� ����� �� float �ڷ����Դϴ�.</param>		
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

	// ���� ��ȣ : �ڽ��� �ο����� ��ȣ
	int LinkNumber;
	// ū��ġ
	int iLocation1;
	// ��ġ�ȿ��� ����
	int iLocation2;
	// �ϴ���
	int iWork;
	// ��ü
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
	//����
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



//Ŭ���̾�Ʈ���� ��������.
//������ ���׵��� ���Ҷ� �ʿ��� ������
typedef struct ClientsProfile
{
	bool BootSend = false;
	///////////////////////////////////////////////////////////////
	int EnterNumber = 0;						//���� ��ȣ
	SceneLocation CurLocation = SL_Err;			//�ڽ��� ��ġ
	int CurLobby = -1;							//�ڽ��� �κ�
	int CurRoom = -1;							//�ڽ��� ��
	///////////////////////////////////////////////////////////////
	SOCKET ClientSocket;						//����
	std::vector<Tstring> strLogvec;			//���ηα�
	std::list<CommonPacket> strSend;			//������� ��
	///////////////////////////////////////////////////////////////
	//�̺��������̰� ����Ǵ°͵�
	int UniqueNumber = 0;//�̰� �α��ζ� �Ľ����� ã�±������ �Ұ��̴�.
	Tstring ID;
	Tstring PW;
	Tstring MAIL;
	/////////////

	////�����̸�, ���丮
	//bool SaveProfile(const TCHAR* _str)
	//{
	//	/////////////////////////////////////
	//	//�׳� ��� ���� �����Ұ�
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

	//���ο��� ������̴ٰϴ�.
	void MakeUniqueNumber()
	{
		//�������� �����ؼ� �ο���... �̰� �޸���Ʈ�����͸� ����ϴ°��� ���ڱ���....
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







static bool ServerLog(Tstring tex1, int ClientNum, int Location1, /*����*/int Location2, int Work, int Item, TCHAR* comments = nullptr)
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
		inLocation1 = _T("�ý���");
		switch (Location2)
		{
		case SysM_UniqueNum:
		{
			inLocation2 = _T("���� ����� �Դϴ�.");
			inWork = _T("");
			inItem = _T("");
		}
			break;
		case SysM_IntologinScene:
		{
			inLocation2 = _T("���� �Ǿ��� �α��� ȭ������ �̵��߽��ϴ�.");
			inWork = _T("");
			inItem = _T("");
		}
			break;
		case SysM_EXIT:
		{
			inLocation2 = _T("���� ����");
			//���� ��� ���Ƚ��ϴ�.
			if (Item == SysI_EXITOK)
			{
				inItem = _T("���� Ŭ���̾�Ʈ�� ���� �߽��ϴ�.");

				switch (Work)
				{
				case EndClientForLogin:
				{
					inWork = _T("�α���");
				}
				break;
				case EndClientForLobby:
				{
					inWork = _T("�κ�");
				}
				break;
				case EndClientForRoom:
				{
					inWork = _T("��");
				}
				break;
				case EndClientForIngame:
				{
					inWork = _T("���� ����");
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
		//���� ����



		


	}
	break;
	default:
		break;
	}

#ifdef _UNICODE
	std::wcout << (intex1.c_str()) << L"Ŭ��ѹ� : [" << (inClientNum) << L"]  ��ġ : [" << (inLocation1.c_str()) << L"]  ���� : [" << (inLocation2.c_str()) << L"] / [" << (inWork.c_str()) << L"] / [" << (inItem.c_str()) << L"]" << std::endl;
#else
	std::cout << (intex1.c_str()) << "Ŭ��ѹ� : [" << (inClientNum) << "]  ��ġ : [" << (inLocation1.c_str()) << "]  ���� : [" << (inLocation2.c_str()) << "] / [" << (inWork.c_str()) << "] / [" << (inItem.c_str()) << "]" << std::endl;
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
	

	TCHAR m_bIsGamming;			//������ ���� ������.

	//����
	TCHAR m_iHost;				//

	//�ð�
	int m_iMaxTimeUp;
	float m_fMaxTimeDw;
	int m_iCurTimeUp;
	float m_fCurTimeDw;

	//


};