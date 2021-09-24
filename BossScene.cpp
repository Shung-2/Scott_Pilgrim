#include "stdafx.h"
#include "BossScene.h"
#include "Succubus.h"
HRESULT BossScene::Init()
{
	Scene::Init();
	SetBackBufferSize(944, 568);
	MainCam->SetRenderWidth(944);
	MainCam->SetRenderHeight(568);
	MainCam->SetMapSize(944, 568);
	MainCam->transform->SetPosition(944 / 2, 568 / 2);

	background.Init();
	background.renderer->Init("map/boss_room.bmp", 944, 568);
	background.transform->SetPosition(944 / 2, 568 / 2);

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
	character->transform->SetPosition(300, 300);

	matthew = new Character();
	matthew->Init();
	matthew->transform->SetPosition(944 / 2, 568 / 2);
	matthew->collider->isTrigger = true;
	matthew->zOrder->SetZ(matthew->transform->GetX() + 132 / 2);
	matthew->AddComponent(new Matthew());
	matthew->GetComponent<Matthew>()->Init();
	matthew->GetComponent<Matthew>()->SetPlayer(character);
	character->GetComponent<Player>()->boss = matthew;
	for (int i = 0; i < SUCCUBUSMAX; i++)
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

	return S_OK;
}

void BossScene::Release()
{
}

void BossScene::Update()
{
	matthew->Update();
	character->Update();
	background.Update();
	for (int i = 0; i < SUCCUBUSMAX; i++)
	{
		succubus[i]->Update();
	}
}

void BossScene::Render()
{
	background.Render();
	ZORDER->Render();
	MainCam->Render(_hdc);
}
