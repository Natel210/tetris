#include "stdafx.h"
#include "ClientRoomScene.h"

#include "SideView.h"
#include "RoomMainIdle.h"
#include "OtherView.h"

#include "ClientIngmaeLayer.h"
#include "SubViewLayer.h"
#include "ClientIngameLogLayer.h"

#include "ClientCore.h"
#include "ClientHeader.h"

#include "Input/Input.h"
#include "Time/Time.h"


#include <assert.h>


const static float MaxEndCoolTime = 5.0f;


bool ClientRoomScene::bIsStart = false;
bool ClientRoomScene::bStartApply = false;
std::map <int, Tstring> ClientRoomScene::m_RoomPlayermap;
std::map <int, int> ClientRoomScene::m_RoomPlayerScore;
bool ClientRoomScene::m_bHosts = false; 
int ClientRoomScene::m_iMin = 3;
float ClientRoomScene::m_fSec = 0.f;
int ClientRoomScene::m_iIngameCurMin = 0;
float ClientRoomScene::m_fIngameCurSec = 0.f;
float ClientRoomScene::m_fEndCoolTime = MaxEndCoolTime;
bool ClientRoomScene::m_bIsGameEnd = false;
float  ClientRoomScene::m_fChangeCoolTime = 0.0f;
int ClientRoomScene::m_isWinPlayer = 0;

int ClientRoomScene::Init() 
{

	ClientRoomScene::m_iMin = 1;
	ClientRoomScene::m_fSec = 0.f;

	///////////////////////////////////////////////////
	//나는 정보를 받겠다고 올려준다.
	CommonPacket packets;
	packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	packets.PacProp.iLocation1 = SL_ROOM;
	packets.PacProp.iLocation2 = RM_LISTUPDATE;
	packets.PacProp.iWork = RC_PLAYER;
	packets.PacProp.iItem = RM_CHAEKPLAYER;
	packets.SetComment(_T("룸에 접속합니다."));
	ClientCore::pServer->PushSend(packets);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pSideeview = CreateLayer<SideView>(_T("idlesideview"));
	pRoomMainidle = CreateLayer<RoomMainIdle>(_T("RoomMainIdle"));
	pOtherViwe = CreateLayer<OtherView>(_T("OtherView"));

	pIngameLayer = Scene::CreateLayer<ClientIngmaeLayer>(_T("Ingame"));
	pIngameLayer->SetActive(false);
	pIngameLayer->EndUp();
	pSubViewLayer = Scene::CreateLayer<SubViewLayer>(_T("SubView"));
	pSubViewLayer->SetActive(false);
	pSubViewLayer->EndUp();
	pIngameLogView = Scene::CreateLayer<ClientIngameLogLayer>(_T("ingameLogView"));
	pIngameLogView->SetActive(false);
	pIngameLogView->EndUp();

	bStartApply = false;
	TimeManager::CreateTimer(_T("CheckSceneLoc"));
	
	return PR_OK;
}

int ClientRoomScene::release()
{
	pSideeview = nullptr;
	pRoomMainidle = nullptr;
	pIngameLayer = nullptr;
	pSubViewLayer = nullptr;
	pIngameLogView = nullptr;
	return PR_OK;
}

