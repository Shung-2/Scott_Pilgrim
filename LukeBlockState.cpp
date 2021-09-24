#include "stdafx.h"
#include "LukeBlockState.h"

EnemyState* LukeBlockState::Update(EnemyAI* enemy)
{
	// TODO BLOCK
	return nullptr;
}

void LukeBlockState::Enter(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_block_right", true);
	else
		enemy->ChangeClip("luke_block_left", true);
}

void LukeBlockState::Exit(EnemyAI* enemy)
{
}
