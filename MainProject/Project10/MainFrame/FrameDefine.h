#pragma once




// ���������� �����ְ� ���� ���ϰ���
enum ProgressResult
{
	PR_ERRER,
	PR_NONATIVE,
	PR_OK,
	PR_SCENECHNAGE,
	PR_RECONECTSURVER,
};


//TCHAR�� Ȱ���� TSTRING ����
namespace std { typedef basic_string<TCHAR> tstring; }
using Tstring = std::tstring;
