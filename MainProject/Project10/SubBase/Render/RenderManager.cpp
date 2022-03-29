#include "RenderManager.h"
#include <algorithm>

bool WinDCManager::m_bDebugShow = true;

HDC WinDCManager::m_MainDC = NULL;

HDC WinDCManager::m_PrintDC = NULL;
HBITMAP WinDCManager::NewPrintbmp = NULL;
HBITMAP WinDCManager::OldPrintbmp = NULL;

HDC WinDCManager::m_ClearDC = NULL;
HBITMAP WinDCManager::NewClearbmp = NULL;
HBITMAP WinDCManager::OldClearbmp = NULL;

HDC WinDCManager::m_DebugDC = NULL;
HBITMAP WinDCManager::NewDebugbmp = NULL;
HBITMAP WinDCManager::OldDebugbmp = NULL;

std::list<WinDCManager::WinDC> WinDCManager::m_DClist;

int WinDCManager::WindSizeX =  100;
int WinDCManager::WindSizeY =  100;


static bool DCsort(const WinDCManager::WinDC &_src,  const WinDCManager::WinDC &_dest)
{
	return (_src.getidx() < _dest.getidx());
}

bool WinDCManager::init(HDC _Main, int windX, int windY)
{
	if (!_Main)
	{
		return false;
	}

	WindSizeX = windX;
	WindSizeY = windY;

	m_MainDC = _Main;

	//클리어전용 버퍼를만든다. (허연색으로 또는 특정색으로)

	m_ClearDC = CreateCompatibleDC(_Main);
	if (!m_ClearDC)
	{
		return false;
	}
	NewClearbmp = CreateCompatibleBitmap(_Main, WindSizeX, WindSizeY);
	OldClearbmp = (HBITMAP)SelectObject(m_ClearDC, NewClearbmp);

	for (int y = 0; y < WindSizeY; ++y)
	{
		for (int x = 0; x < WindSizeX; ++x)
		{
			SetPixel(m_ClearDC, x, y, RGB(200, 200, 200));
		}
	}


	/////////////////////////////

	m_PrintDC = CreateCompatibleDC(_Main);
	if (!m_PrintDC)
	{
		return false;
	}
	NewPrintbmp = CreateCompatibleBitmap(_Main, WindSizeX, WindSizeY);
	OldPrintbmp = (HBITMAP)SelectObject(m_PrintDC, NewPrintbmp);

	BitBlt(m_PrintDC, 0, 0, windX, windY, m_ClearDC, 0, 0, SRCCOPY);

#ifdef _DEBUG
	m_DebugDC = CreateCompatibleDC(_Main);
	if (!m_DebugDC)
	{
		return false;
	}
	NewDebugbmp = CreateCompatibleBitmap(_Main, WindSizeX, WindSizeY);
	OldDebugbmp = (HBITMAP)SelectObject(m_DebugDC, NewDebugbmp);

	BitBlt(m_DebugDC, 0, 0, windX, windY, m_ClearDC, 0, 0, SRCCOPY);
#endif // _DEBUG








	m_DClist.clear();

	return true;
}


//더블버퍼링하기 전에 넣을것들
bool WinDCManager::Update()
{
	if (!m_PrintDC)
	{
		return false;
	}

	if ((int)m_DClist.size() >= 2)
	{
		m_DClist.sort(DCsort);
	}
	
	////
	std::list<WinDC>::iterator m_StartIter = m_DClist.begin();
	std::list<WinDC>::iterator m_EndIter = m_DClist.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		//덮어쓴다.
		BitBlt(m_PrintDC, 0, 0, WindSizeX, WindSizeY, (*m_StartIter).m_DC, ((*m_StartIter).PivotX * -1), ((*m_StartIter).PivotY * -1), SRCAND);
		//오류가 날수도있음..
	}

#ifdef _DEBUG
	//최종에 디버그를 씌워준다.
	if (m_bDebugShow)
	{
		BitBlt(m_PrintDC, 0, 0, WindSizeX, WindSizeY, m_DebugDC, 0, 0, SRCAND);
	}
#endif // _DEBUG

	

	return true;
}

bool WinDCManager::release()
{
	std::list<WinDC>::iterator m_StartIter = m_DClist.begin();
	std::list<WinDC>::iterator m_EndIter = m_DClist.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		SelectObject((*m_StartIter).m_DC, (*m_StartIter).Oldbmp);
		DeleteObject((*m_StartIter).Newbmp);
		DeleteDC((*m_StartIter).m_DC);
	}
	m_DClist.clear();


	SelectObject(m_DebugDC, OldDebugbmp);
	DeleteObject(NewDebugbmp);
	DeleteDC(m_DebugDC);

	SelectObject(m_PrintDC, OldPrintbmp);
	DeleteObject(NewPrintbmp);
	DeleteDC(m_PrintDC);

	SelectObject(m_ClearDC, OldClearbmp);
	DeleteObject(NewClearbmp);
	DeleteDC(m_ClearDC);
	return true;
}

