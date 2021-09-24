#include "stdafx.h"
#include "MalcolmKickState.h"
#include "MalcolmIdleState.h"

EnemyState * MalcolmKickState::Update(EnemyAI * enemy)
{
	_kickTime += TIMEMANAGER->getElapsedTime();
	if (enemy->animator->GetEnd()==true)
	{
		return new MalcolmIdleState();
	}
	return nullptr;
}

void MalcolmKickState::Enter(EnemyAI * enemy)
{
	_kickTime = 0;
	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("malcolm_kick_right",true);
	}
	else
	{
		enemy->ChangeClip("malcolm_kick_left", true);
	}

}

void MalcolmKickState::Exit(EnemyAI * enemy)
{
}
