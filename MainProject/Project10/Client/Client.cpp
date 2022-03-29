// Client.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
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



// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	////////////////////////////////////////////
	// 윈도우 인스턴스
    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	////////////////////////////////////////////
	init();
	////////////////////////////////////////////
	HDC mainDC = GetDC(ClientCore::mainhWnd);
	////////////////////////////////////////////
	//매니져 인스턴스
	TimeManager::init();
	InputManager::init();
	//InputManager::SethWnd(ClientCore::mainhWnd);
	WinDCManager::init(mainDC, WindSizeX, WindSizeY);
	ColorManager::init();
	////////////////////////////////////////////
	//구조 인스턴스
	ClientCore::init();
	////////////////////////////////////////////
	//서버 인스턴스
	ClientCore::pServer = new UseServer();
	ClientCore::pServer->init(IP, PORT);
	//////////////////////////////////////////////
	ClientCore::ClientPlayer.eLoginfo.m_UniqueID = ClientCore::pServer->MyUniqueNum;
	//////////////////////////////////////////////
	// 각각에 보내주고 받는 쓰래드
	//HANDLE SendHandle = (HANDLE)_beginthreadex(nullptr, 0, UseServer::Sends, (void*)ClientCore::pServer, 0, nullptr);
	HANDLE RecvHandle = (HANDLE)_beginthreadex(nullptr, 0, UseServer::Recvs, (void*)ClientCore::pServer, 0, nullptr);
	//윈도우 제어
	ClientCore::PrintDC = WinDCManager::GetPrintDC();

	//Loop구간
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
		// 기본 메시지 루프입니다.
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
			WinDCManager::ClearDC();// DC클리어
			InvalidateRect(ClientCore::mainhWnd, NULL, FALSE);//윈도우 변화전송

			float fMainTimer = MainTime;
			float fMainFPS = 1.0f / fMainTimer;

			if (isUpdate > 0.0f)
			{
				isUpdate -= fMainTimer;
				TimeManager::FindTimer(_T("MainTime"))->EndCheck();			// 시간체크
				continue;
			}
			else
			{
				isUpdate = 0.0f;
			}



#ifdef _DEBUG
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//시간의 디버깅 출력
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
			WinDCManager::Update();									// 모든 것을 끝낸 다음 그린다.
			TimeManager::FindTimer(_T("MainTime"))->EndCheck();			// 시간체크
			TimeManager::FindTimer(_T("MainTime"))->StartCheck();//시간 체크 시작
			/////////////////////////////////////////////////////////////////////
			ClientCore::pServer->LogClear();
		}

	}
	//////////////////////////////////////////////////////
	//ShowWindow(ClientCore::mainhWnd, FALSE);
	//////////////////////////////////////////////////////
	//윈도우가 죽을때에 정보를 보내주어야겠다.
	double Ticks = GetTickCount();
	double GetTicks = 2000.0;

	CommonPacket packets;
	packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
	packets.PacProp.iLocation1 = SL_SYS;
	packets.PacProp.iLocation2 = SysM_EXIT;
	packets.PacProp.iWork = 1;
	packets.PacProp.iItem = 1;
	packets.SetComment(_T("시스템을 종료합니다."));

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
	// 접속 제거
	ClientCore::ClientRun = false;
	ClientCore::pServer->ServerClose();
	//////////////////////////////////


	// 코어 로직 제거
	ClientCore::release();
	//////////////////////////////////
	// 매니저 제거
	TimeManager::release();
	InputManager::release();
	WinDCManager::release();
	ColorManager::release();
	//////////////////////////////////


	//////////////////////////////////
	// 서버 제거
	ClientCore::pServer->release();
	delete ClientCore::pServer;
	ClientCore::pServer = nullptr;
	//////////////////////////////////

	//////////////////////////////////
	// 종료
	PostQuitMessage(0);
	//////////////////////////////////

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
		//처리를 해야겠네.
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
		////그냥 버튼 눌렀을때 매시지를 받는걸 그대로 전송해서 판단하겠다.
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
