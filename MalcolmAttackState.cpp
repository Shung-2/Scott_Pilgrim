#include "stdafx.h"
#include "MalcolmAttackState.h"
#include "MalcolmIdleState.h"
#include "MalcolmhitState.h"
#include "MalcolmKickState.h"

EnemyState * MalcolmAttackState::Update(EnemyAI * enemy)
{
	if (enemy->animator->GetEnd()==true)
	{
		return new MalcolmIdleState();
	}
	return nullptr;
}

void MalcolmAttackState::Enter(EnemyAI * enemy)
{
	_attackTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_attack_right", true);
	}
	else
	{
		enemy->ChangeClip("malcolm_attack_left", true);
	}
}

void MalcolmAttackState::Exit(EnemyAI * enemy)
{
}
