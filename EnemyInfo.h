#pragma once
#include "Component.h"
class Player;

class EnemyInfo : public Component
{
private:
	bool _dir;		// 방향 | FALSE == RIGHT, TRUE == LEFT
	int _hp;		// 체력

	/* 210730 리팩토링 by 대영
	1. 공격할 때 마다 데미지 변경하기 */
	int _minDamage;	// 최소 공격력
	int _maxDamage; // 최대 공격력
	//-------------------------------

	float _speed;	// 속도
	string _name;

public:	
	virtual void Init();

	bool GetDir() const { return _dir; }
	void SetDir(bool dir) { _dir = dir; }

	int GetHp() { return _hp; }
	void Sethp(int hp) { _hp = hp; }

	/* 210730 리팩토링 by 대영
	1. 공격할 때 마다 데미지 변경하기 */
	int GetMinDamage() const { return _minDamage; }
	void SetMinDamage(int damage) { _minDamage = damage; }

	int GetMaxDamage() const { return _maxDamage; }
	void SetMaxDamage(int damage) { _maxDamage = damage; }
	//-------------------------------

	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	void SetName(string name) { _name = name; }
	string GetName() const { return _name; }

	/* 210629 적 플레이어 충돌 */
	void Hit(int damage);
};