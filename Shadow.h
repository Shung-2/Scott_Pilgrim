#pragma once
#include "Component.h"
class Shadow :
    public Component
{
private:
    ZOrder* _zOrder;
    RECT _shadowRc;
    BLENDFUNCTION _blendFunc;
    int _width;
    int _height;
    int _deltaX;
    int _deltaY;
public:
    virtual void Init();
    virtual void Update();
    virtual void Render();

    void SetWidth(int width) { _width = width; }
    void SetHeight(int height) { _height = height; }
    void SetDeltaX(int deltaX) { _deltaX = deltaX; }
    void SetDeltaY(int deltaY) { _deltaY = deltaY; }
};

