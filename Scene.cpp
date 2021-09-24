#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

HRESULT Scene::Init()
{
    HDC hdc = GetDC(_hWnd);
    HBITMAP hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
    _backDC = CreateCompatibleDC(hdc);
    SelectObject(_backDC, hBit);
    DeleteObject(hBit);
    if(mainCam == nullptr)
        mainCam = new Cam();
    mainCam->Init();
    CAMERAMANAGER->SetMainCam(mainCam->camera);
    ReleaseDC(_hWnd, hdc);
    return S_OK;
}


void Scene::Release()
{
    SAFE_RELEASE(mainCam);
}

void Scene::Update()
{
}

void Scene::Render()
{
}

void Scene::SetBackBufferSize(int width, int height)
{
    HDC hdc = GetDC(_hWnd);
    HBITMAP hBit = CreateCompatibleBitmap(hdc, width, height);
    _backDC = CreateCompatibleDC(hdc);
    SelectObject(_backDC, hBit);
    DeleteObject(hBit);
    ReleaseDC(_hWnd, hdc);
}

void Scene::ChangeMainCam(Cam* newCam)
{
    SAFE_RELEASE(mainCam);
    mainCam = newCam;
}
