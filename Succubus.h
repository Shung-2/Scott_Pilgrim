#pragma once
#include "Component.h"
class SuccubusState;
class Succubus : public Component
{
private:
	GameObject* _Matthew;
	SuccubusState* _succubusstate;
	float _hp;
	float _speed;

public:
	Succubus();
	~Succubus();
	Animator* animator;
	BoxCollider* collision;
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
	void ChangeClip(string name, bool isInitFrame);
	float GetSpeed() const { return _speed; }
	Transform* GetMatthew() const { return _Matthew->transform; }
	void SetMatthew(GameObject* Matthew) { _Matthew = Matthew; }
};

