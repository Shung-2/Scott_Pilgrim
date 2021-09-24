#pragma once
#include "GameObject.h"
class Projectile :
    public Component
{
protected:
    int _targetTag;
    string _hitEffectName;
    int _damage;
    float _activeLimit;
    float _activeTime;
    bool _dir;
    bool _isNeedEffectDir;
public:
    Projectile() {};
    ~Projectile() {};
    virtual void Init(string targetTag, string hitEffectName, int damage, float activeLimit);
    virtual void Update();
    virtual void Fire(int x, int y, bool dir);
    virtual void OnTriggerEnter(GameObject* gameObject);

    void SetDir(bool dir) { _dir = dir; }
    bool GetDir() { return _dir; }

    void SetNeedEffectDir(bool isNeedDir) { _isNeedEffectDir = isNeedDir; }
    bool GetNeedEffectDir() { return _isNeedEffectDir; }
};

