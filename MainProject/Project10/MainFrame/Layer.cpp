#include "Layer.h"
#include "Scene.h"
#include "OBJItem.h"

Layer::Layer() : m_LayerhDC(NULL)
{}


Layer::~Layer()
{}

int Layer::Input(float time)
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->Input(time))
			{
				return PR_SCENECHNAGE;
			}
		}
	}
	return PR_OK;
}

int Layer::Update(float time)
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->Update(time))
			{
				return PR_SCENECHNAGE;
			}
		}
	}
	return PR_OK;
}

int Layer::LateUpdate(float time)
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->LateUpdate(time))
			{
				return PR_SCENECHNAGE;
			}
		}
	}
	return PR_OK;
}

int Layer::Transform(float time)
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->Transform(time))
			{
				return PR_SCENECHNAGE;
			}
		}
	}
	return PR_OK;
}

int Layer::Render(float time)
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->Render(time, m_LayerhDC))
			{
				return PR_SCENECHNAGE;
			}
		}

	}
	return PR_OK;
}

int Layer::DebugRender(float time)
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->DebugRender(time))
			{
				return PR_SCENECHNAGE;
			}
		}
	}
	return PR_OK;
}

int Layer::Collision(float time)
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			//m_StartIter->second->Collision(time);
			if (PR_SCENECHNAGE == m_StartIter->second->Collision(time))
			{
				return PR_SCENECHNAGE;
			}
		}
	}
	return PR_OK;
}

OBJItem * Layer::FindObj(Tstring name)
{
	m_StartIter = m_mapObj.find(name);
	if (m_StartIter == m_mapObj.end())
	{
		return nullptr;
	}
	return m_StartIter->second;
}

bool Layer::RemoveObj(Tstring name)
{
	OBJItem * pFindItem = FindObj(name);
	if (pFindItem != nullptr)
	{
		pFindItem->pLayer = nullptr;
		pFindItem->release();
		delete pFindItem;
		pFindItem = nullptr;
		m_mapObj.erase(name);
		return true;
	}
	return false;
}

bool Layer::GetActive() 
{
	if (pScene)
	{
		return  GameObj::GetActive() && pScene->GetActive();
	}
	else
	{
		return GameObj::GetActive();
	}
	//나의 씬을 알고 있어야겠는데?
	return false;
}

int Layer::StartUp()
{
	return 0;
}

int Layer::EndUp()
{
	return 0;
}

void Layer::RemoveObj()
{
	m_StartIter = m_mapObj.begin();
	m_EndIter = m_mapObj.end();
	while (m_StartIter != m_EndIter)
	{
		m_StartIter->second->pLayer = nullptr;
		m_StartIter->second->release();
		delete m_StartIter->second;
		m_StartIter->second = nullptr;
		m_StartIter = m_mapObj.erase(m_StartIter);
	}
}

HDC Layer::GetLayerDC() const
{
	return m_LayerhDC;
}
