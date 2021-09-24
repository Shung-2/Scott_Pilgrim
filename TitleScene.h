#pragma once
#include "Scene.h"
class TitleScene :
    public Scene
{
private:
    int _titleAlpha;
    int _fadeOutAlpha;
    float _startBlinkTime;
    bool _isStart;
public:
    TitleScene() {};
    ~TitleScene() {};

    ImageObject background;
    ImageObject title;
    ImageObject start;
    ImageObject fadeOut;
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();
};