bool WinDCManager::CreateHDC(const TCHAR * _Name, int _Idx, int _pivotX, int _pivotY, int _sizeX, int _sizeY)
{
	WinDC newWindc = WinDC();
	newWindc.m_iDrowIdx = _Idx;
	newWindc.m_DCname = _Name;
	newWindc.PivotX = _pivotX;
	newWindc.PivotY = _pivotY;
	newWindc.SizeX = _sizeX;
	newWindc.SizeY = _sizeY;

	newWindc.m_DC = CreateCompatibleDC(m_MainDC);
	if (!newWindc.m_DC)
	{
		return false;
	}
	newWindc.Newbmp = CreateCompatibleBitmap(m_MainDC, _sizeX, _sizeY);
	newWindc.Oldbmp = (HBITMAP)SelectObject(newWindc.m_DC, newWindc.Newbmp);


	BitBlt(newWindc.m_DC, 0, 0, _sizeX, _sizeY, m_ClearDC, 0, 0, SRCCOPY);
	m_DClist.push_back(newWindc);

	return false;
}

HDC WinDCManager::FindDC(const TCHAR * _Name)
{
	std::list<WinDC>::iterator m_StartIter = m_DClist.begin();
	std::list<WinDC>::iterator m_EndIter = m_DClist.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((*m_StartIter).m_DCname == _Name)
		{
			return (*m_StartIter).m_DC;
		}

	}
	return NULL;
}

WinDCManager::WinDC WinDCManager::FindWinDC(const TCHAR * _Name)
{
	std::list<WinDC>::iterator m_StartIter = m_DClist.begin();
	std::list<WinDC>::iterator m_EndIter = m_DClist.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((*m_StartIter).m_DCname == _Name)
		{
			return (*m_StartIter);
		}

	}
	return WinDC();
}

bool WinDCManager::DelDC(const TCHAR * _Name)
{
	std::list<WinDC>::iterator m_StartIter = m_DClist.begin();
	std::list<WinDC>::iterator m_EndIter = m_DClist.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((*m_StartIter).m_DCname == _Name)
		{
			SelectObject((*m_StartIter).m_DC, (*m_StartIter).Oldbmp);
			DeleteObject((*m_StartIter).Newbmp);
			DeleteDC((*m_StartIter).m_DC);
			m_StartIter = m_DClist.erase(m_StartIter);
			return true;
		}
	}
	return false;
}

bool WinDCManager::ClearDC(const TCHAR * _Name)
{
	std::list<WinDC>::iterator m_StartIter = m_DClist.begin();
	std::list<WinDC>::iterator m_EndIter = m_DClist.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		if ((*m_StartIter).m_DCname == _Name)
		{
			BitBlt(m_StartIter->m_DC, 0, 0, m_StartIter->SizeX, m_StartIter->SizeY, m_ClearDC, 0, 0, SRCCOPY);
			return true;
		}
	}
	return false;
}

bool WinDCManager::ClearDC()
{
	std::list<WinDC>::iterator m_StartIter = m_DClist.begin();
	std::list<WinDC>::iterator m_EndIter = m_DClist.end();
	for (; m_StartIter != m_EndIter; ++m_StartIter)
	{
		BitBlt(m_StartIter->m_DC, 0, 0, m_StartIter->SizeX, m_StartIter->SizeY, m_ClearDC, 0, 0, SRCCOPY);
	}
	BitBlt(m_PrintDC, 0, 0, WindSizeX, WindSizeY, m_ClearDC, 0, 0, SRCCOPY);
	
	return true;
}

bool WinDCManager::ClearPrintDC()
{
	BitBlt(m_PrintDC, 0, 0, WindSizeX, WindSizeY, m_ClearDC, 0, 0, SRCCOPY);
	return true;
}

HDC WinDCManager::GetPrintDC()
{
	return m_PrintDC;
}

HDC WinDCManager::GetDebugDC()
{
	return m_DebugDC;
}


WinDCManager::WinDCManager()
{}

WinDCManager::~WinDCManager()
{}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

std::unordered_map<Tstring, HBRUSH> ColorManager::m_Brushmap;
std::unordered_map<Tstring, HPEN> ColorManager::m_Penmap;
std::unordered_map<Tstring, COLORREF> ColorManager::m_TexColormap;

bool ColorManager::CreateBrush(const TCHAR * _key, LOGBRUSH _brushDESC)
{
	HBRUSH findbrush = FindBrush(_key);
	if (findbrush)
	{
		return false;
	}
	findbrush = CreateBrushIndirect(&_brushDESC);
	m_Brushmap.insert(std::make_pair(_key, findbrush));
	return true;
}

bool ColorManager::CreatePen(const TCHAR * _key, LOGPEN _penDESC)
{
	HPEN findpen = FindPen(_key);
	if (findpen)
	{
		return false;
	}
	findpen = CreatePenIndirect(&_penDESC);
	m_Penmap.insert(std::make_pair(_key, findpen));
	return true;
}

bool ColorManager::CreateTexColor(const TCHAR * _key, COLORREF _Color)
{
	if (FindTexColor(_key))
	{
		return false;
	}
	m_TexColormap.insert(std::make_pair(_key, _Color));
	return true;
}

