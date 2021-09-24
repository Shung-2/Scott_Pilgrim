#include "stdafx.h"
#include "StartScene.h"
#include "Item.h"
#include "Player.h"
#include "WallObj.h"
#include "Wall.h"
#include "Doberman.h"
#include "Matthew.h"
#include "Malcolm.h"
#include "William.h"
#include "Succubus.h"
#include "HpUI.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::Init()
{    
    Scene::Init();
    CameraInit();
    EnemyClipManager();
    sceneInfoLoader.SetLinkObjectVAddress(&_propV);
    for (int i = 0; i < 13; i++)
    {
        sceneInfoLoader.LoadObjectInfo(i);
    }

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(0));
    sceneInfoLoader.LoadObjectInfo(13);

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(1));
    sceneInfoLoader.LoadObjectInfo(14);

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(2));
    sceneInfoLoader.LoadObjectInfo(15);

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(3));
    sceneInfoLoader.LoadObjectInfo(16);

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(4));
    sceneInfoLoader.LoadObjectInfo(17);

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(5));
    sceneInfoLoader.LoadObjectInfo(18);

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(6));
    sceneInfoLoader.LoadObjectInfo(19);

    sceneInfoLoader.SetLinkObjectVAddress(ENEMYMANAGER->GetEnemyVAddress(7));
    sceneInfoLoader.LoadObjectInfo(20);
    // 210629 시영 추가
	EffectClipInit();
    ItemImageClip();
    //위에는 건들지 마시오



    character = new Character();
    character->name = "character";
    character->zOrder->SetZ(character->transform->GetY() + 52);
	character->AddComponent(new Player);
	character->GetComponent<Player>()->Init();
	character->zOrder->Init();
	character->zOrder->SetZ(568 / 2 + 52);
	character->collider->isTrigger = true;
    character->AddComponent(new DebugText());
    character->GetComponent<DebugText>()->Init();

    UiInit();

    cameraControler.Init();
    cameraControler.SetPlayerTransform(character->transform);
    ENEMYMANAGER->SetPlayerTransform(character);
    ENEMYMANAGER->SetCameraControler(&cameraControler);
    for (int i = 0; i < _enemyV.size(); i++)
    {
        _enemyV[i]->Init();
        _enemyV[i]->GetComponent<EnemyAI>()->SetPlayer(character);
    }

	trashBox = new ItemObject();
	trashBox->Init();
	trashBox->item->SetItemImage("trashbox_right");
	trashBox->transform->SetPosition(640, 300);
	trashBox->zorder->Init();

	// 보스 매튜 구현//
	matthew = new Character();
	matthew->Init();
	matthew->transform->SetPosition(10000, 4000);
	matthew->collider->isTrigger = true;
	matthew->zOrder->SetZ(matthew->transform->GetX()+132/2);
	matthew->AddComponent(new Matthew());
	matthew->GetComponent<Matthew>()->Init();
	matthew->GetComponent<Matthew>()->SetPlayer(character);
	character->GetComponent<Player>()->boss = matthew;

	matthew->transform->SetX(5000);
    matthew->SetActive(false);
	for ( int i = 0; i < SUCCUBUSMAX; i++)
	{
		succubus[i] = new Character();
		succubus[i]->Init();
		succubus[i]->transform->SetPosition(600, 200);
		succubus[i]->collider->enable = false;
		succubus[i]->AddComponent(new Succubus());
		succubus[i]->GetComponent<Succubus>()->Init();
		succubus[i]->SetActive(false);
		matthew->GetComponent<Matthew>()->_succubus[i] = succubus[i];
	}
	
    BackgroundInit();
    WallInit();

	fadeOut.Init();
	fadeOut.renderer->Init();
	fadeOut.renderer->Resize(WINSIZEX, WINSIZEY);
	fadeOut.renderer->SetAlphaMode(true, 0);
	fadeOut.SetActive(false);
	fadeOutAlpha = 0;

    MAPMANAGER->player = character;
    MAPMANAGER->enemyV = &_enemyV;
    return S_OK;
}

void StartScene::Release()
{
	for (int i = 0; i < _propV.size(); i++)
	{
		_propV[i]->SetActive(false);
	}
	trashBox->SetActive(false);
}

