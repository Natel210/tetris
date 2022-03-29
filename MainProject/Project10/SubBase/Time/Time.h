#pragma once
#include "../SubHeader.h"

// �̰� ���� �����̽�ó�� ���δ� ����ƽ �Լ��� �����Ǿ��ְ� �ڽ��� �������� �ʴ´�.
// �� �ϳ��� �����ϴ� �ý���
class TimeManager
{
private:
	class Timer
	{
	private:
		friend TimeManager;
		//���ư��·���..
	private:
		LARGE_INTEGER m_iCount;
		LARGE_INTEGER m_iStartTime;
		LARGE_INTEGER m_iEndTime;
		LARGE_INTEGER m_iCalTime;
		float m_fDeltaTime;
	private:
		bool Init();
	public:
		void StartCheck();//äũ����
		void EndCheck();//äũ���� + �ð� �����

		float GetDeltaTime() const;

	public:

		//QueryPerformanceFrequency(&m_Count);

		//// ������� �� ������? cpu��?
		//// 0��
		//QueryPerformanceCounter(&m_PrevTime);
		//// 0 ��������

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

