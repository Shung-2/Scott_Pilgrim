#include "stdafx.h"
#include "RichardAttack3State.h"
#include "RichardIdleState.h"

EnemyState* RichardAttack3State::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
		enemy->enemyinfo->SetDir(false);
	else
		enemy->enemyinfo->SetDir(true);

	if (enemy->animator->GetEnd())
	{
		/* 위치 좌표 보정 */
		enemy->transform->MoveY(20);
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(40);
		}
		else
		{
			enemy->transform->MoveX(-40);
		}
		return new RichardIdleState();
	}
	return nullptr;
}

void RichardAttack3State::Enter(EnemyAI* enemy)
{
	enemy->Attack(70);

	/* 위치 좌표 보정 */
	enemy->transform->MoveY(-20);
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("richard_attack3_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("richard_attack3_left", true);
	}
}

void RichardAttack3State::Exit(EnemyAI* enemy)
{
}
