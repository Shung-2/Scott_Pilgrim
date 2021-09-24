#include "stdafx.h"
#include "AnimationClip.h"

HRESULT AnimationClip::Init(const char* filename, int width, int height, int frameNum, float frameTerm)
{
	HDC hdc = GetDC(_hWnd);
	wholeDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)LoadImage(_hInstance, filename, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	oBit = (HBITMAP)SelectObject(wholeDC, hBit);

	this->frameTerm = frameTerm;
	this->frameNum = frameNum;
	frameHeight = height;
	frameWidth = width / frameNum;
	currentFrame = 0;
	isLoop = true;

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

AnimationClip::AnimationClip()
{

}

AnimationClip::~AnimationClip()
{

}
