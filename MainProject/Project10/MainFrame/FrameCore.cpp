#include "FrameCore.h"
#include "Scene.h"


std::unordered_map<Tstring, class Scene*> FrameCore::m_mapScene;
std::unordered_map<Tstring, class Scene*>::iterator FrameCore::m_StartIter;
std::unordered_map<Tstring, class Scene*>::iterator FrameCore::m_EndIter;
bool FrameCore::DebugMode;

Scene * FrameCore::FindScene(Tstring name)
{
	m_StartIter = m_mapScene.find(name);
	if (m_StartIter == m_mapScene.end())
	{
		return nullptr;
	}
	return m_StartIter->second;
}

bool FrameCore::RemoveScene(Tstring name)
{
	Scene * pFindScene = nullptr;
	pFindScene = FindScene(name);
	if (pFindScene != nullptr)
	{
		pFindScene->RemoveLayer();
		pFindScene->release();
		delete pFindScene;
		pFindScene = nullptr;
		m_mapScene.erase(name);
		return true;
	}
	return false;
}

void FrameCore::DebugModeChange()
{
	DebugMode = !DebugMode;
}

bool FrameCore::Logic(float time)
{
	//사전 변화시킬거 먼저 세팅합니다.
	//주로 온 오프를 담당합니다.
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();
	while (m_StartIter != m_EndIter)
	{
		m_StartIter->second->PrevSetting(time);
		++m_StartIter;
	}
	Input(time);
	Update(time);
	LateUpdate(time);
	Transform(time);
	Render(time);
	DebugRender(time);
	Collision(time);
	
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();
	while (m_StartIter != m_EndIter)
	{
		if (m_StartIter->second->GetDel())
		{
			if (m_StartIter->second != nullptr)
			{
				m_StartIter->second->RemoveLayer();
				m_StartIter->second->release();
				delete m_StartIter->second;
				m_StartIter->second = nullptr;
				m_StartIter = m_mapScene.erase(m_StartIter);
			}
			else
			{
				++m_StartIter;
			}
		}
		else
		{
			++m_StartIter;
		}
	}

	return true;
}

int FrameCore::Input(float time)
{
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((m_StartIter->second->GetActive()) && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Input(time);
		}
	}
	return 1;
}

int FrameCore::Update(float time)
{
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((m_StartIter->second->GetActive()) && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Update(time);
		}
	}
	return 1;
}

int FrameCore::LateUpdate(float time)
{
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((m_StartIter->second->GetActive()) && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->LateUpdate(time);
		}
	}
	return 1;
}

int FrameCore::Transform(float time)
{
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((m_StartIter->second->GetActive()) && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Transform(time);
		}
	}
	return 1;
}

int FrameCore::Render(float time)
{
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((m_StartIter->second->GetActive()) && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Render(time);
		}
	}
	return 1;
}

int FrameCore::DebugRender(float time)
{
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((m_StartIter->second->GetActive()) && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->DebugRender(time);
		}
	}
	return 1;
}


/////////////////////////////////////////////////////////////////////////////////
int FrameCore::Collision(float time)
{
	m_StartIter = m_mapScene.begin();
	m_EndIter = m_mapScene.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((m_StartIter->second->GetActive()) && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Collision(time);
		}
	}
	return PR_OK;
}
