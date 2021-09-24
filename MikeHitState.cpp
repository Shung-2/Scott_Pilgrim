#include "stdafx.h"
#include "MikeHitState.h"
#include "MikeIdleState.h"

EnemyState* MikeHitState::Update(EnemyAI* enemy)
{
	if (enemy->animator->GetEnd())
	{
		return new MikeIdleState();
	}
    return nullptr;
}

void MikeHitState::Enter(EnemyAI* enemy)
{
	enemy->hitState = new MikeHitState();

	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("mike_hit_right", true);
	else
		enemy->ChangeClip("mike_hit_left", true);
}

void MikeHitState::Exit(EnemyAI* enemy)
{
}
