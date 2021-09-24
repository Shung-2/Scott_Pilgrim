#include "stdafx.h"
#include "ClipManager.h"
void ClipManager::Init()
{
}
void ClipManager::Release()
{
}
//map에 저장될 클립의 이름, 이미지 파일 경로("*.bmp"), 이미지 넓이, 이미지 크기, 프레임개수, 프레임간격(단위 초, ex - 0.08f)
//추가된 AnimationClip포인터를 반환
AnimationClip* ClipManager::AddClip(string clipName, const char* fileName, int width, int height, int frameNum, float frameTerm)
{
    AnimationClip* clip = FindClip(clipName);

    if (clip != nullptr)
        return clip;

    clip = new AnimationClip();

    clip->Init(fileName, width, height, frameNum, frameTerm);
    _clipMap.insert(pair<string, AnimationClip*>(clipName, clip));

    return clip;
}

//AddClip에서 추가한 clipName으로 AnimationClip을 찾아줌, 찾지 못했을 경우 nullptr을 반환
AnimationClip* ClipManager::FindClip(string clipName)
{
    _clipMapIter = _clipMap.find(clipName);

    //찾았다!
    if (_clipMapIter != _clipMap.end())
    {
        return _clipMapIter->second;
    }

    return nullptr;
}
