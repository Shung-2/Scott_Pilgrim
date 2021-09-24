#include "stdafx.h"
#include "MalcolmIdleState.h"
#include "MalcolmMoveState.h"

EnemyState * MalcolmIdleState::Update(EnemyAI * enemy)
{
	if (GetDistance(enemy->transform->GetX(),enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY()) < 500)
	{
		if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
		{
			enemy->enemyinfo->SetDir(false);
		}
		else
		{
			enemy->enemyinfo->SetDir(true);
		}
		return new MalcolmMoveState();
	}

	return nullptr;
}

void MalcolmIdleState::Enter(EnemyAI * enemy)
{
	_idleTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_idle_right", true);
	}
	else
	{
		enemy->ChangeClip("malcolm_idle_left", true);
	}
}

void MalcolmIdleState::Exit(EnemyAI * enemy)
{
}
