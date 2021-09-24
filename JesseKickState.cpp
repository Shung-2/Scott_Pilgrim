#include "stdafx.h"
#include "JesseIdleState.h"
#include "JesseKickState.h"

EnemyState* JesseKickState::Update(EnemyAI* enemy)
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
		enemy->transform->MoveY(-20);
		if (enemy->enemyinfo->GetDir())
		{
			enemy->transform->MoveX(25);
		}
		else
		{
			enemy->transform->MoveX(-25);
		}
		return new JesseIdleState();
	}

	return nullptr;
}

void JesseKickState::Enter(EnemyAI* enemy)
{
	enemy->Attack(100);

	/* 위치 좌표 보정 */
	enemy->transform->MoveY(+20);
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(25);
		enemy->ChangeClip("jesse_kick_right", true);
	}
	else
	{
		enemy->transform->MoveX(-25);
		enemy->ChangeClip("jesse_kick_left", true);
	}
}

void JesseKickState::Exit(EnemyAI* enemy)
{
}
