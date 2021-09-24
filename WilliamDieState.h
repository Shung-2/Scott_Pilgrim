#pragma once
#include "EnemyState.h"
class WilliamDieState :
    public EnemyState
{
public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

