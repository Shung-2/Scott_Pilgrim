#include "stdafx.h"
#include "LukeAttack1State.h"
#include "LukeAttack2State.h"

EnemyState* LukeAttack1State::Update(EnemyAI* enemy)
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
		return new LukeAttack2State();
	}
	return nullptr;
}

void LukeAttack1State::Enter(EnemyAI* enemy)
{
	enemy->Attack(70);

	/* 위치 좌표 보정 */
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->transform->MoveX(40);
		enemy->ChangeClip("luke_attack1_right", true);
	}
	else
	{
		enemy->transform->MoveX(-40);
		enemy->ChangeClip("luke_attack1_left", true);
	}
}

void LukeAttack1State::Exit(EnemyAI* enemy)
{
}