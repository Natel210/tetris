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

	//나중에 이거 순수가상함수 화 시킬거임.
public:
	ServerLogicBase();
	~ServerLogicBase();
};

