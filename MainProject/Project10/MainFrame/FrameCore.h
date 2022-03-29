#pragma once
#include "FrameHeader.h"

class FrameCore
{
private:
	static std::unordered_map<Tstring, class Scene*> m_mapScene;
	static std::unordered_map<Tstring, class Scene*>::iterator m_StartIter;
	static std::unordered_map<Tstring, class Scene*>::iterator m_EndIter;
	static bool DebugMode;
public:
	//���� ĳ���� �ؾ߰���?
	static class Scene* FindScene(Tstring name);//�̰� �׳� ����ü�� �޴°�.

	static bool RemoveScene(Tstring name);

	static void DebugModeChange();


	//���� �����κ�
	static bool Logic(float time);
	
private:
	static int Input(float time);
	static int Update(float time);
	static int LateUpdate(float time);
	static int Transform(float time);
	static int Render(float time);
	static int DebugRender(float time);
	static int Collision(float time);


private:
	FrameCore() {}
	~FrameCore(){}

public:
	template<typename T>
	static T* FindScene(Tstring name)
	{
		m_StartIter = m_mapScene.find(name);
		if (m_StartIter != m_mapScene.end())
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
	static T* CreateScene(Tstring name)
	{
		T* newScene = FindScene<T>(name);
		if (newScene)
		{
			return newScene;
		}
		newScene = new T;
		if (!dynamic_cast<Scene*>(newScene))
		{
			//���̳��� ���ɽ����̾ȵǸ�....
			//��ӱ����� �ƴ϶���̾߱� ������ �ɷ����� �����Ű�����........
			//�޸� ������ ���ش�.
			delete newScene;
			newScene = nullptr;
			return nullptr;
		}
		//������ ���������� �Ǿ��ٸ�.
		//��Ÿ��Ÿ�������� �־��ְ�
		newScene->SetRTTI();
		//�ʱ�ȭ ����
		if (!newScene->Init())
		{
			delete newScene;
			newScene = nullptr;
			return nullptr;
		}
		m_mapScene.insert(std::make_pair(name, (Scene*)newScene));
		return newScene;
	}


};

