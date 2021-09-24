#include "stdafx.h"
#include "MalcolmMoveState.h"
#include "MalcolmIdleState.h"
#include "MalcolmAttackState.h"
#include "MalcolmKickState.h"
#include "MalcolmRunState.h"

EnemyState * MalcolmMoveState::Update(EnemyAI * enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("malcolm_move_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("malcolm_move_left", false);
			enemy->enemyinfo->SetDir(true);
		}

	}
	if (GetDistance(enemy->transform->GetX(),enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(),enemy->GetPlayerTransform()->GetY()) >500)
	{
		return new MalcolmIdleState();
	}
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 200)
	{
		return new MalcolmRunState();
	}

	float angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY());

	enemy->transform->MoveX(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * cosf(angle));
	enemy->zOrder->MoveZ(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * -sinf(angle));

	return nullptr;
}

void MalcolmMoveState::Enter(EnemyAI * enemy)
{
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_move_right", true);
	}
	else
	{
		enemy->ChangeClip("malcolm_move_left", true);
	}
}

void MalcolmMoveState::Exit(EnemyAI * enemy)
{
}
