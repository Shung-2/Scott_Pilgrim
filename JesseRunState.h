#pragma once
#include "EnemyState.h"

class JesseRunState : public EnemyState
{
private:
	float _speed;
public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};