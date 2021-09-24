#include "stdafx.h"
#include "BackgroundManager.h"

HRESULT BackgroundManager::Init()
{
    return S_OK;
}

void BackgroundManager::Update()
{
    if (_player == nullptr || _backgroundV.size() == 0) return;
    int playerX = _player->GetX();
    for (int i = 0; i < _backgroundV.size(); i++) 
    {
        int minX = _unitWidth * i - _margin - (SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->GetScreenWidth() / 2);
        int maxX = _unitWidth * (i + 1) + _margin + (SCENEMANAGER->GetCurScene()->mainCam->GetComponent<Camera>()->GetScreenWidth() / 2);
        if (playerX >= minX && playerX <= maxX) 
        {
            if(_backgroundV[i]->isActive == false)
                _backgroundV[i]->SetActive(true);
        }
        else 
        {
            if (_backgroundV[i]->isActive == true)
                _backgroundV[i]->SetActive(false);
        }
        _backgroundV[i]->Update();
    }
}

void BackgroundManager::Render()
{
    for (int i = 0; i < _backgroundV.size(); i++)
    {
        _backgroundV[i]->Render();
    }
}

void BackgroundManager::Release()
{
}
