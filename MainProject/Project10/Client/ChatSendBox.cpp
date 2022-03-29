#include "stdafx.h"
#include "ChatSendBox.h"


ChatSendBox::ChatSendBox()
{
}


ChatSendBox::~ChatSendBox()
{
}

int ChatSendBox::Input(float time)
{
	return PR_OK;
}

int ChatSendBox::Update(float time)
{
	return PR_OK;
}

int ChatSendBox::LateUpdate(float time)
{
	return PR_OK;
}

int ChatSendBox::Transform(float time)
{
	return PR_OK;
}

int ChatSendBox::Render(float time, HDC drow)
{
	return PR_OK;
}

int ChatSendBox::DebugRender(float time)
{
	return PR_OK;
}

int ChatSendBox::Collision(float time)
{
	return PR_OK;
}

int ChatSendBox::Init()
{
	return PR_OK;
}

int ChatSendBox::release()
{
	WNDItem::release(0);
	return PR_OK;
}
