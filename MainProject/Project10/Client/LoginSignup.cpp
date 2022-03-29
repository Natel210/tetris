#include "stdafx.h"
#include "LoginSignup.h"
#include "resource.h"

#include "ClientHeader.h"
#include "ClientIngameEnum.h"
#include "ClientCore.h"

#include <assert.h>

#define MoveDiralogPosX 200
#define MoveDiralogPosY 200

static bool bCreating = false;


static PlayerLogInfo CreatePlayer;
static bool bIDCheck = false;
static bool bPWCheck = false;
static bool bEMCheck = false;
static Tstring strRePW;

static bool bIDDoubleCheck = false;

static bool CraeteCheckPlayer(HWND hWnd)
{
	return true;
}

static bool UseId(const Tstring str) 
{
	bool bNum = false;
	bool bAlphabat = false;
	for (int i = 0; i < (int)str.size(); ++i)
	{
		//숫자
		if (   (int)str.c_str()[i] <= 57 && (int)str.c_str()[i] >= 48)
		{
			bNum = true;
		}
		//영문
		if ((int)str.c_str()[i] <= 122 && (int)str.c_str()[i] >= 97)
		{
			bAlphabat = true;
		}
	}
	if (bNum && bAlphabat)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

static int UsePW(const Tstring str)
{
	if (str.size() == 0 )
	{
		return -1;
	}
	bool Number = false;
	bool Alphabat = false;
	bool Special = false;
	for (int i = 0 ; i < (int)str.size() ; ++i)
	{
		//특수문자체크
		if (str.c_str()[i] == ('*'))
		{
			Special = true;
		}
		if (str.c_str()[i] == ('^'))
		{
			Special = true;
		}
		if (str.c_str()[i] == ('%'))
		{
			Special = true;
		}
		if (str.c_str()[i] == ('$'))
		{
			Special = true;
		}
		if (str.c_str()[i] == ('#'))
		{
			Special = true;
		}
		if (str.c_str()[i] == ('@'))
		{
			Special = true;
		}
		if (str.c_str()[i] == ('!'))
		{
			Special = true;
		}

		//숫자
		if ((int)str.c_str()[i] <= 57 && (int)str.c_str()[i] >= 48)
		{
			Number = true;
		}

		//영문
		if ((int)str.c_str()[i] <= 122 && (int)str.c_str()[i] >= 97)
		{
			Alphabat = true;
		}

	}




	int iresult = 0;

	if (!Alphabat)//Alphabat 0 or 1
	{
		iresult += 1;
	}
	// 0 클리어
	// 1 알파벳
	// 2 넘버
	// 3 알파벳 넘버
	// 4 특수문자
	// 5 특문 알파벳
	// 6 특문 넘버
	// 7 특문 알파벳 넘버

	if (!Number)//Number 0 or 2
	{
		iresult += 2;
	}

	if (!Special)//Alphabat 0 or 4
	{
		iresult += 4;
	}

	return iresult;
}


static LRESULT CALLBACK IDCheckProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (!IsWindowEnabled(hWnd))
		{
			break;
		}
		WINDOWINFO  mainwindesc;
		GetWindowInfo(ClientCore::mainhWnd, &mainwindesc);
		SetTimer(hWnd, 1000, 100, NULL);

		int Topsize = mainwindesc.rcClient.top + MoveDiralogPosY + 50;
		int Leftsize = mainwindesc.rcClient.left + MoveDiralogPosX + 200;


		WINDOWINFO curWind;
		GetWindowInfo(hWnd, &curWind);
		int SizeY = curWind.rcWindow.bottom - curWind.rcWindow.top;
		int SizeX = curWind.rcWindow.right - curWind.rcWindow.left;

		SetWindowPos(hWnd, HWND_TOP, Leftsize, Topsize, SizeX, SizeY, NULL);


		SetDlgItemText(hWnd, IDC_IDSHOW1, (CreatePlayer.m_ID));

		if (!UseId(CreatePlayer.m_ID))
		{
			SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("소문자, 숫자로 구성되어야 합니다.")));
			bIDDoubleCheck = false;
		}
		else
		{
			//레이어의 속성을 움직이게 하겠다.
			CommonPacket packets;
			//memset(&packets, 0, sizeof(CommonPacket));
			//ZeroMemory(&packets, sizeof(CommonPacket));
			/////////
			packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
			packets.PacProp.iLocation1 = SL_LOG_IN;
			packets.PacProp.iLocation2 = LI_CREATE;
			packets.PacProp.iWork = CC_CHECK;
			packets.PacProp.iItem = LI_ID;


			memcpy(packets.Comments, (void*)&CreatePlayer, sizeof(PlayerLogInfo));
			ClientCore::pServer->PushSend(packets);

			packets.PacProp.iLocation1 = SL_Err;
			packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOG_IN, LI_CREATE, CC_CHECK);
			if (packets == DisConnected)
			{
				assert(true);
				return 0;
			}
			if (packets.PacProp.iLocation1 == SL_LOG_IN)
			{
				if (packets.PacProp.iItem == LI_IDNEW)
				{
					bIDDoubleCheck = true;
					SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("사용 가능 합니다.")));
				}
				else
				{
					bIDDoubleCheck = false;
					SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("사용 불가능 합니다.")));
				}
			}
		}
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 1000);
		return TRUE;
	}
	case WM_TIMER:
	{
		CommonPacket packets = CommonPacket();
		packets.PacProp.iLocation1 = SL_Err;
		packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOG_IN, LI_CREATE, CC_CHECK);
		if (packets == DisConnected)
		{
			assert(true);
			return 0;
		}
		if (packets.PacProp.iLocation1 == SL_LOG_IN)
		{
			if (packets.PacProp.iItem == LI_IDNEW)
			{
				bIDDoubleCheck = true;
				SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("사용 가능 합니다.")));
			}
			else
			{
				bIDDoubleCheck = false;
				SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("사용 불가능 합니다.")));
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		packets = CommonPacket();

	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_IDOK:
		{
			if (bIDDoubleCheck)
			{
				SetDlgItemText(GetParent(hWnd), IDC_SIID, CreatePlayer.m_ID);
				SetDlgItemText(GetParent(hWnd), IDC_SISHOW1, _T("아이디 중복 확인이 완료되었습니다."));
				MessageBox(hWnd, TEXT(" 정상적으로 적용되었습니다. "), TEXT(" "), MB_OK);
				EndDialog(hWnd, ID_IDOK);
				return 0;
			}
			break;
		}
		case ID_IDCant:
		{
			bIDDoubleCheck = false;
			EndDialog(hWnd, ID_IDCant);
			return 0;
		}
		case ID_IDRENAEM:
		{
			//서버에게 확인을 부탁해야함.
			//그래서 ID를 판독하고 넘겨 준다.

			//bIDDoubleCheck = !bIDDoubleCheck;

			if (!UseId(CreatePlayer.m_ID))
			{
				SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("소문자 및 숫자 외에 다른 문자가 사용되었습니다.")));
				bIDDoubleCheck = false;
			}
			else
			{

				//레이어의 속성을 움직이게 하겠다.
				CommonPacket packets;
				//memset(&packets, 0, sizeof(CommonPacket));
				//ZeroMemory(&packets, sizeof(CommonPacket));
				/////////
				packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
				packets.PacProp.iLocation1 = SL_LOG_IN;
				packets.PacProp.iLocation2 = LI_CREATE;
				packets.PacProp.iWork = CC_CHECK;
				packets.PacProp.iItem = LI_ID;


				memcpy(packets.Comments, (void*)&CreatePlayer, sizeof(PlayerLogInfo));
				ClientCore::pServer->PushSend(packets);

			/*	packets.PacProp.iLocation1 = SL_Err;
				packets = ClientCore::pServer->PopRecv(ClientCore::pServer->MyUniqueNum, SL_LOG_IN, LI_CREATE, CC_CHECK);

				if (packets == DisConnected)
				{
					return PR_RECONECTSURVER;
				}
				if (packets.PacProp.iLocation1 == SL_LOG_IN)
				{
					if (packets.PacProp.iItem == LI_IDNEW)
					{
						bIDDoubleCheck = true;
						SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("사용 가능 합니다.")));
					}
					else
					{
						bIDDoubleCheck = false;
						SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("사용 불가능 합니다.")));
					}
				}*/
			}

			return 0;
		}
		case IDC_IDSHOW1:
		{
			TCHAR savebuff[_MAX_PATH];
			GetDlgItemText(hWnd, IDC_IDSHOW1, savebuff, sizeof(TCHAR) * _MAX_PATH);
			memcpy(CreatePlayer.m_ID, savebuff, sizeof(TCHAR) * 20);
			//CreatePlayer.m_ID = savebuff;

			//EndDialog(hWnd, ID_IDCant);
			//서버에게 확인을 부탁해야함.
			//그래서 ID를 판독하고 넘겨 준다.
			SetDlgItemText(hWnd, IDC_IDCHECKMSG, _T("."));
			//bIDDoubleCheck = true;
			return 0;
		}
		default:
			break;
		}
		
	}
	default:
		break;
	}
	return 0;
}


