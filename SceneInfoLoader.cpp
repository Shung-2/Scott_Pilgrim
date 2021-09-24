#include "stdafx.h"
#include "SceneInfoLoader.h"

void SceneInfoLoader::LoadObjectInfo()
{
	vector<string> objectStringInfo = TXTDATAMANAGER->txtLoad("scene_info.txt");
	_typeV.clear();
	for (int i = 0; i < objectStringInfo.size() / 3; i++) {
		int x = atoi(objectStringInfo[i * 3].c_str());
		int y = atoi(objectStringInfo[i * 3 + 1].c_str());
		int objectType = atoi(objectStringInfo[i * 3 + 2].c_str());
		_sceneObjectV->push_back(MakeObject(x, y, objectType));
		_typeV.push_back(objectType);
	}
}

void SceneInfoLoader::LoadObjectInfo(int type)
{
	vector<string> objectStringInfo = TXTDATAMANAGER->txtLoad("scene_info.txt");
	_typeV.clear();
	for (int i = 0; i < objectStringInfo.size() / 3; i++) {
		int x = atoi(objectStringInfo[i * 3].c_str());
		int y = atoi(objectStringInfo[i * 3 + 1].c_str());
		int objectType = atoi(objectStringInfo[i * 3 + 2].c_str());
		if (objectType != type) continue;
		_sceneObjectV->push_back(MakeObject(x, y, objectType));
		_typeV.push_back(type);
	}
}

GameObject* SceneInfoLoader::MakeObject(float x, float y, int type)
{
	GameObject* newObject = nullptr;
	switch (type) {
	case 0:
		newObject = MakeSnow1(x, y);
		break;
	case 1:
		newObject = MakeSnow2(x, y);
		break;
	case 2:
		newObject = MakeFencePillar(x, y);
		break;
	case 3:
		newObject = MakeFencePillar2(x, y);
		break;
	case 4:
		newObject = MakeGuardRail(x, y);
		break;
	case 5:
		newObject = MakeFirePlug(x, y);
		break;
	case 6:
		newObject = MakeHorse1(x, y);
		break;
	case 7:
		newObject = MakeHorse2(x, y);
		break;
	case 8:
		newObject = MakePostbox(x, y);
		break;
	case 9:
		newObject = MakeShovel(x, y);
		break;
	case 10:
		newObject = MakeSignBoard(x, y);
		break;
	case 11:
		newObject = MakeWell(x, y);
		break;
	case 12:
		newObject = MakeWood(x, y);
		break;
	case 13:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeLuke(x, y);
		else
			newObject = MakeLukeEditor(x, y);
		break;
	case 14:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeDoberman(x, y);
		else
			newObject = MakeDobermanEditor(x, y);
		break;
	case 15:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeMalcolm(x, y);
		else
			newObject = MakeMalcolmEditor(x, y);
		break;
	case 16:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeWilliam(x, y);
		else
			newObject = MakeWilliamEditor(x, y);
		break;
	case 17:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeJesse(x, y);
		else
			newObject = MakeJesseEditor(x, y);
		break;
	case 18:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeMike(x, y);
		else
			newObject = MakeMikeEditor(x, y);
		break;
	case 19:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeLee(x, y);
		else
			newObject = MakeLeeEditor(x, y);
		break;
	case 20:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeRichard(x, y);
		else
			newObject = MakeRichardEditor(x, y);
		break;
	}
	return newObject;
}

GameObject* SceneInfoLoader::MakeSnow1(float x, float y)
{
	GameObject* snow = new GameObject();
	snow->transform->SetPosition(x, y);
	snow->AddComponent(new Renderer());
	snow->GetComponent<Renderer>()->Init("map/snow1.bmp", 108, 44);
	snow->AddComponent(new ZOrder());
	snow->GetComponent<ZOrder>()->Init();
	snow->GetComponent<ZOrder>()->SetZ(snow->transform->GetY() + 22);
	return snow;
}

GameObject* SceneInfoLoader::MakeSnow2(float x, float y)
{
	GameObject* snow2 = new GameObject();
	snow2->transform->SetPosition(x, y);
	snow2->AddComponent(new Renderer());
	snow2->GetComponent<Renderer>()->Init("map/snow2.bmp", 164, 62);
	snow2->AddComponent(new ZOrder());
	snow2->GetComponent<ZOrder>()->Init();
	snow2->GetComponent<ZOrder>()->SetZ(snow2->transform->GetY() + 31);
	return snow2;
}

