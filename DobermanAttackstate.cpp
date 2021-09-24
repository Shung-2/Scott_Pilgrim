#include "stdafx.h"
#include "DobermanAttackState.h"
#include "DobermanIdleState.h"

EnemyState * DobermanAttackState::Update(EnemyAI * enemy)
{
	_attackTime += TIMEMANAGER->getElapsedTime();
	if (_attackTime >= 2.0f)
	{
		return new DobermanIdleState();
	}

	return nullptr;
}

void DobermanAttackState::Enter(EnemyAI * enemy)
{
	_attackTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("doberman_attack_right", true);
	}
	else
	{
		enemy->ChangeClip("doberman_attack_left", true);
	}

}

void DobermanAttackState::Exit(EnemyAI * enemy)
{
}
