#include "stdafx.h"
#include "JesseAttack2State.h"
#include "JesseAttack3State.h"

EnemyState* JesseAttack2State::Update(EnemyAI* enemy)
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
		return new JesseAttack3State();
	}
	return nullptr;
}

void JesseAttack2State::Enter(EnemyAI* enemy)
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

void JesseAttack2State::Exit(EnemyAI* enemy)
{
}
