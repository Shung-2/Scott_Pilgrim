#pragma once
#include "PlayerState.h"
class PlayerAttackState :
	public PlayerState
{

private:
	float _attackTime;		//공격 이미지를 위한 딜레이 타임
	bool _doubleAttack;		//두번째 공격에 들어갈때

public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);
	void Attack(Player* player);
};

