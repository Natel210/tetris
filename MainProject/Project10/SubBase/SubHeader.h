#pragma once
#include <unordered_map>
#include <tchar.h>
#include <string.h>
#include <Windows.h>

static const float NonDoubleTap = INFINITY;//난값.. 어짜피 난값이들어가면 연산자체가 안된다.
static int NoFindIndex = INT_MIN;

namespace std { typedef basic_string<TCHAR> tstring; }
using Tstring = std::tstring;
