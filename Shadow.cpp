#include "stdafx.h"
#include "Shadow.h"

void Shadow::Init()
{
	_zOrder = gameObject->GetComponent<ZOrder>();
	_width = 90;
	_height = 30;
	_deltaX = 0;
	_deltaY = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.SourceConstantAlpha = 180;
}

void Shadow::Update()
{
	_shadowRc = RectMakeCenter(transform->GetX() + _deltaX, _zOrder->GetZ() + _deltaY, _width, _height);
}

void Shadow::Render()
{
	HBRUSH hBrush, oBrush;
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oBrush = (HBRUSH)SelectObject(BackBuffer, hBrush);
	Ellipse(BackBuffer, _shadowRc);
	SelectObject(BackBuffer, oBrush);
	DeleteObject(hBrush);
}
