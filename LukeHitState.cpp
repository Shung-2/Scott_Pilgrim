#include "stdafx.h"
#include "LukeHitState.h"
#include "LukeIdleState.h"

EnemyState* LukeHitState::Update(EnemyAI* enemy)
{
	if (enemy->animator->GetEnd())
	{
		return new LukeIdleState();
	}
	return nullptr;
}

void LukeHitState::Enter(EnemyAI* enemy)
{
	enemy->hitState = new LukeHitState();

	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_hit_right", true);
	else
		enemy->ChangeClip("luke_hit_left", true);
}

void LukeHitState::Exit(EnemyAI* enemy)
{
}
