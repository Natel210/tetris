#pragma once
#include <unordered_map>
#include <tchar.h>
#include <string.h>
#include <Windows.h>

static const float NonDoubleTap = INFINITY;//����.. ��¥�� �����̵��� ������ü�� �ȵȴ�.
static int NoFindIndex = INT_MIN;

namespace std { typedef basic_string<TCHAR> tstring; }
using Tstring = std::tstring;
