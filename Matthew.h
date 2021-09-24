#pragma once
#include "Component.h"
#define SUCCUBUSMAX 4
class Matthewstate;
class Matthew : public Component
{
private:
	Matthewstate* _matthewstate;
	
	int _hp;
	float _speed;
	int _damage;
	float _gravity;
	bool _dir;

public:
	Matthew();
	~Matthew();
	GameObject* _player;
	GameObject* _succubus[SUCCUBUSMAX];
	Animator* animator;
	BoxCollider* collision;
	ZOrder* zOrder;
	int _attackTime;
	float _phaseTime;
	float jumpPower;
	int hitCount;
	bool hitable;
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
	void ChangeCilp(string name, bool isInitFrame);
	bool Getdir() const { return _dir; }
	void Setdir(bool dir) { _dir = dir; }
	float GetSpeed() const { return _speed; }
	int GetHp(){ return _hp; }
	int GetGravity() const { return _gravity; }
	void Sethp(int hp) { _hp = hp; }
	int GetDamage()const { return _damage; }
	void SetDamage(int damage) { _damage = damage; }
	Transform* GetPlayer() const { return _player->transform; }

	void SetPlayer(GameObject* player) { _player = player; }

	void Hit(int damage);
};

