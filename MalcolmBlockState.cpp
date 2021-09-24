#include "stdafx.h"
#include "MalcolmBlockState.h"
#include "MalcolmIdleState.h"

EnemyState * MalcolmBlockState::Update(EnemyAI * enemy)
{
	if (enemy->animator->GetEnd() == true)
	{
		return new MalcolmIdleState();
	}
	return nullptr;
}

void MalcolmBlockState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_block_right", true);
	}
	else
	{
		enemy->ChangeClip("malcolm_block_left", true);
	}
}

void MalcolmBlockState::Exit(EnemyAI * enemy)
{
}