#include "stdafx.h"
#include "LeeHitState.h"
#include "LeeIdleState.h"

EnemyState* LeeHitState::Update(EnemyAI* enemy)
{
	if (enemy->animator->GetEnd())
	{
		return new LeeIdleState();
	}
	return nullptr;
}

void LeeHitState::Enter(EnemyAI* enemy)
{
	enemy->hitState = new LeeHitState();
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("lee_hit_right", true);
	else
		enemy->ChangeClip("lee_hit_left", true);
}

void LeeHitState::Exit(EnemyAI* enemy)
{
}
