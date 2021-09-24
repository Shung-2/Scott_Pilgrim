#include "stdafx.h"
#include "MikeAttack2State.h"
#include "MikeAttack3State.h"

EnemyState* MikeAttack2State::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	/* 위치 좌표 보정 */
	if (enemy->animator->GetEnd())
	{
		enemy->transform->MoveY(-10);
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(40);
		}
		else
		{
			enemy->transform->MoveX(-40);
		}
		return new MikeAttack3State();
	}
	return nullptr;
}

void MikeAttack2State::Enter(EnemyAI* enemy)
{
	enemy->Attack(100);

	/* 위치 좌표 보정 */
	enemy->transform->MoveY(10);
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("mike_attack2_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("mike_attack2_left", true);
	}
}

void MikeAttack2State::Exit(EnemyAI* enemy)
{
}
