#include "stdafx.h"
#include "RichardHitState.h"
#include "RichardIdleState.h"

EnemyState* RichardHitState::Update(EnemyAI* enemy)
{
	if (enemy->animator->GetEnd())
	{
		return new RichardIdleState();
	}
	return nullptr;
}

void RichardHitState::Enter(EnemyAI* enemy)
{
	enemy->hitState = new RichardHitState();

	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("richard_hit_right", true);
	else
		enemy->ChangeClip("richard_hit_left", true);
}

void RichardHitState::Exit(EnemyAI* enemy)
{
}
