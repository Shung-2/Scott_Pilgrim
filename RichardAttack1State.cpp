#include "stdafx.h"
#include "RichardAttack1State.h"
#include "RichardAttack2State.h"

EnemyState* RichardAttack1State::Update(EnemyAI* enemy)
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
			enemy->transform->MoveX(40);
		}
		else
		{
			enemy->transform->MoveX(-40);
		}
		return new RichardAttack2State();
	}

	return nullptr;
}

void RichardAttack1State::Enter(EnemyAI* enemy)
{
	enemy->Attack(70);

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("richard_attack1_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("richard_attack1_left", true);
	}
}

void RichardAttack1State::Exit(EnemyAI* enemy)
{
}
