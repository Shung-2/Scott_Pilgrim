#pragma once
#include "EnemyState.h"

class LeeDieState : public EnemyState
{
private:
	float _speedX;
	float _speedY;
	float _gravity;
	float _dieTime;
public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

