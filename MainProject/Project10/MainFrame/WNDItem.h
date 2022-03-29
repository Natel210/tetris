#pragma once
#include "OBJItem.h"
class WNDItem :	public OBJItem
{
private:
	friend class Layer;
private:
	LONG_PTR m_OldProc = NULL;
	bool IsActiveCheck = true;
protected:
	HWND m_hWnd = NULL;
	RECT m_Rect;
protected:
	bool m_bReUpdate = false;

private:
	LPCWSTR m_lpClassName;
	LPCWSTR m_lpWindowName;
	DWORD m_dwStyle;
	HWND m_hParanthWND = NULL;
	HINSTANCE m_hInstance;
	LPVOID m_lpParam;

	bool m_bChangeRGB = false;
	COLORREF m_iChangeRGBColor = COLORREF();
public:
	inline void SetChangeBK(bool _Update, COLORREF _Color = RGB(0, 0, 0))
	{
		m_bChangeRGB = _Update;
		m_iChangeRGBColor = _Color;
	}
	inline bool GetChangeBK() const
	{
		return m_bChangeRGB;
	}
	inline COLORREF GetChangeBKColor() const
	{
		if (m_bChangeRGB)
		{
			return m_iChangeRGBColor;
		}
		else
		{
			return  RGB(0, 0, 0);
		}
		
	}
protected:
	virtual int Input(float time) = 0;
	virtual int Update(float time) = 0;
	virtual int LateUpdate(float time) = 0;
	virtual int Transform(float time);
	virtual int Render(float time, HDC drow);
	virtual int DebugRender(float time);
	virtual int Collision(float time);

private:
	virtual int Init() = 0;
	virtual int release() = 0;
protected:
	virtual int Init(LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int Width, int Height, HWND hWndParent, HINSTANCE hInstance, LPVOID lpParam) final;
	virtual int release(int nothing) final;


private:
	void CreateWindowsItem();
	void DestrotyWindowsItem();
protected:
	virtual bool GetActive() final;
	virtual void SetActive(bool active) final;

public:
	virtual void WNDItem::UpdatePositon()final;
	virtual void WNDItem::MovePos(int x, int y)final;
	virtual void WNDItem::SetSize(int x, int y)final;
	virtual void WNDItem::WndShow()final;
	virtual void WNDItem::WndHide()final;
public:
	virtual LRESULT CALLBACK CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;


private:
	static std::unordered_map<HWND, WNDItem*> m_WndItemmap;

public:
	static void ALLHIDE()
	{
		std::unordered_map<HWND, WNDItem*>::iterator startIter = m_WndItemmap.begin() ;
		std::unordered_map<HWND, WNDItem*>::iterator endIter = m_WndItemmap.end();
		for (; startIter != endIter; ++startIter)
		{
			ShowWindow(startIter->first, SW_HIDE);
		}

	}
	static void ALLSHOW()
	{
		std::unordered_map<HWND, WNDItem*>::iterator startIter = m_WndItemmap.begin();
		std::unordered_map<HWND, WNDItem*>::iterator endIter = m_WndItemmap.end();
		for (; startIter != endIter; ++startIter)
		{
			ShowWindow(startIter->first, SW_SHOWNORMAL);
		}
	}
public:
	static WNDItem* FindItem(HWND hWnd)
	{
		std::unordered_map<HWND, WNDItem*>::iterator FindIter;
		FindIter = m_WndItemmap.find(hWnd);	
		if (FindIter != m_WndItemmap.end())
		{
			return FindIter->second;
		}
		return nullptr;
	}

	static bool IsFocusItem()
	{
		std::unordered_map<HWND, WNDItem*>::iterator FindIter = m_WndItemmap.begin();
		HWND curfocuswnd = GetFocus();
		while (FindIter != m_WndItemmap.end())
		{
			if (curfocuswnd == FindIter->first)
			{
				return true;
			}
			++FindIter;
		}
		return false;
	}
	////////////

///////////////////////

public:
	static LRESULT CALLBACK StaticWNDProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT coll_result = 0;
		WNDItem* finditem = nullptr;
		if (IsWindowEnabled(hWnd))
		{
			finditem = FindItem(hWnd);
		}
	
		if (finditem)
		{
			coll_result = finditem->CustomProc(hWnd, message, wParam, lParam);
			if (coll_result == 0 && finditem->m_OldProc)
			{
				coll_result = CallWindowProc(WNDPROC(finditem->m_OldProc), hWnd, message, wParam, lParam);
			}
		}
		return coll_result;
	}

protected:
	WNDItem();
	~WNDItem();
};

