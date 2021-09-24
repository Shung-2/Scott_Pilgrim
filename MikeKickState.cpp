#include "stdafx.h"
#include "MikeIdleState.h"
#include "MikeKickState.h"

EnemyState* MikeKickState::Update(EnemyAI* enemy)
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
		return new MikeIdleState();
	}

	return nullptr;
}

void MikeKickState::Enter(EnemyAI* enemy)
{
	enemy->Attack(100);

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(25);
		enemy->ChangeClip("mike_kick_right", true);
	}
	else
	{
		enemy->transform->MoveX(-25);
		enemy->ChangeClip("mike_kick_left", true);
	}
}

void MikeKickState::Exit(EnemyAI* enemy)
{
}
