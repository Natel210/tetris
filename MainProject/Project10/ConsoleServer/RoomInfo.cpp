#include "stdafx.h"
#include "RoomInfo.h"



Tstring RoomInfo::getRoomSendMsg(int Playeridx)
{
	Tstring strtext;
	strtext = _T("");
	for (int i = 0 ;i < 7 ; ++i)
	{
		if (PlayerId[i] == Playeridx)
		{
			strtext = m_PushMsg[i];
			m_PushMsg[i] = _T("");
			break;
		}
	}
	return strtext;
}

void RoomInfo::ClearRoomSendMsg(int Playeridx)
{
	for (int i = 0; i < 7; ++i)
	{
		if (PlayerId[i] == Playeridx)
		{
			//strtext = m_PushMsg[i];
			m_PushMsg[i] = _T("");
			break;
		}
	}
	return ;
}

void RoomInfo::SetRoomSendMsg(const Tstring & _str)
{
	//PlayerId[idx]
	for (int idx = 0 ; idx < 7 ; ++idx)
	{
		if (m_PushMsg[idx][0] == (TCHAR)(-52))
		{
			m_PushMsg[idx].clear();
		}
		m_PushMsg[idx] += _str;
		m_PushMsg[idx] += '\n';

	}
}

RoomInfo::RoomInfo()
{
}


RoomInfo::~RoomInfo()
{
}

