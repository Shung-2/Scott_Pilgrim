#include "stdafx.h"
#include "WilliamHitState.h"
#include "WilliamIdleState.h"

EnemyState * WilliamHitState::Update(EnemyAI * enemy)
{
	if (enemy->animator->GetEnd() == true)
	{
		return new WilliamHitState();
	}
	return nullptr;
}

void WilliamHitState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("william_hit_right",true);
	}
	else
	{
		enemy->ChangeClip("william_hit_left", true);
	}
}
void WilliamHitState::Exit(EnemyAI * enemy)
{
}
