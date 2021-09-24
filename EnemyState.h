#pragma once
#include "Enemy.h"

class EnemyAI;

class EnemyState
{
public:
	virtual EnemyState* Update(EnemyAI* enemy) = 0;
	virtual void Enter(EnemyAI* enemy) = 0;
	virtual void Exit(EnemyAI* enemy) = 0;
};