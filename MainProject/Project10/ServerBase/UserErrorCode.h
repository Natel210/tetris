#pragma once

#include <Windows.h>


#ifdef _DEBUG
#define DebugErr(title, Comment) MessageBoxA(NULL, Comment, title, MB_OK)
#else
#define DebugErr(title, Comment)
#endif

#define ServerErr(Comment) MessageBoxA(NULL, Comment, "���� ����", MB_OK)