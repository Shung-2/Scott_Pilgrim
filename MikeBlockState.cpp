#include "stdafx.h"
#include "MikeBlockState.h"

EnemyState* MikeBlockState::Update(EnemyAI* enemy)
{
	// TODO BLOCK
    return nullptr;
}

void MikeBlockState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("mike_block_right", true);
	else
		enemy->ChangeClip("mike_block_left", true);
}

void MikeBlockState::Exit(EnemyAI* enemy)
{
}
