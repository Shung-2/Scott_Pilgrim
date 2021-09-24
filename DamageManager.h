#pragma once
#define INFO_MAX 20
class DamageManager : public singletonBase<DamageManager>
{
private:
	typedef struct tagDamageInfo {
		float x;
		float y;
		float time;
		bool isActive;
		image* number;
	}INFO;
private:
	float _speed;
	float _activeMaxTime;
	INFO _infoArr[INFO_MAX];
	image* number[10];
public:
	HRESULT Init();
	void Update();
	void Render();
	void Release();
	void CreateDamage(int damage, float x, float y);
};

