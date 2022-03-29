#pragma once




// 구조간에서 전해주고 싶은 리턴값들
enum ProgressResult
{
	PR_ERRER,
	PR_NONATIVE,
	PR_OK,
	PR_SCENECHNAGE,
	PR_RECONECTSURVER,
};


//TCHAR을 활용한 TSTRING 정의
namespace std { typedef basic_string<TCHAR> tstring; }
using Tstring = std::tstring;
