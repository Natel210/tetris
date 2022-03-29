#pragma once
#include "../SubHeader.h"
#include <list>


//��� ���� ������ ��Ʈ�� �̷������ ��Ʈ�� �������ȴ�.
//����ƽ �̱���
class WinDCManager
{
public:
	class WinDC
	{
		friend WinDCManager;
		Tstring m_DCname;
		int m_iDrowIdx;
		HDC m_DC = NULL;
		HBITMAP Newbmp = NULL;
		HBITMAP Oldbmp = NULL;
	public:
		int getidx() const {
			return m_iDrowIdx;
		}
		int PivotX;
		int PivotY;
		int SizeX;
		int SizeY;

		WinDC() {}
		~WinDC() {}
	};
private:
	static bool m_bDebugShow;



	static HDC m_MainDC;
	static HDC m_PrintDC;
	static HBITMAP NewPrintbmp;
	static HBITMAP OldPrintbmp;
	
	static HDC m_ClearDC;
	static HBITMAP NewClearbmp;
	static HBITMAP OldClearbmp;

	static HDC m_DebugDC;
	static HBITMAP NewDebugbmp;
	static HBITMAP OldDebugbmp;

	static int WindSizeX;
	static int WindSizeY;

	// 1) ���̾�� DC�� �������ְ� �װ����� ��ġ�������Ѵ�.

	static std::list<WinDC> m_DClist;

public:
	static bool init(HDC _Main ,int windX ,int windY);
	static bool Update();
	static bool release();

	static bool CreateHDC(const TCHAR * _Name, int _Idx, int _pivotX = 0 , int _pivotY = 0, int _sizeX = WindSizeX, int _sizeY = WindSizeY);
	static HDC FindDC(const TCHAR * _Name);
	static WinDC FindWinDC(const TCHAR * _Name);
	static bool DelDC(const TCHAR * _Name);

	static bool ClearDC(const TCHAR * _Name);
	static bool ClearDC();//��ü �ʱ�ȭ
	static bool ClearPrintDC();//����Ʈ ���� �ʱ�ȭ

	static HDC GetPrintDC();
	static HDC GetDebugDC();


private:
	WinDCManager();
	~WinDCManager();
};


//////////////////////////////////////////////////////////////////////
//�׸��� �׸����� ��弳���� �ʿ��ѵ� �̰� ���������� �����ؾ� �ҰͰ��� ���� �̰� �ϴ� ����ü �������� �������
class ColorManager
{
private:
	static std::unordered_map<Tstring, HBRUSH> m_Brushmap;
	static std::unordered_map<Tstring, HPEN> m_Penmap;
	static std::unordered_map<Tstring, COLORREF> m_TexColormap;



public:
	static bool CreateBrush(const TCHAR * _key, LOGBRUSH _brushDESC);
	static bool CreatePen(const TCHAR * _key ,LOGPEN _penDESC);
	static bool CreateTexColor(const TCHAR * _key, COLORREF _Color);
	static bool CreateTexColor(const TCHAR * _key, int _r, int _g, int _b);


	static HBRUSH FindBrush(const TCHAR * _key);
	static HPEN FindPen(const TCHAR * _key);
	static COLORREF FindTexColor(const TCHAR * _key);

	static bool init();
	static void release();

private:
	ColorManager()
	{}
	~ColorManager()
	{}
};

//////////////////////////////////////////////////////////////////////