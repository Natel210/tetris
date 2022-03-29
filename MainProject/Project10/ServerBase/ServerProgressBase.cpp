#include "ServerProgressBase.h"

unsigned int ServerProgressBase::m_iSurverTimeUp = 0;
float ServerProgressBase::m_fSurverTime = 0.0f;

CommonPacket ServerProgressBase::Progress(const CommonPacket & _recvPack)
{
	return CommonPacket();
}

ServerProgressBase * ServerProgressBase::Copy()
{
	ServerProgressBase* newCopy = new ServerProgressBase;
	(*newCopy) = (*this);
	return dynamic_cast<ServerProgressBase*>(newCopy);
}

ServerProgressBase::ServerProgressBase()
{
}


ServerProgressBase::~ServerProgressBase()
{
}
