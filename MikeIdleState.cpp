#include "stdafx.h"
#include "MikeIdleState.h"
#include "MikeWalkState.h"
#include "MikeRunState.h"

EnemyState* MikeIdleState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		enemy->enemyinfo->SetDir(false);
	}
	else
	{
		enemy->enemyinfo->SetDir(true);
	}

	/* Patrol 설정 */
	_idleTime += TIMEMANAGER->getElapsedTime();
	if (_idleTime >= _idleMaxTime)
	{
		_idleTime = 0;
		int patrolIdx = RND->getInt(4);
		enemy->deltaX = RND->getFromFloatTo(30.f, 60.f);
		enemy->deltaY = RND->getFromFloatTo(30.f, 60.f);

		switch (patrolIdx)
		{
			// 제1사분면
		case 0:
			enemy->patrolPoint = { enemy->transform->GetX() + enemy->deltaX, enemy->transform->GetY() - enemy->deltaY };
			break;

			// 제2사분면
		case 1:
			enemy->patrolPoint = { enemy->transform->GetX() + enemy->deltaX, enemy->transform->GetY() + enemy->deltaY };
			break;

			// 제3사분면
		case 2:
			enemy->patrolPoint = { enemy->transform->GetX() - enemy->deltaX, enemy->transform->GetY() + enemy->deltaY };
			break;

			// 제4사분면
		case 3:
			enemy->patrolPoint = { enemy->transform->GetX() - enemy->deltaX, enemy->transform->GetY() - enemy->deltaY };
			break;
		}
		return new MikeWalkState();
	}

	/* IDLE 상태 내 범위 안에 PLAYER가 있을 경우 */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 200)
	{
		if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
			enemy->enemyinfo->SetDir(false);
		else
			enemy->enemyinfo->SetDir(true);
		return new MikeRunState();
	}

	return nullptr;
}

void MikeIdleState::Enter(EnemyAI* enemy)
{
}

void MikeIdleState::Exit(EnemyAI* enemy)
{
}
