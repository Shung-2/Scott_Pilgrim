#pragma once
#include "EnemyState.h"
class MalcolmKickState :public EnemyState
{
private:
	float _kickTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

