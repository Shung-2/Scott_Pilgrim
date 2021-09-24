#include "stdafx.h"
#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init()
{
	for (int i = 0; i < EFFECT_MIN; i++)
	{
		EFFECTINFO effectInfo;
		ZeroMemory(&effectInfo, sizeof(EFFECTINFO));
		_effectV.push_back(effectInfo);
	}
}

void EffectManager::Update()
{
	for (_effectIter = _effectV.begin(); _effectIter != _effectV.end();) 
	{
		if (_effectIter->active == false)
		{
			_effectIter++;
			continue;
		}
		//이펙트가 최대프레임이 안되면 이터레이터를 증가시키면서 진행
		if (_effectIter->curFrame != _effectIter->maxFrame)
		{
			_effectIter->time += TIMEMANAGER->getElapsedTime();
			if (_effectIter->time >= _effectIter->frameTerm) {//프레임 시간이 간격보다 커지면
				_effectIter->curFrame++;//다음 프레임으로 이동
				_effectIter->time = 0;//프레임 시간 초기화
			}
			_effectIter++;//이펙트가 종료된것이 아니면 이터레이터를 증가
		}
		//이펙트가 최대프레임이 됐을 경우
		else if(_effectV.size() > EFFECT_MIN)
			//이펙트의 개수가 최소개수보다 많다면 이펙트를 벡터에서 erase
			_effectIter = _effectV.erase(_effectIter);
		else
			//이펙트 개수가 최소개수보다 적다면 erase하지 않고 active만 초기화
			_effectIter->active = false;
	}
}

void EffectManager::Render()
{
	for (int i = 0; i < _effectV.size(); i++) {
		if (_effectV[i].active == false) continue;
		AnimationClip* curClip = CLIPMANAGER->FindClip(_effectV[i].clipName);
		GdiTransparentBlt(BackBuffer,
			_effectV[i].x, _effectV[i].y,
			curClip->frameWidth, curClip->frameHeight,
			curClip->wholeDC,
			curClip->frameWidth * _effectV[i].curFrame, 0,
			curClip->frameWidth, curClip->frameHeight,
			RGB(255, 0, 255));
	}
}

void EffectManager::Release()
{
	_effectV.clear();
}

void EffectManager::EmissionEffect(string effectClipName, int x, int y)
{
	AnimationClip targetClip = *CLIPMANAGER->FindClip(effectClipName);
	if (GetActiveNum() == EFFECT_MIN) 
	{
		EFFECTINFO effectInfo;
		effectInfo.x = x - targetClip.frameWidth / 2;
		effectInfo.y = y - targetClip.frameHeight / 2;
		effectInfo.active = true;
		effectInfo.time = 0;
		effectInfo.curFrame = 0;
		effectInfo.maxFrame = targetClip.frameNum;
		effectInfo.frameTerm = targetClip.frameTerm;
		effectInfo.clipName = effectClipName;
		_effectV.push_back(effectInfo);
	}
	else
	{
		for (int i = 0; i < EFFECT_MIN; i++)
		{
			if (_effectV[i].active == true) continue;
			_effectV[i].x = x - targetClip.frameWidth / 2;
			_effectV[i].y = y - targetClip.frameHeight / 2;
			_effectV[i].active = true;
			_effectV[i].time = 0;
			_effectV[i].curFrame = 0;
			_effectV[i].maxFrame = targetClip.frameNum;
			_effectV[i].frameTerm = targetClip.frameTerm;
			_effectV[i].clipName = effectClipName;
			break;
		}
	}
}

int EffectManager::GetActiveNum()
{
	int result = 0;
	for (int i = 0; i < EFFECT_MIN; i++) {
		if (_effectV[i].active == true)
			result++;
	}
	return result;
}
