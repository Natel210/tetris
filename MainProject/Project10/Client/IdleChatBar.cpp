#include "stdafx.h"
#include "IdleChatBar.h"
#include "Input/Input.h"
#include "ClientCore.h"
#include "ClientHeader.h"

static const int limlan = 60;
static bool RoomCahtEntercntl = false;

IdleChatBar::IdleChatBar()
{
}


IdleChatBar::~IdleChatBar()
{
}

int IdleChatBar::Input(float time)
{
	if (KEY_PUSH(EnterKey) && CntlEnterCollTime < 0.f)
	{
		//메시지를 보낸다.
		CntlEnterCollTime = 0.2f;


		if (GetFocusBox())
		{

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

int IdleChatBar::Update(float time)
{
	CommonPacket packets = CommonPacket();
	
	packets = ClientCore::pServer->PopRecv(ClientCore::ClientPlayer.eLoginfo.m_UniqueID, SL_ROOM, RM_CHAT, CC_CHAT, LB_CHATPUSH);
	if (packets.PacProp.iLocation1 == SL_ROOM && packets.PacProp.iItem == LB_CHATPUSH)
	{
		
	}
	

	
	return PR_OK;
}

int IdleChatBar::LateUpdate(float time)
{
	return PR_OK;
}

int IdleChatBar::Transform(float time)
{
	return PR_OK;
}

int IdleChatBar::Render(float time, HDC drow)
{
	return PR_OK;
}

int IdleChatBar::DebugRender(float time)
{
	return PR_OK;
}

int IdleChatBar::Collision(float time)
{
	return PR_OK;
}

int IdleChatBar::Init()
{
	WNDItem::Init(TEXT("edit"), TEXT("IdleChat"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT /*| ES_AUTOVSCROLL */ | ES_AUTOHSCROLL /*| ES_MULTILINE *//*| ES_NOHIDESEL*/, 600 + (Map_maxX * 30) + 15, (Map_maxY * 15) +315, 240, 30, ClientCore::mainhWnd, ClientCore::mainhInst, NULL);
	SetText(L"");
	PostMessage(m_hWnd, EM_LIMITTEXT, limlan, 0);

	SetFocus(m_hWnd);
	return PR_OK;
}

int IdleChatBar::release()
{
	WNDItem::release(0);
	return PR_OK;
}



LRESULT IdleChatBar::CustomProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			if (GetFocusBox() && RoomCahtEntercntl == false)
			{


				CommonPacket packets;
				//memset(&packets, 0, sizeof(CommonPacket));
				//ZeroMemory(&packets, sizeof(CommonPacket));
				/////////
				packets.PacProp.LinkNumber = ClientCore::ClientPlayer.eLoginfo.m_UniqueID;
				packets.PacProp.iLocation1 = SL_ROOM;
				packets.PacProp.iLocation2 = RM_CHAT;
				packets.PacProp.iWork = CC_CHAT;
				packets.PacProp.iItem = LB_CHATPUSH;


				//Edit_GetText(m_hWnd,,)
				TCHAR msgbuff[limlan] = { 0, };
				GetWindowText(m_hWnd, msgbuff, limlan);
				packets.SetComment(msgbuff, limlan);

				ClientCore::pServer->PushSend(packets);
				SetWindowText(m_hWnd, NULL);
				RoomCahtEntercntl = true;

				
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
			RoomCahtEntercntl = false;
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
