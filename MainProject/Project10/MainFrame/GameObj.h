#pragma once
#include "FrameHeader.h"
//#include <typeinfo.h>//공부하고... 이건 쓸지 안쓸지도 모르겠다.



//무조건 상속받게 만들거다...
//프로파일러-전용
//각 클래스 마다의 이름과 속성을 가지고있다.
enum ClassUseType
{
	ClassErr = -1,
	Class_SCENE,
	Class_LAYER,
	Class_OBJ
};

class GameObj
{
protected:
	Tstring m_strTag;			//누가 누구인지
	Tstring m_strName;			//나의 이름
	ClassUseType m_eCuseType = ClassErr;	//클래스 타입
	const type_info* m_classtype;//클래스의 타입을 저장할거다.
	
	bool IsActive = true;	// 활성화 유무
	bool IsDel = false;		// 지워짐 여부

protected:
	virtual void SetRTTI() final
	{
		//일단은 타입 인포 된것같다?
		m_classtype = &typeid(*this);
	}


public:
	inline void virtual SetActive(bool active)
	{
		IsActive = active;
		return;
	}

	inline virtual bool GetActive() 
	{
		return IsActive;
	}
	inline bool GetDel() const
	{
		return IsDel;
	}
	inline void Delete() 
	{
		IsDel = true;
		return;
	}

	//Get만있음
	inline const Tstring& GetTag() const
	{

	}
	inline const Tstring& GetName() const
	{

	}
	inline ClassUseType GetClassType() const
	{
		//std::type_info::name();
		//(&this).name()
	}

	inline const type_info*  GetRTTI() const
	{
		return m_classtype;
	}

public:
	GameObj();
	virtual ~GameObj() = 0;
};

