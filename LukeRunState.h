#pragma once
#include "EnemyState.h"

class LukeRunState : public EnemyState
{
private:
	
	float _speed;
	/* 210730 �����丵 by �뿵 */
	int _runFlag;
	float _runningTime;
	float _runLimitTime;
	float _runAngle;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};