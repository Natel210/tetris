#include "stdafx.h"
#include "ServerLogic.h"
#include "UserPacket.h"



CommonPacket  ServerLogicBase::Logic(const CommonPacket& _recvPack)
{

	//_recvPack.PacProp

	/////////////////////////////////////////////////
	//ȸ�Ű�
	Tstring m_str = _T("[����ȸ��]");
	m_str += _recvPack.Comments;
	CommonPacket resultPack = CommonPacket();
	resultPack.SetComment(m_str);
	//
	//

	//

	CommonPacket packresult;


	return CommonPacket();

}

ServerLogicBase::ServerLogicBase()
{
}


ServerLogicBase::~ServerLogicBase()
{
}
