#include "stdafx.h"
#include "UIRenderer.h"

UIRenderer::UIRenderer()
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Init()
{
	HDC hdc = GetDC(_hWnd);
	_width = 100;
	_height = 100;
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	oBit = (HBITMAP)SelectObject(memDC, hBit);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	SelectObject(alphaMemDC, hBit);

	ReleaseDC(_hWnd, hdc);
	alpha = 255;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.AlphaFormat = 0;
	blendFunction.SourceConstantAlpha = alpha;
	_isAlpha = false;
}

void UIRenderer::Init(const char* filename, int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->_width = width;
	this->_height = height;
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)LoadImage(_hInstance, filename, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	oBit = (HBITMAP)SelectObject(memDC, hBit);

	hBit = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);

	DeleteObject(hBit);
	ReleaseDC(_hWnd, hdc);
	alpha = 255;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.AlphaFormat = 0;
	blendFunction.SourceConstantAlpha = alpha;
	_isAlpha = false;
}

void UIRenderer::Update()
{
}

void UIRenderer::Render()
{
	int startX = SCENEMANAGER->GetCurScene()->mainCam->transform->GetX() + transform->GetX() - _width/2;
	int startY = SCENEMANAGER->GetCurScene()->mainCam->transform->GetY() + transform->GetY() - _height / 2;
	if (_isAlpha == false) {
		BitBlt(alphaMemDC, 0, 0, _width, _height, BackBuffer, startX, startY, SRCCOPY);
		GdiTransparentBlt(
			alphaMemDC,			//복사될 영역의 DC
			0,					//복사될 좌표(left)
			0,					//복사될 좌표(top)
			_width,				//복사될 크기 (가로크기)
			_height,			//복사될 크기 (세로크기)
			memDC,				//복사해올 DC 
			0, 0,				//복사해올 시작좌표(left, top)
			_width,				//복사해올 가로크기
			_height,			//복사해올 세로크기
			RGB(255, 0, 255)	//복사할때 제외할 픽셀값
		);
		AlphaBlend(
			BackBuffer,	//출력할 곳의 DC
			startX,						//출력할 DC에서 그림의 찍을 좌표 x
			startY,						//출력할 DC에서 그림의 찍을 좌표 y
			_width,						//출력한 DC에서 그림의 가로 길이
			_height,					//출력한 DC에서 그림의 세로 길이
			alphaMemDC,					//그림의 DC
			0,							//그림에서 그리기 시작할 좌표 x
			0,							//그림에서 그리기 시작할 좌표 y
			_width,						//그림에서 출력DC에 그릴 그림의 가로 길이
			_height,					//그림에서 출력DC에 그릴 그림의 세로 길이
			blendFunction);				//알파블렌드에서의 옵션값
	}
	else {
		GdiTransparentBlt(
			BackBuffer,			//복사될 영역의 DC
			startX,				//복사될 좌표(left)
			startY,				//복사될 좌표(top)
			_width,				//복사될 크기 (가로크기)
			_height,			//복사될 크기 (세로크기)
			memDC,				//복사해올 DC 
			0, 0,				//복사해올 시작좌표(left, top)
			_width,				//복사해올 가로크기
			_height,			//복사해올 세로크기
			RGB(255, 0, 255)	//복사할때 제외할 픽셀값
		);
	}
}
//렌더러의 사이즈를 재조정
void UIRenderer::Resize(int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->_width = width;
	this->_height = height;
	memDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(memDC, oBit);
	oBit = (HBITMAP)SelectObject(memDC, hBit);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);
}

void UIRenderer::SetAlphaMode(bool isAlpha, int alpha)
{
	_isAlpha = isAlpha;
	SetAlpha(alpha);
}

void UIRenderer::SetAlpha(int alpha)
{
	this->alpha = alpha;
	blendFunction.SourceConstantAlpha = this->alpha;
}

//렌더러의 DC영역을 단색으로 채움
void UIRenderer::FillColor(COLORREF color)
{
	HBRUSH hBrush, oBrush;
	hBrush = CreateSolidBrush(color);
	oBrush = (HBRUSH)SelectObject(memDC, hBrush);
	PatBlt(memDC, 0, 0, _width, _height, PATCOPY);
	SelectObject(memDC, oBrush);
	DeleteObject(hBrush);
}
