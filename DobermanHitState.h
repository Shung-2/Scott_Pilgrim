#pragma once
#include "EnemyState.h"
class DobermanHitState : public EnemyState
{
private:
	float _hitTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

