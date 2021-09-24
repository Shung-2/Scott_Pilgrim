#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(const char* filename, int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->_width = width;
	this->_height = height;
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);

	hBit = (HBITMAP)LoadImage(_hInstance, filename, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	oBit = (HBITMAP)SelectObject(memDC, hBit);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);
	DeleteObject(hBit);
	ReleaseDC(_hWnd, hdc);
	_alpha = 255;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = _alpha;
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
	_transColor = RGB(255, 0, 255);
	_scaleX = 1;
	_scaleY = 1;
}

void Renderer::Init()
{
	HDC hdc = GetDC(_hWnd);
	_width = transform->GetWidth();
	_height = transform->GetHeight();
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	oBit = (HBITMAP)SelectObject(memDC, hBit);
	SelectObject(alphaMemDC, hBit);
	DeleteObject(hBit);

	_alpha = 255;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = _alpha;
	rc = RectMakeCenter(transform->GetX(), transform->GetY(),
		_width, _height);
	ReleaseDC(_hWnd, hdc);
	_transColor = RGB(255, 0, 255);
	_scaleX = 1;
	_scaleY = 1;
}

void Renderer::Render()
{
	int startX = transform->GetX() - _width * _scaleX / 2;
	int startY = transform->GetY() - _height * _scaleY / 2;
	if (!KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(BackBuffer, rc);
	}
	if (_isAlpha == true) {
		BitBlt(alphaMemDC, 0, 0, _width * _scaleX, _height * _scaleY, BackBuffer, startX, startY, SRCCOPY);
		GdiTransparentBlt(
			alphaMemDC,		//복사될 영역의 DC
			0,				//복사될 좌표(left)
			0,				//복사될 좌표(top)
			_width * _scaleX,			//복사될 크기 (가로크기)
			_height * _scaleY,		//복사될 크기 (세로크기)
			memDC,			//복사해올 DC 
			0, 0,			//복사해올 시작좌표(left, top)
			_width,			//복사해올 가로크기
			_height,		//복사해올 세로크기
			_transColor		//복사할때 제외할 픽셀값
		);
		AlphaBlend(
			BackBuffer,		//복사될 영역의 DC
			startX,			//복사될 좌표(left)
			startY,			//복사될 좌표(top)
			_width * _scaleX,			//복사될 크기 (가로크기)
			_height * _scaleY,		//복사될 크기 (세로크기)
			alphaMemDC,		//복사해올 DC 
			0, 0,			//복사해올 시작좌표(left, top)
			_width * _scaleX,			//복사해올 가로크기
			_height * _scaleY,		//복사해올 세로크기
			blendFunc		//복사할때 제외할 픽셀값
		);
	}
	else {
		GdiTransparentBlt(
			BackBuffer,			//복사될 영역의 DC
			startX,				//복사될 좌표(left)
			startY,				//복사될 좌표(top)
			_width * _scaleX,	//복사될 크기 (가로크기)
			_height * _scaleY,	//복사될 크기 (세로크기)
			memDC,				//복사해올 DC 
			0, 0,				//복사해올 시작좌표(left, top)
			_width,				//복사해올 가로크기
			_height,			//복사해올 세로크기
			_transColor			//복사할때 제외할 픽셀값
		);
	}
}


void Renderer::Update()
{
	rc = RectMakeCenter(transform->position.x,
		transform->position.y,
		_width,
		_height);
}

void Renderer::Release()
{
	if (this != nullptr) {
		DeleteObject(hBit);
		ReleaseDC(_hWnd, memDC);
		ReleaseDC(_hWnd, alphaMemDC);
	}
}

void Renderer::OnEnable()
{
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		_width,
		_height);
}

void Renderer::OnDisable()
{
}

void Renderer::SetAlphaMode(bool isAlpha, int alpha)
{
	_isAlpha = isAlpha;
	_alpha = alpha;
	blendFunc.SourceConstantAlpha = _alpha;
}

void Renderer::Resize(int newWidth, int newHeight)
{
	if (_width == newWidth && _height == newHeight)
		return;
	HDC hdc = GetDC(_hWnd);

	HBITMAP scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);
	SelectObject(memDC, oBit);
	oBit = (HBITMAP)SelectObject(memDC, scaleBitmap);

	scaleBitmap = CreateCompatibleBitmap(hdc, newWidth * _scaleX, newHeight * _scaleY);
	SelectObject(alphaMemDC, scaleBitmap);

	ReleaseDC(_hWnd, hdc);
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		newWidth,
		newHeight);

	DeleteObject(scaleBitmap);
	_width = newWidth;
	_height = newHeight;
}

void Renderer::ResizeAlphaMemDC(float newWidth, float newHeight)
{
	if (_width == newWidth && _height == newHeight)
		return;
	HDC hdc = GetDC(_hWnd);

	HBITMAP scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);

	scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);
	SelectObject(alphaMemDC, scaleBitmap);

	ReleaseDC(_hWnd, hdc);
	DeleteObject(scaleBitmap);
}

void Renderer::SetScale(float scaleX, float scaleY)
{
	ResizeAlphaMemDC(_width * scaleX, _height * scaleY);
	_scaleX = scaleX;
	_scaleY = scaleY;
}

void Renderer::SetScaleX(float scaleX)
{
	ResizeAlphaMemDC(_width * scaleX, _height);
	_scaleX = scaleX;
}

void Renderer::SetScaleY(float scaleY)
{
	ResizeAlphaMemDC(_width, _height * scaleY);
	_scaleY = scaleY;
}
