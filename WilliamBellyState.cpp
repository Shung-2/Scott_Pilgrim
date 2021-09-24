#include "stdafx.h"
#include "WilliamBellyState.h"
#include "WilliamIdleState.h"

EnemyState * WilliamBellyState::Update(EnemyAI * enemy)
{
	if (enemy->animator->GetEnd()==true)
	{
		return new WilliamIdleState();
	}
	return nullptr;
}

void WilliamBellyState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("william_belly_right", true);
	}
	else
	{
		enemy->ChangeClip("william_belly_left", true);
	}
}

void WilliamBellyState::Exit(EnemyAI * enemy)
{
}
