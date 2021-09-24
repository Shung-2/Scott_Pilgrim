#include "stdafx.h"
#include "WilliamIdleState.h"
#include "WilliamMoveState.h"

EnemyState * WilliamIdleState::Update(EnemyAI * enemy)
{
	if (GetDistance(enemy->transform->GetX(),enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY())<200)
	{
		if (enemy->transform->GetX()< enemy->GetPlayerTransform()->GetX())
		{
			enemy->enemyinfo->SetDir(false);
		}
		else
		{
			enemy->enemyinfo->SetDir(true);
		}
		return new WilliamMoveState();
	}
	return nullptr;
}

void WilliamIdleState::Enter(EnemyAI * enemy)
{
	_idleTime = 0;
	if (enemy->enemyinfo->GetDir()== false)
	{
		enemy->ChangeClip("william_idle_right", true);
	}
	else
	{
		enemy->ChangeClip("william_idle_left", true);
	}

}

void WilliamIdleState::Exit(EnemyAI * enemy)
{
}
