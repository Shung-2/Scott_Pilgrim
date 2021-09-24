#pragma once
#include "AnimationClip.h"
class ClipManager : public singletonBase<ClipManager>
{
private:
	map<string, AnimationClip*> _clipMap;
	map<string, AnimationClip*>::iterator _clipMapIter;
public:
	ClipManager() {};
	~ClipManager() {};
	void Init();
	void Release();
	AnimationClip* AddClip(string clipName, const char* fileName, int width, int height, int frameNum, float frameTerm);
	AnimationClip* FindClip(string clipName);
};

