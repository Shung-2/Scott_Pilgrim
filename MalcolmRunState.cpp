#include "stdafx.h"
#include "MalcolmRunState.h"
#include "MalcolmAttackState.h"
#include "MalcolmKickState.h"
#include "MalcolmMoveState.h"

EnemyState * MalcolmRunState::Update(EnemyAI * enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir()==true)
		{
			enemy->ChangeClip("malcolm_run_right",false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("malcolm_run_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 300)
	{
		return new MalcolmMoveState();
	}
	if (GetDistance(enemy->transform->GetX(),enemy->transform->GetY(),
					enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY())< 50)
	{
		switch (RND->getInt(2))
		{
		case 0:
			return new MalcolmAttackState();
			break;

		case 1:
			return new MalcolmKickState();
			break;
		}

	}
	float angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY());

	enemy->transform->MoveX(enemy->enemyinfo->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() * cosf(angle));
	enemy->zOrder->MoveZ(enemy->enemyinfo->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() * -sinf(angle));

	return nullptr;
}

void MalcolmRunState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_run_right", true);
	}
	else
	{
		enemy->ChangeClip("malcolm_run_left", true);
	}
}
void MalcolmRunState::Exit(EnemyAI * enemy)
{
}
