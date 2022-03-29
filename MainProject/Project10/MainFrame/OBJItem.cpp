#include "OBJItem.h"
#include "Layer.h"


OBJItem::OBJItem()
{
}


OBJItem::~OBJItem()
{
}

bool OBJItem::GetActive() 
{
	if (pLayer)
	{
		return  GameObj::GetActive() && pLayer->GetActive();
	}
	else
	{
		return GameObj::GetActive();
	}
	//나의 씬을 알고 있어야겠는데?
	return false;
}

int OBJItem::Transform(float time)
{
	return 0;
}

int OBJItem::Render(float time, HDC drow)
{
	return 0;
}

int OBJItem::DebugRender(float time)
{
	return 0;
}

int OBJItem::Collision(float time)
{
	return 0;
}
