#include "stdafx.h"
#include "Animator.h"

Animator::Animator()
{
}


Animator::~Animator()
{

}

void Animator::Init()
{
	renderer = gameObject->GetComponent<Renderer>();
	if (renderer == nullptr) {
		throw "Animator에서 발생 : 게임 오브젝트에 Renderer컴포넌트가 없습니다";
	}
	currentFrame = 0;
	_isPause = false;
	_isEnd = false;
}

void Animator::Update()
{
	if (curClip == nullptr)
		return;
	if (_isPause == true) return;
	frameTime += TIMEMANAGER->getElapsedTime();
	if (frameTime >= curClip->frameTerm) {
		currentFrame++;
		if (currentFrame == curClip->frameNum) {
			if (curClip->isLoop == true)
				currentFrame = 0;
			else {
				_isEnd = true;
				currentFrame = curClip->frameNum - 1;
				for (transactionIter = transactionMap.begin(); transactionIter != transactionMap.end(); transactionIter++) {
					if (transactionIter->second.startClip == curClip) {
						SetClip(transactionIter->second.nextClip);
					}
				}
			}
		}
		BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
			curClip->wholeDC, curClip->frameWidth * currentFrame, 0, SRCCOPY);
		frameTime = 0;
	}
}

void Animator::Render()
{

}

void Animator::SetClip(AnimationClip* newClip)
{
	preClip = curClip;
	curClip = newClip;
	_isEnd = false;
	currentFrame = 0;
	frameTime = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, 0, 0, SRCCOPY);
}

void Animator::SetClip(AnimationClip* newClip, int startFrame)
{
	preClip = curClip;
	curClip = newClip;
	_isEnd = false;
	currentFrame = startFrame;
	frameTime = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, currentFrame * curClip->frameWidth, 0, SRCCOPY);
}

void Animator::SetClip(string clipName)
{
	preClip = curClip;
	curClip = GetClip(clipName);
	_isEnd = false;
	currentFrame = 0;
	frameTime = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, 0, 0, SRCCOPY);
}

void Animator::SetClip(string clipName, int startFrame)
{
	preClip = curClip;
	curClip = GetClip(clipName);
	_isEnd = false;
	currentFrame = startFrame;
	frameTime = 0;
	renderer->Resize(curClip->frameWidth, curClip->frameHeight);
	BitBlt(renderer->memDC, 0, 0, curClip->frameWidth, curClip->frameHeight,
		curClip->wholeDC, currentFrame * curClip->frameWidth, 0, SRCCOPY);
}

void Animator::AddClip(string clipName, AnimationClip* newClip)
{
	clipMap.insert(make_pair(clipName, newClip));
}

AnimationClip* Animator::GetClip(string clipName)
{
	map<string, AnimationClip*>::iterator iter;
	iter = clipMap.find(clipName);
	if (iter != clipMap.end()) {
		return iter->second;
	}
	return nullptr;
}

void Animator::AddTransaction(string name, AnimationClip* startClip, AnimationClip* nextClip)
{
	TRANSACTION newTransaction = { startClip, nextClip };
	transactionMap.insert(make_pair( name, newTransaction));
}

void Animator::Pause()
{
	_isPause = true;
}

void Animator::Resume()
{
	_isPause = false;
}
