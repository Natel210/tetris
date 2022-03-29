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


//사용자가 사용할 패킷에 대해서 정의합니다. 

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
//1번 정보
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
//2번 정보 (정확한위치)
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
	LI_SIGNIN,	//로그인
	LI_CREATE,	//생성
	LI_FIND,	//ID PW찾기
	LI_EXIT,	//나가기

	LI_Enpty1,
	LI_Enpty2,
	LI_Enpty3,
	LI_Enpty4,
	LI_Enpty5,
	LI_Enpty6,
	LI_Enpty7,
	LI_Enpty8,
	LI_Enpty9,
	LI_Enpty0,//여분의 케이스
};

enum LobbyScene
{
	LB_Err = SecLobbyLoc,
	LB_CREATE,//생성
	LB_ENTER,//들어가기
	LB_FINDROOM,
	LB_CHECKPLAYER,//플레이어 체크
	LB_CHAT,//채팅
	LB_RANK,//랭킹
	LB_LOGOUT,//로그아웃
	LB_EXIT,//나가기

	LB_Enpty1,
	LB_Enpty2,
	LB_Enpty3,
	LB_Enpty4,
	LB_Enpty5,
	LB_Enpty6,
	LB_Enpty7,
	LB_Enpty8,
	LB_Enpty9,
	LB_Enpty0,//여분의 케이스
};

enum RoomScene
{
	RM_Err = SecRoomLoc,
	RM_READY,//준비
	RM_SELMAP,//맵선택
	RM_CHAT,//채팅
	RM_SELTIME,//시간선택
	RM_SELNODE,//노드선택
	RM_EXIT,//나가기
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
	RM_Enpty0,//여분의 케이스
};

enum IngameScene
{
	IG_Err = SecIngameLoc,
	//이건 내가 봤을때 드로우 판을 그냥 전달해주는개 맞는거 같은뎅?

	IG_GAMETIME,
	IG_PLAYPANEL,//그냥 전체를 줘야겠다. (개인소유공간이니깐)
	IG_NODELIST,//처음에 모두에게 어떤 노드가 리스트로 있는지 가르쳐준다. (그다음 믹스? 어짜피 인덱스 타임으로 할건데 4086개정도면 죽을때 까지 할 수 있지 않을가?)
	IG_NODESP,//이건 특수한 스킬같은걸로 상대방이 터트리면 서버에서는 이걸 처리해준다.  (자신)이팩트표시나면서 상대방에게 해달라고 send
			  //상대방들은 적이한걸보고 일절 숫자의 라인이 올라감
			  IG_GAMEEND,//게임이 종료됬음을 알리는것 (보내는 경우에는 내가 죽었을때, 그래서 서버가 작업을 하면서 업데이트가 되면 그거에 따라서 준비함)
			  IG_Player,
			  IG_Enpty2,
			  IG_Enpty3,
			  IG_Enpty4,
			  IG_Enpty5,
			  IG_Enpty6,
			  IG_Enpty7,
			  IG_Enpty8,
			  IG_Enpty9,
			  IG_Enpty0,//여분의 케이스
};

enum RankSecne
{
	RK_Err = SecLankLoc,
	RK_UPDATE,//들어올때 순위 계산을 한다 (불필요하게 할필요는없다.)
	RK_FIND,// 어떤사람을 찾아서 그분의 상태를 표시한다.
	RK_REFRESH,//제갱신 요청

	RK_Enpty1,
	RK_Enpty2,
	RK_Enpty3,
	RK_Enpty4,
	RK_Enpty5,
	RK_Enpty6,
	RK_Enpty7,
	RK_Enpty8,
	RK_Enpty9,
	RK_Enpty0,//여분의 케이스
};


///////////////////////////////////////////////////////////////////////////////////////
//3번 정보

#define ComCmd 10000
#define RoomCmd 20000
#define GameCmd 30000

enum CommonCommend
{
	CC_Err = ComCmd,
	CC_CREATE,			// 생성을
	CC_CHECK,			// 검사를
	CC_ERR,				// 애러를
	CC_FIND,			// 찾기를
	CC_ENTER,			// 들어가기
	CC_UPDATE,			// 갱신을
	CC_CHAT,			// 채팅을
	CC_SIGN,			// 로그인 로그아웃
	CC_EXIT,			// 나가기
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
//4번 정보

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
