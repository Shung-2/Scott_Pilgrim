#include "stdafx.h"
#include "LeeAttack1State.h"
#include "LeeAttack2State.h"

EnemyState* LeeAttack1State::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	/* 위치 좌표 보정 */
	if (enemy->animator->GetEnd())
	{
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(20);
		}
		else
		{
			enemy->transform->MoveX(-20);
		}
		return new LeeAttack2State();
	}

	return nullptr;
}

void LeeAttack1State::Enter(EnemyAI* enemy)
{
	enemy->Attack(100);

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(20);
		enemy->ChangeClip("lee_attack1_right", true);
	}
	else
	{
		enemy->transform->MoveX(-20);
		enemy->ChangeClip("lee_attack1_left", true);
	}
}

void LeeAttack1State::Exit(EnemyAI* enemy)
{
}
