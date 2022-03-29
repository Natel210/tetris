#pragma once
#include "../SubHeader.h"



class InputManager
{
//private:
//	static HWND m_hWnd;
//public:
//	static void SethWnd(HWND _wnd)
//	{
//		m_hWnd = _wnd;
//	}
private:
	class Input
	{
	private:
		friend InputManager;
	private:
		bool m_bPush, m_bUp, m_bStay, m_bDouble, m_bNone; // 상태들
		int m_ikey;		// 내가 지정한 키값
		float m_fDelay = 0.f;  // 더블키 입력시 제한 시간.
		float m_fMaxDelay = 0.07f;

	private:
		inline bool init(int _Key)
		{
			m_ikey = _Key;
			return  true;
		}


		//실제 구동로직.
		inline void UpdateKey(float time = NonDoubleTap)//어떠한 시간값이 필요하곘죠..
		{
			// 디폴트 파라미터를 활용해서 더블텝 off의 기능을 만든다.
			if (0 < m_fDelay && !isnan(time))
			{
				m_fDelay -= time;
			}
			else
			{
				m_fDelay = 0.0f;
			}

			//if (m_hWnd != GetFocus())
			//{
			//	m_bPush = false;
			//	m_bUp = false;
			//	m_bStay = false;
			//	m_bDouble = false;
			//	m_bNone = true;
			//	return;
			//}

			// 1) 키가 들어왔는지 부터 확인한다.
			if (GetAsyncKeyState(m_ikey) & 0x8000 )//이전에 안눌렀다가 지금 막 눌러진 상태
			{
				//2) 스테이트 별 비교
				if (!m_bPush && !m_bDouble && !m_bStay)
				{
					if (0 < m_fDelay)
					{
						m_bPush = false;
						m_bUp = false;
						m_bStay = false;
						m_bDouble = true;
						m_bNone = false;
					}
					else
					{
						m_bPush = true;
						m_bUp = false;
						m_bStay = false;
						m_bDouble = false;
						m_bNone = false;
					}
				}
				else
				{
					m_bPush = false;
					m_bUp = false;
					m_bStay = true;
					m_bDouble = false;
					m_bNone = false;
				}
			}
			else//안누르고 있는상태
			{
				if (m_bPush || m_bStay || m_bDouble)//눌렀거나 누르는중이거나 더블이던가.
				{
					m_bUp = true;

					m_bPush = false;
					m_bStay = false;
					m_bDouble = false;
					m_bNone = false;

					m_fDelay = m_fMaxDelay;
				}
				else
				{
					m_bPush = false;
					m_bUp = false;
					m_bStay = false;
					m_bDouble = false;
					m_bNone = true;
				}
			}
		}
	private:
//getstate
		inline bool GetPush() const
		{
			return m_bPush;
		}
		inline bool GetUp() const 
		{
			return m_bUp;
		}
		inline bool GetStay() const
		{
			return m_bStay;
		}
		inline bool GetDouble() const
		{
			return m_bDouble;
		}
		inline bool GetNone() const
		{
			return m_bNone;
		}
	private:
		/*bool */
		Input() : m_bPush(false), m_bUp(false), m_bStay(false), m_bDouble(false), m_bNone(true)
		{

		}
		~Input()
		{

		}
	};

private:
	static std::unordered_map<Tstring, Input*> m_Inputmap;
public:
	static bool CreateInput(const TCHAR * _Name, int _Key);
	static Input* FindInput(const TCHAR * _Name);
	static int FindKey(const TCHAR * _Name);
	static bool DelInput(const TCHAR * _Name);

public:
	static bool GetPush(const TCHAR * _Name);
	static bool GetUp(const TCHAR * _Name);
	static bool GetStay(const TCHAR * _Name);
	static bool GetDouble(const TCHAR * _Name);
	static bool GetNone(const TCHAR * _Name);

public:
	static bool init();
	//전부다 한곳에서 업데이트를 진행 해야한다.
	static bool Update(float time = NonDoubleTap);

	static bool release();


	//내가 일단 필요하다고 생각되는 키에 대해서 미리 정의.
private:
	static bool BaseKeySet();


private:
	InputManager();
	~InputManager();
};
//디버깅용 이 문자열이 무슨키로 등록됬는지...
#define GETKEY(str)  InputManager::FindKey(str)

#define CREATE_KEY(name, key) InputManager::CreateInput(name, key)
#define KEY_PUSH(str) InputManager::GetPush(str)
#define KEY_KEY(str) InputManager::GetPush(str) || InputManager::GetStay(str)
#define KEY_UP(str) InputManager::GetUp(str)
#define KEY_STAY(str) InputManager::GetStay(str)
#define KEY_DOUBLE(str) InputManager::GetDouble(str)
#define KEY_NONE(str) InputManager::GetNone(str)


#define MouseLB _T("MouseLB")
#define MouseRB _T("MouseRB")
#define EnterKey _T("Enter")

#define DebugKey1 _T("DebugKey1")
#define DebugKey2 _T("DebugKey2")
#define DebugKey3 _T("DebugKey3")
#define DebugKey4 _T("DebugKey4")
#define DebugKey5 _T("DebugKey5")
#define DebugKey6 _T("DebugKey6")
#define DebugKey7 _T("DebugKey7")
#define DebugKey8 _T("DebugKey8")
#define DebugKey9 _T("DebugKey9")

//#define DebugKey1 "DebugKey1"
//#define DebugKey1 "DebugKey1"
//#define DebugKey1 "DebugKey1"
//#define DebugKey1 "DebugKey1"
//#define DebugKey1 "DebugKey1"
//#define DebugKey1 "DebugKey1"