// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#include "ControllerServer.h"


#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

///////////////////////
//서브 lib 추가
#ifdef X64
#ifdef DEBUGMODE
#pragma comment(lib, "SubBaseDx64.lib")
#else
#pragma comment(lib, "SubBasex64.lib")
#endif // _DEBUG
#else
#ifdef DEBUGMODE
#pragma comment(lib, "SubBaseDx32.lib")
#else
#pragma comment(lib, "SubBasex32.lib")
#endif 
#endif// X64


#include "Time/Time.h" 
#include "Input/Input.h"

///////////////////////
//서버 lib 추가
#ifdef X64
#ifdef DEBUGMODE
#pragma comment(lib, "ServerBaseDx64.lib")
#else
#pragma comment(lib, "ServerBasex64.lib")
#endif // _DEBUG
#else
#ifdef DEBUGMODE
#pragma comment(lib, "ServerBaseDx32.lib")
#else
#pragma comment(lib, "ServerBasex32.lib")
#endif 
#endif// X64

#include "NetCore.h"