#include "stdafx.h"
#include "Ground.h"

void Ground::Init()
{
	_width = transform->GetWidth();
	_height = transform->GetHeight();
	_deltaX = 0;
	_deltaY = 0;
	_x = gameObject->transform->GetX();
	_y = gameObject->transform->GetY();
	_z = gameObject->GetComponent<ZOrder>()->GetZ();
	GROUNDMANAGER->AddGround(this);
}

void Ground::Init(int width, int height, int deltaX, int deltaY)
{
	_width = width;
	_height = height;
	_deltaX = deltaX;
	_deltaY = deltaY;
	_x = gameObject->transform->GetX() + _deltaX;
	_y = gameObject->transform->GetY() + _deltaY;
	_z = gameObject->GetComponent<ZOrder>()->GetZ();
	GROUNDMANAGER->AddGround(this);
}

void Ground::Update()
{
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void Ground::Render()
{
	HPEN hPen, oPen;
	HBRUSH hBrush, oBrush;
	if (KEYMANAGER->isToggleKey(VK_TAB)) 
	{
		return;
	}
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oBrush = (HBRUSH)SelectObject(BackBuffer, hBrush);
	hPen = CreatePen(PS_DOT, 1, RGB(125, 125, 0));
	oPen = (HPEN)SelectObject(BackBuffer, hPen);
	Rectangle(BackBuffer, _rc);
	SelectObject(BackBuffer, oPen);
	SelectObject(BackBuffer, oBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void Ground::OnEnable()
{
	GROUNDMANAGER->AddGround(this);
}

void Ground::OnDisable()
{
	GROUNDMANAGER->EraseGround(this);
}

bool Ground::CheckWallCross(float nextX, float nextY)
{
	if (WALLMANAGER->CheckCross(_x, _y, nextX, nextY)) {
		return true;
	}
	return false;
}

void Ground::Move(float x, float y)
{
	MoveX(x);
	MoveY(y);
}

void Ground::MoveX(float x)
{
	if (CheckWallCross(_x + x, _y) == true)
		return;
	_x += x;
}

void Ground::MoveY(float y)
{
	if (CheckWallCross(_x, _y + y) == true)
		return;
	_y += y;
}

void Ground::ReSize(int width, int height)
{
	if (_width == width && _height == height)
		return;
	_width = width;
	_height = height;
}