void StartScene::Update()
{
    for (int i = 0; i < _propV.size(); i++) 
    {
        _propV[i]->Update();
    }
    for (int i = 0; i < _enemyV.size(); i++)
    {
        _enemyV[i]->Update();
    }
	if (character->transform->GetX() >= _mapWidth - 800)
	{
		fadeOut.SetActive(true);
		if (fadeOutAlpha < 255)
		{
			fadeOutAlpha++;
		}
		fadeOut.transform->SetPosition(MainCam->transform->GetX(), MainCam->transform->GetY());
		fadeOut.renderer->SetAlpha(fadeOutAlpha);
	}
	fadeOut.Update();
	trashBox->Update();
    character->Update();
    cameraControler.Update();
    BGMANAGER->Update();
    EFFECTMANAGER->Update();
    ZORDER->Update();
    MainCam->Update();
    MAPMANAGER->Update();
    ENEMYMANAGER->Update();
    DAMAGEMANAGER->Update();
    uiBox.Update();


    // 광철 에너미 Update
	//matthew->Update();
	for (int i = 0; i < SUCCUBUSMAX; i++)
	{
		succubus[i]->Update();
	}

	matthew->Update();
	if (fadeOutAlpha == 255)
	{
		Release();
		fadeOutAlpha++;
		SCENEMANAGER->LoadScene("boss");
		SCENEMANAGER->GetCurScene()->Init();
	}

}

void StartScene::Render()
{
    BGMANAGER->Render();
    ZORDER->Render();
    for (int i = 0; i < WALL_NUM; i++) {
		wall[i]->Render();
    }
    EFFECTMANAGER->Render();
    DAMAGEMANAGER->Render();
    sprintf_s(debug[0], "Player X : %f, Player Y : %f", character->transform->GetX(), character->transform->GetY());
    sprintf_s(debug[1], "FPS : %d ", TIMEMANAGER->getFPS());
	fadeOut.Render();
    //TextOut(BackBuffer, MainCam->transform->GetX() - MainCam->GetScreenWidth() / 2, 20, debug[0], strlen(debug[0]));
    //TextOut(BackBuffer, MainCam->transform->GetX() - MainCam->GetScreenWidth() / 2, 40, debug[1], strlen(debug[1]));
    //TextOut(BackBuffer, MainCam->transform->GetX() - MainCam->GetScreenWidth() / 2, 60, debug[2], strlen(debug[2]));
    uiBox.Render();
    HPRender();
    MainCam->Render(_hdc);
}

void StartScene::UiInit()
{
    uiBox.Init();
    uiBox.uiRenderer->Init("ui/uibox.bmp", 187, 60);
    uiBox.transform->SetPosition(-(WINSIZEX / 2 - 120), -(WINSIZEY / 2 - 50));
    char filename[32];
    for (int i = 0; i < 10; i++)
    {
        sprintf_s(filename, "ui/number%d.bmp", i);
        numImg[i] = new image();
        numImg[i]->init(filename, 21, 30, true, RGB(255, 0, 255));
    }
}

void StartScene::HPRender()
{
    vector<int> hpNumV;
    int hpCopy = character->GetComponent<Player>()->hp;
    while (hpCopy != 0)
    {
        int num = hpCopy % 10;
        hpNumV.push_back(num);
        hpCopy /= 10;
    }
    for (int i = 0; i < hpNumV.size(); i++)
    {
        numImg[hpNumV[i]]->render(BackBuffer, MainCam->transform->GetX() - (WINSIZEX / 2 - 180 + 21 * i),
            MainCam->transform->GetY() - (WINSIZEY / 2 - 40));
    }
}

void StartScene::BackgroundInit()
{
    for (int i = 0; i < BG_NUM; i++) {
        char fileName[64];
        sprintf_s(fileName, "map/background%d.bmp", i + 1);
		background[i] = new ImageObject();
		background[i]->renderer->Init(fileName, 922, 680);
		background[i]->transform->SetPosition(922 * i + 922 /2, 680 /2);
		background[i]->name = "background";
        BGMANAGER->AddBackground(background[i]);
    }
	BGMANAGER->SetMargin(30);
	BGMANAGER->SetBackgroundWidth(922);
    BGMANAGER->SetPlayer(character->transform);
}

void StartScene::CameraInit()
{
    _mapWidth = 21206;
    _mapHeight = 680;
    MainCam->SetMapSize(_mapWidth, _mapHeight);
    MainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    MainCam->SetRenderHeight(568);
    MainCam->SetMapSize(21206, 680);
    SetBackBufferSize(_mapWidth, _mapHeight);
}