int ClientRoomScene::PrevSetting(float time)
{

	









	//시간 감쇄 구간.
	if (m_bIsGameEnd == true && ClientRoomScene::m_isWinPlayer != 0)
	{
		m_fEndCoolTime -= time;
	}

	if (m_fChangeCoolTime > 0.f)
	{
		m_fChangeCoolTime -= time;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//나의 노드 선택 방법
	Mynode();
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//플레이어즈 정보 받아내기
	RecvPlayerList();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//플레이어들의 시작 정보 받아내기
	//RecvPlayerStart();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//룸 정보 받아들이기
	if (!bIsStart/* && m_fEndCoolTime <= 0.0f*/)
	{
		RecvRoomStarts();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//룸 끝나는 정보
	CommonPacket packets = CommonPacket();
	packets = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_INGAME, IG_GAMEEND, IC_END, IG_ENDPLAYSTATS);
	if (packets == DisConnected)
	{
		return PR_RECONECTSURVER;
	}
	if (packets.PacProp.iLocation1 == SL_INGAME)
	{
		memcpy(&ClientCore::ClientPlayer.eGameinfo.m_Win, &packets.Comments[0], sizeof(int));
		memcpy(&ClientCore::ClientPlayer.eGameinfo.m_Lose, &packets.Comments[4], sizeof(int));
		memcpy(&ClientCore::ClientPlayer.eGameinfo.m_MostScore, &packets.Comments[8], sizeof(int));
		int windplayer = 0;
		memcpy(&windplayer, &packets.Comments[12], sizeof(int));
		m_isWinPlayer = windplayer;
		/*if (bIsStart && windplayer != 0)
		{

		}*/
		if (windplayer != 0)
		{
			m_bIsGameEnd = true;
			pIngameLayer->GameEnd();
		}
		
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//룸 플레이어 스코어
	RecvplayerScore();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//결과물 드림
	if (m_bIsGameEnd)
	{
		if (m_fEndCoolTime < 0.0f)
		{
			bStartApply = false;
			bIsStart = false;
			m_bIsGameEnd = false;
		}

		TCHAR MainTimerBuff[_MAX_PATH];
		memset(MainTimerBuff, 0, sizeof(TCHAR) * _MAX_PATH);
		RECT MainTimerRect;
		MainTimerRect.bottom = 200;
		MainTimerRect.top = 100;
		MainTimerRect.right = 300;
		MainTimerRect.left = 0;
		swprintf_s(MainTimerBuff, TEXT("[남은 시간 : %.3f]"), m_fEndCoolTime);
		Tstring strMainTimer = MainTimerBuff;
		DrawText(WinDCManager::GetPrintDC(), strMainTimer.c_str(), (int)strMainTimer.size(), &MainTimerRect, DT_LEFT);
		//return PR_OK;
	}

	//변화가 왔을 때.
	//처리한다.
	if (bStartApply == false && m_fChangeCoolTime <= 0.0f)
	{
		if (bIsStart == false)
		{
			IdelChanged(time);
			bStartApply = true;
		}
		else
		{
			ingamechnaged(time);
			bStartApply = true;
		}
		return PR_OK;
	}





















	////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////보내기
	if (PR_RECONECTSURVER == GameStartEndCheck(time))
	{
		return PR_RECONECTSURVER;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//주기마다 체크해야할것들
	if (m_fUpdateTime < 0)
	{
		if (PR_RECONECTSURVER == CommonMode(time))
		{
			return PR_RECONECTSURVER;
		}

		if (bIsStart)
		{
			if (PR_RECONECTSURVER == InGameMode(time))
			{
				return PR_RECONECTSURVER;
			}
		}
		else
		{
			if (PR_RECONECTSURVER == IdleMode(time))
			{
				return PR_RECONECTSURVER;
			}
		}
		m_fUpdateTime = 0.1f;
	}
	else
	{
		m_fUpdateTime -= time;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






	if (m_fcheckPalyer <= 0.f)
	{
		packets = CommonPacket();
		packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
		packets.PacProp.iLocation1 = SL_ROOM;
		packets.PacProp.iLocation2 = RM_LISTUPDATE;
		packets.PacProp.iWork = RC_PLAYER;
		packets.PacProp.iItem = RM_CHAEKPLAYER;
		packets.SetComment(_T("룸에 정보를 받아옵니다.."));
		ClientCore::pServer->PushSend(packets);
		m_fcheckPalyer = 0.001f;
	}
	else
	{
		m_fcheckPalyer -= time;
	}
	

		return PR_OK;
}

int ClientRoomScene::UpdatePlayerList()
{
	//CommonPacket packets;
	//packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	//packets.PacProp.iLocation1 = SL_ROOM;
	//packets.PacProp.iLocation2 = RM_LISTUPDATE;
	//packets.PacProp.iWork = RC_PLAYER;
	//packets.PacProp.iItem = RM_CHAEKPLAYER;
	//packets.SetComment(_T("찾아라!"));

	//ClientCore::pServer->PushSend(packets);




	return 0;
}

void ClientRoomScene::Mynode()
{
	if (BT_ERR == pIngameLayer->GetNextBlock())
	{
		nextnode = rand() % ((BT_31MD + 1) * 10);
		nextnode /= 10;
		pIngameLogView->SetNextNode(nextnode);
		pIngameLayer->SetNextBlock(nextnode);
	}
}

void ClientRoomScene::RecvPlayerList()
{
	CommonPacket packets2 = CommonPacket();
	packets2 = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_ROOM, RM_LISTUPDATE, RC_PLAYER, RM_CHAEKPLAYER);
	if (packets2.PacProp.iLocation1 == SL_ROOM && packets2.PacProp.iWork == RC_PLAYER
		&&packets2.PacProp.iItem == RM_CHAEKPLAYER )
	{

		m_RoomPlayermap.clear();

		int maxidx = 0;
		memcpy(&maxidx, &packets2.Comments[0], sizeof(int));

		int hostnum = 0;
		memcpy(&hostnum, &packets2.Comments[4], sizeof(int));

		//int windplayer = 0;
		//memcpy(&windplayer, &packets2.Comments[8], sizeof(int));
		//m_isWinPlayer = windplayer;
		/*if (bIsStart && windplayer != 0)
		{
			m_isWinPlayer = windplayer;
		}*/

		/////////////////////////////////////////////////////////////////////////////////////////////
		if (hostnum == ClientCore::ClientPlayer.eLoginfo.m_UniqueID)
			m_bHosts = true;
		///////////////////////////////
		else
			m_bHosts = false;
		/////////////////////////////////////////////////////////////////////////////////////////////
		TCHAR savebuff[20];
		int saveIDnum;
		for (int idx = 0; idx < maxidx; ++idx)
		{
			memcpy(&saveIDnum, &packets2.Comments[idx * 24 + 12], sizeof(int));
			memcpy(savebuff, &packets2.Comments[idx * 24 + 4 + 12], sizeof(TCHAR) * 20);
			m_RoomPlayermap.insert(std::make_pair(saveIDnum, savebuff));
		}
	}
	else if (packets2 == DisConnected)
	{
		assert(true);
		//return PR_RECONECTSURVER;
	}
}

void ClientRoomScene::RecvRoomStarts()
{
	int iMapIDX = pRoomMainidle->GetMapIDX();;
	CommonPacket packets = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_ROOM, RM_STATSUPDATE, CC_UPDATE);
	if (packets.PacProp.iLocation1 == SL_ROOM && packets.PacProp.iItem == RM_STATS)
	{
		int OtherPlayerReadys[6] = { 0, };
		memcpy(&OtherPlayerReadys[0], &packets.Comments[0], sizeof(int) * 6);
		pOtherViwe->SetOtherReady(OtherPlayerReadys);
		if (!gethost())
		{
			int iMin;
			float iSec;
			memcpy(&iMin, &packets.Comments[sizeof(int) * 6], sizeof(int));
			memcpy(&iSec, &packets.Comments[sizeof(float) * 7], sizeof(float));
			if (iMin != m_iMin || iSec != m_fSec)
			{
				pSideeview->m_bchanged = true;
				m_iMin = iMin;
				m_fSec = iSec;
			}
			memcpy(&iMapIDX, &packets.Comments[sizeof(int) * 8], sizeof(int));
			pRoomMainidle->SetMapIDX(iMapIDX);
		}
		pOtherViwe->SetOtherMap(iMapIDX);
	}
	else if (packets.PacProp.iLocation1 == SL_ROOM && packets.PacProp.iItem == RM_STARTOK)
	{
		int OtherPlayerReadys[6] = { 0, };
		memcpy(&OtherPlayerReadys[0], &packets.Comments[0], sizeof(int) * 6);
		pOtherViwe->SetOtherReady(OtherPlayerReadys);
		int iMin;
		float iSec;
		memcpy(&iMin, &packets.Comments[sizeof(int) * 6], sizeof(int));
		memcpy(&iSec, &packets.Comments[sizeof(float) * 7], sizeof(float));
		if (iMin != m_iMin || iSec != m_fSec)
		{
			pSideeview->m_bchanged = true;
			m_iMin = iMin;
			m_fSec = iSec;
		}
		memcpy(&iMapIDX, &packets.Comments[sizeof(int) * 8], sizeof(int));
		pRoomMainidle->SetMapIDX(iMapIDX);
		pOtherViwe->SetOtherMap(iMapIDX);
		bIsStart = true;
		bStartApply = false;
	}

}


void ClientRoomScene::RecvplayerScore()
{
	CommonPacket packets = CommonPacket();
	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_INGAME, IG_Player, IC_SEND, IG_SCORE);
	if (packets.PacProp.iLocation1 == SL_INGAME)
	{
		IngameScoreSurver pScroe[7] = {};
		int pDeath[7] = { 0, };
		int ApplyOp = 0;
		int OptionComment = 0;
		memcpy(&pScroe[0], &packets.Comments[0], sizeof(IngameScoreSurver) * 7);
		memcpy(&pDeath, &packets.Comments[sizeof(IngameScoreSurver) * 7], sizeof(int) * 7);
		memcpy(&ApplyOp, &packets.Comments[(sizeof(IngameScoreSurver) * 7) + (sizeof(int) * 7)], sizeof(int));
		memcpy(&OptionComment, &packets.Comments[(sizeof(IngameScoreSurver) * 7) + (sizeof(int) * 8)], sizeof(int));
		m_RoomPlayerScore.clear();
		for (int idx = 0; idx < 7; ++idx)
		{
			int score = pScroe[idx].m_Score;
			m_RoomPlayerScore.insert(std::make_pair(idx, score));
		}
		pIngameLogView->SetScore(pScroe);


		//	/////////////////////////////////////////////////////////////
		//죽음 여부를 확인 합니다.
		int GameEndType = 0;//게임의 종료타입
		int GameResult = 0;//나의 승패여부
		int AliveCount = 0;
		int DeathCount = 0;
		int EmptyCount = 0;
		//int Deathcount = 7;
		for (int i = 0; i < 7; ++i)
		{

			if (pDeath[i] == 1)
			{
				++AliveCount;
			}
			else if (pDeath[i] == 2)
			{
				++DeathCount;
			}
			else if (pDeath[i] == 0)
			{
				++EmptyCount;
			}
		}

		/*if (m_fChangeCoolTime >= 0.0f)
		{
		return 0;
		}*/

		if (AliveCount <= 1 && DeathCount != 0 && EmptyCount != 7)
		{
			if (1 == pIngameLayer->GetEnd())
			{

				//++ClientCore::ClientPlayer.eGameinfo.m_Win;
				GameEndType = 1;
				//ClientRoomScene::m_isWinPlayer = true;
				//나만 살아남고 이겼습니다.
				//난 이겼습니다.
				//나도 죽음을 줍니다.,
				// 그리고 내가 필요한 것은 
				// 나의 승리
				int a = 0;
			}
			else
			{
				//++ClientCore::ClientPlayer.eGameinfo.m_Lose;
				GameEndType = 2;
				//ClientRoomScene::m_isWinPlayer = false;
				//나는 졌습니다.
			}

			//
			if (GameEndType != 0 && m_isWinPlayer == 0)
			{
				m_fEndCoolTime = MaxEndCoolTime;
				//그리고 서버에게 나의 상태를 보내어야한다.
				//int 3개로 합시다.
				//1번 승패
				//2번 스코어
				CommonPacket packets;
				packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
				packets.PacProp.iLocation1 = SL_INGAME;
				packets.PacProp.iLocation2 = IG_GAMEEND;
				packets.PacProp.iWork = IC_END;
				packets.PacProp.iItem = IG_ENDPLAYSTATS;

				int score = pIngameLayer->GetScore();

				memcpy(&packets.Comments[0], &ClientCore::ClientPlayer.eGameinfo.m_Win, sizeof(int));
				memcpy(&packets.Comments[4], &ClientCore::ClientPlayer.eGameinfo.m_Lose, sizeof(int));
				memcpy(&packets.Comments[8], &score, sizeof(int));
				memcpy(&packets.Comments[12], &GameEndType, sizeof(int));


				ClientCore::pServer->PushSend(packets);



				//다시 받는다. 스코어를

				//memcpy(&ClientRoomScene::m_isWinPlayer, &packets.Comments[12], sizeof(int));
			}



			//1번은 다시 돌아가서 순환여부를 확인하겠습니다.
			// 이순간이 우리 모두가 죽었을떄입니다.
			// 일정 시간을 부여하고
			// 결과창을 띄워줍니다.
			// 이결과창은 받아서 만들어야할 필요가없습니다.
			// 마지막에서 받은 스코어 값과 아이디 값을 기반으로
			// 누가 몇점이라는 차일드 박스를 소환하면 그만입니다.

		}
		/////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
		//시간이 지났는지
		if (m_iIngameCurMin == 0 && m_fIngameCurSec == 0.0f)
		{
			if (m_bIsGameEnd == false)
			{
				GameEndType = 3;
				m_fEndCoolTime = MaxEndCoolTime;
				CommonPacket packets;
				packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
				packets.PacProp.iLocation1 = SL_INGAME;
				packets.PacProp.iLocation2 = IG_GAMEEND;
				packets.PacProp.iWork = IC_END;
				packets.PacProp.iItem = IG_ENDPLAYSTATS;

				int score = pIngameLayer->GetScore();

				memcpy(&packets.Comments[0], &ClientCore::ClientPlayer.eGameinfo.m_Win, sizeof(int));
				memcpy(&packets.Comments[4], &ClientCore::ClientPlayer.eGameinfo.m_Lose, sizeof(int));
				memcpy(&packets.Comments[8], &score, sizeof(int));
				memcpy(&packets.Comments[12], &GameEndType, sizeof(int));


				ClientCore::pServer->PushSend(packets);



				//다시 받는다. 스코어를


				//memcpy(&ClientRoomScene::m_isWinPlayer, &packets.Comments[12], sizeof(int));
			}
			//m_bIsGameEnd = true;
			
		}


		//	////////////////////////////////////////////////////////////

	}
}

int ClientRoomScene::StartCheck()
{


	return 0;
}


int ClientRoomScene::GameStartEndCheck(float time)
{
	if (m_fStartUpdateTime > 0.0f)
	{
		m_fStartUpdateTime -= time;
		return 0;
	}
	m_fStartUpdateTime = 0.1f;//통과했다면 다시 잡아줍니다.


	if (bIsStart == false)
	{
		if(PR_RECONECTSURVER == StartCheck())
		{
			return PR_RECONECTSURVER;
		}
	}
	else if (bIsStart == true)
	{
		if (PR_RECONECTSURVER == EndtCheck(time))
		{
			return PR_RECONECTSURVER;
		}

	}
	return 0;
}

int ClientRoomScene::EndtCheck(float time)
{
	if (!ClientCore::pServer)
	{
		return 0;
	}
	/*if ((m_iMin - m_iIngameCurMin) <= 1)
	{
		return;
	}*/

	//map을 주고 받어요
	pIngameLayer->SendMaps();
	//pSubViewLayer->RecvMaps();
	CommonPacket packets;
	packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	packets.PacProp.iLocation1 = SL_INGAME;
	packets.PacProp.iLocation2 = IG_Player;
	packets.PacProp.iWork = IC_SEND;
	packets.PacProp.iItem = IG_SCORE;
	int scores = pIngameLayer->GetScore();
	IngameScoreSurver IngameSurvers = IngameScoreSurver();
	memcpy(&IngameSurvers.m_Name[0], &ClientCore::ClientPlayer.eLoginfo.m_ID[0], sizeof(TCHAR) * 20);
	IngameSurvers.m_PlayerIngameNum = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	IngameSurvers.m_Score = scores;

	int death = pIngameLayer->GetEnd();//1이 생존 2이 사망
	int OP = 0;
	int OPcom = 0;

	memcpy(&packets.Comments[0], &IngameSurvers, sizeof(IngameScoreSurver));
	memcpy(&packets.Comments[sizeof(IngameScoreSurver)], &death, sizeof(int));
	memcpy(&packets.Comments[sizeof(IngameScoreSurver) + (sizeof(int) * 1)], &OP, sizeof(int));
	memcpy(&packets.Comments[sizeof(IngameScoreSurver) + (sizeof(int) * 2)], &OPcom, sizeof(int));

	ClientCore::pServer->PushSend(packets);




	////Sleep((10);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//받아요


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	return 0;
}

int ClientRoomScene::IdleMode(float time)
{
	CommonPacket packets;
	packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	packets.PacProp.iLocation1 = SL_ROOM;
	packets.PacProp.iLocation2 = RM_STATSUPDATE;
	packets.PacProp.iWork = CC_UPDATE;
	packets.PacProp.iItem = RM_STATS;

	int iReady = 0;
	if (pRoomMainidle->GetReady())
	{
		if (m_bHosts)
		{
			iReady = PREADY_START;
		}
		else
		{
			iReady = PREADY_READY;
		}
	}
	else
	{
		if (m_bHosts)
		{
			iReady = PREADY_WAIT;
		}
		else
		{
			iReady = PREADY_STAY;
		}
	}

	int iMapIDX = pRoomMainidle->GetMapIDX();

	memcpy(&packets.Comments[0], &iReady, sizeof(int));
	memcpy(&packets.Comments[sizeof(int)], &m_iMin, sizeof(int));
	memcpy(&packets.Comments[sizeof(int) * 2], &m_fSec, sizeof(float));
	memcpy(&packets.Comments[sizeof(int) * 2 + sizeof(float)], &iMapIDX, sizeof(int));
	///////////순수하게 시작여부만확인했었네.


	/////////////////정보를 받는다.
	//CommonPacket packets;
	//packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	//packets.PacProp.iLocation1 = SL_ROOM;
	//packets.PacProp.iLocation2 = RM_STATSUPDATE;
	//packets.PacProp.iWork = CC_UPDATE;
	//packets.PacProp.iItem = RM_START;

	//packets.SetComment(_T("시작 가능 해요?"));
	//ClientCore::pServer->PushSend(packets);


	//////////////

	ClientCore::pServer->PushSend(packets);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////아이들상태 일때 끝내기 나온거 빼주는 작업
	//ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_INGAME, IG_GAMEEND, IC_END, IG_ENDPLAYSTATS);
	//CommonPacket recvpack = CommonPacket();
	///*recvpack =*/ ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_INGAME, IG_PLAYPANEL, IC_SEND, IG_MAP);
	return 0;
}

int ClientRoomScene::InGameMode(float  time)
{
	//혹시나 있을 것을 빼주는 역할
	//ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_ROOM, RM_STATSUPDATE, CC_UPDATE);
	return 0;
}

int ClientRoomScene::CommonMode(float time)
{
	return UpdatePlayerList();
}

void ClientRoomScene::IdelChanged(float time)
{
	//아이들 뷰
	pSideeview->SetActive(true);
	pSideeview->StartUp();
	pRoomMainidle->SetActive(true);
	pRoomMainidle->StartUp();
	pOtherViwe->SetActive(true);
	pOtherViwe->StartUp();
	//////////////////////////////////////////////
	pIngameLayer->SetActive(false);
	pIngameLayer->EndUp();
	pSubViewLayer->SetActive(false);
	pSubViewLayer->EndUp();
	pIngameLogView->SetActive(false);
	pIngameLogView->EndUp();



	////나는 다시준비해야함
	pRoomMainidle->ResetReady();
	///////////////////////////////
	////나가기 우선
	pSideeview->SetPrevExit(pIngameLogView->ReturnLobby());
	///////////////////////////////
	//
	////////////////////////////////







}

void ClientRoomScene::ingamechnaged(float time)
{
	pSideeview->SetActive(false);
	pSideeview->EndUp();
	pRoomMainidle->SetActive(false);
	pRoomMainidle->EndUp();
	pOtherViwe->SetActive(false);
	pOtherViwe->EndUp();
	//////////////////////////////////////////////
	pIngameLayer->SetActive(true);
	pIngameLayer->StartUp();
	pSubViewLayer->SetActive(true);
	pSubViewLayer->StartUp();
	pIngameLogView->SetActive(true);
	pIngameLogView->StartUp();
	////////////////////////////////////////////////////
	//시간 초기화
	m_iIngameCurMin = m_iMin;
	m_fIngameCurSec = m_fSec;

	m_isWinPlayer = 0;
	//맵타일 초기화
	//pRoomMainidle->GetMapIDX();
	pIngameLayer->ClearGame(pRoomMainidle->GetMapIDX());
	//m_fEndCoolTime = MaxEndCoolTime;
	m_bIsGameEnd = false;

}

ClientRoomScene::ClientRoomScene() : Scene(), pIngameLayer(nullptr)
{
}


ClientRoomScene::~ClientRoomScene()
{
}
