#include "stdafx.h"
#include "DobermanHitState.h"
#include "DobermanIdleState.h"

EnemyState * DobermanHitState::Update(EnemyAI * enemy)
{
	_hitTime = TIMEMANAGER->getElapsedTime();
	if (_hitTime >= 2.0f)
	{
		return new DobermanIdleState();
	}

	return nullptr;
}

void DobermanHitState::Enter(EnemyAI * enemy)
{
	_hitTime = 0;
	enemy->hitState = new DobermanHitState();
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("doberman_hit_right", true);
	}
	else
	{
		enemy->ChangeClip("doberman_hit_left", true);
	}
}

void DobermanHitState::Exit(EnemyAI * enemy)
{
}
