#include "stdafx.h"
#include "RichardBlockState.h"

EnemyState* RichardBlockState::Update(EnemyAI* enemy)
{
	// TODO BLOCK
    return nullptr;
}

void RichardBlockState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("richard_block_right", true);
	else
		enemy->ChangeClip("richard_block_left", true);
}

void RichardBlockState::Exit(EnemyAI* enemy)
{
}
