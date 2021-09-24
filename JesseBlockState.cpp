#include "stdafx.h"
#include "JesseBlockState.h"

EnemyState* JesseBlockState::Update(EnemyAI* enemy)
{
    // TODO BLOCK
    return nullptr;
}

void JesseBlockState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("jesse_block_right", true);
	else
		enemy->ChangeClip("jesse_block_left", true);
}

void JesseBlockState::Exit(EnemyAI* enemy)
{
}
