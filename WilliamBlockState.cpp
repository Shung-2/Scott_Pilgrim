#include "stdafx.h"
#include "WilliamBlockState.h"
#include "WilliamIdleState.h"

EnemyState * WilliamBlockState::Update(EnemyAI * enemy)
{
	if (enemy->animator->GetEnd()== true)
	{
		return new WilliamIdleState();
	}
	return nullptr;
}

void WilliamBlockState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("william_block_right", true);
	}
	else
	{
		enemy->ChangeClip("william_block_left", true);
	}
}

void WilliamBlockState::Exit(EnemyAI * enemy)
{
}
