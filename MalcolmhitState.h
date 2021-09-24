#pragma once
#include "EnemyState.h"
class MalcolmHitState :
	public EnemyState
{
private:

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);

};

