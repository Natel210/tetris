#pragma once

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


#include "Input/Input.h"
#include "Render/RenderManager.h"


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
#endif // X64

#endif // WIN32

#include "UseServer.h"


///////////////////////
//기반 프레임 lib 추가
///////////////////////
//서버 lib 추가
#ifdef X64
#ifdef DEBUGMODE
#pragma comment(lib, "MainFrameDx64.lib")
#else
#pragma comment(lib, "MainFramex64.lib")
#endif // _DEBUG
#else
#ifdef DEBUGMODE
#pragma comment(lib, "MainFrameDx32.lib")
#else
#pragma comment(lib, "MainFramex32.lib")
#endif // X64

#endif // WIN32


namespace
{


	static const int WindSizeX = 1200;
	static const int WindSizeY = 900;

}




#include "ClientIngameEnum.h"