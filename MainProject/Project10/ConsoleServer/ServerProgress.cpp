#include "stdafx.h"
#include "ServerProgress.h"
#include "ControllerServer.h"
#include "NetCore.h"
#include "Lobbyinfo.h"
#include "RoomInfo.h"


static bool DownScoreSort(std::pair<int, int> _src, std::pair<int, int> _dest)
{
	if (_src.first > _dest.first)
	{
		return true;
	}
	return false;
}


CommonPacket ServerProgress::Progress(const CommonPacket & _recvPack)
{
	SceneLocation enums = (SceneLocation)_recvPack.PacProp.iLocation1;

	CommonPacket resultPack = CommonPacket();

	switch (enums)
	{
	case SL_Err:
		break;
	case SL_SYS:
		resultPack = SYS_Scene(_recvPack);
		break;
	case SL_LOG_IN:
		resultPack = Login_Scene(_recvPack);
		break;
	case SL_LOBBY:
		resultPack = Lobby_Scene(_recvPack);
		break;
	case SL_ROOM:
		resultPack = Room_Scene(_recvPack);
		break;
	case SL_INGAME:
		resultPack = Ingame_Scene(_recvPack);
		break;
	case SL_RANKING:
		resultPack = Ranking_Scene(_recvPack);
		break;
	default:
		break;
	}

	return resultPack;
}

ServerProgressBase * ServerProgress::Copy()
{
	ServerProgress* newCopy = new ServerProgress;
	(*newCopy) = (*this);
	return dynamic_cast<ServerProgressBase*>(newCopy);
}

//////////////////////////////////////////////////////////////

CommonPacket ServerProgress::SYS_Scene(const CommonPacket & _recvPack)
{
	SystemMassages enums = (SystemMassages)_recvPack.PacProp.iLocation2;

	CommonPacket resultPack;

	switch (enums)
	{
	case SysM_EXIT:
	{
		resultPack = _recvPack;
		//플레이어를 알아온다,
		Player* myplayer = NetCore::FindPlayer(NetCore::FindPlayerID(resultPack.PacProp.LinkNumber));
		int location;
		if (!myplayer)
		{
			location = playLogin;
		}
		else
		{
			location = myplayer->ePlayerStates.States;
		}
		

		switch (location)
		{
		case playLogin:
		{
			resultPack.PacProp.iItem = SysI_EXITOK;
			resultPack.PacProp.iWork = EndClientForLogin;
			break;
		}

		case playlobby:
		{
			LobbyInfo* myrobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!myrobby)
			{
				resultPack.PacProp.iItem = SysI_EXITNO;
				break;
			}
			myrobby->PlayerLobbyleave(*myplayer);

			myrobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!myrobby)
			{
				resultPack.PacProp.iItem = SysI_EXITOK;
				resultPack.PacProp.iWork = EndClientForLobby;
				break;
			}
			resultPack.PacProp.iItem = SysI_EXITNO;
			break;
		}
			break;
		case playroomidle:
		{
			RoomInfo* pRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
			LobbyInfo* pRobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!pRoom)
			{
				break;
			}

			resultPack.PacProp.iItem = RM_EXITNO;
			for (int idx = 0; idx < 7; ++idx)
			{
				if (pRoom->PlayerId[idx] == resultPack.PacProp.LinkNumber)
				{

					--pRoom->m_iCurNum;
					pRoom->MapInfo[idx][10][23] = { 0, };
					pRoom->PlayerId[idx] = 0;
					pRoom->PlayerReady[idx] = 0;
					pRoom->PlayerGamescore[idx] = 0;
					pRoom->PlayerDeath[idx] = -1;
					if (pRoom->hostid == pRoom->PlayerId[idx])
					{
						pRoom->hostid = 0;
					}


					if (pRoom->m_iCurNum <= 0)
					{
						pRoom->m_iCurNum = 0;
						pRobby->DeleteRoom(pRoom->m_iRoomNum);
					}

					//pRobby->DeleteRoom(pRoom->m_iRoomNum);
					Player* curplayer = NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber));
					curplayer->ePlayerStates.RoomNum = -1;
					curplayer->ePlayerStates.States = playlobby;

					resultPack.PacProp.iItem = RM_EXITOK;
					resultPack.PacProp.iWork = EndClientForRoom;
					break;
				}
			}
			if (resultPack.PacProp.iItem != RM_EXITOK)
			{
				break;
			}



			/////////////////////////////////////////////////////////////////////////////////////
			LobbyInfo* myrobby = NetCore::FindPlayerLobby(resultPack.PacProp.LinkNumber);
			if (!myrobby)
			{
				resultPack.PacProp.iItem = SysI_EXITNO;
				break;
			}
			myrobby->PlayerLobbyleave(*myplayer);

			myrobby = NetCore::FindPlayerLobby(resultPack.PacProp.LinkNumber);
			if (!myrobby)
			{
				resultPack.PacProp.iItem = SysI_EXITOK;
				resultPack.PacProp.iWork = EndClientForRoom;
				break;
			}
			resultPack.PacProp.iItem = SysI_EXITNO;
			break;
		}
			break;
		case playingmae:
		{
			RoomInfo* pRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
			LobbyInfo* pRobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!pRoom)
			{
				break;
			}

		
			resultPack.PacProp.iItem = RM_EXITNO;
			for (int idx = 0; idx < 7; ++idx)
			{
				if (pRoom->PlayerId[idx] == resultPack.PacProp.LinkNumber)
				{
					--pRoom->m_iCurNum;
					pRoom->MapInfo[idx][10][23] = { 0, };
					pRoom->PlayerId[idx] = 0;
					pRoom->PlayerReady[idx] = 0;
					pRoom->PlayerGamescore[idx] = 0;
					pRoom->PlayerDeath[idx] = -1;
					if (pRoom->hostid == pRoom->PlayerId[idx])
					{
						pRoom->hostid = 0;
					}


					if (pRoom->m_iCurNum <= 0)
					{
						pRoom->m_iCurNum = 0;
						pRobby->DeleteRoom(pRoom->m_iRoomNum);
					}

					//pRobby->DeleteRoom(pRoom->m_iRoomNum);

					Player* curplayer = NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber));
					curplayer->ePlayerStates.RoomNum = -1;
					curplayer->ePlayerStates.States = playlobby;

					resultPack.PacProp.iItem = RM_EXITOK;
					resultPack.PacProp.iWork = EndClientForIngame;
					break;
				}
			}

			if (resultPack.PacProp.iItem != RM_EXITOK)
			{
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////
			LobbyInfo* myrobby = NetCore::FindPlayerLobby(resultPack.PacProp.LinkNumber);
			if (!myrobby)
			{
				resultPack.PacProp.iItem = SysI_EXITNO;
				break;
			}

			myrobby->PlayerLobbyleave(*myplayer);

			myrobby = NetCore::FindPlayerLobby(resultPack.PacProp.LinkNumber);
			if (!myrobby)
			{
				resultPack.PacProp.iItem = SysI_EXITOK;
				resultPack.PacProp.iWork = EndClientForIngame;
				break;
			}
			resultPack.PacProp.iItem = SysI_EXITNO;
			break;
		}
			break;
		default:
		{
			resultPack.PacProp.iItem = SysI_EXITOK;
			resultPack.PacProp.iWork = EndClient;
		}
			
			break;
		}




		//PlayerLogInfo recvliginfo;
		//memcpy(&recvliginfo, _recvPack.Comments, sizeof(PlayerLogInfo));
		//resultPack = _recvPack;
		//if (NetCore::isLogin(recvliginfo.m_ID, recvliginfo.m_PW))
		//{
		//	resultPack.PacProp.iItem = LI_LoginOk;

		//
		//	myplayer->ePlayerStates;
		//	myplayer->ePlayerStates.RoomNum = -1;
		//	myplayer->ePlayerStates.States = playlobby;
		//	memcpy(resultPack.Comments, myplayer, sizeof(Player));

		//	/////////////////////////////////////
		//	LobbyInfo* curLobby = NetCore::FindLobby(0);
		//	if (curLobby != nullptr)
		//	{
		//		curLobby->PlayerLobbyEnter(*myplayer);
		//	}
		//}
		//else
		//{
		//	resultPack.PacProp.iItem = LI_NonLogin;
		//	resultPack.SetComment("No");
		//}
		//break;
	}
		break;
	
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Login_Scene(const CommonPacket & _recvPack)
{
	LoginScene enums = (LoginScene)_recvPack.PacProp.iLocation2;

	CommonPacket resultPack;

	switch (enums)
	{
	case LI_SIGNIN:							   
		resultPack = Login_Signin(_recvPack);  
		break;								   
	case LI_CREATE:							   
		resultPack = Login_Create(_recvPack);  
		break;								   
	case LI_FIND:							   
		resultPack = Login_Find(_recvPack);	   
		break;								   
	case LI_EXIT:							   
		resultPack = Login_EXIT(_recvPack);	   
		break;								   
	default:								   
		break;								   
	}										   
	return resultPack;
}

