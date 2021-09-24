#pragma once
#include "EnemyState.h"

class LukeAttack3State : public EnemyState
{
private:

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