GameObject* SceneInfoLoader::MakeFencePillar(float x, float y)
{
	GameObject* fencePillar = new GameObject();
	fencePillar->transform->SetPosition(x, y);
	fencePillar->AddComponent(new Renderer());
	fencePillar->GetComponent<Renderer>()->Init("map/fence_pillar.bmp", 114, 168);
	fencePillar->AddComponent(new ZOrder());
	fencePillar->GetComponent<ZOrder>()->Init();
	fencePillar->GetComponent<ZOrder>()->SetZ(fencePillar->transform->GetY() + 84);
	return fencePillar;
}

GameObject* SceneInfoLoader::MakeFencePillar2(float x, float y)
{
	GameObject* fencePillar2 = new GameObject();
	fencePillar2->transform->SetPosition(x, y);
	fencePillar2->AddComponent(new Renderer());
	fencePillar2->GetComponent<Renderer>()->Init("map/fence_pillar2.bmp", 114, 156);
	fencePillar2->AddComponent(new ZOrder());
	fencePillar2->GetComponent<ZOrder>()->Init();
	fencePillar2->GetComponent<ZOrder>()->SetZ(fencePillar2->transform->GetY() + 78);
	return fencePillar2;
}

GameObject* SceneInfoLoader::MakeGuardRail(float x, float y)
{
	GameObject* guardRail = new GameObject();
	guardRail->transform->SetPosition(x, y);
	guardRail->AddComponent(new Renderer());
	guardRail->GetComponent<Renderer>()->Init("map/guardrail.bmp", 106, 112);
	guardRail->AddComponent(new ZOrder());
	guardRail->GetComponent<ZOrder>()->Init();
	guardRail->GetComponent<ZOrder>()->SetZ(guardRail->transform->GetY() + 56);
	return guardRail;
}

GameObject* SceneInfoLoader::MakeFirePlug(float x, float y)
{
	GameObject* firePlug = new GameObject();
	firePlug->transform->SetPosition(x, y);
	firePlug->AddComponent(new Renderer());
	firePlug->GetComponent<Renderer>()->Init("map/fireplug.bmp", 98, 100);
	firePlug->AddComponent(new ZOrder());
	firePlug->GetComponent<ZOrder>()->Init();
	firePlug->GetComponent<ZOrder>()->SetZ(firePlug->transform->GetY() + 50);
	return firePlug;
}

GameObject* SceneInfoLoader::MakeHorse1(float x, float y)
{
	GameObject* horse1 = new GameObject();
	horse1->transform->SetPosition(x, y);
	horse1->AddComponent(new Renderer());
	horse1->GetComponent<Renderer>()->Init("map/horse1.bmp", 110, 116);
	horse1->AddComponent(new ZOrder());
	horse1->GetComponent<ZOrder>()->Init();
	horse1->GetComponent<ZOrder>()->SetZ(horse1->transform->GetY() + 58);
	return horse1;
}

GameObject* SceneInfoLoader::MakeHorse2(float x, float y)
{
	GameObject* horse2 = new GameObject();
	horse2->transform->SetPosition(x, y);
	horse2->AddComponent(new Renderer());
	horse2->GetComponent<Renderer>()->Init("map/horse2.bmp", 106, 130);
	horse2->AddComponent(new ZOrder());
	horse2->GetComponent<ZOrder>()->Init();
	horse2->GetComponent<ZOrder>()->SetZ(horse2->transform->GetY() + 58);
	return horse2;
}

GameObject* SceneInfoLoader::MakePostbox(float x, float y)
{
	GameObject* postbox = new GameObject();
	postbox->transform->SetPosition(x, y);
	postbox->AddComponent(new Renderer());
	postbox->GetComponent<Renderer>()->Init("map/postbox.bmp", 74, 104);
	postbox->AddComponent(new ZOrder());
	postbox->GetComponent<ZOrder>()->Init();
	postbox->GetComponent<ZOrder>()->SetZ(postbox->transform->GetY() + 52);
	return postbox;
}

