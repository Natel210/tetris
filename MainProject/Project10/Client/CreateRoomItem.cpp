#include "stdafx.h"
#include "CreateRoomItem.h"
#include "ClientHeader.h"
#include "ClientCore.h"

#include "resource.h"

#include "FrameCore.h"
#include "ClientLobbyScene.h"
#include "ClientRoomScene.h"
#include <windowsx.h>

static int RoomProcPosY2 = 200;
static int RoomProcPosX2 = 200;
bool CreateRoomItem::m_bisCreate = false;

static LRESULT CALLBACK CreateRoomproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (!IsWindowEnabled(hWnd))
		{
			break;
		}

		//ActiveWind = true;

		WINDOWINFO  mainwindesc;
		GetWindowInfo(ClientCore::mainhWnd, &mainwindesc);


		int Topsize = mainwindesc.rcClient.top + RoomProcPosY2;
		int Leftsize = mainwindesc.rcClient.left + RoomProcPosX2;


		WINDOWINFO curWind;
		GetWindowInfo(hWnd, &curWind);
		int SizeY = curWind.rcWindow.bottom - curWind.rcWindow.top;
		int SizeX = curWind.rcWindow.right - curWind.rcWindow.left;

		SetWindowPos(hWnd, HWND_TOP, Leftsize, Topsize, SizeX, SizeY, NULL);


		HWND myNAMEhnd = GetDlgItem(hWnd, IDC_CRROOMNAME);
		HWND myPWhnd = GetDlgItem(hWnd, IDC_ECR_ROOMPW);
		HWND myNumhnd = GetDlgItem(hWnd, IDC_ROOMLIM);
		PostMessage(myNAMEhnd, EM_LIMITTEXT, 30, 0);
		PostMessage(myPWhnd, EM_LIMITTEXT, 8, 0);

		//int)(DWORD)SNDMSG((hwndCtl), CB_ADDSTRING, 0L, (LPARAM)(LPCTSTR)(lpsz)))
		//ComboBox_AddString(myNumhnd, TEXT("1"));
		//ComboBox_AddString(myNumhnd, TEXT("1"));
		ComboBox_AddString(myNumhnd, TEXT("2"));
		ComboBox_AddString(myNumhnd, TEXT("3"));
		ComboBox_AddString(myNumhnd, TEXT("4"));
		ComboBox_AddString(myNumhnd, TEXT("5"));
		ComboBox_AddString(myNumhnd, TEXT("6"));
		ComboBox_AddString(myNumhnd, TEXT("7"));
		ComboBox_SetCurSel(myNumhnd, 2);


		//SetDlgItemText(hWnd, IDC_CRERR, "");

		SetTimer(hWnd, 12, 10, nullptr);

		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 12);
		break;
	}
	case WM_TIMER:
	{
		CommonPacket packets = CommonPacket();
		packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_CREATE, CC_CREATE, LB_ROOM);
		if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_ROOM)
		{
			CreateRoomItem::m_bisCreate = true;
			EndDialog(hWnd, ID_CROK);
			return 1;
		}
		break;
	}
	case WM_COMMAND:
	{
		TCHAR embuff[_MAX_PATH];
		switch (LOWORD(wParam))
		{

		//만들기 오케이
		case ID_CROK:
		{
			////////////////////////


			GetDlgItemText(hWnd, IDC_CRROOMNAME, embuff, sizeof(TCHAR) * _MAX_PATH);
			//등록해주고
			int roompw;
			GetDlgItemInt(hWnd, IDC_ECR_ROOMPW, &roompw, TRUE);
			bool ispub = true;
			if (roompw != 0)
			{
				ispub = false;
			}

			HWND myNumhnd = GetDlgItem(hWnd, IDC_ROOMLIM);
			int cursel =  ComboBox_GetCurSel(myNumhnd);
			int lmtNum = 0;
			Tstring strs = L"";
			ComboBox_GetLBText(myNumhnd, cursel, strs.c_str());
			lmtNum = _wtoi(strs.c_str());

			//만들어야겠네!
			CommonPacket packets;
			packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
			packets.PacProp.iLocation1 = SL_LOBBY;
			packets.PacProp.iLocation2 = LB_CREATE;
			packets.PacProp.iWork = CC_CREATE;
			packets.PacProp.iItem = LB_ROOM;
			
			packets.SetComment(embuff, 30);
			memcpy(&packets.Comments[30], &lmtNum, sizeof(int));
			memcpy(&packets.Comments[30 + sizeof(int)], &ispub, sizeof(bool));
			memcpy(&packets.Comments[30 + sizeof(int) + sizeof(bool)], &roompw, sizeof(int));

			ClientCore::pServer->PushSend(packets);

		

			//while (true)
			//{
			//	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, LB_CREATE, CC_CREATE, LB_ROOM);
			//	if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_ROOM)
			//	{
			//		break;
			//	}
			//	//else if (packets == DisConnected)
			//	//{
			//	//	return PR_RECONECTSURVER;
			//	//}
			//}

			////packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
			////packets.PacProp.iLocation1 = SL_LOBBY;
			////packets.PacProp.iLocation2 = LB_ENTER;
			////packets.PacProp.iWork = CC_ENTER;
			////packets.PacProp.iItem = LB_ROOM;

			////ClientCore::pServer->PushSend(packets);

			////packets.PacProp.iLocation1 = SL_Err;

			////while (packets.PacProp.iLocation1 != SL_LOBBY)
			////{
			////	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOBBY, packets.PacProp.iLocation2, packets.PacProp.iWork);
			////}


			////if (packets.PacProp.iItem == LB_ROOMENTER)
			////{
			////	int ireturn = 0;
			////	memcpy(&ireturn, packets.Comments, sizeof(int));

			////	ClientRoomScene* pNextScene = FrameCore::CreateScene<ClientRoomScene>(GameRoomScene);
			////	pNextScene->SetActive(false);
			////	ClientLobbyScene* pCurScene = FrameCore::FindScene<ClientLobbyScene>(GameLobbyScene);
			////	pNextScene->SetActive(true);
			////	pCurScene->SetActive(false);
			////	pCurScene->Delete();
			////}
			//CreateRoomItem::m_bisCreate = true;



			//EndDialog(hWnd, ID_CROK);
			//return 1;
			break;
		}
		//취소
		case ID_CRCANT:
		{
			EndDialog(hWnd, ID_CRCANT);
			break;
		}




		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return 0;
}



CreateRoomItem::CreateRoomItem()
{
}


CreateRoomItem::~CreateRoomItem()
{
}

int CreateRoomItem::Input(float time)
{
	return PR_OK;
}

int CreateRoomItem::Update(float time)
{
	return PR_OK;
}

int CreateRoomItem::LateUpdate(float time)
{
	return PR_OK;
}

int CreateRoomItem::Transform(float time)
{
	return PR_OK;
}

int CreateRoomItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int CreateRoomItem::DebugRender(float time)
{
	return PR_OK;
}

int CreateRoomItem::Collision(float time)
{
	m_bisCreate = false;
	if (m_iCollButton && counts <= 0)
	{
		ShowWindow(Createdlg, SW_SHOWNORMAL);
		m_iCollButton = false;
	}
	return PR_OK;
}

int CreateRoomItem::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("CreateRoom"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (int)(WindSizeX * 0.06f), (int)(WindSizeY * 0.85f), 200, 50, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 방만들기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));

	Createdlg = CreateDialog(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_CREATEROOM), m_hWnd, DLGPROC(CreateRoomproc));

	return PR_OK;
}

int CreateRoomItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}
