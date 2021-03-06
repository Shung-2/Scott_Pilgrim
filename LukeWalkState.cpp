#include "stdafx.h"
#include "LukeIdleState.h"
#include "LukeWalkState.h"
#include "LukeRunState.h"
#include "LukeAttack1State.h"

EnemyState* LukeWalkState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("luke_walk_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("luke_walk_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}

	/* PATROL-MOVE */
	_moveStartTime += TIMEMANAGER->getElapsedTime();
	enemy->transform->MoveX(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * cosf(_angle));
	enemy->zOrder->MoveZ(enemy->enemyinfo->GetSpeed() * TIMEMANAGER->getElapsedTime() * -sinf(_angle));

	/* PATROL로 설정한 장소를 도착할 수 없을 때 */
	if (_moveStartTime >= _moveMaxTime)
	{
		_moveStartTime = 0;
		return new LukeIdleState();
	}

	/* PATROL로 설정한 장소 근처 도착시 */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(), enemy->patrolPoint.first, enemy->patrolPoint.second) < 1.0f)
	{
		return new LukeIdleState();
	}

	/* IDLE 상태 내 범위 안에 PLAYER가 있을 경우 */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 200)
	{
		if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
			enemy->enemyinfo->SetDir(false);
		else
			enemy->enemyinfo->SetDir(true);
		return new LukeRunState();
	}

	return nullptr;
}

void LukeWalkState::Enter(EnemyAI* enemy)
{
	_moveStartTime = 0.0f;
	_moveMaxTime = 5.0f;

	/* PATROL ANGLE */
	_angle = GetAngle(enemy->transform->GetX(), enemy->transform->GetY(), enemy->patrolPoint.first, enemy->patrolPoint.second);
	
	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("luke_walk_right", true);
	else
		enemy->ChangeClip("luke_walk_left", true);
}

void LukeWalkState::Exit(EnemyAI* enemy)
{
}