#include "stdafx.h"
#include "LeeBlockState.h"

EnemyState* LeeBlockState::Update(EnemyAI* enemy)
{
    // TODO BLOCK
    return nullptr;
}

void LeeBlockState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("lee_block_right", true);
	else
		enemy->ChangeClip("lee_block_left", true);
}

void LeeBlockState::Exit(EnemyAI* enemy)
{
}
