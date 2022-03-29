#include "Scene.h"
#include "FrameCore.h"
#include "Layer.h"

void Scene::RemoveLayer()
{
	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();
	while (m_StartIter != m_EndIter)
	{
		m_StartIter->second->pScene = nullptr;
		m_StartIter->second->RemoveObj();
		m_StartIter->second->release();
		delete m_StartIter->second;
		m_StartIter->second = nullptr;
		m_StartIter = m_mapLayer.erase(m_StartIter);
	}
}


Scene::Scene()
{}


Scene::~Scene()
{}

void Scene::SetActive(bool b)
{
	if (GetActive() == false && b == true)
	{
		m_StartIter = m_mapLayer.begin();
		m_EndIter = m_mapLayer.end();
		while (m_StartIter != m_EndIter)
		{
			m_StartIter->second->StartUp();
			++m_StartIter;
		}
	}
	else if (GetActive() == true && b == false)
	{
		m_StartIter = m_mapLayer.begin();
		m_EndIter = m_mapLayer.end();
		while (m_StartIter != m_EndIter)
		{
			m_StartIter->second->EndUp();
			++m_StartIter;
		}
	}
	GameObj::SetActive(b);
}



int Scene::PrevSetting(float time)
{
	return PR_OK;
}

int Scene::Input(float time)
{
	if (!GetActive())
	{
		return PR_NONATIVE;
	}

	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Input(time);
		}
	}

	return PR_OK;
}

int Scene::Update(float time)
{
	if (!GetActive())
	{
		return PR_NONATIVE;
	}

	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->LayerUpdate(time))
			{
				m_StartIter = m_mapLayer.begin();
				m_EndIter = m_mapLayer.end();
			}
			if (PR_SCENECHNAGE == m_StartIter->second->Update(time))
			{
				m_StartIter = m_mapLayer.begin();
				m_EndIter = m_mapLayer.end();
			}
		}
	}

	return PR_OK;
}

int Scene::LateUpdate(float time)
{
	if (!GetActive())
	{
		return PR_NONATIVE;
	}

	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();

	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->LateUpdate(time);

		}
	}


	return PR_OK;
}

int Scene::Transform(float time)
{
	if (!GetActive())
	{
		return PR_NONATIVE;
	}
	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Transform(time);
		}
	}
	return PR_OK;
}

int Scene::Render(float time)
{
	if (!GetActive())
	{
		return PR_NONATIVE;
	}
	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->Render(time);
		}
	}
	return PR_OK;
}

int Scene::DebugRender(float time)
{
	if (!GetActive())
	{
		return PR_NONATIVE;
	}
	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			m_StartIter->second->DebugRender(time);
		}
	}
	return PR_OK;
}

int Scene::Collision(float time)
{
	if (!GetActive())
	{
		return PR_NONATIVE;
	}
	m_StartIter = m_mapLayer.begin();
	m_EndIter = m_mapLayer.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if (m_StartIter->second->GetActive() && (!m_StartIter->second->GetDel()))
		{
			if (PR_SCENECHNAGE == m_StartIter->second->Collision(time))
			{
				m_StartIter = m_mapLayer.begin();
				m_EndIter = m_mapLayer.end();
			}
		}
	}
	return PR_OK;
}

Layer * Scene::FindLayer(Tstring name)
{
	m_StartIter = m_mapLayer.find(name);
	if (m_StartIter == m_mapLayer.end())
	{
		return nullptr;
	}
	return m_StartIter->second;
}

bool Scene::RemoveLayer(Tstring name)
{
	Layer * pFindLayer = FindLayer(name);
	if (pFindLayer != nullptr)
	{
		pFindLayer->pScene = nullptr;
		pFindLayer->release();
		delete pFindLayer;
		pFindLayer = nullptr;
		m_mapLayer.erase(name);
		return true;
	}
	return false;
}











