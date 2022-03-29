#include "Time.h"

std::unordered_map<Tstring, TimeManager::Timer*> TimeManager::m_Timermap;

bool TimeManager::CreateTimer(const TCHAR * _Name)
{
	Timer* NewTime = nullptr;
	NewTime = FindTimer(_Name);
	if (NewTime)
		return false;

	NewTime = new Timer();
	if (!NewTime->Init())
	{
		delete NewTime;
		NewTime = nullptr;
		return false;
	}
	
	m_Timermap.insert(std::make_pair(_Name, NewTime));
	return true;
}

bool TimeManager::CreateTimer(const TCHAR* _Name, int size)
{
	TCHAR timerbuff[_MAX_PATH];		
	//WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, _Name, size, timerbuff, 30, NULL, NULL);


	Timer* NewTime = nullptr;
	NewTime = FindTimer(timerbuff);
	if (NewTime)
		return false;

	NewTime = new Timer();
	if (!NewTime->Init())
	{
		delete NewTime;
		NewTime = nullptr;
		return false;
	}

	m_Timermap.insert(std::make_pair(timerbuff, NewTime));
	return true;
}

bool TimeManager::IsTimer(const TCHAR * _Name)
{
	if (m_Timermap.size() == 0)
	{
		return false;
	}
	std::unordered_map<Tstring, Timer*>::iterator FindIter;
	FindIter = m_Timermap.find(_Name);
	if (FindIter != m_Timermap.end())
	{
		return true;
	}
	return false;
}

TimeManager::Timer * TimeManager::FindTimer(const TCHAR * _Name)
{
	std::unordered_map<Tstring, Timer*>::iterator FindIter;
	FindIter = m_Timermap.find(_Name);
	if (FindIter != m_Timermap.end())
	{
		return FindIter->second;
	}
	return nullptr;
}

float TimeManager::GetDeltaTime(const TCHAR * _Name)
{
	Timer* pTime = FindTimer(_Name);
	if (!pTime)
	{
		return 0.0f;
	}
	float delta = pTime->GetDeltaTime();
	pTime = nullptr;
	return delta;
}

bool TimeManager::DelTimer(const TCHAR * _Name)
{
	std::unordered_map<Tstring, Timer*>::iterator FindIter;
	FindIter = m_Timermap.find(_Name);
	if (FindIter != m_Timermap.end())
	{
		delete FindIter->second;
		FindIter->second = nullptr;
		m_Timermap.erase(_Name);
		return true;
	}
	
	return false;
}

bool TimeManager::init()
{
	m_Timermap.clear();
	CreateTimer(_T("MainTime"));
	return true;
}

bool TimeManager::release()
{
	//매니저가 죽을때....가업성.
	std::unordered_map<Tstring, Timer*>::iterator m_StartIter =  m_Timermap.begin();
	std::unordered_map<Tstring, Timer*>::iterator m_EndIter = m_Timermap.end();
	for (; m_StartIter != m_EndIter; )
	{
		delete m_StartIter->second;
		m_StartIter->second = nullptr;

		m_StartIter = m_Timermap.erase(m_StartIter);
		m_EndIter = m_Timermap.end();
	}

	return true;
}

TimeManager::TimeManager()
{
	
}


TimeManager::~TimeManager()
{
	

}


/////////////////////////////////////////////////////////////
//이너 클래스

bool TimeManager::Timer::Init()
{
	//LARGE_INTEGER m_iCount;
	//LARGE_INTEGER m_iStartTime;
	//LARGE_INTEGER m_iEndTime;
	// 나의 CPU성능 입니다. 
	// 틱(처리, 윈도우즈에서는 성능단위를 틱으로 설명 하더라....)/s
	// 초당 처리 횟수
	if (!QueryPerformanceFrequency(&m_iCount))
	{
		//0으로 나온다면 오류
		return false;
	}
	//카운터 초기화
	QueryPerformanceCounter(&m_iStartTime);
	QueryPerformanceCounter(&m_iEndTime);
	m_fDeltaTime = 0.0;

	return true;
}

void TimeManager::Timer::StartCheck()
{
	QueryPerformanceCounter(&m_iStartTime);
}

void TimeManager::Timer::EndCheck()
{
	QueryPerformanceCounter(&m_iEndTime);

	////연산합니다.
	m_iCalTime.QuadPart = m_iEndTime.QuadPart - m_iStartTime.QuadPart;//틱수
	m_fDeltaTime = (float)m_iCalTime.QuadPart / (float)m_iCount.QuadPart;

}

float TimeManager::Timer::GetDeltaTime() const
{
	return m_fDeltaTime;
}
