#pragma once
#include "EnemyState.h"
class WilliamBellyState : public EnemyState
{
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

