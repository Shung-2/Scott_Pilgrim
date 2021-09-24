#pragma once
#include "EnemyState.h"

class LukeIdleState : public EnemyState
{
private:
	bool _isPatrol;
	float _idleTime;
	float _idleMaxTime;
	
public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};