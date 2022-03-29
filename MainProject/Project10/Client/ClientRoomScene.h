#pragma once
#include "Scene.h"
#include <map>

class ClientRoomScene : public Scene
{
private:
	friend class FrameCore;
	friend class ClientCore;







private:
	float m_fcheckPalyer = 0.001f;















private:	
	static bool bIsStart;			//씬체인지
	static bool bStartApply;		//적용 여부 

private:				
	static bool m_bHosts;			//호스트 여부
public:
	//get
	static bool gethost()			//get
	{
		return m_bHosts;
	}	

public:
	//ingame time
	static int m_iIngameCurMin;
	static float m_fIngameCurSec;
	//Set time
	static int m_iMin;
	static float m_fSec;
	// state end
	static bool m_bIsGameEnd;
	// result
	static int m_isWinPlayer;

	//// func apply after cool time
	static float m_fEndCoolTime;
	static float m_fChangeCoolTime;
	




private:	// 내부 클래스

	class SideView* pSideeview = nullptr;						//대기 상태
	class RoomMainIdle* pRoomMainidle = nullptr;
	class OtherView* pOtherViwe = nullptr;
	
	class ClientIngmaeLayer* pIngameLayer = nullptr;			//게임 진행중
	class SubViewLayer* pSubViewLayer = nullptr;
	class ClientIngameLogLayer* pIngameLogView = nullptr;


public:	// 내부 저장용
	static std::map <int, Tstring> m_RoomPlayermap;
	static std::map <int, int> m_RoomPlayerScore;


private:	// 내부의 시간 및 인덱스 돌리기용
	float m_fUpdateTime = 0.5f;
	float m_fStartUpdateTime = 0.05f;
	int nextnode = 0;


protected:	//기본 함수
	virtual int Init() final;
	virtual int release() final;
protected:
	virtual int PrevSetting(float time);

	//Logic
private:
	int GameStartEndCheck(float time);
private:
	int StartCheck();
	int EndtCheck(float time);
////////////////////////////////////////////////////////////
private:
	void IdelChanged(float time);
	void ingamechnaged(float time);
///////////////////////////////////////////////////////////
private:
	int IdleMode(float time);
	int InGameMode(float time);
	int CommonMode(float time);



private:
	//items
	int UpdatePlayerList();





private:
	void Mynode();

private:
	void RecvPlayerList();
	void RecvRoomStarts();
	void RecvplayerScore();
	








protected:
	ClientRoomScene();
	~ClientRoomScene();
};

