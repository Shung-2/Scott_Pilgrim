#pragma once
#include "EnemyState.h"
class JesseWalkState : public EnemyState
{
private:
	float _angle;
	float _moveStartTime;
	float _moveMaxTime;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};