GameObject* SceneInfoLoader::MakeShovel(float x, float y)
{
	GameObject* shovel = new GameObject();
	shovel->transform->SetPosition(x, y);
	shovel->AddComponent(new Renderer());
	shovel->GetComponent<Renderer>()->Init("map/shovel.bmp", 52, 94);
	shovel->AddComponent(new ZOrder());
	shovel->GetComponent<ZOrder>()->Init();
	shovel->GetComponent<ZOrder>()->SetZ(shovel->transform->GetY() + 52);
	return shovel;
}

GameObject* SceneInfoLoader::MakeSignBoard(float x, float y)
{
	GameObject* signBoard = new GameObject();
	signBoard->transform->SetPosition(x, y);
	signBoard->AddComponent(new Renderer());
	signBoard->GetComponent<Renderer>()->Init("map/signboard.bmp", 108, 102);
	signBoard->AddComponent(new ZOrder());
	signBoard->GetComponent<ZOrder>()->Init();
	signBoard->GetComponent<ZOrder>()->SetZ(signBoard->transform->GetY() + 51);
	return signBoard;
}

GameObject* SceneInfoLoader::MakeWell(float x, float y)
{
	GameObject* well = new GameObject();
	well->transform->SetPosition(x, y);
	well->AddComponent(new Renderer());
	well->GetComponent<Renderer>()->Init("map/well.bmp", 106, 82);
	well->AddComponent(new ZOrder());
	well->GetComponent<ZOrder>()->Init();
	well->GetComponent<ZOrder>()->SetZ(well->transform->GetY() + 41);
	well->AddComponent(new Ground());
	well->GetComponent<Ground>()->Init(106, 10, 0, -35);
	return well;
}

GameObject* SceneInfoLoader::MakeWood(float x, float y)
{
	GameObject* wood = new GameObject();
	wood->transform->SetPosition(x, y);
	wood->AddComponent(new Renderer());
	wood->GetComponent<Renderer>()->Init("map/wood.bmp", 370, 74);
	wood->AddComponent(new ZOrder());
	wood->GetComponent<ZOrder>()->Init();
	wood->GetComponent<ZOrder>()->SetZ(wood->transform->GetY() + 37);
	wood->AddComponent(new Ground());
	wood->GetComponent<Ground>()->Init(370, 10, 0, -25);
	return wood;
}

GameObject* SceneInfoLoader::MakeLuke(float x, float y)
{
	GameObject* luke = new Luke();
	luke->transform->SetPosition(x, y);
	luke->SetActive(false);
	luke->Init();
	return luke;
}

GameObject* SceneInfoLoader::MakeLukeEditor(float x, float y)
{
	GameObject* demoLuke = new GameObject();
	demoLuke->transform->SetPosition(x, y);
	demoLuke->AddComponent(new Renderer());
	demoLuke->GetComponent<Renderer>()->Init("luke/luke.bmp", 96, 128);
	demoLuke->AddComponent(new ZOrder());
	demoLuke->GetComponent<ZOrder>()->Init();
	demoLuke->GetComponent<ZOrder>()->SetZ(demoLuke->transform->GetY() + 64);
	return demoLuke;
}

GameObject* SceneInfoLoader::MakeDoberman(float x, float y)
{
	GameObject* doberman = new Doberman();
	doberman->transform->SetPosition(x, y);
	doberman->SetActive(false);
	doberman->Init();
	return doberman;
}

GameObject* SceneInfoLoader::MakeDobermanEditor(float x, float y)
{
	GameObject* demoDoberman = new GameObject();
	demoDoberman->transform->SetPosition(x, y);
	demoDoberman->AddComponent(new Renderer());
	demoDoberman->GetComponent<Renderer>()->Init("doberman/doberman.bmp", 164, 96);
	demoDoberman->AddComponent(new ZOrder());
	demoDoberman->GetComponent<ZOrder>()->Init();
	demoDoberman->GetComponent<ZOrder>()->SetZ(demoDoberman->transform->GetY() + 48);
	return demoDoberman;
}

GameObject* SceneInfoLoader::MakeMalcolm(float x, float y)
{
	GameObject* malcolm = new Malcolm();
	malcolm->transform->SetPosition(x, y);
	malcolm->SetActive(false);
	malcolm->Init();
	return malcolm;
}

