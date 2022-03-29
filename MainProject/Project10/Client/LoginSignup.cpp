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
		//����
		if (   (int)str.c_str()[i] <= 57 && (int)str.c_str()[i] >= 48)
		{
			bNum = true;
		}
		//����
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
		//Ư������üũ
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

		//����
		if ((int)str.c_str()[i] <= 57 && (int)str.c_str()[i] >= 48)
		{
			Number = true;
		}

		//����
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
	// 0 Ŭ����
	// 1 ���ĺ�
	// 2 �ѹ�
	// 3 ���ĺ� �ѹ�
	// 4 Ư������
	// 5 Ư�� ���ĺ�
	// 6 Ư�� �ѹ�
	// 7 Ư�� ���ĺ� �ѹ�

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
			SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("�ҹ���, ���ڷ� �����Ǿ�� �մϴ�.")));
			bIDDoubleCheck = false;
		}
		else
		{
			//���̾��� �Ӽ��� �����̰� �ϰڴ�.
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
					SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("��� ���� �մϴ�.")));
				}
				else
				{
					bIDDoubleCheck = false;
					SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("��� �Ұ��� �մϴ�.")));
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
				SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("��� ���� �մϴ�.")));
			}
			else
			{
				bIDDoubleCheck = false;
				SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("��� �Ұ��� �մϴ�.")));
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
				SetDlgItemText(GetParent(hWnd), IDC_SISHOW1, _T("���̵� �ߺ� Ȯ���� �Ϸ�Ǿ����ϴ�."));
				MessageBox(hWnd, TEXT(" ���������� ����Ǿ����ϴ�. "), TEXT(" "), MB_OK);
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
			//�������� Ȯ���� ��Ź�ؾ���.
			//�׷��� ID�� �ǵ��ϰ� �Ѱ� �ش�.

			//bIDDoubleCheck = !bIDDoubleCheck;

			if (!UseId(CreatePlayer.m_ID))
			{
				SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("�ҹ��� �� ���� �ܿ� �ٸ� ���ڰ� ���Ǿ����ϴ�.")));
				bIDDoubleCheck = false;
			}
			else
			{

				//���̾��� �Ӽ��� �����̰� �ϰڴ�.
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
						SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("��� ���� �մϴ�.")));
					}
					else
					{
						bIDDoubleCheck = false;
						SetDlgItemText(hWnd, IDC_IDCHECKMSG, (_T("��� �Ұ��� �մϴ�.")));
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
			//�������� Ȯ���� ��Ź�ؾ���.
			//�׷��� ID�� �ǵ��ϰ� �Ѱ� �ش�.
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
		//�ð� ����
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
		//�̰� �ð��� Ȱ���ؼ� �ؾ߰ڳ�..
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
				SetDlgItemText(hWnd, IDC_SISHOW1, _T("��� �Ұ����մϴ�.(�׽�Ʈ ���������� �������)"));
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
			SetDlgItemText(hWnd, IDC_SISHOW1, _T("Ȯ�� ���Դϴ�. ��ٷ��ּ���."));
			bIDDoubleCheck = false;
			bIDC_SISHOW1_SetOK = 0;
		}
		else if (packets.PacProp.iItem == LI_IDNEW)
		{
			if (bIDC_SISHOW1_SetOK == 0)
			{
				SetDlgItemText(hWnd, IDC_SISHOW1, _T("��� �����մϴ�."));
				bIDDoubleCheck = true;
				bIDC_SISHOW1_SetOK = 2;
			}
		}
		else
		{
			if (packets.PacProp.iItem == LI_IDALREADY)
			{
				SetDlgItemText(hWnd, IDC_SISHOW1, _T("�ߺ��Ǿ����ϴ�. ��� �Ұ��� �մϴ�."));
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
			strresive = _T("�Է����ּ���.");
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 0:
			//strresive = "��밡���� ���̵� �Դϴ�.";
			break;
		case 1:
		{
			strresive = _T("�ҹ��� ���ĺ� ����(�׽�Ʈ ���������� �������)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 2:
		{
			strresive = _T("���� ����(�׽�Ʈ ���������� �������)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 3:
		{
			strresive = _T("�ҹ��� ���ĺ� / ���� ����(�׽�Ʈ ���������� �������)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 4:
		{
			strresive = _T("Ư�� ��ȣ ����(�׽�Ʈ ���������� �������)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 5:
		{
			strresive = _T("Ư�� ��ȣ / �ҹ��� ���ĺ� ����(�׽�Ʈ ���������� �������)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 6:
		{
			strresive = _T("Ư�� ��ȣ / ���� ����(�׽�Ʈ ���������� �������)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		case 7:
		{
			strresive = _T("Ư�� ��ȣ / ���� ���� / ���ĺ� ����(�׽�Ʈ ���������� �������)");
			bPWCheck = true;
			SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			break;
		}
		default:
		{
			strresive = _T("�ٽ� �Է��� �ּ���~");
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

			MessageBox(hWnd, TEXT(" ���������� ���̵� �����Ǿ����ϴ�. "), TEXT(" ���� �մϴ�!!! "), MB_OK);
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
			////�̰� �ð��� Ȱ���ؼ� �ؾ߰ڳ�..
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
			//		SetDlgItemText(hWnd, IDC_SISHOW1, "��� �����մϴ�.");
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
				strresive = "�Է����ּ���.";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 0:
				strresive = "��밡���� ���̵� �Դϴ�.";
				break;
			case 1:
			{
				strresive = "�ҹ��� ���ĺ� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 2:
			{
				strresive = "���� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 3:
			{
				strresive = "�ҹ��� ���ĺ� / ���� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 4:
			{
				strresive = "Ư�� ��ȣ ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 5:
			{
				strresive = "Ư�� ��ȣ / �ҹ��� ���ĺ� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 6:
			{
				strresive = "Ư�� ��ȣ / ���� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 7:
			{
				strresive = "Ư�� ��ȣ / ���� ���� / ���ĺ� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			default:
			{
				strresive = "�ٽ� �Է��� �ּ���~";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			}*/
			if (CreatePlayer.m_PW == strRePW && CreatePlayer.m_PW[0] != 0)
			{

				strresive += _T("��й�ȣ�� ��ġ �մϴ�.");
				bPWCheck = true;
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			}
			else
			{
				strresive += _T("��й�ȣ�� ��ġ ���� �ʽ��ϴ�.");
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
				strresive = "�Է����ּ���.";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 0:
				strresive = "��밡���� ���̵� �Դϴ�.";
				break;
			case 1:
			{
				strresive = "�ҹ��� ���ĺ� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 2:
			{
				strresive = "���� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 3:
			{
				strresive = "�ҹ��� ���ĺ� / ���� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 4:
			{
				strresive = "Ư�� ��ȣ ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 5:
			{
				strresive = "Ư�� ��ȣ / �ҹ��� ���ĺ� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 6:
			{
				strresive = "Ư�� ��ȣ / ���� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			case 7:
			{
				strresive = "Ư�� ��ȣ / ���� ���� / ���ĺ� ����";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			default:
			{
				strresive = "�ٽ� �Է��� �ּ���~";
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
				return 0;
			}
			}*/
			if (CreatePlayer.m_PW == strRePW && CreatePlayer.m_PW[0] != 0)
			{
				strresive += _T("��й�ȣ�� ��ġ �մϴ�.");
				bPWCheck = true;
				SetDlgItemText(hWnd, IDC_SISHOW2, strresive.c_str());
			}
			else
			{
				strresive += _T("��й�ȣ�� ��ġ ���� �ʽ��ϴ�.");
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



			//���̵� üũ��ư
		case ID_IDCHECK:
		{
			//GetDlgItemText(hWnd, IDC_SIID, savebuff, sizeof(TCHAR) * _MAX_PATH);
			//if (CreatePlayer.m_ID != savebuff || CreatePlayer.m_ID == "")
			//{
			//	SetDlgItemText(hWnd, IDC_SISHOW1, "�ߺ� Ȯ���� ���� �ʾҽ��ϴ�.");
			//	memcpy(CreatePlayer.m_ID, savebuff, sizeof(TCHAR) * 20);
			//	//CreatePlayer.m_ID = savebuff;
			//	DialogBox(ClientCore::mainhInst, MAKEINTRESOURCE(IDD_IDCHECK), hWnd, DLGPROC(IDCheckProc));
			//}
			//else
			//{
			//	MessageBox(hWnd, TEXT("�̹� Ȯ�� �Ǿ����ϴ�."), TEXT(""), MB_OK);
			//}
			////IDC_SISHOW1
			break;
		}
			/////////������ư
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
					//����ڴٴ� ������ �����߰ھ��!
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (ClientCore::pServer)
					{
						//���̾��� �Ӽ��� �����̰� �ϰڴ�.
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
						MessageBox(hWnd, TEXT(" ���̵� �ߺ� üũ�� �ٽ� �ѹ� �� Ȯ�����ּ���. "), TEXT(" ���� ���� "), MB_OK);
					}
					else if (!bPWCheck)
					{
						MessageBox(hWnd, TEXT(" ��й�ȣ�� �ٽ� �ѹ� �� Ȯ���� �ּ���. "), TEXT(" ���� ���� "), MB_OK);
					}

					else
					{
						MessageBox(hWnd, TEXT(" �˼� ���� �ַ��Դϴ�. ���� �ּ���. "), TEXT(" ���� ���� "), MB_OK);
					}
				}
			}
			break;
		}
			//��� ��ư
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
	SetText(L" ȸ�� ���� ");
	HFONT font = CreateFont(50, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)font, MAKELPARAM(TRUE, 0));
	return PR_OK;
}

int LoginSignup::release()
{
	WNDItem::release(0);
	return PR_OK;
}
