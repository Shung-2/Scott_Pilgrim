#include "stdafx.h"
#include "DamageManager.h"

HRESULT DamageManager::Init()
{
    for (int i = 0; i < INFO_MAX; i++)
    {
        _infoArr[i].isActive = false;
        _infoArr[i].x = 0;
        _infoArr[i].y = 0;
        _infoArr[i].number = nullptr;
    }
    char filename[32];
    for (int i = 0; i < 10; i++)
    {
        sprintf_s(filename, "ui/number%d.bmp", i);
        number[i] = new image();
        number[i]->init(filename, 21, 30, true, RGB(255, 0, 255));
    }
    _speed = 30;
    _activeMaxTime = 1.f;
    return S_OK;
}

void DamageManager::Update()
{
    for (int i = 0; i < INFO_MAX; i++)
    {
        if (_infoArr[i].isActive == false) continue;
        _infoArr[i].y -= _speed * TIMEMANAGER->getElapsedTime();
        _infoArr[i].time += TIMEMANAGER->getElapsedTime();
        if (_infoArr[i].time >= _activeMaxTime)
        {
            _infoArr[i].isActive = false;
        }
    }
}

void DamageManager::Render()
{
    for (int i = 0; i < INFO_MAX; i++)
    {
        if (_infoArr[i].isActive == false) continue;
        _infoArr[i].number->render(BackBuffer, _infoArr[i].x, _infoArr[i].y);
    }
}

void DamageManager::Release()
{
}

void DamageManager::CreateDamage(int damage, float x, float y)
{
    int copy = damage;
    vector<int> numV;
    while (copy != 0)
    {
        int num = copy % 10;
        numV.push_back(num);
        copy /= 10;
    }

    for (int i = numV.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < INFO_MAX; j++)
        {
            if (_infoArr[j].isActive == true) continue;
            _infoArr[j].x = x - 11 + (22 * (numV.size() - 1 - i));
            _infoArr[j].y = y;
            _infoArr[j].isActive = true;
            _infoArr[j].number = number[numV[i]];
            _infoArr[j].time = 0;
            break;
        }
    }
}