void StartScene::WallInit()
{
    for (int i = 0; i < WALL_NUM; i++)
    {
		wall[i] = new WallObj();
    }
    wall[0]->Init(0, 300, 1000, 300);

    wall[1]->Init(0, WINSIZEY, 2960, WINSIZEY);

    wall[2]->Init(800, 200, 1000, 300);

    wall[3]->Init(800, 200, 1450, 200);

    wall[4]->Init(1450, 200, 1650, 280);

    wall[5]->Init(1650, 280, 4650, 280);

    wall[6]->Init(4650, 280, 4450, 200);

    wall[7]->Init(4450, 200, 4850, 200);
    
    wall[8]->Init(4850, 200, 5150, 350);

    wall[9]->Init(5150, 350, 7135, 350);

    wall[10]->Init(7135, 350, 6935, 200);

    wall[11]->Init(6932, 200, 7340, 200);

    wall[12]->Init(7340, 200, 7640, 350);

    wall[13]->Init(7640, 350, 16750, 350);

    wall[14]->Init(16750, 350, 17100, 500);

    wall[15]->Init(17100, 500, 21000, 500);

    wall[16]->Init(3470, WINSIZEY, 16900, WINSIZEY);

    wall[17]->Init(16900, WINSIZEY, 17250, WINSIZEY + 120);

    wall[18]->Init(17250, WINSIZEY + 120, 21000, WINSIZEY + 120);
}

void StartScene::ItemImageClip()
{
    CLIPMANAGER->AddClip("trashbox_right", "item/trashbox_right.bmp", 115, 87, 1, 1);
	CLIPMANAGER->AddClip("trashbox_left", "item/trashbox_left.bmp", 115, 87, 1, 1);
    CLIPMANAGER->AddClip("chair", "item/chair.bmp", 41, 48, 1, 1);

    //walk attack 
    CLIPMANAGER->AddClip("trashbox_walk_attack_right", "item/trashbox_walk_attack_right.bmp", 805, 93, 7, 0.2f);
    CLIPMANAGER->FindClip("trashbox_walk_attack_right")->isLoop = false;

	CLIPMANAGER->AddClip("trashbox_walk_attack_left", "item/trashbox_walk_attack_left.bmp", 805, 93, 7, 0.2f);
	CLIPMANAGER->FindClip("trashbox_walk_attack_left")->isLoop = false;
	//throw
	CLIPMANAGER->AddClip("trashbox_walk_throw_right", "item/trashbox_walk_throw_right.bmp", 807, 69, 7, 0.2f);
	CLIPMANAGER->FindClip("trashbox_walk_throw_right")->isLoop = false;

	CLIPMANAGER->AddClip("trashbox_walk_throw_left", "item/trashbox_walk_throw_left.bmp", 460, 87, 4, 0.2f);
	CLIPMANAGER->FindClip("trashbox_walk_throw_left")->isLoop = false;
}

