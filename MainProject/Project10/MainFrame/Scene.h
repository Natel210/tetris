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
			//해당이름이 존제는 하는데....
			if (typeid(T).name() == m_StartIter->second->GetRTTI()->name())
			{
				//모든것이 존재한다면....
				return dynamic_cast<T*>(m_StartIter->second);
			}
			return nullptr;
		}
		return nullptr;
	}//타입까지 확실하게 찾는것.

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
			//다이나믹 업케스팅이안되면....
			//상속구조가 아니라는이야기 임으로 걸러낼수 있을거같은데........
			//메모리 해제를 해준다.
			delete newLayer;
			newLayer = nullptr;
			return nullptr;
		}
		//생성이 정상적으로 되었다면.
		//런타임타입정보를 넣어주고
		newLayer->SetRTTI();
		//초기화 진행
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

