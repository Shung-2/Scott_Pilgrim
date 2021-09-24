#include "stdafx.h"
SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init()
{
    return S_OK;
}

void SceneManager::Update()
{
    _curScene->Update();
}

void SceneManager::Render()
{
    _curScene->Render();
}

void SceneManager::Release()
{
}

void SceneManager::AddScene(string sceneName, Scene* scene)
{
    sceneMap.insert(pair<string, Scene*>(sceneName, scene));
}

void SceneManager::LoadScene(string sceneName)
{
    if(_curScene != nullptr)
        _curScene->Release();
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        _curScene = sceneIter->second;
    }
}

Scene* SceneManager::GetScene(string sceneName)
{
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        return sceneIter->second;
    }
    return nullptr;
}

Scene* SceneManager::GetCurScene()
{
    return _curScene;
}

int SceneManager::GetCurSceneIdx()
{
    int idx = 0;
    for (sceneIter = sceneMap.begin(); sceneIter != sceneMap.end(); sceneIter++)
    {
        if (sceneIter->second == _curScene)
            return idx;
        idx++;
    }
    return -1;
}
