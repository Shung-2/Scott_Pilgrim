#include "stdafx.h"
#include "CameraControler.h"
void CameraControler::Init()
{
    _lock = false;
    for (int i = 0; i < CAM_SECTOR_NUM; i++)
    {
        _isLockPoint[i] = false;
    }
    _camLockPoint[0] = 2350;
    _camLockPoint[1] = 4030;
    _camLockPoint[2] = 6145;
    _camLockPoint[3] = 8480;
    _camLockPoint[4] = 11680;

    _camSpeed = 300.f;
}

void CameraControler::Update()
{
    _playerX = _playerTr->GetX();
    _camX = MainCam->transform->GetX();
    for (int i = 0; i < CAM_SECTOR_NUM; i++)
    {
        if (_isLockPoint[i] == false && _playerTr->GetX() >= _camLockPoint[i])
        {
            _lock = true;
            _isLockPoint[i] = true;
        }
    }
    if (_lock == false)
    {
        if (_playerX <= _camX)
        {
            float deltaX = _camX - _playerX;
            if (deltaX >= _camSpeed * TIMEMANAGER->getElapsedTime())
                MainCam->transform->MoveX(-_camSpeed * TIMEMANAGER->getElapsedTime());
            else
                MainCam->transform->MoveX(-deltaX);
        }
        else
        {
            float deltaX = _playerX - _camX;
            if (deltaX >= _camSpeed * TIMEMANAGER->getElapsedTime())
                MainCam->transform->MoveX(_camSpeed * TIMEMANAGER->getElapsedTime());
            else
                MainCam->transform->MoveX(deltaX);
        }
		if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
			MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
    }
}