void StartScene::EnemyClipManager()
{
    /*
        CLIP MANAGER (ORDER - JESSE, LEE, LUKE, MIKE, RICHARD) by. 시영
    */

    /* JESSE CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("jesse_idle_right", "jesse/jesse_idle_right.bmp", 344, 132, 4, 0.20f);
    CLIPMANAGER->AddClip("jesse_idle_left", "jesse/jesse_idle_left.bmp", 344, 132, 4, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("jesse_walk_right", "jesse/jesse_walk_right.bmp", 468, 138, 6, 0.20f);
    CLIPMANAGER->AddClip("jesse_walk_left", "jesse/jesse_walk_left.bmp", 468, 138, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("jesse_run_right", "jesse/jesse_run_right.bmp", 928, 134, 8, 0.20f);
    CLIPMANAGER->AddClip("jesse_run_left", "jesse/jesse_run_left.bmp", 928, 134, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("jesse_block_right", "jesse/jesse_block_right.bmp", 276, 136, 3, 0.20f);
    CLIPMANAGER->AddClip("jesse_block_left", "jesse/jesse_block_left.bmp", 276, 136, 3, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("jesse_hit_right", "jesse/jesse_hit_right.bmp", 470, 128, 5, 0.20f);
    CLIPMANAGER->AddClip("jesse_hit_left", "jesse/jesse_hit_left.bmp", 470, 128, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("jesse_kick_right", "jesse/jesse_kick_right.bmp", 1092, 116, 7, 0.20f);
    CLIPMANAGER->AddClip("jesse_kick_left", "jesse/jesse_kick_left.bmp", 1092, 116, 7, 0.20f);
    // ATTACK
    CLIPMANAGER->AddClip("jesse_attack_right", "jesse/jesse_attack_right.bmp", 924, 126, 7, 0.20f);
    CLIPMANAGER->AddClip("jesse_attack_left", "jesse/jesse_attack_left.bmp", 924, 126, 7, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("jesse_die_right", "jesse/jesse_die_right.bmp", 1680, 114, 12, 0.20f);
    CLIPMANAGER->AddClip("jesse_die_left", "jesse/jesse_die_left.bmp", 1680, 114, 12, 0.20f);

    /* LEE CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("lee_idle_right", "lee/lee_idle_right.bmp", 800, 132, 8, 0.20f);
    CLIPMANAGER->AddClip("lee_idle_left", "lee/lee_idle_left.bmp", 800, 132, 8, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("lee_walk_right", "lee/lee_walk_right.bmp", 576, 138, 6, 0.20f);
    CLIPMANAGER->AddClip("lee_walk_left", "lee/lee_walk_left.bmp", 576, 138, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("lee_run_right", "lee/lee_run_right.bmp", 864, 144, 8, 0.20f);
    CLIPMANAGER->AddClip("lee_run_left", "lee/lee_run_left.bmp", 864, 144, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("lee_block_right", "lee/lee_block_right.bmp", 88, 132, 1, 0.20f);
    CLIPMANAGER->AddClip("lee_block_left", "lee/lee_block_left.bmp", 88, 132, 1, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("lee_hit_right", "lee/lee_hit_right.bmp", 550, 134, 5, 0.20f);
    CLIPMANAGER->AddClip("lee_hit_left", "lee/lee_hit_left.bmp", 550, 134, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("lee_kick_right", "lee/lee_kick_right.bmp", 1050, 136, 7, 0.20f);
    CLIPMANAGER->AddClip("lee_kick_left", "lee/lee_kick_left.bmp", 1050, 136, 7, 0.20f);
    // ATTACK 1
    CLIPMANAGER->AddClip("lee_attack1_right", "lee/lee_attack1_right.bmp", 560, 128, 4, 0.20f);
    CLIPMANAGER->AddClip("lee_attack1_left", "lee/lee_attack1_left.bmp", 560, 128, 4, 0.20f);
    // ATTACK 2
    CLIPMANAGER->AddClip("lee_attack2_right", "lee/lee_attack2_right.bmp", 568, 132, 4, 0.20f);
    CLIPMANAGER->AddClip("lee_attack2_left", "lee/lee_attack2_left.bmp", 568, 132, 4, 0.20f);
    // ATTACK 3
    CLIPMANAGER->AddClip("lee_attack3_right", "lee/lee_attack3_right.bmp", 672, 156, 7, 0.20f);
    CLIPMANAGER->AddClip("lee_attack3_left", "lee/lee_attack3_left.bmp", 672, 156, 7, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("lee_die_right", "lee/lee_die_right.bmp", 2072, 172, 14, 0.20f);
    CLIPMANAGER->AddClip("lee_die_left", "lee/lee_die_left.bmp", 2072, 172, 14, 0.20f);

	/* LUKE CLIP MANAGER */
// IDLE
	CLIPMANAGER->AddClip("luke_idle_right", "luke/luke_idle_right.bmp", 800, 128, 8, 0.20f);
	CLIPMANAGER->AddClip("luke_idle_left", "luke/luke_idle_left.bmp", 800, 128, 8, 0.20f);
	// WALK
	CLIPMANAGER->AddClip("luke_walk_right", "luke/luke_walk_right.bmp", 564, 136, 6, 0.20f);
	CLIPMANAGER->AddClip("luke_walk_left", "luke/luke_walk_left.bmp", 564, 136, 6, 0.20f);
	// RUN
	CLIPMANAGER->AddClip("luke_run_right", "luke/luke_run_right.bmp", 880, 130, 8, 0.20f);
	CLIPMANAGER->AddClip("luke_run_left", "luke/luke_run_left.bmp", 880, 130, 8, 0.20f);
	// BLOCK
	CLIPMANAGER->AddClip("luke_block_right", "luke/luke_block_right.bmp", 264, 128, 3, 0.20f);
	CLIPMANAGER->AddClip("luke_block_left", "luke/luke_block_left.bmp", 264, 128, 3, 0.20f);
	// HIT
	CLIPMANAGER->AddClip("luke_hit_right", "luke/luke_hit_right.bmp", 600, 130, 5, 0.20f);
	CLIPMANAGER->AddClip("luke_hit_left", "luke/luke_hit_left.bmp", 600, 130, 5, 0.20f);
	// KICK
	CLIPMANAGER->AddClip("luke_kick_right", "luke/luke_kick_right.bmp", 1050, 134, 7, 0.20f);
	CLIPMANAGER->AddClip("luke_kick_left", "luke/luke_kick_left.bmp", 1050, 134, 7, 0.20f);
	// ATTACK 1
	CLIPMANAGER->AddClip("luke_attack1_right", "luke/luke_attack1_right.bmp", 560, 134, 4, 0.20f);
	CLIPMANAGER->AddClip("luke_attack1_left", "luke/luke_attack1_left.bmp", 560, 134, 4, 0.20f);
	// ATTACK 2
	CLIPMANAGER->AddClip("luke_attack2_right", "luke/luke_attack2_right.bmp", 568, 132, 4, 0.20f);
	CLIPMANAGER->AddClip("luke_attack2_left", "luke/luke_attack2_left.bmp", 568, 132, 4, 0.20f);
	// ATTACK 3
	CLIPMANAGER->AddClip("luke_attack3_right", "luke/luke_attack3_right.bmp", 832, 170, 8, 0.20f);
	CLIPMANAGER->AddClip("luke_attack3_left", "luke/luke_attack3_left.bmp", 832, 170, 8, 0.20f);
	// DIE
	CLIPMANAGER->AddClip("luke_die_right", "luke/luke_die_right.bmp", 2100, 172, 14, 0.20f);
	CLIPMANAGER->AddClip("luke_die_left", "luke/luke_die_left.bmp", 2100, 172, 14, 0.20f);
    /* MIKE CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("mike_idle_right", "mike/mike_idle_right.bmp", 798, 134, 8, 0.20f);
    CLIPMANAGER->AddClip("mike_idle_left", "mike/mike_idle_left.bmp", 798, 134, 8, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("mike_walk_right", "mike/mike_walk_right.bmp", 564, 134, 6, 0.20f);
    CLIPMANAGER->AddClip("mike_walk_left", "mike/mike_walk_left.bmp", 564, 134, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("mike_run_right", "mike/mike_run_right.bmp", 880, 146, 8, 0.20f);
    CLIPMANAGER->AddClip("mike_run_left", "mike/mike_run_left.bmp", 880, 146, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("mike_block_right", "mike/mike_block_right.bmp", 282, 124, 3, 0.20f);
    CLIPMANAGER->AddClip("mike_block_left", "mike/mike_block_left.bmp", 282, 124, 3, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("mike_hit_right", "mike/mike_hit_right.bmp", 550, 126, 5, 0.20f);
    CLIPMANAGER->AddClip("mike_hit_left", "mike/mike_hit_left.bmp", 550, 126, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("mike_kick_right", "mike/mike_kick_right.bmp", 1064, 130, 7, 0.20f);
    CLIPMANAGER->AddClip("mike_kick_left", "mike/mike_kick_left.bmp", 1064, 130, 7, 0.20f);
    // ATTACK 1
    CLIPMANAGER->AddClip("mike_attack1_right", "mike/mike_attack1_right.bmp", 560, 124, 4, 0.20f);
    CLIPMANAGER->AddClip("mike_attack1_left", "mike/mike_attack1_left.bmp", 560, 124, 4, 0.20f);
    // ATTACK 2
    CLIPMANAGER->AddClip("mike_attack2_right", "mike/mike_attack2_right.bmp", 560, 136, 4, 0.20f);
    CLIPMANAGER->AddClip("mike_attack2_left", "mike/mike_attack2_left.bmp", 560, 136, 4, 0.20f);
    // ATTACK 3
    CLIPMANAGER->AddClip("mike_attack3_right", "mike/mike_attack3_right.bmp", 816, 170, 8, 0.20f);
    CLIPMANAGER->AddClip("mike_attack3_left", "mike/mike_attack3_left.bmp", 816, 170, 8, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("mike_die_right", "mike/mike_die_right.bmp", 2352, 172, 14, 0.20f);
    CLIPMANAGER->AddClip("mike_die_left", "mike/mike_die_left.bmp", 2352, 172, 14, 0.20f);

    /* RICHARD CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("richard_idle_right", "richard/richard_idle_right.bmp", 800, 132, 8, 0.20f);
    CLIPMANAGER->AddClip("richard_idle_left", "richard/richard_idle_left.bmp", 800, 132, 8, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("richard_walk_right", "richard/richard_walk_right.bmp", 588, 136, 6, 0.20f);
    CLIPMANAGER->AddClip("richard_walk_left", "richard/richard_walk_left.bmp", 588, 136, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("richard_run_right", "richard/richard_run_right.bmp", 864, 148, 8, 0.20f);
    CLIPMANAGER->AddClip("richard_run_left", "richard/richard_run_left.bmp", 864, 148, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("richard_block_right", "richard/richard_block_right.bmp", 270, 132, 3, 0.20f);
    CLIPMANAGER->AddClip("richard_block_left", "richard/richard_block_left.bmp", 270, 132, 3, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("richard_hit_right", "richard/richard_hit_right.bmp", 540, 132, 5, 0.20f);
    CLIPMANAGER->AddClip("richard_hit_left", "richard/richard_hit_left.bmp", 540, 132, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("richard_kick_right", "richard/richard_kick_right.bmp", 1036, 144, 7, 0.20f);
    CLIPMANAGER->AddClip("richard_kick_left", "richard/richard_kick_left.bmp", 1036, 144, 7, 0.20f);
    // ATTACK 1
    CLIPMANAGER->AddClip("richard_attack1_right", "richard/richard_attack1_right.bmp", 560, 130, 4, 0.20f);
    CLIPMANAGER->AddClip("richard_attack1_left", "richard/richard_attack1_left.bmp", 560, 130, 4, 0.20f);
    // ATTACK 2
    CLIPMANAGER->AddClip("richard_attack2_right", "richard/richard_attack2_right.bmp", 576, 138, 4, 0.20f);
    CLIPMANAGER->AddClip("richard_attack2_left", "richard/richard_attack2_left.bmp", 576, 138, 4, 0.20f);
    // ATTACK 3
    CLIPMANAGER->AddClip("richard_attack3_right", "richard/richard_attack3_right.bmp", 848, 166, 8, 0.20f);
    CLIPMANAGER->AddClip("richard_attack3_left", "richard/richard_attack3_left.bmp", 848, 166, 8, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("richard_die_right", "richard/richard_die_right.bmp", 2072, 172, 14, 0.20f);
    CLIPMANAGER->AddClip("richard_die_left", "richard/richard_die_left.bmp", 2072, 172, 14, 0.20f);

	/*Doberman CLIP MANAGER*/
	CLIPMANAGER->AddClip("doberman_idle_left", "doberman/idle_left.bmp", 656, 96, 4, 0.3f);
	CLIPMANAGER->AddClip("doberman_idle_right", "doberman/idle_right.bmp", 656, 96, 4, 0.3f);
	CLIPMANAGER->AddClip("doberman_move_left", "doberman/move_left.bmp", 1146, 96, 6, 0.2f);
	CLIPMANAGER->AddClip("doberman_move_right", "doberman/move_right.bmp", 1146, 96, 6, 0.2f);
	CLIPMANAGER->AddClip("doberman_attack_left", "doberman/attack_left.bmp", 1075, 96, 7, 0.2f);
	CLIPMANAGER->AddClip("doberman_attack_right", "doberman/attack_right.bmp", 1075, 96, 7, 0.2f);
	CLIPMANAGER->AddClip("doberman_hit_left", "doberman/hit_left.bmp", 664, 160, 4, 0.2f);
	CLIPMANAGER->AddClip("doberman_hit_right", "doberman/hit_right.bmp", 664, 160, 4, 0.2f);

	/*malcolm*/
	CLIPMANAGER->AddClip("malcolm_idle_left", "malcolm/malcolm_idle_left.bmp", 456, 159, 4, 0.3f);
	CLIPMANAGER->AddClip("malcolm_idle_right", "malcolm/malcolm_idle_right.bmp", 456, 159, 4, 0.3f);
	CLIPMANAGER->AddClip("malcolm_move_left", "malcolm/malcolm_move_left.bmp", 832, 164, 8, 0.3f);
	CLIPMANAGER->AddClip("malcolm_move_right", "malcolm/malcolm_move_right.bmp", 832, 164, 8, 0.2f);
	CLIPMANAGER->AddClip("malcolm_run_left", "malcolm/malcolm_run_left.bmp", 1320, 158, 8, 0.2f);
	CLIPMANAGER->AddClip("malcolm_run_right", "malcolm/malcolm_run_right.bmp", 1320, 158, 8, 0.2f);
	CLIPMANAGER->AddClip("malcolm_attack_left", "malcolm/malcolm_attack_left.bmp", 1638, 174, 9, 0.2f);
	CLIPMANAGER->AddClip("malcolm_attack_right", "malcolm/malcolm_attack_right.bmp", 1638, 174, 9, 0.2f);
	CLIPMANAGER->AddClip("malcolm_kick_left", "malcolm/malcolm_kick_left.bmp", 1050, 159, 5, 0.2f);
	CLIPMANAGER->AddClip("malcolm_kick_right", "malcolm/malcolm_kick_right.bmp", 1050, 159, 5, 0.2f);
	CLIPMANAGER->AddClip("malcolm_block_left", "malcolm/malcolm_block_left.bmp", 214, 154, 2, 0.2f);
	CLIPMANAGER->AddClip("malcolm_block_right", "malcolm/malcolm_block_right.bmp", 214, 154, 2, 0.2f);
	CLIPMANAGER->AddClip("malcolm_hit_left", "malcolm/malcolm_hit_left.bmp", 576, 158, 4, 0.2f);
	CLIPMANAGER->AddClip("malcolm_hit_right", "malcolm/malcolm_hit_right.bmp", 576, 158, 4, 0.2f);

	/*william*/
	CLIPMANAGER->AddClip("william_idle_left", "william/william_idle_left.bmp", 488, 146, 4, 0.3f);
	CLIPMANAGER->AddClip("william_idle_right", "william/william_idle_right.bmp", 488, 146, 4, 0.3f);
	CLIPMANAGER->AddClip("william_move_left", "william/william_move_left.bmp", 1160, 144, 8, 0.3f);
	CLIPMANAGER->AddClip("william_move_right", "william/william_move_right.bmp", 1160, 144, 8, 0.3f);
	CLIPMANAGER->AddClip("william_attack_left", "william/william_attack_left.bmp", 2024, 138, 11, 0.2f);
	CLIPMANAGER->AddClip("william_attack_right", "william/william_attack_right.bmp", 2024, 138, 11, 0.2f);
	CLIPMANAGER->AddClip("william_belly_left", "william/william_belly_left.bmp", 952, 134, 7, 0.2f);
	CLIPMANAGER->AddClip("william_belly_right", "william/william_belly_right.bmp", 952, 134, 7, 0.2f);
	CLIPMANAGER->AddClip("william_block_left", "william/william_block_left.bmp", 198, 131, 2, 0.2f);
	CLIPMANAGER->AddClip("william_block_right", "william/william_block_right.bmp", 198, 131, 2, 0.2f);
	CLIPMANAGER->AddClip("william_hit_left", "william/william_hit_left.bmp", 429, 148, 4, 0.3f);
	CLIPMANAGER->AddClip("william_hit_right", "william/william_hit_right.bmp", 429, 148, 4, 0.3f);
}

void StartScene::EffectClipInit()
{
	CLIPMANAGER->AddClip("ground_effect", "effect/ground_effect.bmp", 671, 65, 4, 0.12f);
	CLIPMANAGER->AddClip("run_or_break_effect_right", "effect/run_or_break_effect_right.bmp", 411, 50, 6, 0.12f);
	CLIPMANAGER->AddClip("run_or_break_effect_left", "effect/run_or_break_effect_left.bmp", 411, 50, 6, 0.12f);
	CLIPMANAGER->AddClip("attack_effect", "effect/attack_effect.bmp", 660, 145, 5, 0.12f);
	CLIPMANAGER->AddClip("block_effect", "effect/block_effect.bmp", 725, 145, 5, 0.12f);
}