static int bIDC_SISHOW1_SetOK = 2;
//
static LRESULT CALLBACK SignInProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (!IsWindowEnabled(hWnd))
		{
			break;
		}
		//시간 설정
		SetTimer(hWnd, 111, 1000, NULL);


		//ActiveWind = true;
		//
		WINDOWINFO  mainwindesc;
		GetWindowInfo(ClientCore::mainhWnd, &mainwindesc);


		int Topsize =  mainwindesc.rcClient.top + MoveDiralogPosY;
		int Leftsize = mainwindesc.rcClient.left + MoveDiralogPosX;
		

		WINDOWINFO curWind;
		GetWindowInfo(hWnd, &curWind);
		int SizeY = curWind.rcWindow.bottom - curWind.rcWindow.top;
		int SizeX = curWind.rcWindow.right	- curWind.rcWindow.left;

		SetWindowPos(hWnd, HWND_TOP, Leftsize, Topsize, SizeX, SizeY, NULL);

		SetDlgItemText(hWnd, IDC_SISHOW2, _T(""));

		//////////////////////////

		CreatePlayer = PlayerLogInfo();
		bIDCheck = false;
		bPWCheck = false;
		bEMCheck = false;
		strRePW = _T("");
		bIDDoubleCheck = false;


		///////////////////////////


		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, 111);
		return TRUE;
	}
	case WM_TIMER:
	{
		//
		Tstring strresive;
		TCHAR savebuff[_MAX_PATH];
		//이걸 시간을 활요해서 해야겠네..
		GetDlgItemText(hWnd, IDC_SIID, savebuff, sizeof(TCHAR) * _MAX_PATH);
		memcpy(CreatePlayer.m_ID, savebuff, sizeof(TCHAR) * 20);
		if (CreatePlayer.m_ID[0] == 0)
		{
			SetDlgItemText(hWnd, IDC_SISHOW1, _T(""));
			break;
		}
		if (!UseId(CreatePlayer.m_ID))
		{
			if (bIDC_SISHOW1_SetOK != 1)
			{
				SetDlgItemText(hWnd, IDC_SISHOW1, _T("사용 불가능합니다.(테스트 버전에서는 만들어짐)"));
				bIDC_SISHOW1_SetOK = 2;
				bIDDoubleCheck = true;
			}
		}
		CommonPacket packets;
		packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
		packets.PacProp.iLocation1 = SL_LOG_IN;
		packets.PacProp.iLocation2 = LI_CREATE;
		packets.PacProp.iWork = CC_CHECK;
		packets.PacProp.iItem = LI_ID;
		memcpy(packets.Comments, (void*)&CreatePlayer, sizeof(PlayerLogInfo));
		ClientCore::pServer->PushSend(packets);
		packets.PacProp.iLocation1 = SL_Err;
		packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOG_IN, LI_CREATE, CC_CHECK);
		//if (packets == DisConnected)
		//{
		//	return PR_RECONECTSURVER;
		//}
		//if (packets.PacProp.iLocation1 != SL_LOG_IN)
		//{
		//	return PR_OK;
		//}
		PlayerLogInfo recvplayer = PlayerLogInfo();
		memcpy(&recvplayer, packets.Comments, sizeof(PlayerLogInfo));
		
		if (StrCmpW(recvplayer.m_ID, CreatePlayer.m_ID) != 0)
		{
			SetDlgItemText(hWnd, IDC_SISHOW1, _T("확인 중입니다. 기다려주세요."));
			bIDDoubleCheck = false;
			bIDC_SISHOW1_SetOK = 0;
		}
		else if (packets.PacProp.iItem == LI_IDNEW)
		{
			if (bIDC_SISHOW1_SetOK == 0)
			{
				SetDlgItemText(hWnd, IDC_SISHOW1, _T("사용 가능합니다."));
				bIDDoubleCheck = true;
				bIDC_SISHOW1_SetOK = 2;
			}
		}
		else
		{
			if (packets.PacProp.iItem == LI_IDALREADY)
			{
				SetDlgItemText(hWnd, IDC_SISHOW1, _T("중복되었습니다. 사용 불가능 합니다."));
				bIDDoubleCheck = false;
				bIDC_SISHOW1_SetOK = 0;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		GetDlgItemText(hWnd, IDC_SIPW, savebuff, sizeof(TCHAR) * _MAX_PATH);
		memcpy(CreatePlayer.m_PW, savebuff, sizeof(TCHAR) * 60);

		bPWCheck = false;
		switch (UsePW(CreatePlayer.m_PW))
		{
		case -1:
		{
			strresive = _T("입력해주세요.");
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 0:
			//strresive = "사용가능한 아이디 입니다.";
			break;
		case 1:
		{
			strresive = _T("소문자 알파벳 누락(테스트 버전에서는 만들어짐)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 2:
		{
			strresive = _T("숫자 누락(테스트 버전에서는 만들어짐)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 3:
		{
			strresive = _T("소문자 알파벳 / 숫자 누락(테스트 버전에서는 만들어짐)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 4:
		{
			strresive = _T("특수 기호 누락(테스트 버전에서는 만들어짐)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 5:
		{
			strresive = _T("특수 기호 / 소문자 알파벳 누락(테스트 버전에서는 만들어짐)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 6:
		{
			strresive = _T("특수 기호 / 숫자 누락(테스트 버전에서는 만들어짐)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 7:
		{
			strresive = _T("특수 기호 / 숫자 누락 / 알파벳 누락(테스트 버전에서는 만들어짐)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		default:
		{
			strresive = _T("다시 입력해 주세요~");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		packets = CommonPacket();
		packets.PacProp.iLocation1 = SL_Err;
		packets = ClientCore::pServer->PopRecv(ClientCore::pServer->MyUniqueNum, SL_LOG_IN, LI_CREATE, CC_CREATE, LI_ID);

		if (packets == DisConnected)
		{
			assert(true);
			return 0;
		}
		if (packets.PacProp.iLocation1 == SL_LOG_IN)
		{
			bCreating = false;

			MessageBox(hWnd, TEXT(" 정상적으로 아이디가 생성되었습니다. "), TEXT(" 축하 합니다!!! "), MB_OK);
			EndDialog(hWnd, ID_SICREATE);
		}




		break;
	}

	case WM_COMMAND:
	{
		Tstring strresive;
		TCHAR savebuff[_MAX_PATH];
		switch (LOWORD(wParam))
		{
		case IDC_SIID:
		{
			////이걸 시간을 활요해서 해야겠네..
			//GetDlgItemText(hWnd, IDC_SIID, savebuff, sizeof(TCHAR) * _MAX_PATH);
			//memcpy(CreatePlayer.m_ID, savebuff, sizeof(TCHAR) * 20);
			//if (!UseId(CreatePlayer.m_ID))
			//{
			//	
			//}
			//CommonPacket packets;
			//packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
			//packets.PacProp.iLocation1 = SL_LOG_IN;
			//packets.PacProp.iLocation2 = LI_CREATE;
			//packets.PacProp.iWork = CC_CHECK;
			//packets.PacProp.iItem = LI_ID;
			//memcpy(packets.Comments, (void*)&CreatePlayer, sizeof(PlayerLogInfo));
			//ClientCore::pServer->PushSend(packets);
			//packets.PacProp.iLocation1 = SL_Err;
			//while (packets.PacProp.iLocation1 != SL_LOG_IN)
			//{
			//	packets = ClientCore::pServer->PopRecv(packets.PacProp.LinkNumber, SL_LOG_IN, LI_CREATE, CC_CHECK);
			//}
			//if (packets.PacProp.iItem == LI_IDNEW)
			//{
			//	if (bIDC_SISHOW1_SetOK == false)
			//	{
			//		SetDlgItemText(hWnd, IDC_SISHOW1, "사용 가능합니다.");
			//		bIDC_SISHOW1_SetOK = true;
			//	}
			//}
			//else
			//{
			//	if (bIDC_SISHOW1_SetOK == true)
			//	{
			//		SetDlgItemText(hWnd, IDC_SISHOW1, "");
			//		bIDC_SISHOW1_SetOK = false;
			//	}
			//}
			//break;
		}
		case IDC_SIPW:
		{
			GetDlgItemText(hWnd, IDC_SIPW, savebuff, sizeof(TCHAR) * _MAX_PATH);
			memcpy(CreatePlayer.m_PW, savebuff, sizeof(TCHAR) * 60);

			/*bPWCheck = false;
			switch (UsePW(CreatePlayer.m_PW))
			{
			case -1:
			{
				strresive = "입력해주세요.";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 0:
				strresive = "사용가능한 아이디 입니다.";
				break;
			case 1:
			{
				strresive = "소문자 알파벳 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 2:
			{
				strresive = "숫자 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 3:
			{
				strresive = "소문자 알파벳 / 숫자 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 4:
			{
				strresive = "특수 기호 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 5:
			{
				strresive = "특수 기호 / 소문자 알파벳 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 6:
			{
				strresive = "특수 기호 / 숫자 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 7:
			{
				strresive = "특수 기호 / 숫자 누락 / 알파벳 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			default:
			{
				strresive = "다시 입력해 주세요~";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			}*/
			if (CreatePlayer.m_PW == strRePW && CreatePlayer.m_PW[0] != 0)
			{

				strresive += _T("비밀번호가 일치 합니다.");
				bPWCheck = true;
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			}
			else
			{
				strresive += _T("비밀번호가 일치 하지 않습니다.");
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			}
			break;
		}
		case IDC_SIPWRE:
		{
			GetDlgItemText(hWnd, IDC_SIPWRE, savebuff, sizeof(TCHAR) * _MAX_PATH);
			strRePW = savebuff;
			/*bPWCheck = false;
			switch (UsePW(CreatePlayer.m_PW))
			{
			case -1:
			{
				strresive = "입력해주세요.";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 0:
				strresive = "사용가능한 아이디 입니다.";
				break;
			case 1:
			{
				strresive = "소문자 알파벳 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 2:
			{
				strresive = "숫자 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 3:
			{
				strresive = "소문자 알파벳 / 숫자 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 4:
			{
				strresive = "특수 기호 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 5:
			{
				strresive = "특수 기호 / 소문자 알파벳 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 6:
			{
				strresive = "특수 기호 / 숫자 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 7:
			{
				strresive = "특수 기호 / 숫자 누락 / 알파벳 누락";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			default:
			{
				strresive = "다시 입력해 주세요~";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			}*/
			if (CreatePlayer.m_PW == strRePW && CreatePlayer.m_PW[0] != 0)
			{
				strresive += _T("비밀번호가 일치 합니다.");
				bPWCheck = true;
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			}
			else
			{
				strresive += _T("비밀번호가 일치 하지 않습니다.");
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			}
			break;
		}
		case IDC_SIEM:
		{
			GetDlgItemText(hWnd, IDC_SIEM, savebuff, sizeof(TCHAR) * _MAX_PATH);

			//CreatePlayer.m_Email = savebuff;
			memcpy(CreatePlayer.m_Email, savebuff, sizeof(TCHAR) * 100);
			

			break;
		}
			
		//case:
			//IDC_SIID
			//IDC_SIPW
			//IDC_SIPWRE
			//IDC_SIEM



			//아이디 체크버튼
		case ID_IDCHECK:
		{
			//GetDlgItemText(hWnd, IDC_SIID, savebuff, sizeof(TCHAR) * _MAX_PATH);
			//if (CreatePlayer.m_ID != savebuff || CreatePlayer.m_ID == "")
			//{
			//	SetDlgItemText(hWnd, IDC_SISHOW1, "중복 확인이 되지 않았습니다.");
			//	memcpy(CreatePlayer.m_ID, savebuff, sizeof(TCHAR) * 20);
			//	//CreatePlayer.m_ID = savebuff;
			//	DialogBox(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_IDCHECK), hWnd, DLGPROC(IDCheckProc));
			//}
			//else
			//{
			//	MessageBox(hWnd, TEXT("이미 확인 되었습니다."), TEXT(""), MB_OK);
			//}
			////IDC_SISHOW1
			break;
		}
			/////////만들기버튼
		case ID_SICREATE:
		{
			if (BN_CLICKED == HIWORD(wParam))
			{
				if (bCreating)
				{
					break;
				}

				if (CraeteCheckPlayer(hWnd) && bIDDoubleCheck &&  bPWCheck && !bCreating)
				{
					//만들겠다는 정보를 보내야겠어요!
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (ClientCore::pServer)
					{
						//레이어의 속성을 움직이게 하겠다.
						CommonPacket packets;
						//memset(&packets, 0, sizeof(CommonPacket));
						//ZeroMemory(&packets, sizeof(CommonPacket));
						/////////
						packets.PacProp.LinkNumber = ClientCore::pServer->MyUniqueNum;
						packets.PacProp.iLocation1 = SL_LOG_IN;
						packets.PacProp.iLocation2 = LI_CREATE;
						packets.PacProp.iWork = CC_CREATE;
						packets.PacProp.iItem = LI_ID;


						memcpy(packets.Comments, (void*)&CreatePlayer, sizeof(PlayerLogInfo));
						ClientCore::pServer->PushSend(packets); 

						bCreating = true;
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//
				
					return 0;
				}
				else
				{
					if (!bIDDoubleCheck)
					{
						MessageBox(hWnd, TEXT(" 아이디 중복 체크를 다시 한번 더 확인해주세요. "), TEXT(" 생성 실패 "), MB_OK);
					}
					else if (!bPWCheck)
					{
						MessageBox(hWnd, TEXT(" 비밀번호를 다시 한번 더 확인해 주세요. "), TEXT(" 생성 실패 "), MB_OK);
					}

					else
					{
						MessageBox(hWnd, TEXT(" 알수 없는 애러입니다. 문의 주세요. "), TEXT(" 생성 실패 "), MB_OK);
					}
				}
			}
			break;
		}
			//취소 버튼
		case ID_SICANT:
		{
			EndDialog(hWnd, ID_SICANT);
		}
			
			return 0;

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


LoginSignup::LoginSignup()
{
}


LoginSignup::~LoginSignup()
{
}

int LoginSignup::Input(float time)
{
	return PR_OK;
}

int LoginSignup::Update(float time)
{
	return PR_OK;
}

int LoginSignup::LateUpdate(float time)
{
	return PR_OK;
}

int LoginSignup::Transform(float time)
{
	return PR_OK;
}

int LoginSignup::Render(float time, HDC drow)
{
	return PR_OK;
}

int LoginSignup::DebugRender(float time)
{
	return PR_OK;
}

int LoginSignup::Collision(float time)
{
	if (m_iCollButton)
	{
		//HWND Dialog = CreateDialog(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_SIGNIN), ClientCore::mainhWnd, DLGPROC(SignInProc));
		//ShowWindow(Dialog, SW_SHOW);


		bCreating = false;
		DialogBox(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_SIGNUP), m_hWnd, DLGPROC(SignInProc));
		m_iCollButton = false;
	}



	return PR_OK;
}

int LoginSignup::Init()
{
	WNDItem::Init(TEXT("button"), TEXT("LoginSignin"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 430, 230, 70, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L" 회원 가입 ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int LoginSignup::release()
{
	WNDItem::release(0);
	return PR_OK;
}
