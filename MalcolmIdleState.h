#pragma once
#include "EnemyState.h"
class MalcolmIdleState : public EnemyState
{
private:
	float _idleTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

