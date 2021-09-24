#pragma once
class GameObject;
class BackgroundManager : public singletonBase<BackgroundManager>
{
private:
	vector<GameObject*> _backgroundV;
	int _unitWidth;
	int _margin;
	int _screenSize;
	Transform* _player;
public:
	BackgroundManager() {};
	~BackgroundManager() {};

	HRESULT Init();
	void Update();
	void Render();
	void Release();

	void SetPlayer(Transform* player) { _player = player; }
	void AddBackground(GameObject* gameObject) { _backgroundV.push_back(gameObject); }
	GameObject* GetBackground(int idx) { return _backgroundV[idx]; }

	void SetBackgroundWidth(int width) { _unitWidth = width; }
	int GetBackgroundWidth() { return _unitWidth; }

	void SetMargin(int margin) { _margin = margin; }
	int GetMargin() { return _margin; }
};