CommonPacket ServerProgress::Lobby_Scene(const CommonPacket & _recvPack)
{

	LobbyScene enums = (LobbyScene)_recvPack.PacProp.iLocation2;

	CommonPacket resultPack;

	switch (enums)
	{
	case LB_CREATE:
		resultPack = Lobby_Create(_recvPack);
		break;
	case LB_ENTER:
		resultPack = Lobby_Enter(_recvPack);
		break;
	case LB_CHECKPLAYER:
		resultPack = Lobby_CheckPlayer(_recvPack);
		break;
	case LB_CHAT:
		resultPack = Lobby_Chat(_recvPack);
		break;
	case LB_RANK:
		resultPack = Lobby_Rank(_recvPack);
		break;
	case LB_LOGOUT:
		resultPack = Lobby_Logout(_recvPack);
		break;
	case LB_EXIT:
		resultPack = Lobby_EXIT(_recvPack);
		break;
	case LB_FINDROOM:
		resultPack = Lobby_FIndroom(_recvPack);
		break;
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Room_Scene(const CommonPacket & _recvPack)
{
	RoomScene enums = (RoomScene)_recvPack.PacProp.iLocation2;

	CommonPacket resultPack;

	switch (enums)
	{
	case RM_CHAT:
		resultPack = Room_Chat(_recvPack);
		break;
	case RM_SELTIME:
		resultPack = Room_Seltime(_recvPack);
		break;
	case RM_SELNODE:
		resultPack = Room_SelNode(_recvPack);
		break;
	case RM_EXIT:
		resultPack = Room_EXIT(_recvPack);
		break;
	case RM_INIT:
		resultPack = Room_INIT(_recvPack);
		break;
	case RM_LISTUPDATE:
		resultPack = Room_LISTUPDATE(_recvPack);
		break;
	case RM_STATSUPDATE:
		resultPack = Room_STATSUPDATE(_recvPack);
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Ingame_Scene(const CommonPacket & _recvPack)
{





	IngameScene enums = (IngameScene)_recvPack.PacProp.iLocation2;

	CommonPacket resultPack;

	switch (enums)
	{
	case IG_PLAYPANEL:
		resultPack = Ingame_PlayPanel(_recvPack);
		break;
	case IG_NODESP:
		resultPack = Ingame_NodeSp(_recvPack);
		break;
	case IG_GAMEEND:
		resultPack = Ingame_Gameend(_recvPack);
		break;
	case IG_Player:
		resultPack = Ingame_Player(_recvPack);
		break;
	default:
		break;
	}
	
	return resultPack;
}

CommonPacket ServerProgress::Ranking_Scene(const CommonPacket & _recvPack)
{
	RankSecne enums = (RankSecne)_recvPack.PacProp.iLocation2;

	CommonPacket resultPack;

	switch (enums)
	{
	case RK_UPDATE:
		resultPack = Rank_Update(_recvPack);
		break;
	case RK_FIND:
		resultPack = Rank_Find(_recvPack);
		break;
	default:
		break;
	}

	return resultPack;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

CommonPacket ServerProgress::Login_Signin(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_CHECK:
	{
		PlayerLogInfo recvliginfo;
		memcpy(&recvliginfo, _recvPack.Comments, sizeof(PlayerLogInfo));
		resultPack = _recvPack;
		int ilogins = NetCore::isLogin(recvliginfo.m_ID, recvliginfo.m_PW);
		if (ilogins == 2)
		{
			resultPack.PacProp.iItem = LI_LoginOk;
			
			Player* myplayer = NetCore::FindPlayer(recvliginfo.m_ID);
			myplayer->ePlayerStates;
			myplayer->ePlayerStates.RoomNum = -1;
			myplayer->ePlayerStates.States = playlobby;
			memcpy(resultPack.Comments, myplayer, sizeof(Player));

			/////////////////////////////////////
			LobbyInfo* curLobby = NetCore::FindLobby(0);
			if (curLobby != nullptr)
			{
				curLobby->PlayerLobbyEnter(*myplayer);
			}
		}
		else if (ilogins == 1)
		{
			resultPack.PacProp.iItem = LI_AllreadyLogin;
			resultPack.SetComment(_T("No-AllreadyLogin"));
		}
		else
		{
			resultPack.PacProp.iItem = LI_NonLogin;
			resultPack.SetComment(_T("No"));
		}
		break;
	}
	default:
		break;
	}


	return resultPack;
}

CommonPacket ServerProgress::Login_Create(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_CREATE:
	{
		PlayerLogInfo recvliginfo;
		memcpy(&recvliginfo, _recvPack.Comments, sizeof(PlayerLogInfo));

		//////////////////////////////////
		//고유번호 부여
		SYSTEMTIME eTime;
		GetSystemTime(&eTime);
		int unnum = eTime.wMinute * 1000000;
		unnum += eTime.wSecond * 10000;
		unnum += eTime.wMilliseconds;
		recvliginfo.m_UniqueID = unnum;

		//////////////////////////////////
		NetCore::AddPlayer(recvliginfo);
		resultPack.PacProp = _recvPack.PacProp;
		
		resultPack.SetComment(_T("OK"));
		break;
	}
		
	case CC_CHECK:
	{
		if (_recvPack.PacProp.iItem == LI_ID)
		{
			PlayerLogInfo recvliginfo;
			memcpy(&recvliginfo, _recvPack.Comments, sizeof(PlayerLogInfo));
			resultPack.PacProp = _recvPack.PacProp;
			if (NetCore::isPlayerId(recvliginfo.m_ID))
			{
				resultPack = _recvPack;
				resultPack.PacProp.iItem = LI_IDALREADY;
			}
			else
			{
				resultPack = _recvPack;
				resultPack.PacProp.iItem = LI_IDNEW;
				//resultPack.SetComment(_T("OK"));
			}
		}

		break;
	}
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Login_Find(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_FIND:
	{
		if (_recvPack.PacProp.iItem == LI_ID)
		{
			resultPack = _recvPack;
			TCHAR embuff[_MAX_PATH];
			memcpy(embuff, (void*)_recvPack.Comments, sizeof(TCHAR) * 100);
			Tstring strid = NetCore::FindID(embuff);
			if (strid == _T(""))
			{
				resultPack.SetComment(_T("[ 없음 ]"));
			}
			else
			{
				resultPack.SetComment(strid);
			}
			
			break;
		}
		if (_recvPack.PacProp.iItem == LI_PW)
		{
			resultPack = _recvPack;
			PlayerLogInfo embuff;
			memcpy(&embuff, (void*)_recvPack.Comments, sizeof(PlayerLogInfo));
			Tstring strid = NetCore::FindPW(embuff.m_Email,embuff.m_ID);
			if (strid == _T(""))
			{
				resultPack.SetComment(_T(""));
			}
			else
			{
				resultPack.SetComment(strid);
			}
			break;
		}
	}
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Login_EXIT(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_EXIT:
		break;
	default:
		break;
	}
	return resultPack;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

CommonPacket ServerProgress::Lobby_Create(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_CREATE:
	{
		if (_recvPack.PacProp.iItem == LB_ROOM)
		{
			resultPack = _recvPack;


			LobbyInfo* curlobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);


			int idx = 1;
			while (true)
			{
				if (!curlobby->FindRoom(idx))
				{
					break;
				}
				++idx;
			}

			curlobby->CreateRoom(idx);
			
			

			RoomInfo* CreatesRoom = curlobby->FindRoom(idx);
			memcpy(CreatesRoom->m_RoomNameArr, &_recvPack.Comments[0], sizeof(TCHAR) * 30);
			memcpy(&CreatesRoom->m_iLimNum, &_recvPack.Comments[30], sizeof(int));
			memcpy(&CreatesRoom->m_bPub, &_recvPack.Comments[30 + sizeof(int)], sizeof(bool));
			memcpy(&CreatesRoom->m_password, &_recvPack.Comments[30 + sizeof(int) + sizeof(bool)], sizeof(int));

			CreatesRoom->m_iRoomNum = idx;
			CreatesRoom->m_iCurNum = 1;
			CreatesRoom->m_bIsActive = true;
			CreatesRoom->PlayerId[0] = _recvPack.PacProp.LinkNumber;


			Player* curplayer = NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber));
			curplayer->ePlayerStates.RoomNum = idx;
			curplayer->ePlayerStates.States = playroomidle;

			memcpy(resultPack.Comments, &CreatesRoom->m_iRoomNum, sizeof(int));

			//Player finplayer = NetCore::FindPlayer(_recvPack.Comments);
			//if (finplayer.eLoginfo.m_UniqueID == _recvPack.PacProp.LinkNumber)
			//{
			//	memcpy(resultPack.Comments, &finplayer, sizeof(Player));
			//	//resultPack.Comments
			//}

			break;
		}
	}
	case CC_ERR:
		break;
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Lobby_Enter(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	resultPack = _recvPack;

	switch (enums)
	{
	case CC_ENTER:
		if (_recvPack.PacProp.iItem == LB_ROOM)
		{
			int iroomnum = 0;
			memcpy(&iroomnum, _recvPack.Comments, sizeof(int));

			LobbyInfo* pFindLobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!pFindLobby)
			{
				resultPack.PacProp.iItem = LB_ROOMERR;
				break;
			}
			RoomInfo* pFindRoom = pFindLobby->FindRoom(iroomnum);
			if (!pFindRoom)
			{
				resultPack.PacProp.iItem = LB_ROOMERR;
				break;
			}
			if (pFindRoom->IsIngame == true)
			{
				resultPack.PacProp.iItem = LB_ROOMISGAMMING;
			}
			else if (pFindRoom->m_iCurNum < pFindRoom->m_iLimNum)
			{
				++pFindRoom->m_iCurNum;
			}
			else
			{
				//실패를 리턴해준다.
				resultPack.PacProp.iItem = LB_ROOMLIMITNUM;
				break;
			}
			
			Player* curplayer = NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber));
			curplayer->ePlayerStates.RoomNum = iroomnum;
			curplayer->ePlayerStates.States = playroomidle;
			resultPack.PacProp.iItem = LB_ROOMENTER;
			pFindLobby->EnterRoom(pFindRoom->m_iRoomNum, curplayer->eLoginfo.m_UniqueID);
			//	LB_ROOMPWFALSE,


		}

		break;
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Lobby_CheckPlayer(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_FIND:
	{
		if (_recvPack.PacProp.iItem == LB_PLAYERLIST)
		{
			resultPack = _recvPack;

			LobbyInfo* plobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (plobby)
			{
				std::unordered_map<int, Player> players =  plobby->getLobbyPlayers();
				std::unordered_map<int, Player>::iterator m_startiter = players.begin();

				int Size = (int)players.size();
				if (Size > 400)
				{
					Size = 400;
				}


				//푸싱
				TCHAR* newdata = new TCHAR[ (Size) * 24  + 4];
				memcpy(&newdata[0], &Size, sizeof(int));

				for (int i = 1 ; i < Size + 1; ++i)
				{
					if (m_startiter == players.end())
					{
						Size = i;
						break;
					}
					memcpy(&newdata[i * 24 - 20], &m_startiter->second.eLoginfo.m_UniqueID, sizeof(int));
					memcpy(&newdata[i* 24 - 16], &m_startiter->second.eLoginfo.m_ID[0], sizeof(TCHAR) * 20);
					++m_startiter;
				}

				memcpy(&resultPack.Comments[0], &newdata[0], sizeof(TCHAR) * ((Size * 24) + 4));
				

				delete[] newdata;
				newdata = nullptr;
			}
			break;
		}
				
		if (_recvPack.PacProp.iItem == LB_PLAYER)
		{
			resultPack = _recvPack;
			Player* finplayer = NetCore::FindPlayer(_recvPack.Comments);
			if (!finplayer)
			{
				break;
			}
			memcpy(resultPack.Comments, finplayer, sizeof(Player));


			//if (finplayer->eLoginfo.m_UniqueID == _recvPack.PacProp.LinkNumber)
			//{
			//	memcpy(resultPack.Comments, finplayer, sizeof(Player));
			//	//resultPack.Comments
			//}

			break;
		}


		break;
	}
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Lobby_Chat(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	resultPack = _recvPack;
	switch (enums)
	{
	case CC_CHAT:
	{
		if (_recvPack.PacProp.iItem == LB_CHATPUSH)
		{
			Tstring strmsg = NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber);
			strmsg += _T(": ");
			strmsg += _recvPack.Comments;
			//Player findplayer = NetCore::FindPlayer(_recvPack.PacProp.LinkNumber);
			//findplayer
			NetCore::SetLobbySendMsg(_recvPack.PacProp.LinkNumber, strmsg);
		}
		resultPack.SetComment(_T("ok"));
	}
		break;
	case CC_FIND:
	{
		if (_recvPack.PacProp.iItem == LB_CHATCHECK)
		{
			Tstring sendmsg = NetCore::getLobbySendMsg(_recvPack.PacProp.LinkNumber);
			resultPack.SetCommentinChating(sendmsg);
			break;
		}
		if (_recvPack.PacProp.iItem == LB_CHATEND)
		{
			NetCore::ClearLobbySendMsg(_recvPack.PacProp.LinkNumber);
			//resultPack.SetComment(sendmsg);
			break;
		}


	}
		
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Lobby_Rank(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_ENTER:
		break;
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Lobby_Logout(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_ENTER:
	{
		if (_recvPack.PacProp.iItem == LB_RETURNTOLOGIN)
		{
			LobbyInfo* myrobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!myrobby)
			{
				break;
			}
			myrobby->PlayerLobbyleave(*NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber)));
			resultPack = _recvPack;
			//myrobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			//if (!myrobby)
			//{
			//	//resultPack.PacProp.iItem = SysI_EXITOK;
			//	//resultPack.PacProp.iWork = EndClientForLobby;

			//	break;
			//}
			////resultPack.PacProp.iItem = SysI_EXITNO;



		}
		break;
	}
		
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Lobby_EXIT(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_EXIT:
		break;
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Lobby_FIndroom(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_FIND:
	{
		resultPack = _recvPack;
		if (_recvPack.PacProp.iItem == LB_ROOMSEARCHENTERS)
		{
			int startcount = 0;
			memcpy(&startcount, &_recvPack.Comments[0], sizeof(int));


			LobbyInfo* curlobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!curlobby)
			{
				break;
			}
			int cursel = curlobby->EnterableRoom(startcount);

			RoomInfoLobby Searchrooms[9] = { RoomInfoLobby(), };
			int roomcount = 0;
			RoomInfo* curroom = nullptr;

			cursel += 0;
			if (curlobby)
			{
				while (true)
				{
					if (curlobby->RoomSize() < cursel)
					{
						break;
					}

					curroom = nullptr;
					curroom = curlobby->FindRoom(cursel);
					if (curroom)
					{
						if (!curroom->m_bIsActive)
						{
						}
						else if (curroom->m_iLimNum <= curroom->m_iCurNum)
						{

						}
						else if (curroom->IsIngame)
						{
						}
						else
						{
							Searchrooms[roomcount] = (curroom)->toRoomInfoLobby();
							++roomcount;
							if (9 <= roomcount)
							{
								break;
							}
						}
					}
					++cursel;
				}
			}
			memcpy(&resultPack.Comments[0], &Searchrooms[0], sizeof(RoomInfoLobby) * 9);
		}

		if (_recvPack.PacProp.iItem == LB_ROOMSEARCHALL)
		{
			int startcount = 0;
			memcpy(&startcount, &_recvPack.Comments[0], sizeof(int));


			LobbyInfo* curlobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
			if (!curlobby)
			{
				break;
			}
			int cursel = startcount; //= curlobby->EnterableRoom(startcount);

			RoomInfoLobby Searchrooms[9] = { RoomInfoLobby(), };
			int roomcount = 0;
			RoomInfo* curroom = nullptr;


			if (curlobby)
			{
				while (true)
				{
					if (curlobby->RoomSize() < cursel)
					{
						break;
					}

					curroom = nullptr;
					curroom = curlobby->FindRoom(cursel);
					if (curroom)
					{
						if (!curroom->m_bIsActive)
						{
						}
						/*	else if (curroom->m_iLimNum <= curroom->m_iCurNum)
							{

							}
							else if (curroom->IsIngame)
							{
							}*/
						else
						{
							Searchrooms[roomcount] = (curroom)->toRoomInfoLobby();
							++roomcount;
							if (9 <= roomcount)
							{
								break;
							}
						}
					}
					++cursel;
				}
			}
			memcpy(&resultPack.Comments[0], &Searchrooms[0], sizeof(RoomInfoLobby) * 9);
		}
		break;
	}
	default:
		break;
	}
	return resultPack;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
CommonPacket ServerProgress::Room_Chat(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	resultPack = _recvPack;
	RoomInfo* pRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
	if (!pRoom)
	{
		resultPack.SetComment(_T(""));
		return resultPack;
	}
	switch (enums)
	{
	case CC_CHAT:
	{
		if (_recvPack.PacProp.iItem == LB_CHATPUSH)
		{
			Tstring strmsg = NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber);
			strmsg += _T(": ");
			strmsg += _recvPack.Comments;
			//Player findplayer = NetCore::FindPlayer(_recvPack.PacProp.LinkNumber);
			//findplayer
			pRoom->SetRoomSendMsg(strmsg);
			resultPack.SetComment(_T("ok"));
			break;
		}
	}
	case CC_FIND:
	{
		if (_recvPack.PacProp.iItem == LB_CHATCHECK)
		{
			Tstring sendmsg = pRoom->getRoomSendMsg(_recvPack.PacProp.LinkNumber);
			resultPack.SetCommentinChating(sendmsg);
			break;
		}
		if (_recvPack.PacProp.iItem == LB_CHATEND)
		{
			pRoom->ClearRoomSendMsg(_recvPack.PacProp.LinkNumber);
			resultPack.SetComment(_T("ClearTCHARleave"));
			break;
		}
		
	}

	default:
		break;
	}
	//resultPack = _recvPack;
	return resultPack;
}

CommonPacket ServerProgress::Room_Seltime(const CommonPacket & _recvPack)
{
	RoomCommend enums = (RoomCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case RC_MOVE:
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Room_SelNode(const CommonPacket & _recvPack)
{
	RoomCommend enums = (RoomCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case RC_MOVE:
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Room_EXIT(const CommonPacket & _recvPack)
{
	RoomCommend enums = (RoomCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case RC_EXIT:
	{
		resultPack = _recvPack;
		RoomInfo* pRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
		LobbyInfo* pRobby = NetCore::FindPlayerLobby(_recvPack.PacProp.LinkNumber);
		if (!pRoom)
		{
			Player* curplayer = NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber));
			curplayer->ePlayerStates.RoomNum = -1;
			curplayer->ePlayerStates.States = playlobby;

			resultPack.PacProp.iItem = RM_EXITOK;
			break;
		}

		if (resultPack.PacProp.iItem == RM_EXITQ)
		{
			resultPack.PacProp.iItem = RM_EXITNO;
			for (int idx = 0; idx < 7; ++idx)
			{
				if (pRoom->PlayerId[idx] == resultPack.PacProp.LinkNumber)
				{
					--pRoom->m_iCurNum;
					pRoom->MapInfo[idx][10][23] = { 0, };
					pRoom->PlayerId[idx] = 0;
					pRoom->PlayerReady[idx] = 0;
					pRoom->PlayerGamescore[idx] = 0;
					pRoom->PlayerDeath[idx] = -1;
					if (pRoom->hostid == pRoom->PlayerId[idx])
					{
						pRoom->hostid = 0;
					}


					if (pRoom->m_iCurNum <= 0)
					{
						pRoom->m_iCurNum = 0;
						pRobby->DeleteRoom(pRoom->m_iRoomNum);
					}

					//////////////////////////////////////////
					
					Player* curplayer = NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber));
					curplayer->ePlayerStates.RoomNum = -1;
					curplayer->ePlayerStates.States = playlobby;

					resultPack.PacProp.iItem = RM_EXITOK;
					return resultPack;
				}
			}
		}
		
	}
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Room_INIT(const CommonPacket & _recvPack)
{
	RoomCommend enums = (RoomCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case RC_PLAYER:
	{
		resultPack = _recvPack;
		//TCHAR clear[]
		//memcpy
		RoomInfo* pRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
		if (!pRoom)
		{
			break;
		}
		int saveIDnum = 0;
		for (int idx = 0; idx < 7; ++idx)
		{
			saveIDnum = pRoom->PlayerId[idx];
			memcpy(&resultPack.Comments[idx * 24 + 4], &saveIDnum, sizeof(int));
			memcpy(&resultPack.Comments[idx * 24 + 4 + 4], NetCore::FindPlayerID(pRoom->PlayerId[idx]).c_str(), sizeof(TCHAR) * 20);
		}
	}
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Room_LISTUPDATE(const CommonPacket & _recvPack)
{
	RoomCommend enums = (RoomCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case RC_PLAYER:
	{
		resultPack = _recvPack;
		//TCHAR clear[]
		//memcpy
		RoomInfo* curRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
		if (!curRoom)
		{
			break;
		}
		//////////////////////////////////////////////////// 7 * 20의 정보를 받음

		int counts = 0;
		int saveIDnum = 0;
		for (int idx = 0; idx < 7; ++idx)
		{
			saveIDnum = curRoom->PlayerId[idx];
			if (saveIDnum == -1)
			{

				
			}
			else if (saveIDnum == 0)
			{
			}
			else
			{
				memcpy(&resultPack.Comments[counts * 24 + 12], &saveIDnum, sizeof(int));
				memcpy(&resultPack.Comments[counts * 24 + 4 + 12], NetCore::FindPlayerID(saveIDnum).c_str(), sizeof(TCHAR) * 20);
				++counts;
			}
		}
		memcpy(&resultPack.Comments[0], &counts, sizeof(int));

		bool Cheocks = false;
		int hostplayer = -1;
		for (int idx = 0; idx < 7; ++idx)
		{
			if (curRoom->PlayerId[idx] == curRoom->hostid)
			{
				Cheocks = true;
				hostplayer = curRoom->hostid;
				break;
			}
		}
		if (!Cheocks)
		{
			curRoom->hostid = 0;
		}
		if (curRoom->hostid == 0)
		{
			for (int idx = 0; idx < 7; ++idx)
			{
				if (curRoom->PlayerId[idx] != 0)
				{
					curRoom->hostid = curRoom->PlayerId[idx];
					hostplayer = curRoom->hostid;
					break;
				}
			}
		}


		if (curRoom->hostid == 0)
		{
			//룸파괴염

		}
		else
		{
			memcpy(&resultPack.Comments[4], &hostplayer, sizeof(int));
		}
		
		memcpy(&resultPack.Comments[8], &curRoom->m_iWinIDNum, sizeof(int));
		/*	if ()
			{
				memcpy(&resultPack.Comments[8], &curRoom->m_iWinIDNum, sizeof(int));
			}*/
		

		//////////////////////////////////////////////
		//여기서 스테이트를 판단해서 지우고 하는작업을한다.,
		if (curRoom->IsIngame)
		{
			////준비상태
			//curRoom->PlayerReady[0] = 0;
			//curRoom->PlayerReady[1] = 0;
			//curRoom->PlayerReady[2] = 0;
			//curRoom->PlayerReady[3] = 0;
			//curRoom->PlayerReady[4] = 0;
			//curRoom->PlayerReady[5] = 0;
			//curRoom->PlayerReady[6] = 0;

			////1번 유효인지 체크한다.
			//bool Cheocks = false;
			//for (int idx = 0; idx < 7; ++idx)
			//{
			//	if (curRoom->PlayerId[idx] == curRoom->hostid)
			//	{
			//		Cheocks = true;
			//		break;
			//	}
			//}
			//if (!Cheocks)
			//{
			//	curRoom->hostid = 0;
			//}
			//if (curRoom->hostid == 0)
			//{
			//	for (int idx = 0; idx < 7; ++idx)
			//	{
			//		if (curRoom->PlayerId[idx] != 0)
			//		{
			//			curRoom->hostid = curRoom->PlayerId[idx];
			//			curRoom->PlayerReady[idx] = 1;
			//			break;
			//		}
			//	}
			//}

			//for (int idx = 0; idx < 7; ++idx)
			//{
			//	if (curRoom->PlayerId[idx] == curRoom->hostid)
			//	{
			//		curRoom->PlayerReady[idx] = 3;
			//		continue;
			//	}
			//	if (curRoom->PlayerId[idx] != 0)
			//	{
			//		curRoom->PlayerReady[idx] = 1;
			//	}

			//}
		}
		else
		{
			//맵정리
			memset(curRoom->MapInfo, 0, sizeof(TCHAR) * 7 * 10 * 23);
			//죽음 정리

			memset(curRoom->PlayerDeath, 0, sizeof(int) * 7);

			//점수정리
			memset(curRoom->PlayerGamescore, 0, sizeof(int) * 7);
			//시간정리
		}

/*
		std::unordered_map<int, Player>copymap = curlobby->getLobbyPlayers();
		std::unordered_map<int, Player>::iterator startiter = copymap.begin();
		std::unordered_map<int, Player>::iterator enditer = copymap.end();
		
		int mapsize = (int)copymap.size();
		memcpy(&resultPack.Comments[0], &mapsize, sizeof(TCHAR)*4);
		int counts = 0;
		int saveIDnum = 0;
		for (; startiter != enditer; ++startiter, ++counts)
		{
			saveIDnum = startiter->second.eLoginfo.m_UniqueID;
			memcpy(&resultPack.Comments[counts * 24 + 4], &saveIDnum, sizeof(int));
			memcpy(&resultPack.Comments[counts * 24 + 4 + 4], startiter->second.eLoginfo.m_ID, sizeof(TCHAR) * 20);
		}*/
	}
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Room_STATSUPDATE(const CommonPacket & _recvPack)
{
	RoomCommend enums = (RoomCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_UPDATE:
	{
		resultPack = _recvPack;
		if (resultPack.PacProp.iItem == RM_STATS)
		{
			RoomInfo* curRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
			if (!curRoom)
			{
				break;
			}
			int readys = 0;
			memcpy(&readys, &resultPack.Comments[0], sizeof(int));
			//자신의 번호를 찾는다.
			int Myidx = -1;
			for (int idx = 0; idx < 7; ++idx)
			{
				if (curRoom->PlayerId[idx] == resultPack.PacProp.LinkNumber)
				{
					Myidx = idx;
					break;
				}
			}
			if (Myidx == -1)
			{
				break;
			}
			curRoom->PlayerReady[Myidx] = readys;


			if (readys == 3 || readys == 4)
			{
				int min;
				float sec;

				memcpy(&min, &resultPack.Comments[sizeof(int)], sizeof(int));
				memcpy(&sec, &resultPack.Comments[sizeof(int) * 2], sizeof(float));
				curRoom->m_min = min;
				curRoom->m_fsecTime = sec;


				int mapidx;
				memcpy(&mapidx, &resultPack.Comments[sizeof(int) * 2 + sizeof(float)], sizeof(int));
				curRoom->m_imapidx = mapidx;
			}

			int OtherPlayerReadys[6] = { 0, };

			int count = 0;
			for (int idx = 0; (idx < 7) && (count < 6); ++idx)
			{
				if (curRoom->PlayerId[idx] == resultPack.PacProp.LinkNumber)
				{
					continue;
				}
				else
				{
					OtherPlayerReadys[count] = curRoom->PlayerReady[idx];
					++count;
				}

			}

			memcpy(&resultPack.Comments[0], &OtherPlayerReadys[0], sizeof(int) * 6);
			memcpy(&resultPack.Comments[sizeof(int) * 6], &curRoom->m_min, sizeof(int));
			float sec = curRoom->m_fsecTime;
			memcpy(&resultPack.Comments[sizeof(int) * 7], &sec, sizeof(float));
			memcpy(&resultPack.Comments[sizeof(int) * 7 + sizeof(float)], &curRoom->m_imapidx, sizeof(int));


			//적용
			if (curRoom->IsIngame)
			{
				resultPack.PacProp.iItem = RM_STARTOK;
				curRoom->m_iWinIDNum = 0;
				break;
			}
			bool NoStartGame = false;
			int countNon = 0;
			bool isHostPlayer = false;
			int isPlayer = 0;

			for (int idx = 0; idx < 7; ++idx)
			{
				if (curRoom->PlayerReady[idx] == 0)
				{
					++countNon;
					continue;
				}
				if (curRoom->PlayerReady[idx] == 3)
				{
					NoStartGame = true;
					break;
				}
				if (curRoom->PlayerReady[idx] == 1)
				{
					NoStartGame = true;
					break;
				}

				if (curRoom->PlayerReady[idx] == 4)
				{
					isHostPlayer = true;
					continue;
				}
				if (curRoom->PlayerReady[idx] == 2)
				{
					++isPlayer;
					continue;
				}

			}

			if (!isHostPlayer)
			{
				NoStartGame = true;
			}
			if (isPlayer == 0)
			{
				NoStartGame = true;
			}




			if (countNon > 5)
			{
				NoStartGame = true;
			}


			if (!NoStartGame)
			{
				resultPack.PacProp.iItem = RM_STARTOK;

				Player* pResultPlayer = nullptr;
				for (int idx = 0; idx < 7; ++idx)
				{
					pResultPlayer = nullptr;
					pResultPlayer = NetCore::FindPlayer(NetCore::FindPlayerID(curRoom->PlayerId[idx]));
					if (!pResultPlayer)
					{
						continue;
					}
					pResultPlayer->ePlayerStates.States = playingmae;
				}
				//게임상태
				curRoom->IsIngame = true;

				//맵정리
				memset(curRoom->MapInfo, 0, sizeof(TCHAR) * 7 * 10 * 23);
				//죽음 정리

				memset(curRoom->PlayerDeath, 0, sizeof(int) * 7);

				//점수정리
				memset(curRoom->PlayerGamescore, 0, sizeof(int) * 7);
				
			}
			else
			{

				//시간정리

				//for (int idx = 0; idx < 7; ++idx)
				//{
				//	if (curRoom->PlayerReady[idx] == 4)
				//	{
				//		curRoom->PlayerReady[idx] = 3;
				//	}
				//	if (curRoom->PlayerReady[idx] == 2)
				//	{
				//		curRoom->PlayerReady[idx] = 1;
				//	}
				//}
				//curRoom->m_iWinIDNum = 0;

				

			}
			break;
			///////////////////////////////////////////////////////////////////////////////////////////////
			//if (resultPack.PacProp.iItem == RM_STATS)
			//{
			//	RoomInfo* curRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
			//	if (!curRoom)
			//	{
			//		break;
			//	}
			//	/////////////////////////
			//	int readys = 0;
			//	memcpy(&readys, &resultPack.Comments[0], sizeof(int));
			//	///////////////////////////
			//	//자신의 번호를 찾는다.
			//	int Myidx = -1;
			//	for (int idx = 0 ;idx < 7; ++idx)
			//	{
			//		if (curRoom->PlayerId[idx] == resultPack.PacProp.LinkNumber)
			//		{
			//			Myidx = idx;
			//			break;
			//		}
			//	}
			//	if (Myidx == -1)
			//	{
			//		break;
			//	}
			//	curRoom->PlayerReady[Myidx] = readys;
			//	if (readys == 3 || readys == 4)
			//	{
			//		int min;
			//		float sec;
			//		memcpy(&min, &resultPack.Comments[sizeof(int)], sizeof(int));
			//		memcpy(&sec, &resultPack.Comments[sizeof(int) * 2], sizeof(float));
			//		curRoom->m_min = min;
			//		curRoom->m_fsecTime = sec;
			//		int mapidx;
			//		memcpy(&mapidx, &resultPack.Comments[sizeof(int)*2 + sizeof(float)], sizeof(int));
			//		curRoom->m_imapidx = mapidx;
			//	}
			//	///////////////정보의 업데이트는 끗
			//	int OtherPlayerReadys[6] = { 0, };
			//	
			//	int count = 0;
			//	for (int idx = 0; (idx < 7) && (count < 6) ; ++idx)
			//	{
			//		if (curRoom->PlayerId[idx] == resultPack.PacProp.LinkNumber)
			//		{
			//			continue;
			//		}
			//		else
			//		{
			//			OtherPlayerReadys[count] = curRoom->PlayerReady[idx];
			//			++count;
			//		}
			//		 
			//	}
			//	memcpy(&resultPack.Comments[0] , &OtherPlayerReadys[0], sizeof(int) *6);
			//	memcpy(&resultPack.Comments[sizeof(int) * 6], &curRoom->m_min, sizeof(int));
			//	float sec = curRoom->m_fsecTime;
			//	memcpy(&resultPack.Comments[sizeof(int) * 7], &sec, sizeof(float));
			//	memcpy(&resultPack.Comments[sizeof(int) * 7 + sizeof(float)], &curRoom->m_imapidx, sizeof(int));
			//}
			//
			//if (resultPack.PacProp.iItem == RM_START)
			//{
			//	RoomInfo* curRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
			//	if (!curRoom)
			//	{
			//		break;
			//	}
			//	if (curRoom->IsIngame)
			//	{
			//		resultPack.PacProp.iItem = RM_STARTOK;
			//		break;
			//	}
			//	bool NoStartGame = false;
			//	int countNon = 0;
			//	bool isHostPlayer = false;
			//	int isPlayer = 0;
			//	for (int idx = 0; idx < 7; ++idx)
			//	{
			//		if (curRoom->PlayerReady[idx] == 0)
			//		{
			//			++countNon;
			//			continue;
			//		}
			//		if (curRoom->PlayerReady[idx] == 3)
			//		{
			//			NoStartGame = true;
			//			break;
			//		}
			//		if (curRoom->PlayerReady[idx] == 1)
			//		{
			//			NoStartGame = true;
			//			break;
			//		}
			//		if (curRoom->PlayerReady[idx] == 4)
			//		{
			//			isHostPlayer = true;
			//			continue;
			//		}
			//		if (curRoom->PlayerReady[idx] == 2)
			//		{
			//			++isPlayer;
			//			continue;
			//		}
			//	}
			//	if (!isHostPlayer)
			//	{
			//		NoStartGame = true;
			//	}
			//	if (isPlayer == 0)
			//	{
			//		NoStartGame = true;
			//	}
			//	if (countNon > 5 )
			//	{
			//		NoStartGame = true;
			//	}
			//	if (NoStartGame)
			//	{
			//		resultPack.PacProp.iItem = RM_STARTNO;
			//	}
			//	else
			//	{
			//		resultPack.PacProp.iItem = RM_STARTOK;
			//		Player* pResultPlayer = nullptr;
			//		for (int idx = 0; idx < 7; ++idx)
			//		{
			//			pResultPlayer = nullptr;
			//			pResultPlayer = NetCore::FindPlayer(NetCore::FindPlayerID(curRoom->PlayerId[idx]));
			//			if (!pResultPlayer)
			//			{
			//				continue;
			//			}
			//			pResultPlayer->ePlayerStates.States = playingmae;
			//		}
			//		//게임상태
			//		curRoom->IsIngame = true;
			//		//맵정리
			//		memset(curRoom->MapInfo, 0, sizeof(TCHAR) * 7 * 10 * 23);
			//		//죽음 정리
			//		memset(curRoom->PlayerDeath, 0, sizeof(int) * 7);
			//		//점수정리
			//		memset(curRoom->PlayerGamescore, 0, sizeof(int) * 7);
			//		//시간정리
			//		//for (int idx = 0; idx < 7; ++idx)
			//		//{
			//		//	if (curRoom->PlayerReady[idx] == 4)
			//		//	{
			//		//		curRoom->PlayerReady[idx] = 3;
			//		//	}
			//		//	if (curRoom->PlayerReady[idx] == 2)
			//		//	{
			//		//		curRoom->PlayerReady[idx] = 1;
			//		//	}
			//		//}
			//		
			//		
			//		//curRoom->m_iWinIDNum = 0;
			//	}
			//}
		}
		break;
	}
	default:
		break;
	}

	return resultPack;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

CommonPacket ServerProgress::Ingame_PlayPanel(const CommonPacket & _recvPack)
{
	CommonPacket resultPack;
	RoomInfo* pRoomInfo = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
	if (!pRoomInfo)
	{
		return resultPack;
	}


	IngameCommend enums = (IngameCommend)_recvPack.PacProp.iWork;
	
	switch (enums)
	{
	case IC_NODE:
		break;
	case IC_TIME:
		break;
	case IC_SEND:
	{
		TCHAR resultmaps[6][10][23];
		
		int idx = 0;
		EnterCriticalSection(&ControllerServer::m_eCritical);
		for (int a = 0; a < 7; ++a)
		{
			if (pRoomInfo->PlayerId[a] == _recvPack.PacProp.LinkNumber)
			{
				memcpy(&pRoomInfo->MapInfo[a][0], &_recvPack.Comments[0], sizeof(TCHAR) * 23 * 10);
			}
			else
			{
				memcpy(&resultmaps[idx][0][0], &pRoomInfo->MapInfo[a][0][0], sizeof(TCHAR) * 23 * 10);
				++idx;
			}
		}
		LeaveCriticalSection(&ControllerServer::m_eCritical);
		resultPack = _recvPack;

		memcpy(&resultPack.Comments[0], &ServerProgressBase::m_iSurverTimeUp, sizeof(int));
		memcpy(&resultPack.Comments[sizeof(int)], &ServerProgressBase::m_fSurverTime, sizeof(float));
		memcpy(&resultPack.Comments[sizeof(int) + sizeof(float)], resultmaps, sizeof(TCHAR) * 23 * 10 * 6);

		break;
	}
	
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Ingame_NodeSp(const CommonPacket & _recvPack)
{
	IngameCommend enums = (IngameCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case IC_NODE:
		break;
	case IC_TIME:
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Ingame_Gameend(const CommonPacket & _recvPack)
{
	IngameCommend enums = (IngameCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case IC_END:
	{
		resultPack = _recvPack;
		
		int win, lose, score, GameEndType = 0;
		memcpy(&win, &resultPack.Comments[0], sizeof(int));
		memcpy(&lose, &resultPack.Comments[4], sizeof(int));
		memcpy(&score, &resultPack.Comments[8], sizeof(int));
		memcpy(&GameEndType, &resultPack.Comments[12], sizeof(int));
		

		if (GameEndType == 0)
		{
			break;//이건 이상한거임
		}

		Player* pPlayer = NetCore::FindPlayer(NetCore::FindPlayerID(_recvPack.PacProp.LinkNumber));
		if (!pPlayer)
		{
			break;
		}
		if (pPlayer->eGameinfo.m_MostScore < score)
		{
			pPlayer->eGameinfo.m_MostScore = score;
		}
		
		//pPlayer->eGameinfo.m_Win = win;
		//pPlayer->eGameinfo.m_Lose = lose;
		//PlayerGamescore
		RoomInfo* curRoom = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
		if (!curRoom)
		{
			break;
		}

		//int WinOrLose = 2;
		//게임 결과반영
		if (curRoom->IsIngame == true)
		{
			////////////////////////////////////////////////////
			//점수와 인덱스를 넣고 소팅해야하나.
			//그리고 그걸 토대로 승리여부판정.
			if (GameEndType == 1)
			{
				int winsave = -1;
				int deathcount = 0;
				for (int i = 0; i < 7; ++i)
				{
					if (curRoom->PlayerDeath[i] == 1)
					{
						winsave = curRoom->PlayerId[i];
					}
					else
					{
						++deathcount;
					}
				}
				if (winsave == -1 && deathcount == 7)
				{
					winsave = 1;
					curRoom->m_iWinIDNum = 1;
				}

				if (winsave == -1 && deathcount != 6)
				{
					break;
				}
				Player* pResultPlayer = nullptr;
				for (int i = 0; i < 7; ++i)
				{
					pResultPlayer = nullptr;
					pResultPlayer = NetCore::FindPlayer(NetCore::FindPlayerID(curRoom->PlayerId[i]));
					if (!pResultPlayer)
					{
						continue;
					}
					if (curRoom->PlayerId[i] == winsave)
					{
						pPlayer->eGameinfo.m_Win += 1;
						curRoom->m_iWinIDNum = pPlayer->eLoginfo.m_UniqueID;
						continue;
					}
					pResultPlayer->eGameinfo.m_Lose += 1;
				} 
				//이김
			}
			else if (GameEndType == 2)
			{
				/*int winsave = -1;
				int deathcount = 0;
				for (int i = 0; i < 7; ++i)
				{
					if (curRoom->PlayerDeath[i] == 1)
					{
						winsave = curRoom->PlayerId[i];
					}
					else
					{
						++deathcount;
					}
				}
				if (winsave == -1 && deathcount == 7)
				{
					winsave = 1;
					curRoom->m_iWinIDNum = 1;
				}

				if (winsave == -1 && deathcount != 6)
				{
					break;
				}
				Player* pResultPlayer = nullptr;
				for (int i = 0; i < 7; ++i)
				{
					pResultPlayer = nullptr;
					pResultPlayer = NetCore::FindPlayer(NetCore::FindPlayerID(curRoom->PlayerId[i]));
					if (!pResultPlayer)
					{
						continue;
					}
					if (curRoom->PlayerId[i] == winsave)
					{
						pPlayer->eGameinfo.m_Win += 1;
						curRoom->m_iWinIDNum = pPlayer->eLoginfo.m_UniqueID;
						continue;
					}
					pResultPlayer->eGameinfo.m_Lose += 1;
				}*/
				break;
				//짐
			}
			else if (GameEndType == 3)
			{
				//판결을 요구한다.
				std::list<std::pair<int,int>> sortlist;

				for (int i = 0; i < 7; ++i)
				{
				 	sortlist.push_back(std::make_pair(curRoom->PlayerGamescore[i], curRoom->PlayerId[i]));
				}

				if (1 < sortlist.size())
				{
					sortlist.sort(DownScoreSort);


					if (sortlist.front().second == pPlayer->eLoginfo.m_UniqueID)
					{
						++pPlayer->eGameinfo.m_Win;
						curRoom->m_iWinIDNum = pPlayer->eLoginfo.m_UniqueID;
						Player* pResultPlayer = nullptr;
						for (int i = 0; i < 7; ++i)
						{
							pResultPlayer = nullptr;
							pResultPlayer = NetCore::FindPlayer(NetCore::FindPlayerID(curRoom->PlayerId[i]));

							if (!pResultPlayer)
							{
								continue;
							}
							if (curRoom->PlayerId[i] == pPlayer->eLoginfo.m_UniqueID)
							{
								continue;
							}


							++pResultPlayer->eGameinfo.m_Lose;
						}
						//WinOrLose = 1;
					}
					else
					{
						//++pPlayer->eGameinfo.m_Lose;
						//WinOrLose = 2;
						break;
					}
				}
			}


			////////////////////////////////////////////////////
			curRoom->IsIngame = false;



			//준비상태
			Player* pResultPlayer = nullptr;
			for (int idx = 0; idx < 7; ++idx)
			{
				curRoom->PlayerReady[idx] = 0;
				pResultPlayer = nullptr;
				pResultPlayer = NetCore::FindPlayer(NetCore::FindPlayerID(curRoom->PlayerId[idx]));
				if (!pResultPlayer)
				{
					continue;
				}
				pResultPlayer->ePlayerStates.States = playroomidle;
			}

			//1번 유효인지 체크한다.
			bool Cheocks = false;
			for (int idx = 0; idx < 7; ++idx)
			{
				if (curRoom->PlayerId[idx] == curRoom->hostid)
				{
					Cheocks = true;
					break;
				}
			}
			if (!Cheocks)
			{
				curRoom->hostid = 0;
			}
			if (curRoom->hostid == 0)
			{
				for (int idx = 0; idx < 7; ++idx)
				{
					if (curRoom->PlayerId[idx] != 0)
					{
						curRoom->hostid = curRoom->PlayerId[idx];
						curRoom->PlayerReady[idx] = 1;
						break;
					}
				}
			}

			for (int idx = 0; idx < 7; ++idx)
			{
				if (curRoom->PlayerId[idx] == curRoom->hostid)
				{
					curRoom->PlayerReady[idx] = 3;
					continue;
				}
				if (curRoom->PlayerId[idx] != 0)
				{
					curRoom->PlayerReady[idx] = 1;
				}

			}
		}



		memcpy(&resultPack.Comments[0], &pPlayer->eGameinfo.m_Win, sizeof(int));
		memcpy(&resultPack.Comments[4], &pPlayer->eGameinfo.m_Lose, sizeof(int));
		memcpy(&resultPack.Comments[8], &pPlayer->eGameinfo.m_MostScore, sizeof(int));
		memcpy(&resultPack.Comments[12], &curRoom->m_iWinIDNum, sizeof(int));
	}
		break;
	default:
		break;
	}

	return resultPack;
}

CommonPacket ServerProgress::Ingame_Player(const CommonPacket & _recvPack)
{
	CommonPacket resultPack;
	resultPack = _recvPack;
	RoomInfo* pRoomInfo = NetCore::FindPlayRoom(_recvPack.PacProp.LinkNumber);
	if (!pRoomInfo)
	{
		return resultPack;
	}


	IngameCommend enums = (IngameCommend)_recvPack.PacProp.iWork;

	switch (enums)
	{
	case IC_NODE:
		break;
	case IC_TIME:
		break;
	case IC_SEND:
	{
		if (resultPack.PacProp.iItem == IG_SCORE)
		{
			IngameScoreSurver IngameSurvers;
			int Death = 0;
			int Op = 0;
			int Opcom = 0;

			memcpy(&IngameSurvers, &resultPack.Comments[0], sizeof(IngameScoreSurver));
			memcpy(&Death, &resultPack.Comments[sizeof(IngameScoreSurver)],sizeof(int));
			memcpy(&Op, &resultPack.Comments[sizeof(IngameScoreSurver) + (sizeof(int) * 1)], sizeof(int));
			memcpy(&Opcom, &resultPack.Comments[sizeof(IngameScoreSurver) + (sizeof(int) * 2)], sizeof(int));

			int myidx = -1;
			for (int idx = 0 ;idx < 7 ; ++idx)
			{
				if (pRoomInfo->PlayerId[idx] == resultPack.PacProp.LinkNumber)
				{
					myidx = idx;
					pRoomInfo->PlayerGamescore[idx] = IngameSurvers.m_Score;
					pRoomInfo->PlayerDeath[idx] = Death;
					Op;//일단 보류합니다.
					Opcom;
					break;
				}
			}
			if (myidx == -1)
			{
				break;
			}
			IngameScoreSurver pScroe[7] = { IngameScoreSurver (),};
			int pDeath[7] = { 0, };
			int ApplyOp = 0;
			int OptionComment = 0;

			for (int idx = 0; idx < 7; ++idx)
			{
				pScroe[idx].m_PlayerIngameNum = pRoomInfo->PlayerId[idx];
				if (pRoomInfo->PlayerId[idx] == 0)
				{ 
					pScroe[idx].m_Name[0] = 0;
					continue;
				}
				pScroe[idx].m_Score = pRoomInfo->PlayerGamescore[idx];
				memcpy(&pScroe[idx].m_Name[0], &NetCore::FindPlayerID(pScroe[idx].m_PlayerIngameNum)[0], sizeof(TCHAR) * 20);
				pDeath[idx] = pRoomInfo->PlayerDeath[idx];
			}

			memcpy(&resultPack.Comments[0], &pScroe[0], sizeof(IngameScoreSurver) * 7);
			memcpy(&resultPack.Comments[sizeof(IngameScoreSurver) * 7], &pDeath, sizeof(int) * 7);

			memcpy(&resultPack.Comments[(sizeof(IngameScoreSurver) * 7) + (sizeof(int) * 7)], &ApplyOp, sizeof(int));
			memcpy(&resultPack.Comments[(sizeof(IngameScoreSurver) * 7) + (sizeof(int) * 8)], &OptionComment, sizeof(int));
			//pRoomInfo[idx]


			///////////////////////////////////////////////////////////////////
			//종료 되었나만 판단해준다.
			int Results = 0;


			int livecount = 0;
			int deathcount = 0;
			int emptycount = 0;
			for (int i = 0 ; i < 7; ++i)
			{
				if (pDeath[i] == 0)
				{
				}
				else if (pDeath[i] == 1)
				{
				}
				/*else if ()
				{
				}*/
				
			}


			memcpy(&resultPack.Comments[(sizeof(IngameScoreSurver) * 7) + (sizeof(int) * 9)], &Results, sizeof(int));
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




			//IngameScoreSurver
			break;

		}
		break;
	}

	default:
		break;
	}

	return resultPack;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

CommonPacket ServerProgress::Rank_Update(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_ERR:
		break;
	case CC_UPDATE:
	{
		resultPack = _recvPack;
		/////////////////////////////////////////////////////////
		//전체 플레이어를 받는다.
		int SortType = 0;
		int FindCount = 0;
		memcpy(&SortType, &_recvPack.Comments[0], sizeof(int));
		memcpy(&FindCount, &_recvPack.Comments[4], sizeof(int));
		std::vector<Player> resultPlayerList;
		NetCore::FindPlayers(SortType, FindCount, resultPlayerList);
		/////////////////////////////////////////////////////////
		int realcount = (int)resultPlayerList.size();
		memcpy(&resultPack.Comments[0], &realcount, sizeof(int));
		//자신의 카운터를 다시 리턴한다.
		for (int counts = 0; counts < realcount; ++counts)
		{
			memcpy(&resultPack.Comments[4 + (counts * 32) + 0], &resultPlayerList[counts].eLoginfo.m_ID[0], sizeof(TCHAR) * 20);
			memcpy(&resultPack.Comments[4 + (counts * 32) + 20], &resultPlayerList[counts].eGameinfo.m_MostScore, sizeof(int));
			memcpy(&resultPack.Comments[4 + (counts * 32) + 24], &resultPlayerList[counts].eGameinfo.m_Win, sizeof(int));
			memcpy(&resultPack.Comments[4 + (counts * 32) + 28], &resultPlayerList[counts].eGameinfo.m_Lose, sizeof(int));
		}
	}
		break;
	case CC_EXIT:
		break;
	default:
		break;
	}
	return resultPack;
}

CommonPacket ServerProgress::Rank_Find(const CommonPacket & _recvPack)
{
	CommonCommend enums = (CommonCommend)_recvPack.PacProp.iWork;
	CommonPacket resultPack;
	switch (enums)
	{
	case CC_ERR:
		break;
	case CC_FIND:
		break;
	case CC_ENTER:
		break;
	default:
		break;
	}
	return resultPack;
}

