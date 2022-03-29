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
	//직접 캐스팅 해야겠죠?
	static class Scene* FindScene(Tstring name);//이건 그냥 씬자체만 받는것.

	static bool RemoveScene(Tstring name);

	static void DebugModeChange();


	//실제 구동부분
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
			//다이나믹 업케스팅이안되면....
			//상속구조가 아니라는이야기 임으로 걸러낼수 있을거같은데........
			//메모리 해제를 해준다.
			delete newScene;
			newScene = nullptr;
			return nullptr;
		}
		//생성이 정상적으로 되었다면.
		//런타임타입정보를 넣어주고
		newScene->SetRTTI();
		//초기화 진행
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

