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

	//100ms������ �ð��̴�.
	float MyTimes = pcheck->fSelTime;

	while (MyTimes < 0.0f)
	{
		TimeManager::FindTimer(strTimerName.c_str())->EndCheck();
		TimeManager::FindTimer(strTimerName.c_str())->StartCheck();

		////////////�׸��� ���𰡸� �Ұ��� �ִٸ� �̾߱��Ұ�...


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
	//Ÿ�̸Ӹ� ����� ��� �����带 �Ѵ�.
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


