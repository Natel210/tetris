#pragma once
#include "../SubHeader.h"

// 이건 네임 스페이스처럼 전부다 스테틱 함수로 구성되어있고 자신은 생성되지 않는다.
// 즉 하나가 관리하는 시스템
class TimeManager
{
private:
	class Timer
	{
	private:
		friend TimeManager;
		//돌아가는로직..
	private:
		LARGE_INTEGER m_iCount;
		LARGE_INTEGER m_iStartTime;
		LARGE_INTEGER m_iEndTime;
		LARGE_INTEGER m_iCalTime;
		float m_fDeltaTime;
	private:
		bool Init();
	public:
		void StartCheck();//채크시작
		void EndCheck();//채크종료 + 시간 만들기

		float GetDeltaTime() const;

	public:

		//QueryPerformanceFrequency(&m_Count);

		//// 현재까지 얼마 눌렀니? cpu야?
		//// 0번
		//QueryPerformanceCounter(&m_PrevTime);
		//// 0 업데이터

		Timer() : m_fDeltaTime(0.0f)
		{
			memset(&m_iCount, 0, sizeof(LARGE_INTEGER));
			memset(&m_iStartTime, 0, sizeof(LARGE_INTEGER));
			memset(&m_iEndTime, 0, sizeof(LARGE_INTEGER));
			memset(&m_iCalTime, 0, sizeof(LARGE_INTEGER));
		}
		~Timer()
		{}
	};


private:
	static std::unordered_map<Tstring, Timer*> m_Timermap;
public:
	static bool CreateTimer(const TCHAR * _Name);
	static bool CreateTimer(const TCHAR * _Name, int size);
	static bool IsTimer(const TCHAR * _Name);
	static Timer* FindTimer(const TCHAR * _Name);
	static float GetDeltaTime(const TCHAR * _Name);
	static bool DelTimer(const TCHAR * _Name);

public:
	static bool init();
	static bool release();

private:
	TimeManager();
	~TimeManager();
};

#define MainTime TimeManager::GetDeltaTime(_T("MainTime"))

