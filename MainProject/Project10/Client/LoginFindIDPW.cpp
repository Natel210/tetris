#include "stdafx.h"
#include "LoginFindIDPW.h"

#include "ClientHeader.h"
#include "ClientIngameEnum.h"
#include "ClientCore.h"
#include "resource.h"

#define MoveDiralogPosX2 350
#define MoveDiralogPosY2 200


static LRESULT CALLBACK FindIDPW(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (!IsWindowEnabled(hWnd))
		{
			break;
		}
		SetTimer(hWnd, 10, 10, NULL);
		WINDOWINFO  mainwindesc;
		GetWindowInfo(ClientCore::mainhWnd, &mainwindesc);


		int Topsize = mainwindesc.rcClient.top + MoveDiralogPosY2;
		int Leftsize = mainwindesc.rcClient.left + MoveDiralogPosX2;


		WINDOWINFO curWind;
		GetWindowInfo(hWnd, &curWind);
		int SizeY = curWind.rcWindow.bottom - curWind.rcWindow.top;
		int SizeX = curWind.rcWindow.right - curWind.rcWindow.left;

		SetWindowPos(hWnd, HWND_TOP, Leftsize, Topsize, SizeX, SizeY, NULL);

		SetDlgItemText(hWnd, IDC_FIPSHOW1, _T(""));
		SetDlgItemText(hWnd, IDC_FIPSHOW2, _T(""));
		break;
	}
	case WM_TIMER:
	{
		CommonPacket repackets;

		repackets = CommonPacket();
		TCHAR findidbuf[_MAX_PATH];
		GetDlgItemText(hWnd, IDC_FIPCHARIDEM, findidbuf, sizeof(TCHAR) * _MAX_PATH);
		Tstring IDLIST;
		repackets.PacProp.iLocation1 = SL_Err;
		repackets = ClientCore::pServer->PopRecv(repackets.PacProp.LinkNumber, SL_LOG_IN, LI_FIND, CC_FIND, LI_ID);
		if (repackets == DisConnected)
		{
			return PR_RECONECTSURVER;
		}
		if (repackets.PacProp.iLocation1 == SL_LOG_IN)
		{
			TCHAR ibuff[20];
			memcpy(ibuff, (void*)repackets.Comments, sizeof(TCHAR) * 20);
			IDLIST = _T("[ ");
			IDLIST += findidbuf;
			IDLIST += _T(" ]");
			IDLIST += _T("로 등록된 아이디는?\r");
			IDLIST += ibuff;
			IDLIST += _T("입니다.");
			SetDlgItemText(hWnd, IDC_FIPSHOW1, IDLIST.c_str());
		}
		//////////////////////////////////////////////////////////////////
		repackets = CommonPacket();
		repackets.PacProp.iLocation1 = SL_Err;
		repackets = ClientCore::pServer->PopRecv(repackets.PacProp.LinkNumber, SL_LOG_IN, LI_FIND, CC_FIND, LI_PW);
		if (repackets == DisConnected)
		{
			return PR_RECONECTSURVER;
		}
		if (repackets.PacProp.iLocation1 == SL_LOG_IN)
		{
			TCHAR ibuff[60];
			memcpy(ibuff, (void*)repackets.Comments, sizeof(TCHAR) * 60);
			if (ibuff[0] == '\0')
			{
				IDLIST = _T("아이디 및 비밀번호가 잘못 되었습니다.");
			}
			else
			{
				IDLIST = _T("비밀 번호는? ");
				IDLIST += ibuff;
				IDLIST += _T(" 입니다.");
			}
			SetDlgItemText(hWnd, IDC_FIPSHOW2, IDLIST.c_str());
		}
		/////////////////////////////////////////////////////////////////////
		break;
	}
	case WM_COMMAND:
	{
		TCHAR embuff[_MAX_PATH];
		switch (LOWORD(wParam))
		{
		case IDC_FIPFINDID:
		{
			Tstring IDLIST;
			if (embuff[0] == NULL)
			{
				IDLIST = _T("이메일을 다시입력해주세요.");
				SetDlgItemText(hWnd, IDC_FIPSHOW1, IDLIST.c_str());
			}
			else
			{
				CommonPacket packets;
				packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
				packets.PacProp.iLocation1 = SL_LOG_IN;
				packets.PacProp.iLocation2 = LI_FIND;
				packets.PacProp.iWork = CC_FIND;
				packets.PacProp.iItem = LI_ID;
				memcpy(packets.Comments, (void*)embuff, sizeof(TCHAR) * 100 );
				ClientCore::pServer->PushSend(packets);
			}
			break;
		}
		case IDC_FIPFINDPw:
		{
			GetDlgItemText(hWnd, IDC_FIPCHARPWEM, embuff, sizeof(TCHAR) * _MAX_PATH);
			TCHAR idbuff[_MAX_PATH];
			GetDlgItemText(hWnd, IDC_FIPCHARPWID, idbuff, sizeof(TCHAR) * _MAX_PATH);

			Tstring IDLIST;
			if (embuff[0] == NULL)
			{
				IDLIST = _T("이메일을 다시입력해주세요.");
				SetDlgItemText(hWnd, IDC_FIPSHOW2, IDLIST.c_str());
			}
			else if (idbuff[0] == NULL)
			{
				IDLIST = _T("아이디를 다시입력해주세요.");
				SetDlgItemText(hWnd, IDC_FIPSHOW2, IDLIST.c_str());
			}
			else
			{
				CommonPacket packets;
				packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
				packets.PacProp.iLocation1 = SL_LOG_IN;
				packets.PacProp.iLocation2 = LI_FIND;
				packets.PacProp.iWork = CC_FIND;
				packets.PacProp.iItem = LI_PW;
				PlayerLogInfo player;
				memcpy(player.m_Email, (void*)embuff, sizeof(TCHAR) * 100);
				memcpy(player.m_ID, (void*)idbuff, sizeof(TCHAR) * 20);
				memcpy(packets.Comments, (void*)&player, sizeof(PlayerLogInfo));
				ClientCore::pServer->PushSend(packets);
			}
			break;
		}
		case IDC_FIPCANT:
		{
			EndDialog(hWnd, IDC_FIPCANT);
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


LoginFindIDPW::LoginFindIDPW()
{
}


LoginFindIDPW::~LoginFindIDPW()
{
}

int LoginFindIDPW::Input(float time)
{
	return PR_OK;
}

int LoginFindIDPW::Update(float time)
{
	return PR_OK;
}

int LoginFindIDPW::LateUpdate(float time)
{
	return PR_OK;
}

int LoginFindIDPW::Transform(float time)
{
	return PR_OK;
}

int LoginFindIDPW::Render(float time, HDC drow)
{
	return PR_OK;
}

int LoginFindIDPW::DebugRender(float time)
{
	return PR_OK;
}

int LoginFindIDPW::Collision(float time)
{
	if (m_iCollButton)
	{

		DialogBox(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_FINDIDPW), m_hWnd,DLGPROC(FindIDPW));

		m_iCollButton = false;
	}

	return PR_OK;
}

int LoginFindIDPW::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("FindIdPw"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 540, 430, 230, 70, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 아이디 / 비밀 번호 찾기 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int LoginFindIDPW::release()
{
	WNDItem::release(0);
	return PR_OK;
}
