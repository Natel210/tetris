#pragma once
#include "GameObj.h"

class Layer : public GameObj
{
private:
	friend class Scene;
private:
	class Scene* pScene = nullptr;

private:
	virtual int Input(float time) final;
	virtual int Update(float time) final;
	virtual int LateUpdate(float time) final;
	virtual int Transform(float time) final;
	virtual int Render(float time) final;
	virtual int DebugRender(float time) final;
	virtual int Collision(float time) final;
private:
	std::unordered_map<Tstring, class OBJItem*> m_mapObj;
	std::unordered_map<Tstring, class OBJItem*>::iterator m_StartIter;
	std::unordered_map<Tstring, class OBJItem*>::iterator m_EndIter;
public:
	virtual class OBJItem* FindObj(Tstring name) final;
	virtual bool RemoveObj(Tstring name) final;

public:
	virtual bool GetActive() final;

protected:
	virtual int Init() = 0;
	virtual int StartUp();
	virtual int EndUp();
	virtual int LayerUpdate(float time) { return 0; }
	virtual int release() = 0;
private:
	virtual void RemoveObj()final;

protected:
	HDC m_LayerhDC;
protected:
	int LayerPosX;
	int LayerPosY;
	int LayerSizeX;
	int LayerSizeY;
	int LayerZ;

public:
	HDC GetLayerDC() const;



protected:
	Layer();
	Layer(const Tstring& name);
	~Layer();


public:
	template<typename T>
	T* FindObj(Tstring name)
	{
		m_StartIter = m_mapObj.find(name);
		if (m_StartIter != m_mapObj.end())
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
	T* CreateObj(Tstring name)
	{
		T* newItem = FindObj<T>(name);
		if (newItem)
		{
			return newItem;
		}
		newItem = new T;

		if (!dynamic_cast<OBJItem*>(newItem))
		{
			//다이나믹 업케스팅이안되면....
			//상속구조가 아니라는이야기 임으로 걸러낼수 있을거같은데........
			//메모리 해제를 해준다.
			delete newItem;
			newItem = nullptr;
			return nullptr;
		}
		//생성이 정상적으로 되었다면.
		//런타임타입정보를 넣어주고
		newItem->SetRTTI();
		//초기화 진행
		if (!newItem->Init())
		{
			delete newItem;
			newItem = nullptr;
			return nullptr;
		}
		newItem->pLayer = this;
		m_mapObj.insert(std::make_pair(name, (OBJItem*)newItem));
		return newItem;
	}


};

