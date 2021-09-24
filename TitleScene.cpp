#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::Init()
{
    Scene::Init();
    background.Init();
    background.renderer->Init("ui/title.bmp", WINSIZEX, WINSIZEY);

    title.Init();
    title.transform->SetPosition(648, 183);
    title.renderer->Init("ui/title2.bmp", 424, 204);
    title.renderer->SetAlphaMode(true, 255);

    _titleAlpha = 0;

    start.Init();
    start.transform->SetPosition(452, 500);
    start.renderer->Init("ui/start_ui.bmp", 172, 66);

    _startBlinkTime = 0;

    fadeOut.Init();
    fadeOut.renderer->Init();
    fadeOut.renderer->Resize(WINSIZEX, WINSIZEY);
    fadeOut.renderer->SetAlphaMode(true, 0);

    _fadeOutAlpha = 0;
    _isStart = false;
    return S_OK;
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
    _titleAlpha++;
    if (_titleAlpha > 255)
        _titleAlpha = 255;

    _startBlinkTime += TIMEMANAGER->getElapsedTime();
    if (_startBlinkTime >= 1.f)
    {
        _startBlinkTime = 0;
        start.SetActive(!start.isActive);
    }
    background.Update();
    title.renderer->SetAlpha(_titleAlpha);
    title.Update();
    start.Update();
    fadeOut.Update();
    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        _isStart = true;
    }
    if (_isStart == true)
    {
        _fadeOutAlpha++;
        fadeOut.renderer->SetAlpha(_fadeOutAlpha);
        if (_fadeOutAlpha == 255)
        {
			SCENEMANAGER->LoadScene("start");
			SCENEMANAGER->GetCurScene()->Init();
        }
    }
}

void TitleScene::Render()
{
    background.Render();
    title.Render();
    start.Render();
    fadeOut.Render();
    MainCam->Render(_hdc);
}
