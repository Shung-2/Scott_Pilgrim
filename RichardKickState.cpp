#include "stdafx.h"
#include "RichardIdleState.h"
#include "RichardKickState.h"

EnemyState* RichardKickState::Update(EnemyAI* enemy)
{
	if (enemy->enemyinfo->GetDir() == true)
	{
		enemy->enemyinfo->SetDir(false);
	}
	else
	{
		enemy->enemyinfo->SetDir(true);
	}

	/* 위치 좌표 보정 */
	if (enemy->animator->GetEnd())
	{
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(25);
		}
		else
		{
			enemy->transform->MoveX(-25);
		}
		return new RichardIdleState();
	}

	return nullptr;
}

void RichardKickState::Enter(EnemyAI* enemy)
{
	enemy->Attack(100);

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(25);
		enemy->ChangeClip("richard_kick_right", true);
	}
	else
	{
		enemy->transform->MoveX(-25);
		enemy->ChangeClip("richard_kick_left", true);
	}
}

void RichardKickState::Exit(EnemyAI* enemy)
{
}
