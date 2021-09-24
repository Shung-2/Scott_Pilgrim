#include "stdafx.h"
#include "DobermanIdleState.h"
#include "DobermanMoveState.h"

EnemyState* DobermanIdleState::Update(EnemyAI* enemy)
{

	if (GetDistance(enemy->transform->GetX(),enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY()) < 300)
	{
		if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
		{
			enemy->enemyinfo->SetDir(false);
		}
		else
		{
			enemy->enemyinfo->SetDir(true);

		}
		return new DobermanMoveState();
	}
	return nullptr;
}

void DobermanIdleState::Enter(EnemyAI * enemy)
{
	_idleTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("doberman_idle_right", true);
	}
	else
	{
		enemy->ChangeClip("doberman_idle_left", true);
	}
}

void DobermanIdleState::Exit(EnemyAI * enemy)
{
}
