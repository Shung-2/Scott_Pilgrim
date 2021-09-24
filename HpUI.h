#pragma once
#include "Component.h"
class HpUI :
    public Component
{
private:
    int _mode;
    UIRenderer* uiRenderer;
    char filename[32];
public:
    Player* playerInfo;
    virtual void Init(int mode);
    virtual void Update();
    virtual void Render();
};

