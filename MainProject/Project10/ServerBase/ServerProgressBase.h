#pragma once
#include "UserPacket.h"

class ServerProgressBase
{
public:
	virtual CommonPacket Progress(const CommonPacket& _recvPack);

	virtual ServerProgressBase* Copy();
public:
	static unsigned int m_iSurverTimeUp;
	static float m_fSurverTime;
public:
	 ServerProgressBase();
	 //ServerProgressBase();
	 ~ServerProgressBase();
};

