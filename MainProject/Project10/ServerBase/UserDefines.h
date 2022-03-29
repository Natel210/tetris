#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <tchar.h>


namespace std { typedef basic_string<TCHAR> tstring; }
using Tstring = std::tstring;
using schar = char;

#ifdef _UNICODE
#define _tsplitpath_s  _wsplitpath_s
#else
#define _tsplitpath_s _splitpath_s
#endif // _UNICODE


//����ڰ� ����� ��Ŷ�� ���ؼ� �����մϴ�. 

#define devcomIP	("172.20.13.13")
#define intcomIP	("192.168.202.9")
#define nextip		("192.168.202.4")

namespace
{
#ifdef _DEV
	static schar* IP = devcomIP;
#else

#ifdef _Others
	static schar* IP = nextip;
#else
	static schar* IP = intcomIP;
#endif //_Others
	
#endif //_DEV

	//static TCHAR* IP = devcomIP;
	//static TCHAR* IP = intcomIP;
	static u_short PORT = 4560;
}

#define firstLoc 1000


#define SecSysLoc 2000
#define SecLogLoc 3000
#define SecLobbyLoc 4000
#define SecRoomLoc 5000
#define SecIngameLoc 6000
#define SecLankLoc 7000

#define EndClient 400000000
#define EndClientForLogin  EndClient +1
#define EndClientForLobby  EndClient +2
#define EndClientForRoom   EndClient +3
#define EndClientForIngame EndClient +4





///////////////////////////////////////////////////////////////////////////////////////
//1�� ����
enum SceneLocation
{
	SL_Err = firstLoc,
	SL_SYS,
	SL_LOG_IN,
	SL_LOBBY,
	SL_ROOM,
	SL_INGAME,
	SL_RANKING
};
///////////////////////////////////////////////////////////////////////////////////////
//2�� ���� (��Ȯ����ġ)
enum SystemMassages
{
	SysM_UniqueNum = SecSysLoc,
	SysM_CHAT,
	SysM_EXIT,
	SysM_IntologinScene,
};




enum LoginScene
{
	LI_Err = SecLogLoc,
	LI_SIGNIN,	//�α���
	LI_CREATE,	//����
	LI_FIND,	//ID PWã��
	LI_EXIT,	//������

	LI_Enpty1,
	LI_Enpty2,
	LI_Enpty3,
	LI_Enpty4,
	LI_Enpty5,
	LI_Enpty6,
	LI_Enpty7,
	LI_Enpty8,
	LI_Enpty9,
	LI_Enpty0,//������ ���̽�
};

enum LobbyScene
{
	LB_Err = SecLobbyLoc,
	LB_CREATE,//����
	LB_ENTER,//����
	LB_FINDROOM,
	LB_CHECKPLAYER,//�÷��̾� üũ
	LB_CHAT,//ä��
	LB_RANK,//��ŷ
	LB_LOGOUT,//�α׾ƿ�
	LB_EXIT,//������

	LB_Enpty1,
	LB_Enpty2,
	LB_Enpty3,
	LB_Enpty4,
	LB_Enpty5,
	LB_Enpty6,
	LB_Enpty7,
	LB_Enpty8,
	LB_Enpty9,
	LB_Enpty0,//������ ���̽�
};

enum RoomScene
{
	RM_Err = SecRoomLoc,
	RM_READY,//�غ�
	RM_SELMAP,//�ʼ���
	RM_CHAT,//ä��
	RM_SELTIME,//�ð�����
	RM_SELNODE,//��弱��
	RM_EXIT,//������
	RM_STATSUPDATE,
	RM_INIT,
	RM_LISTUPDATE,
	RM_Enpty3,
	RM_Enpty4,
	RM_Enpty5,
	RM_Enpty6,
	RM_Enpty7,
	RM_Enpty8,
	RM_Enpty9,
	RM_Enpty0,//������ ���̽�
};

enum IngameScene
{
	IG_Err = SecIngameLoc,
	//�̰� ���� ������ ��ο� ���� �׳� �������ִ°� �´°� ������?

