#pragma once
#include "Scene.h"

#define SUCCUBUSMAX 4
class BossScene :
	public Scene
{
private:
	ImageObject background;
	Character* character;
	Character* matthew;
	Character* succubus[SUCCUBUSMAX];
public:
	BossScene() {};
	~BossScene() {};

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

