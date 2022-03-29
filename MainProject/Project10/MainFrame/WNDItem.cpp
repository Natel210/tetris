#include "WNDItem.h"

std::unordered_map<HWND, WNDItem*> WNDItem::m_WndItemmap;
WNDItem::WNDItem()
{
}


WNDItem::~WNDItem()
{
}

int WNDItem::Init()
{


	return 1;
}

int WNDItem::release()
{
	return 1;
}

int WNDItem::Init(LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int Width, int Height, HWND hWndParent, HINSTANCE hInstance, LPVOID lpParam)
{
	if (lpClassName == NULL)
	{
		MessageBox(NULL, TEXT("등록된 윈도우 클래스가 없습니다."), TEXT("윈도우 아이템 만들기 실패"), MB_OK);
	}

	m_hWnd = CreateWindowW(lpClassName, lpWindowName, dwStyle, X, Y, Width, Height, hWndParent, HMENU(0), hInstance, lpParam);
	ShowWindow(m_hWnd, SW_HIDE);
	if (!m_hWnd)
	{
		return 0;
	}
	m_OldProc = SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, LONG_PTR(WNDItem::StaticWNDProc));

	m_hParanthWND = hWndParent;

	m_lpClassName = lpClassName;
	m_lpWindowName = lpWindowName;
	m_dwStyle = dwStyle;


	m_Rect.top = Y;
	m_Rect.bottom = Height;
	m_Rect.left = X;
	m_Rect.right = Width;

	m_hInstance = hInstance;
	m_lpParam = lpParam;

	//HDC hDC = GetDC(hWndParent);
	//m_MemoryDC = CreateCompatibleDC(hDC);
	//NewMDCbmp = CreateCompatibleBitmap(hDC, Width, Height);
	//OldMDCbmp = (HBITMAP)SelectObject(m_MemoryDC, NewMDCbmp);


	m_WndItemmap.insert(std::make_pair(m_hWnd, this));
	return PR_OK;
}

int WNDItem::release(int nothing)
{
	//SelectObject(m_MemoryDC, OldMDCbmp);
	//DeleteObject(NewMDCbmp);
	//DeleteDC(m_MemoryDC);
	DestrotyWindowsItem();
	//DestroyWindow(m_hWnd);

	//m_hWnd = NULL;
	m_OldProc = NULL;
	return 1;
}

void WNDItem::CreateWindowsItem()
{
	if (m_lpClassName == NULL)
	{
		MessageBox(NULL, TEXT("등록된 윈도우 클래스가 없습니다."), TEXT("윈도우 아이템 만들기 실패"), MB_OK);
	}

	m_hWnd = CreateWindowW(m_lpClassName, m_lpWindowName, m_dwStyle, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom, m_hParanthWND, HMENU(0), m_hInstance, m_lpParam);
	if (!m_hWnd)
	{
		return;
	}
	m_OldProc = SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, LONG_PTR(WNDItem::StaticWNDProc));

	m_WndItemmap.insert(std::make_pair(m_hWnd, this));
	return;
}

void WNDItem::DestrotyWindowsItem()
{
	//SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, LONG_PTR(m_OldProc));
	 //= FindItem(m_hWnd)
	m_WndItemmap.erase(m_hWnd);
	DestroyWindow(m_hWnd);
	//CloseHandle(m_hWnd);
	m_hWnd = NULL;
}

bool WNDItem::GetActive()
{
	//if (OBJItem::GetActive())
	//{
	//	if (m_hWnd == NULL)
	//	{
	//		CreateWindowsItem();
	//	}
	//	return true;
	//}
	//else
	//{
	//	if (m_hWnd != NULL)
	//	{
	//		DestrotyWindowsItem();
	//	}
	//	return false;
	//}
	//return false;
	return OBJItem::GetActive();
}

void WNDItem::SetActive(bool active)
{
	//if (active)
	//{
	//	CreateWindowsItem();
	//}
	//else
	//{
	//	DestrotyWindowsItem();
	//}
	GameObj::SetActive(active);
	return;
}

int WNDItem::LateUpdate(float time)
{
	return 0;
}

int WNDItem::Transform(float time)
{
	return 0;
}

int WNDItem::Render(float time, HDC drow)
{
	return 0;
}

int WNDItem::DebugRender(float time)
{
	return 0;
}

int WNDItem::Collision(float time)
{
	return 0;
}



void WNDItem::UpdatePositon()
{
	MoveWindow(m_hWnd, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom, true);
}

void WNDItem::MovePos(int x, int y)
{
	m_Rect.left = x;
	m_Rect.top = y;
	UpdatePositon();
}

void WNDItem::SetSize(int x, int y)
{
	m_Rect.right = x;
	m_Rect.bottom = y;
	UpdatePositon();
}

void WNDItem::WndShow()
{
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
}

void WNDItem::WndHide()
{
	ShowWindow(m_hWnd, SW_HIDE);
}
