#include "stdafx.h"
#include "ChatEditBarItem.h"
#include "Input/Input.h"
#include "ClientHeader.h"

static bool LobbyCahtEntercntl = false;

ChatEditBarItem::ChatEditBarItem()
{
}


ChatEditBarItem::~ChatEditBarItem()
{
}

int ChatEditBarItem::Input(float time)
{
	
	/*if (CntlEnterCollTime < 0.f)
	{
		if (isEnterCntl == false)
		{
			isEnterCntl = true;
			CntlEnterCollTime = 0.5f;
		}

	}
	else
	{
		CntlEnterCollTime -= time;
	}*/

	//isEnterCntl = true;
	if (KEY_PUSH(EnterKey) && CntlEnterCollTime < 0.f)
	{
		//메시지를 보낸다.
		CntlEnterCollTime = 0.2f;

		
		if (GetFocusBox())
		{
			//스트링에 걸렸는데..  
		}
		else
		{
			//포커싱을 지정한다.
			if (ClientCore::mainhWnd == GetFocus() || WNDItem::IsFocusItem())
			{
				SetFocusBox();
			}
		}
	}
	else
	{
		CntlEnterCollTime -= time;
	}
	//////////////////////////////////////////////////////////////////////
	//일정 크기가 된다면 짤라버리겠음.
	//////////////////////////////////////////////////////////////////////

	return PR_OK;
}

int ChatEditBarItem::Update(float time)
{
	CommonPacket packets = CommonPacket();
	packets = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_LOBBY, LB_CHAT, CC_CHAT, LB_CHATPUSH);
	if (packets.PacProp.iLocation1 == SL_LOBBY && packets.PacProp.iItem == LB_CHATPUSH)
	{
		//SetWindowText(m_hWnd, NULL);
	}
	return PR_OK;
}

int ChatEditBarItem::LateUpdate(float time)
{
	return PR_OK;
}

int ChatEditBarItem::Transform(float time)
{
	return PR_OK;
}

int ChatEditBarItem::Render(float time, HDC drow)
{
	return PR_OK;
}

int ChatEditBarItem::DebugRender(float time)
{
	return PR_OK;
}

int ChatEditBarItem::Collision(float time)
{
	//Tstring setstr;
	//Tstring getstr = GetText();
	//if (getstr.size() >= 10)
	//{
	//	//getstr.assign(GetText().c_str()[0], GetText().c_str()[9]);
	//	setstr.assign(getstr.begin(), getstr.begin() + 10);
	//	SetText(setstr.c_str());
	//} 

	//SetText(L"123456");

	return PR_OK;
}

int ChatEditBarItem::Init()
{
	WNDItem::Init(TEXT("edit"), TEXT("LobbyChat"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT /*| ES_AUTOVSCROLL */| ES_AUTOHSCROLL /*| ES_MULTILINE *//*| ES_NOHIDESEL*/, (int)(WindSizeX * 0.06f), (int)(WindSizeY * 0.80f), (int)(WindSizeX * 0.88f), 30, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L"");
	PostMessage(m_hWnd, EM_LIMITTEXT, 100, 0);

	SetFocus(m_hWnd);
	return PR_OK;
}

int ChatEditBarItem::release()
{
	WNDItem::release(0);
	return PR_OK;
}



LRESULT ChatEditBarItem::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT edit_result = NULL;

	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RETURN:
		{
			if (GetFocusBox() && LobbyCahtEntercntl == false)
			{
				CommonPacket packet2s;
				//memset(&packets, 0, sizeof(CommonPacket));
				//ZeroMemory(&packets, sizeof(CommonPacket));
				/////////
				packet2s.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
				packet2s.PacProp.iLocation1 = SL_LOBBY;
				packet2s.PacProp.iLocation2 = LB_CHAT;
				packet2s.PacProp.iWork = CC_CHAT;
				packet2s.PacProp.iItem = LB_CHATPUSH;


				//Edit_GetText(m_hWnd,,)
				TCHAR msgbuff[100] = { 0, };
				GetWindowText(m_hWnd, msgbuff, 100);
				packet2s.SetComment(msgbuff, 100);

				ClientCore::pServer->PushSend(packet2s);
				LobbyCahtEntercntl = true;

				SetWindowText(m_hWnd, NULL);

				//SetWindowText(hWnd, TEXT(""));
			}
			edit_result = 0;
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_RETURN:
		{
			LobbyCahtEntercntl = false;
			break;
		}
		default:
			break;
		}
	}

	case WM_LBUTTONDOWN:
	{
		//SetText(L"");
		break;
	}
	case EN_ERRSPACE:
	{
		//SetText(L"???");
		break;
	}
	//case EN_SETFOCUS:
	//{

	//	//SetText(L"");
	//	break;
	//}
	case EN_KILLFOCUS:
	{
		//SetText(L" 채팅창 ");
		break;
	}

	default:
		break;
	}



	return edit_result;
}
