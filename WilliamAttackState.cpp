#include "stdafx.h"
#include "WilliamAttackState.h"
#include "WilliamIdleState.h"

EnemyState * WilliamAttackState::Update(EnemyAI * enemy)
{
	if (enemy->animator->GetEnd()==true)
	{
		return new WilliamIdleState();
	}
	return nullptr;
}

void WilliamAttackState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir()==false)
	{
		enemy->ChangeClip("william_attack_right",true);
	}
	else
	{
		enemy->ChangeClip("william_attack_left",true);
	}
}

void WilliamAttackState::Exit(EnemyAI * enemy)
{
}
