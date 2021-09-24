#include "stdafx.h"
#include "JesseHitState.h"
#include "JesseIdleState.h"

EnemyState* JesseHitState::Update(EnemyAI* enemy)
{
	if (enemy->animator->GetEnd())
	{
		return new JesseIdleState();
	}
	return nullptr;
}

void JesseHitState::Enter(EnemyAI* enemy)
{
	enemy->hitState = new JesseHitState();
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("jesse_hit_right", true);
	else
		enemy->ChangeClip("jesse_hit_left", true);
}

void JesseHitState::Exit(EnemyAI* enemy)
{
}
