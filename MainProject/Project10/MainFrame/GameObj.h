#pragma once
#include "FrameHeader.h"
//#include <typeinfo.h>//�����ϰ�... �̰� ���� �Ⱦ����� �𸣰ڴ�.



//������ ��ӹް� ����Ŵ�...
//�������Ϸ�-����
//�� Ŭ���� ������ �̸��� �Ӽ��� �������ִ�.
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
	Tstring m_strTag;			//���� ��������
	Tstring m_strName;			//���� �̸�
	ClassUseType m_eCuseType = ClassErr;	//Ŭ���� Ÿ��
	const type_info* m_classtype;//Ŭ������ Ÿ���� �����ҰŴ�.
	
	bool IsActive = true;	// Ȱ��ȭ ����
	bool IsDel = false;		// ������ ����

protected:
	virtual void SetRTTI() final
	{
		//�ϴ��� Ÿ�� ���� �ȰͰ���?
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

	//Get������
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

