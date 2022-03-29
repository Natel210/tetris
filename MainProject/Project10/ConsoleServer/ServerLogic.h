#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>

#include "UserErrorCode.h"

struct CommonPacket;
class ServerLogicBase
{
	friend class ServerProgress;
public:
	virtual CommonPacket  Logic(const CommonPacket& _recvPack);

	//���߿� �̰� ���������Լ� ȭ ��ų����.
public:
	ServerLogicBase();
	~ServerLogicBase();
};

