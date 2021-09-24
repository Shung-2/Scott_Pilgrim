#pragma once
#include "EnemyState.h"
class WilliamHitState : public EnemyState
{
public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