	IG_GAMETIME,
	IG_PLAYPANEL,//�׳� ��ü�� ��߰ڴ�. (���μ��������̴ϱ�)
	IG_NODELIST,//ó���� ��ο��� � ��尡 ����Ʈ�� �ִ��� �������ش�. (�״��� �ͽ�? ��¥�� �ε��� Ÿ������ �Ұǵ� 4086�������� ������ ���� �� �� ���� ������?)
	IG_NODESP,//�̰� Ư���� ��ų�����ɷ� ������ ��Ʈ���� ���������� �̰� ó�����ش�.  (�ڽ�)����Ʈǥ�ó��鼭 ���濡�� �ش޶�� send
			  //������� �����Ѱɺ��� ���� ������ ������ �ö�
			  IG_GAMEEND,//������ ��������� �˸��°� (������ ��쿡�� ���� �׾�����, �׷��� ������ �۾��� �ϸ鼭 ������Ʈ�� �Ǹ� �װſ� ���� �غ���)
			  IG_Player,
			  IG_Enpty2,
			  IG_Enpty3,
			  IG_Enpty4,
			  IG_Enpty5,
			  IG_Enpty6,
			  IG_Enpty7,
			  IG_Enpty8,
			  IG_Enpty9,
			  IG_Enpty0,//������ ���̽�
};

enum RankSecne
{
	RK_Err = SecLankLoc,
	RK_UPDATE,//���ö� ���� ����� �Ѵ� (���ʿ��ϰ� ���ʿ�¾���.)
	RK_FIND,// ������ ã�Ƽ� �׺��� ���¸� ǥ���Ѵ�.
	RK_REFRESH,//������ ��û

	RK_Enpty1,
	RK_Enpty2,
	RK_Enpty3,
	RK_Enpty4,
	RK_Enpty5,
	RK_Enpty6,
	RK_Enpty7,
	RK_Enpty8,
	RK_Enpty9,
	RK_Enpty0,//������ ���̽�
};


///////////////////////////////////////////////////////////////////////////////////////
//3�� ����

#define ComCmd 10000
#define RoomCmd 20000
#define GameCmd 30000

enum CommonCommend
{
	CC_Err = ComCmd,
	CC_CREATE,			// ������
	CC_CHECK,			// �˻縦
	CC_ERR,				// �ַ���
	CC_FIND,			// ã�⸦
	CC_ENTER,			// ����
	CC_UPDATE,			// ������
	CC_CHAT,			// ä����
	CC_SIGN,			// �α��� �α׾ƿ�
	CC_EXIT,			// ������
	CC_SEND,
	CC_EMPTY02,
	CC_EMPTY03,
	CC_EMPTY04,
	CC_EMPTY05,
	CC_EMPTY06
};

enum RoomCommend
{
	RC_Err = RoomCmd,
	RC_MOVE,
	RC_CHAT,
	RC_EXIT,
	RC_PLAYER,
	RC_STATS,
	RC_START,
	RC_EMPTY04,
	RC_EMPTY05,
	RC_EMPTY06
};

enum IngameCommend
{
	IC_Err = GameCmd,
	IC_NODE,
	IC_TIME,
	IC_END,
	IC_SEND,
	IC_EMPTY03,
	IC_EMPTY04,
	IC_EMPTY05,
	IC_EMPTY06
};

///////////////////////////////////////////////////////////////////////////////////////
//4�� ����

#define SysItm   100000
#define LoginItm 200000
#define LobbyItm 300000
#define RoomItm  400000
#define GameItm  500000
#define RankItm  600000

enum SysItem
{
	SysI_Unique = SysItm,
	SysI_EXITOK,
	SysI_EXITNO,
};

enum LoginItem
{
	LII_Err = LoginItm,
	LI_ID,
	LI_IDNEW,
	LI_IDALREADY,
	LI_PW,
	LI_EM,
	LI_NUM,
	LI_IDPW,
	LI_LoginOk,
	LI_NonLogin,
	LI_AllreadyLogin,
};

enum LobbyItem
{
	LBI_Err = LobbyItm,
	LB_ROOM,
	LB_PLAYER,
	LB_PLAYERLIST,
	LB_CHATCHECK,
	LB_CHATEND,
	LB_CHATPUSH,
	LB_ROOMSEARCHENTERS,
	LB_ROOMSEARCHNOMAL,
	LB_ROOMSEARCHALL,
	LB_ROOMENTER,
	LB_ROOMPWFALSE,
	LB_ROOMLIMITNUM,
	LB_ROOMISGAMMING,
	LB_ROOMERR,
	LB_RETURNTOLOGIN,
};

enum RoomItem
{
	RMI_Err = RoomItm,
	RM_MAP,
	RM_NODE,
	RM_CHAEKPLAYER,
	RM_STATS,
	RM_START,
	RM_STARTOK,
	RM_STARTNO,
	RM_EXITQ,
	RM_EXITOK,
	RM_EXITNO,
};

enum IngameItem
{
	IGI_Err = GameItm,
	IG_NODE,
	IG_TIME,
	IG_MAP,
	IG_SCORE,
	IG_ENDPLAYSTATS,
};

enum RankItem
{
	RG_Err = RankItm,
	RG_UPDATE,

};