bool ColorManager::CreateTexColor(const TCHAR * _key, int _r, int _g, int _b)
{
	if (FindTexColor(_key))
	{
		return false;
	}
	m_TexColormap.insert(std::make_pair(_key, RGB(_r, _g, _b)));
	return true;
}


HBRUSH ColorManager::FindBrush(const TCHAR * _key)
{
	std::unordered_map<Tstring, HBRUSH> ::iterator finditer;
	finditer = m_Brushmap.find(_key);
	if (finditer != m_Brushmap.end())
	{
		return finditer->second;
	}
	return NULL;
}

HPEN ColorManager::FindPen(const TCHAR * _key)
{
	std::unordered_map<Tstring, HPEN> ::iterator finditer;
	finditer = m_Penmap.find(_key);
	if (finditer != m_Penmap.end())
	{
		return finditer->second;
	}
	return NULL;
}

COLORREF ColorManager::FindTexColor(const TCHAR * _key)
{
	std::unordered_map<Tstring, COLORREF > ::iterator finditer;
	finditer = m_TexColormap.find(_key);
	if (finditer != m_TexColormap.end())
	{
		return finditer->second;
	}
	return NULL;
}


bool ColorManager::init()
{
	m_Brushmap.clear();
	m_Penmap.clear();
	m_TexColormap.clear();

	LOGBRUSH ebrush = {};
	ebrush.lbStyle = BS_SOLID;
	ebrush.lbHatch = HS_API_MAX;

	ebrush.lbColor = RGB(200, 0, 0);
	CreateBrush(_T("ActiveBrush1"), ebrush);

	ebrush.lbColor = RGB(200, 200, 0);
	CreateBrush(_T("ActiveBrush2"), ebrush);

	ebrush.lbColor = RGB(200, 0, 200);
	CreateBrush(_T("ActiveBrush3"), ebrush);

	ebrush.lbColor = RGB(0, 150, 200);
	CreateBrush(_T("ActiveBrush4"), ebrush);

	ebrush.lbColor = RGB(0, 200, 0);
	CreateBrush(_T("ActiveBrush5"), ebrush);

	ebrush.lbColor = RGB(0, 0, 200);
	CreateBrush(_T("ActiveBrush6"), ebrush);

	ebrush.lbColor = RGB(200, 200, 200);
	CreateBrush(_T("ActiveBrush7"), ebrush);

	ebrush.lbColor = RGB(90, 90, 90);

	CreateBrush(_T("NonActiveBrush"), ebrush);

	ebrush.lbColor = RGB(170, 170, 170);

	CreateBrush(_T("BackMapBrush"), ebrush);


	LOGPEN ePen;
	ePen.lopnStyle = PS_SOLID;
	POINT spoint;
	spoint.x = 1;
	spoint.y = 1;
	ePen.lopnWidth = spoint;
	ePen.lopnColor = RGB(75, 75, 75);

	CreatePen(_T("BackMapPen"), ePen);


	ePen.lopnColor = RGB(150, 0, 0);
	CreatePen(_T("ActivePen1"), ePen);

	ePen.lopnColor = RGB(150, 150, 0);
	CreatePen(_T("ActivePen2"), ePen);

	ePen.lopnColor = RGB(150, 0, 150);
	CreatePen(_T("ActivePen3"), ePen);

	ePen.lopnColor = RGB(0, 75, 150);
	CreatePen(_T("ActivePen4"), ePen);

	ePen.lopnColor = RGB(0, 150, 0);
	CreatePen(_T("ActivePen5"), ePen);

	ePen.lopnColor = RGB(0, 0, 150);
	CreatePen(_T("ActivePen6"), ePen);

	ePen.lopnColor = RGB(150, 150, 150);
	CreatePen(_T("ActivePen7"), ePen);

	spoint.x = 3;
	spoint.y = 3;
	ePen.lopnWidth = spoint;
	ePen.lopnColor = RGB(155, 0, 100);
	CreatePen(_T("DebugRect"), ePen);

	return true;

}

void ColorManager::release()
{
	std::unordered_map<Tstring, HBRUSH> ::iterator StartBrushiter = m_Brushmap.begin();
	std::unordered_map<Tstring, HBRUSH> ::iterator EndBrushiter = m_Brushmap.end();
	for (;StartBrushiter != EndBrushiter;)
	{
		DeleteObject(StartBrushiter->second);
		StartBrushiter = m_Brushmap.erase(StartBrushiter);
		EndBrushiter = m_Brushmap.end();
	}


	std::unordered_map<Tstring, HPEN> ::iterator StartPeniter = m_Penmap.begin();
	std::unordered_map<Tstring, HPEN> ::iterator EndPeniter = m_Penmap.end();
	for (; StartPeniter != EndPeniter;)
	{
		DeleteObject(StartPeniter->second);
		StartPeniter = m_Penmap.erase(StartPeniter);
		EndPeniter = m_Penmap.end();
	}

}

























