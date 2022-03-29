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
	static bool bIsStart;			//��ü����
	static bool bStartApply;		//���� ���� 

private:				
	static bool m_bHosts;			//ȣ��Ʈ ����
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
	




private:	// ���� Ŭ����

	class SideView* pSideeview = nullptr;						//��� ����
	class RoomMainIdle* pRoomMainidle = nullptr;
	class OtherView* pOtherViwe = nullptr;
	
	class ClientIngmaeLayer* pIngameLayer = nullptr;			//���� ������
	class SubViewLayer* pSubViewLayer = nullptr;
	class ClientIngameLogLayer* pIngameLogView = nullptr;


public:	// ���� �����
	static std::map <int, Tstring> m_RoomPlayermap;
	static std::map <int, int> m_RoomPlayerScore;


private:	// ������ �ð� �� �ε��� �������
	float m_fUpdateTime = 0.5f;
	float m_fStartUpdateTime = 0.05f;
	int nextnode = 0;


protected:	//�⺻ �Լ�
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

