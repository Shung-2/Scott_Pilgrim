#include "stdafx.h"
#include "Wall.h"

void Wall::Init(float startX, float startY, float endX, float endY)
{
	_startX = startX;
	_startY = startY;
	_endX = endX;
	_endY = endY;

	//y = ax + b;
	//기울이 a(_gradient)는 y의 변화량 / x의 변화량
	_gradient = (_endY - _startY) / (_endX - _startX);
	//y절편(_interceptY)은 y - ax
	_interceptY = _startY - (_gradient * _startX);

	WALLMANAGER->AddWall(this);
}

void Wall::Update()
{
}

void Wall::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB)) 
	{
		LineMake(BackBuffer, _startX, _startY, _endX, _endY);
	}
}

void Wall::SetStartPoint(float startX, float startY)
{
	_startX = startX;
	_startY = startY;

	_gradient = (_endY - _startY) / (_endX - _startX);
	_interceptY = _startY - (_gradient * _startX);
}

void Wall::SetEndPoint(float endX, float endY)
{
	_endX = endX;
	_endY = endY;

	_gradient = (_endY - _startY) / (_endX - _startX);
	_interceptY = _startY - (_gradient * _startX);
}

bool Wall::IsCross(float startX, float startY, float endX, float endY)
{
	//오브젝트가 이동할때 시작점과 끝점이 1차 부등식의 부호가 다를경우
	//선을 넘는것으로 판단
	int start = CalcUpDown(startX, startY);//시작점의 부호
	int end = CalcUpDown(endX, endY);//도착지점의 부호
	//오브젝트가 선의 범위 안에 있을 경우만 판단
	if (IsInLine(startX, startY) == false)
		return false;
	//시작점과 도착지점의 부호가 다를 경우 선을 넘는것
	if (start != end)
		return true;

	return false;
}

int Wall::CalcUpDown(float x, float y)
{
	//1차 함수식을 적용하여 y좌표가 선보다 위에 있는지 아래 있는지 판단
	if (y <= _gradient * x + _interceptY)
		return -1;
	else
		return 1;
}

bool Wall::IsInLine(float x, float y)
{
	float bigX = (_startX > _endX) ? _startX : _endX;
	float smallX = (_startX < _endX) ? _startX : _endX;
	float bigY = (_startY > _endY) ? _startY : _endY;
	float smallY = (_startY < _endY) ? _startY : _endY;

	if (_startY == _endY) 
	{
		if (x > smallX && x < bigX)
			return true;
	}
	if (_startX == _endX) 
	{
		if (y > smallY && y < bigY)
			return true;
	}

	if (x > smallX && x < bigX && y > smallY && y < bigY)
		return true;

	return false;
}
