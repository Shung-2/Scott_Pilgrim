#pragma once
#include "Scene.h"
#include "SceneInfoLoader.h"
#include "CameraControler.h"
#define BG_NUM 23
#define WALL_NUM 19
#define SUCCUBUSMAX 4
class WallObj;

class StartScene :
    public Scene
{
public:
    StartScene();
    ~StartScene();

    vector<GameObject*> _propV;
    vector<GameObject*> _enemyV;
    SceneInfoLoader sceneInfoLoader;
    CameraControler cameraControler;
    ImageObject* background[BG_NUM];
    Box* box;
    ImageObject* imageObj;
    Character* character;
	Character* matthew;
	Character* succubus[SUCCUBUSMAX];
	GameObject* player;
    WallObj* wall[WALL_NUM];
	ItemObject* trashBox;
	ImageObject fadeOut;
	int fadeOutAlpha;
    UIBase uiBox;
    image* numImg[10];
    image* hpUI[3];
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void UiInit();
    void HPRender();
    void BackgroundInit();
    void CameraInit();
    void WallInit();
	void ItemImageClip();
    // 210629 시영 추가 (에너미 클립전용 함수 생성)
    void EnemyClipManager();
	void EffectClipInit();
};
