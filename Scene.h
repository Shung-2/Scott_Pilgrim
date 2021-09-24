#pragma once
#include "Cam.h"
//class Cam;
class Scene
{
private:
protected:
	int _mapWidth;
	int _mapHeight;
	HDC _backDC;
public:
	Scene();
	~Scene();
	Cam* mainCam;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	int GetWidth() { return _mapWidth; }
	int GetHeight() { return _mapHeight; }

	void SetBackBufferSize(int width, int height);
	void ChangeMainCam(Cam* newCam);
	HDC GetBackDC() const { return _backDC;}
};

