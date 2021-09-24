#pragma once
#include <vector>

using namespace std;

class SceneInfoLoader
{
private:
	vector<GameObject*>* _sceneObjectV;
	vector<int> _typeV;
public:
	void SetLinkObjectVAddress(vector<GameObject*>* _objectVAddress) { _sceneObjectV = _objectVAddress; }
	void LoadObjectInfo();
	void LoadObjectInfo(int type);
	GameObject* MakeObject(float x, float y, int type);
	GameObject* MakeSnow1(float x, float y);
	GameObject* MakeSnow2(float x, float y);
	GameObject* MakeFencePillar(float x, float y);
	GameObject* MakeFencePillar2(float x, float y);
	GameObject* MakeGuardRail(float x, float y);
	GameObject* MakeFirePlug(float x, float y);
	GameObject* MakeHorse1(float x, float y);
	GameObject* MakeHorse2(float x, float y);
	GameObject* MakePostbox(float x, float y);
	GameObject* MakeShovel(float x, float y);
	GameObject* MakeSignBoard(float x, float y);
	GameObject* MakeWell(float x, float y);
	GameObject* MakeWood(float x, float y);
	GameObject* MakeLuke(float x, float y);
	GameObject* MakeLukeEditor(float x, float y);
	GameObject* MakeDoberman(float x, float y);
	GameObject* MakeDobermanEditor(float x, float y);
	GameObject* MakeMalcolm(float x, float y);
	GameObject* MakeMalcolmEditor(float x, float y);
	GameObject* MakeWilliam(float x, float y);
	GameObject* MakeWilliamEditor(float x, float y);
	GameObject* MakeJesse(float x, float y);
	GameObject* MakeJesseEditor(float x, float y);
	GameObject* MakeMike(float x, float y);
	GameObject* MakeMikeEditor(float x, float y);
	GameObject* MakeLee(float x, float y);
	GameObject* MakeLeeEditor(float x, float y);
	GameObject* MakeRichard(float x, float y);
	GameObject* MakeRichardEditor(float x, float y);
	vector<int> GetTypeV() const { return _typeV; }
};

