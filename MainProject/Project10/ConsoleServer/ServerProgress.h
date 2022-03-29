#pragma once

#include "UserPacket.h"
#include "ServerProgressBase.h"

////////////////////////////////////////
//struct CommonPacket;
class ServerProgress : public ServerProgressBase
{
public:


public:
	virtual CommonPacket Progress(const CommonPacket& _recvPack);
	virtual ServerProgressBase* Copy();
private:
	CommonPacket SYS_Scene(const CommonPacket& _recvPack);
	CommonPacket Login_Scene(const CommonPacket& _recvPack);
	CommonPacket Lobby_Scene(const CommonPacket& _recvPack);
	CommonPacket Room_Scene(const CommonPacket& _recvPack);
	CommonPacket Ingame_Scene(const CommonPacket& _recvPack);
	CommonPacket Ranking_Scene(const CommonPacket& _recvPack);

	//Login
private:
	CommonPacket Login_Signin(const CommonPacket& _recvPack);
	CommonPacket Login_Create(const CommonPacket& _recvPack);
	CommonPacket Login_Find(const CommonPacket& _recvPack);
	CommonPacket Login_EXIT(const CommonPacket& _recvPack);

	//
private:
	CommonPacket Lobby_Create(const CommonPacket& _recvPack);
	CommonPacket Lobby_Enter(const CommonPacket& _recvPack);
	CommonPacket Lobby_CheckPlayer(const CommonPacket& _recvPack);
	CommonPacket Lobby_Chat(const CommonPacket& _recvPack);
	CommonPacket Lobby_Rank(const CommonPacket& _recvPack);
	CommonPacket Lobby_Logout(const CommonPacket& _recvPack);
	CommonPacket Lobby_EXIT(const CommonPacket& _recvPack);
	CommonPacket Lobby_FIndroom(const CommonPacket& _recvPack);


	//
private:
	CommonPacket Room_Chat(const CommonPacket& _recvPack);
	CommonPacket Room_Seltime(const CommonPacket& _recvPack);
	CommonPacket Room_SelNode(const CommonPacket& _recvPack);
	CommonPacket Room_EXIT(const CommonPacket& _recvPack);
	CommonPacket Room_INIT(const CommonPacket& _recvPack);
	CommonPacket Room_LISTUPDATE(const CommonPacket& _recvPack);
	CommonPacket Room_STATSUPDATE(const CommonPacket& _recvPack);
	

	//
private:
	CommonPacket Ingame_PlayPanel(const CommonPacket& _recvPack);
	CommonPacket Ingame_NodeSp(const CommonPacket& _recvPack);
	CommonPacket Ingame_Gameend(const CommonPacket& _recvPack);
	CommonPacket Ingame_Player(const CommonPacket& _recvPack);

	//
private:
	CommonPacket Rank_Update(const CommonPacket& _recvPack);
	CommonPacket Rank_Find(const CommonPacket& _recvPack);




};









//누가 언제 어디서 무엇을 어떻게 왜?
//[시간 ][누구(클라고유)][어디1(씬)][어디2(어느섹션)][무엇을(접속을시도한다, 회원가입을 시도한다.) ][]
//
//2번






//FSM조합형식으로가자
//[위치1][위치2][누구에게][무엇을][][][][][][][][]