// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#include "ControllerServer.h"


#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

///////////////////////
//���� lib �߰�
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
//���� lib �߰�
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