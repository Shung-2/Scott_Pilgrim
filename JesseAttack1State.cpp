#include "stdafx.h"
#include "JesseIdleState.h"
#include "JesseAttack1State.h"
#include "JesseAttack2State.h"

EnemyState* JesseAttack1State::Update(EnemyAI* enemy)
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
		return new JesseAttack2State();
	}
    return nullptr;
}

void JesseAttack1State::Enter(EnemyAI* enemy)
{
	enemy->Attack(100);

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("jesse_attack_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("jesse_attack_left", true);
	}
}

void JesseAttack1State::Exit(EnemyAI* enemy)
{
}