#include "Input.h"




std::unordered_map<Tstring, InputManager::Input*> InputManager::m_Inputmap;
//HWND InputManager::m_hWnd = NULL;
InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::CreateInput(const TCHAR * _Name, int _Key)
{
	Input* NewInput = nullptr;
	//절대로 이름은 중복되어서는 안된다.
	NewInput = FindInput(_Name);
	if (NewInput)
		//dlalwhswpgkqslek.
		return false;
		//만들기 실패

	NewInput = new Input();
	if (!NewInput->init(_Key))
	{
		delete NewInput;
		NewInput = nullptr;

		return false;
		//생성실패
	}
	m_Inputmap.insert(std::make_pair(_Name, NewInput));

	return true;
}

InputManager::Input * InputManager::FindInput(const TCHAR * _Name)
{
	//static std::unordered_map<Tstring, Input*> m_Inputmap;
	std::unordered_map<Tstring, Input*>::iterator FindIter;
	FindIter = m_Inputmap.find(_Name);
	if (FindIter != m_Inputmap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

int InputManager::FindKey(const TCHAR * _Name)
{
	// 이건 키값을 찾아주는 함수
	Input* pInput = FindInput(_Name);
	if (!pInput)
	{
		return pInput->m_ikey;
	}
	return NoFindIndex;

}

bool InputManager::DelInput(const TCHAR * _Name)
{
	std::unordered_map<Tstring, Input*>::iterator FindIter;
	FindIter = m_Inputmap.find(_Name);
	if (FindIter != m_Inputmap.end())
	{
		delete  FindIter->second;
		FindIter->second = nullptr;
		m_Inputmap.erase(_Name);
		return true;
	}

	return false;
}

bool InputManager::GetPush(const TCHAR * _Name) 
{
	return FindInput(_Name)->GetPush();
}

bool InputManager::GetUp(const TCHAR * _Name) 
{
	return FindInput(_Name)->GetUp();
}

bool InputManager::GetStay(const TCHAR * _Name) 
{
	return FindInput(_Name)->GetStay();
}

bool InputManager::GetDouble(const TCHAR * _Name) 
{
	return FindInput(_Name)->GetDouble();
}

bool InputManager::GetNone(const TCHAR * _Name) 
{
	return FindInput(_Name)->GetNone();
}

bool InputManager::init()
{
	return BaseKeySet();
}

bool InputManager::Update(float time/* = NonDoubleTap*/)
{
	std::unordered_map<Tstring, Input*>::iterator m_StartIter = m_Inputmap.begin();
	std::unordered_map<Tstring, Input*>::iterator m_EndIter = m_Inputmap.end();
	for (; m_StartIter != m_EndIter;++m_StartIter)
	{
		m_StartIter->second->UpdateKey(time);
	}

	return true;
}

bool InputManager::release()
{
	std::unordered_map<Tstring, Input*>::iterator m_StartIter = m_Inputmap.begin();
	std::unordered_map<Tstring, Input*>::iterator m_EndIter = m_Inputmap.end();
	for (; m_StartIter != m_EndIter; )
	{
		delete m_StartIter->second;
		m_StartIter->second = nullptr;

		m_StartIter = m_Inputmap.erase(m_StartIter);
		//제설정
		m_EndIter = m_Inputmap.end();
	}
	//InputManager::m_hWnd = NULL;
	return true;
}

bool InputManager::BaseKeySet()
{
	//CREATE_KEY
	CreateInput(MouseLB, VK_LBUTTON);
	CreateInput(MouseRB, VK_RBUTTON);
	CreateInput(EnterKey, VK_RETURN);
	CreateInput(DebugKey1, 1);
	CreateInput(DebugKey2, 2);
	CreateInput(DebugKey3, 3);
	CreateInput(DebugKey4, 4);
	CreateInput(DebugKey5, 5);
	CreateInput(DebugKey6, 6);
	CreateInput(DebugKey7, 7);
	CreateInput(DebugKey8, 8);
	CreateInput(DebugKey9, 9);

	return true;
}