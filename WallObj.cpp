#include "stdafx.h"
#include "WallObj.h"
#include "Wall.h"
void WallObj::Init(int startX, int startY, int endX, int endY)
{
	wall = new Wall();
	AddComponent(wall);
	wall->Init(startX, startY, endX, endY);
}
