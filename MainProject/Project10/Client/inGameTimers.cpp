#include "stdafx.h"
#include "inGameTimers.h"
#include "Time/Time.h" 
//#include ""
class eCheckTime
{
public:
	float fSelTime = 0.0f;
	const TCHAR* str = L"";
};



static unsigned __stdcall Timercheck(void* arg)
{
	eCheckTime* pcheck = (eCheckTime*)arg;
	Tstring strTimerName = pcheck->str;
	strTimerName += L"Timer";
	

	//TCHAR timerbuff[_MAX_PATH];
	//WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strTimerName.c_str(), (int)strTimerName.size(), timerbuff, 30, NULL, NULL);
	TimeManager::CreateTimer(strTimerName.c_str());



	//TimeManager::CreateTimer(strTimerName.c_str(), (int)strTimerName.size());

	//100ms단위의 시간이다.
	float MyTimes = pcheck->fSelTime;

	while (MyTimes < 0.0f)
	{
		TimeManager::FindTimer(strTimerName.c_str())->EndCheck();
		TimeManager::FindTimer(strTimerName.c_str())->StartCheck();

		////////////그리고 무언가를 할것이 있다면 이야기할것...


		//Sleep((100);
		MyTimes -= TimeManager::GetDeltaTime(strTimerName.c_str());
	}



	return 0;
}


inGameTimers::inGameTimers()
{
}


inGameTimers::~inGameTimers()
{
}

int inGameTimers::Input(float time)
{
	return PR_OK;
}

int inGameTimers::Update(float time)
{
	return PR_OK;
}

int inGameTimers::LateUpdate(float time)
{
	return PR_OK;
}

int inGameTimers::Transform(float time)
{
	return PR_OK;
}

int inGameTimers::Render(float time, HDC drow)
{
	return PR_OK;
}

int inGameTimers::DebugRender(float time)
{
	return PR_OK;
}

int inGameTimers::Collision(float time)
{
	return PR_OK;
}

int inGameTimers::Init()
{
	//타이머를 만들고 비긴 쓰레드를 한다.
	eCheckTime echeck;
	echeck.fSelTime = 3.0f;
	echeck.str = m_strName.c_str();
	
	_beginthreadex(nullptr, 0, Timercheck, (void*)(&echeck), 0, nullptr);





	return PR_OK;
}

int inGameTimers::release()
{


	return PR_OK;
}


