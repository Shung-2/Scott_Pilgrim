#pragma once
#define CAM_SECTOR_NUM 5
class CameraControler
{
private:
    Transform* _playerTr;
    int _camLockPoint[CAM_SECTOR_NUM];
    bool _isLockPoint[CAM_SECTOR_NUM];
    bool _lock;
    float _lockTime;
    float _camSpeed;
    float _playerX;
    float _camX;
public:
    void Init();
    void Update();

    void SetPlayerTransform(Transform* playerTr) { _playerTr = playerTr; }
    void UnLock() { _lock = false; }
};

