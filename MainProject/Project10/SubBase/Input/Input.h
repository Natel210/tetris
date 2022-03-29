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
		bool m_bPush, m_bUp, m_bStay, m_bDouble, m_bNone; // ���µ�
		int m_ikey;		// ���� ������ Ű��
		float m_fDelay = 0.f;  // ����Ű �Է½� ���� �ð�.
		float m_fMaxDelay = 0.07f;

	private:
		inline bool init(int _Key)
		{
			m_ikey = _Key;
			return  true;
		}


		//���� ��������.
		inline void UpdateKey(float time = NonDoubleTap)//��� �ð����� �ʿ��ρ���..
		{
			// ����Ʈ �Ķ���͸� Ȱ���ؼ� ������ off�� ����� �����.
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

			// 1) Ű�� ���Դ��� ���� Ȯ���Ѵ�.
			if (GetAsyncKeyState(m_ikey) & 0x8000 )//������ �ȴ����ٰ� ���� �� ������ ����
			{
				//2) ������Ʈ �� ��
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
			else//�ȴ����� �ִ»���
			{
				if (m_bPush || m_bStay || m_bDouble)//�����ų� ���������̰ų� �����̴���.
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
	//���δ� �Ѱ����� ������Ʈ�� ���� �ؾ��Ѵ�.
	static bool Update(float time = NonDoubleTap);

	static bool release();


	//���� �ϴ� �ʿ��ϴٰ� �����Ǵ� Ű�� ���ؼ� �̸� ����.
private:
	static bool BaseKeySet();


private:
	InputManager();
	~InputManager();
};
//������ �� ���ڿ��� ����Ű�� ��ω����...
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