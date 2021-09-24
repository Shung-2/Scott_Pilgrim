#pragma once
#include "Component.h"
class UIRenderer :
    public Component
{
private:
    HBITMAP hBit, oBit;
    HDC memDC, alphaMemDC;
    BLENDFUNCTION blendFunction;
    int _width;
    int _height;
    bool _isAlpha;
public:
    UIRenderer();
    ~UIRenderer();
    int alpha;
    virtual void Init();
    virtual void Init(const char* filename, int width, int height);
    virtual void Update();
    virtual void Render();
    void Resize(int width, int height);
    void SetAlphaMode(bool isAlpha) { _isAlpha = isAlpha; }
    void SetAlphaMode(bool isAlpha, int alpha);
    void SetAlpha(int alpha);
    void FillColor(COLORREF color);
};

