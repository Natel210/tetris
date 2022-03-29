// Client.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Client.h"
#include <thread>

#include "ClientHeader.h"
#include "Time/Time.h" 
#include "ClientCore.h"

#include <unordered_map>


#include "WNDItem.h"
//#include <mutex>
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

void init() {
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;
	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));


	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

double getCurrentValue() {
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));


	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (double) (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;

	return percent * 100;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////





//////////////////////////////////////////////////////
#define MAX_LOADSTRING 100



// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(251);
	TCHAR* trustreak = new TCHAR;
#endif // DEBUG

	srand((UINT)time(0));


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	////////////////////////////////////////////
	// ������ �ν��Ͻ�
    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	////////////////////////////////////////////
	init();
	////////////////////////////////////////////
	HDC mainDC = GetDC(ClientCore::mainhWnd);
	////////////////////////////////////////////
	//�Ŵ��� �ν��Ͻ�
	TimeManager::init();
	InputManager::init();
	//InputManager::SethWnd(ClientCore::mainhWnd);
	WinDCManager::init(mainDC, WindSizeX, WindSizeY);
	ColorManager::init();
	////////////////////////////////////////////
	//���� �ν��Ͻ�
	ClientCore::init();
	////////////////////////////////////////////
	//���� �ν��Ͻ�
	ClientCore::pServer = new UseServer();
	ClientCore::pServer->init(IP, PORT);
	//////////////////////////////////////////////
	ClientCore::ClientPlayer.eLoginfo.m_UniqueID = ClientCore::pServer->MyUniqueNum;
	//////////////////////////////////////////////
	// ������ �����ְ� �޴� ������
	//HANDLE SendHandle = (HANDLE)_beginthreadex(nullptr, 0, UseServer::Sends, (void*)ClientCore::pServer, 0, nullptr);
	HANDLE RecvHandle = (HANDLE)_beginthreadex(nullptr, 0, UseServer::Recvs, (void*)ClientCore::pServer, 0, nullptr);
	//������ ����
	ClientCore::PrintDC = WinDCManager::GetPrintDC();

	//Loop����
#define MAXUPdate 1.0f
	float isUpdate = 0.5f;
	int TimeUpdateCount = 0;
	float subtime = 0.0f;
	float subfps = 0.0f;
	float fpsfixtime = 0.01f;
	TimeManager::CreateTimer(_T("FPSFIX"));

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (ClientCore::ClientRun)
	{
		TimeManager::FindTimer(_T("FPSFIX"))->EndCheck();
		TimeManager::FindTimer(_T("FPSFIX"))->StartCheck();
		fpsfixtime -= TimeManager::FindTimer(_T("FPSFIX"))->GetDeltaTime();
		ZeroMemory(&msg, sizeof(MSG));
		// �⺻ �޽��� �����Դϴ�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
		{
			GetMessage(&msg, nullptr, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (fpsfixtime < 0.0f)
			{
				fpsfixtime = 0.01f;
			}
			//Sleep((int(fpsfixtime *1000));

			while (!IsWindowVisible(ClientCore::mainhWnd))
			{
				CloseHandle(ClientCore::mainhWnd);
				InitInstance(hInstance, nCmdShow);
			}
			WinDCManager::ClearDC();// DCŬ����
			InvalidateRect(ClientCore::mainhWnd, NULL, FALSE);//������ ��ȭ����

			float fMainTimer = MainTime;
			float fMainFPS = 1.0f / fMainTimer;

			if (isUpdate > 0.0f)
			{
				isUpdate -= fMainTimer;
				TimeManager::FindTimer(_T("MainTime"))->EndCheck();			// �ð�üũ
				continue;
			}
			else
			{
				isUpdate = 0.0f;
			}



#ifdef _DEBUG
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//�ð��� ����� ���
			TCHAR MainTimerBuff[_MAX_PATH];
			memset(MainTimerBuff, 0, sizeof(TCHAR) * _MAX_PATH);
			RECT MainTimerRect;
			MainTimerRect.bottom = 100;
			MainTimerRect.top = 0;
			MainTimerRect.right = 300;
			MainTimerRect.left = 0;
			_stprintf_s(MainTimerBuff, TEXT("[MainTime : %.9f][FPS : %.2f]"), fMainTimer, fMainFPS);
			Tstring strMainTimer = MainTimerBuff;
			DrawText(WinDCManager::GetDebugDC(), strMainTimer.c_str(), (int)strMainTimer.size(), &MainTimerRect, DT_LEFT);
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // _DEBUG
			InputManager::Update(fMainTimer);
			ClientCore::Update(fMainTimer);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			WinDCManager::Update();									// ��� ���� ���� ���� �׸���.
			TimeManager::FindTimer(_T("MainTime"))->EndCheck();			// �ð�üũ
			TimeManager::FindTimer(_T("MainTime"))->StartCheck();//�ð� üũ ����
			/////////////////////////////////////////////////////////////////////
			ClientCore::pServer->LogClear();
		}

	}
	//////////////////////////////////////////////////////
	//ShowWindow(ClientCore::mainhWnd, FALSE);
	//////////////////////////////////////////////////////
	//�����찡 �������� ������ �����־�߰ڴ�.
	double Ticks = GetTickCount();
	double GetTicks = 2000.0;

	CommonPacket packets;
	packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	packets.PacProp.iLocation1 = SL_SYS;
	packets.PacProp.iLocation2 = SysM_EXIT;
	packets.PacProp.iWork = 1;
	packets.PacProp.iItem = 1;
	packets.SetComment(_T("�ý����� �����մϴ�."));

	ClientCore::pServer->PushSend(packets);


	while (true)
	{
		//SL_SYS/ SysM_EXIT / 1 / 1
		packets = CommonPacket();
		packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_SYS, SysM_EXIT);
		if (packets.PacProp.iItem == SysI_EXITOK)
		{
			break;
		}
		//else if (packets == DisConnected)
		//{
		//	return PR_RECONECTSURVER;
		//}
		GetTicks -= (GetTickCount() - Ticks);
		Ticks = GetTickCount();
		if (GetTicks <= 0)
		{
			break;
		}
	}
	





	/////////////////////////////////
	// ���� ����
	ClientCore::ClientRun = false;
	ClientCore::pServer->ServerClose();
	//////////////////////////////////


	// �ھ� ���� ����
	ClientCore::release();
	//////////////////////////////////
	// �Ŵ��� ����
	TimeManager::release();
	InputManager::release();
	WinDCManager::release();
	ColorManager::release();
	//////////////////////////////////


	//////////////////////////////////
	// ���� ����
	ClientCore::pServer->release();
	delete ClientCore::pServer;
	ClientCore::pServer = nullptr;
	//////////////////////////////////

	//////////////////////////////////
	// ����
	PostQuitMessage(0);
	//////////////////////////////////

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
	wcex.hIcon = NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);
	wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm = NULL;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	ClientCore::mainProc = WndProc;
    return RegisterClassExW(&wcex);;
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
      100, 100, WindSizeX, WindSizeY, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ClientCore::mainhWnd = hWnd;
   ClientCore::mainhInst = hInst;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//UpdateWindow(hWnd);
    switch (message)
    {
	//case WM_CREATE:
	//{
	//	RECT mrc;
	//	mrc.top = 2000;
	//	mrc.bottom = 500;
	//	mrc.left = 200;
	//	mrc.right = 500;
	//	ValidateRect(hWnd, &mrc);
	//}
	//break;
	case WM_CTLCOLORBTN:
	{
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcstatic = (HDC)wParam;
		
		//SetBkColor(hdcstatic, RGB(10,10,10));
		//ó���� �ؾ߰ڳ�.
		WNDItem* pWnd = WNDItem::FindItem((HWND)lParam);
		if (pWnd->GetChangeBK())
		{
			COLORREF colors =  pWnd->GetChangeBKColor();
			if (colors != RGB(0,0,0))
			{
				HDC hdcstatic = (HDC)wParam;
				SetBkMode(hdcstatic, OPAQUE);
				SetBkColor(hdcstatic, colors);
				SetDCBrushColor(hdcstatic, colors);
				return (LRESULT)CreateSolidBrush(GetSysColor(colors));
			}
		}
		break;

	}

	case WM_COMMAND:
	{
		DefWindowProc(hWnd, message, wParam, lParam);
		//WNDItem* pItem = WNDItem::FindItem((HWND)lParam);
		////�׳� ��ư �������� �Ž����� �޴°� �״�� �����ؼ� �Ǵ��ϰڴ�.
		//pItem->CustomProc(NULL, message, 1, 1);
		//ClientCore::testmap.clear();
	
		break;
	}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			BitBlt(hdc, 0, 0, WindSizeX, WindSizeY, ClientCore::PrintDC, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		ShowWindow(hWnd, SW_HIDE);
		ClientCore::ClientRun = false;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
