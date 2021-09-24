#pragma once
#include "Component.h"
class Player;

class EnemyInfo : public Component
{
private:
	bool _dir;		// ���� | FALSE == RIGHT, TRUE == LEFT
	int _hp;		// ü��

	/* 210730 �����丵 by �뿵
	1. ������ �� ���� ������ �����ϱ� */
	int _minDamage;	// �ּ� ���ݷ�
	int _maxDamage; // �ִ� ���ݷ�
	//-------------------------------

	float _speed;	// �ӵ�
	string _name;

public:	
	virtual void Init();

	bool GetDir() const { return _dir; }
	void SetDir(bool dir) { _dir = dir; }

	int GetHp() { return _hp; }
	void Sethp(int hp) { _hp = hp; }

	/* 210730 �����丵 by �뿵
	1. ������ �� ���� ������ �����ϱ� */
	int GetMinDamage() const { return _minDamage; }
	void SetMinDamage(int damage) { _minDamage = damage; }

	int GetMaxDamage() const { return _maxDamage; }
	void SetMaxDamage(int damage) { _maxDamage = damage; }
	//-------------------------------

	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { _speed = speed; }

	void SetName(string name) { _name = name; }
	string GetName() const { return _name; }

	/* 210629 �� �÷��̾� �浹 */
	void Hit(int damage);
};