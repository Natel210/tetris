#pragma once
#include "GameObj.h"
class Scene : public GameObj
{
private:
	friend class FrameCore;

private:
	virtual int Input(float time) final;
	virtual int Update(float time) final;
	virtual int LateUpdate(float time) final;
	virtual int Transform(float time) final;
	virtual int Render(float time) final;
	virtual int DebugRender(float time) final;
	virtual int Collision(float time) final;
private:
	std::unordered_map<Tstring, class Layer*> m_mapLayer;
	std::unordered_map<Tstring, class Layer*>::iterator m_StartIter;
	std::unordered_map<Tstring, class Layer*>::iterator m_EndIter;

public:
	virtual class Layer* FindLayer(Tstring name) final;
	virtual bool RemoveLayer(Tstring name) final;

protected:
	virtual int Init() = 0 ;
	virtual int release() = 0 ;
private:
	virtual void RemoveLayer()  final;
protected:
	virtual int PrevSetting(float time);

protected:
	Scene();
	~Scene();

public:
	inline void virtual  SetActive(bool active);

public:
	template<typename T>
	T* FindLayer(Tstring name)
	{
		m_StartIter = m_mapLayer.find(name);
		if (m_StartIter != m_mapLayer.end())
		{
			//�ش��̸��� ������ �ϴµ�....
			if (typeid(T).name() == m_StartIter->second->GetRTTI()->name())
			{
				//������ �����Ѵٸ�....
				return dynamic_cast<T*>(m_StartIter->second);
			}
			return nullptr;
		}
		return nullptr;
	}//Ÿ�Ա��� Ȯ���ϰ� ã�°�.

	template<typename T>
	T* CreateLayer(Tstring name)
	{
		T* newLayer = FindLayer<T>(name);
		if (newLayer)
		{
			return newLayer;
		}
		newLayer = new T;

		if (!dynamic_cast<Layer*>(newLayer))
		{
			//���̳��� ���ɽ����̾ȵǸ�....
			//��ӱ����� �ƴ϶���̾߱� ������ �ɷ����� �����Ű�����........
			//�޸� ������ ���ش�.
			delete newLayer;
			newLayer = nullptr;
			return nullptr;
		}
		//������ ���������� �Ǿ��ٸ�.
		//��Ÿ��Ÿ�������� �־��ְ�
		newLayer->SetRTTI();
		//�ʱ�ȭ ����
		if (!newLayer->Init())
		{
			delete newLayer;
			newLayer = nullptr;
			return nullptr;
		}
		newLayer->pScene = this;
		m_mapLayer.insert(std::make_pair(name, (Layer*)newLayer));
		return newLayer;
	}
};