GameObject* SceneInfoLoader::MakeMalcolmEditor(float x, float y)
{
	GameObject* demoMalcolm = new GameObject();
	demoMalcolm->transform->SetPosition(x, y);
	demoMalcolm->AddComponent(new Renderer());
	demoMalcolm->GetComponent<Renderer>()->Init("malcolm/malcolm.bmp", 114, 159);
	demoMalcolm->AddComponent(new ZOrder());
	demoMalcolm->GetComponent<ZOrder>()->Init();
	demoMalcolm->GetComponent<ZOrder>()->SetZ(demoMalcolm->transform->GetY() + 79);
	return demoMalcolm;
}

GameObject* SceneInfoLoader::MakeWilliam(float x, float y)
{
	GameObject* william = new William();
	william->transform->SetPosition(x, y);
	william->SetActive(false);
	william->Init();
	return william;
}

GameObject* SceneInfoLoader::MakeWilliamEditor(float x, float y)
{
	GameObject* demoWilliam = new GameObject();
	demoWilliam->transform->SetPosition(x, y);
	demoWilliam->AddComponent(new Renderer());
	demoWilliam->GetComponent<Renderer>()->Init("william/william.bmp", 122, 146);
	demoWilliam->AddComponent(new ZOrder());
	demoWilliam->GetComponent<ZOrder>()->Init();
	demoWilliam->GetComponent<ZOrder>()->SetZ(demoWilliam->transform->GetY() + 73);
	return demoWilliam;
}

GameObject* SceneInfoLoader::MakeJesse(float x, float y)
{
	GameObject* jesse = new Jesse();
	jesse->transform->SetPosition(x, y);
	jesse->SetActive(false);
	jesse->Init();
	return jesse;
}

GameObject* SceneInfoLoader::MakeJesseEditor(float x, float y)
{
	GameObject* jesse = new GameObject();
	jesse->transform->SetPosition(x, y);
	jesse->AddComponent(new Renderer());
	jesse->GetComponent<Renderer>()->Init("jesse/jesse.bmp", 90, 132);
	jesse->AddComponent(new ZOrder());
	jesse->GetComponent<ZOrder>()->Init();
	jesse->GetComponent<ZOrder>()->SetZ(jesse->transform->GetY() + 66);
	return jesse;
}

GameObject* SceneInfoLoader::MakeMike(float x, float y)
{
	GameObject* mike = new Mike();
	mike->transform->SetPosition(x, y);
	mike->SetActive(false);
	mike->Init();
	return mike;
}

GameObject* SceneInfoLoader::MakeMikeEditor(float x, float y)
{
	GameObject* mike = new GameObject();
	mike->transform->SetPosition(x, y);
	mike->AddComponent(new Renderer());
	mike->GetComponent<Renderer>()->Init("mike/mike.bmp", 110, 134);
	mike->AddComponent(new ZOrder());
	mike->GetComponent<ZOrder>()->Init();
	mike->GetComponent<ZOrder>()->SetZ(mike->transform->GetY() + 67);
	return mike;
}

GameObject* SceneInfoLoader::MakeLee(float x, float y)
{
	GameObject* lee = new Lee();
	lee->transform->SetPosition(x, y);
	lee->SetActive(false);
	lee->Init();
	return lee;
}

GameObject* SceneInfoLoader::MakeLeeEditor(float x, float y)
{
	GameObject* lee = new GameObject();
	lee->transform->SetPosition(x, y);
	lee->AddComponent(new Renderer());
	lee->GetComponent<Renderer>()->Init("lee/lee.bmp", 100, 132);
	lee->AddComponent(new ZOrder());
	lee->GetComponent<ZOrder>()->Init();
	lee->GetComponent<ZOrder>()->SetZ(lee->transform->GetY() + 66);
	return lee;
}

GameObject* SceneInfoLoader::MakeRichard(float x, float y)
{
	GameObject* richard = new Richard();
	richard->transform->SetPosition(x, y);
	richard->SetActive(false);
	richard->Init();
	return richard;
}

GameObject* SceneInfoLoader::MakeRichardEditor(float x, float y)
{
	GameObject* richard = new GameObject();
	richard->transform->SetPosition(x, y);
	richard->AddComponent(new Renderer());
	richard->GetComponent<Renderer>()->Init("richard/richard.bmp", 108, 132);
	richard->AddComponent(new ZOrder());
	richard->GetComponent<ZOrder>()->Init();
	richard->GetComponent<ZOrder>()->SetZ(richard->transform->GetY() + 66);
	return richard;
}
