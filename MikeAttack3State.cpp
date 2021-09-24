#include "stdafx.h"
#include "MikeAttack3State.h"
#include "MikeIdleState.h"

EnemyState* MikeAttack3State::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	if (enemy->animator->GetEnd())
	{
		/* 위치 좌표 보정 */
		enemy->transform->MoveY(10);
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(40);
		}
		else
		{
			enemy->transform->MoveX(-40);
		}
		return new MikeIdleState();
	}
    return nullptr;
}

void MikeAttack3State::Enter(EnemyAI* enemy)
{
	enemy->Attack(100);

	/* 위치 좌표 보정 */
	enemy->transform->MoveY(-10);
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("mike_attack3_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("mike_attack3_left", true);
	}
}

void MikeAttack3State::Exit(EnemyAI* enemy)
{
}
