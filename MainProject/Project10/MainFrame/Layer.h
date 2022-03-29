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
			//���̳��� ���ɽ����̾ȵǸ�....
			//��ӱ����� �ƴ϶���̾߱� ������ �ɷ����� �����Ű�����........
			//�޸� ������ ���ش�.
			delete newItem;
			newItem = nullptr;
			return nullptr;
		}
		//������ ���������� �Ǿ��ٸ�.
		//��Ÿ��Ÿ�������� �־��ְ�
		newItem->SetRTTI();
		//�ʱ�ȭ ����
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

