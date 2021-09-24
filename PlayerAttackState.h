#pragma once
#include "PlayerState.h"
class PlayerAttackState :
	public PlayerState
{

private:
	float _attackTime;		//���� �̹����� ���� ������ Ÿ��
	bool _doubleAttack;		//�ι�° ���ݿ� ����

public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);
	void Attack(Player* player);
};
