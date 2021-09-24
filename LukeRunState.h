#pragma once
#include "EnemyState.h"

class LukeRunState : public EnemyState
{
private:
	
	float _speed;
	/* 210730 리팩토링 by 대영 */
	int _runFlag;
	float _runningTime;
	float _runLimitTime;
	float _runAngle;

public:
	virtual EnemyState* Update(EnemyAI* enemy);
	virtual void Enter(EnemyAI* enemy);
	virtual void Exit(EnemyAI* enemy);
};