#include "stdafx.h"
#include "Enemy.h"
#include "LukeIdleState.h"
#include "LukeWalkState.h"
#include "LukeRunState.h"
#include "LukeAttack1State.h"
#include "LukeKickState.h"

EnemyState* LukeRunState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("luke_run_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("luke_run_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}

	/* RUN 상태 내 PLAYER가 범위를 벗어날 경우 */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 200)
	{
		return new LukeIdleState();
	}

	/* RUN 상태 내 PLAYER 범위 내 있으며, Z축도 정해진 값과 비슷해질 경우 */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 100 &&
		enemy->zOrder->GetZ() - 6 <= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ() &&
		enemy->zOrder->GetZ() + 6 >= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ())
	{
		/* 콤보공격 OR 발차기 공격 중 랜덤선택 */
		int randomAttack = RND->getInt(2);
		switch (randomAttack)
		{
		case 0:
			return new LukeAttack1State();
		case 1:
			return new LukeKickState();
		}
	}

	/* 210730 리팩토링 by 대영 */
	_runningTime += TIMEMANAGER->getElapsedTime();
	if (_runningTime >= _runLimitTime)
	{
		return new LukeIdleState();
	}
	else
	{
		enemy->transform->MoveX(_speed * TIMEMANAGER->getElapsedTime() * cosf(_runAngle));
		enemy->zOrder->MoveZ(_speed * TIMEMANAGER->getElapsedTime() * -sinf(_runAngle));

		// Y축 보정
		if (_runFlag == 1 && 
			enemy->zOrder->GetZ() <= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ() + 1 &&
			enemy->zOrder->GetZ() >= enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ() - 1)
			//수직이동의 경우
		{
			return new LukeIdleState();
		}
	}

	return nullptr;
}

void LukeRunState::Enter(EnemyAI* enemy)
{
	/* 210730 리팩토링 by 대영
	1. X축, Y축 움직임
	2.랜덤으로 움직임 선택 (X, Y, 대각선) */

	_runFlag = RND->getInt(3);		// switch 문을 사용하기 위한 Flag 설정
	_runningTime = 0.f;				// 동작 시간
	_runLimitTime = 2.f;			// 동작 제한 시간
	
	switch (_runFlag)
	{
	case 0: // X축
		if (enemy->enemyinfo->GetDir() == false)
			_runAngle = 0;
		else
			_runAngle = PI;
		break;
		
	case 1: // Y축
		if (enemy->zOrder->GetZ() < enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ())
			_runAngle = PI * 3 / 2;
		else
			_runAngle = PI / 2;
		break;

	case 2: // 대각선
		_runAngle = GetAngle(enemy->transform->GetX(), enemy->zOrder->GetZ(),
			enemy->GetPlayerTransform()->GetX(), enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ());
		break;
	}

	/* 걷는 속도와 뛰는 속도는 다르므로, 속도 * 1.5 설정 */
	_speed = enemy->enemyinfo->GetSpeed() * 1.5;

	/* 210730 리팩토링 by 대영
	1. Enemy의 상태가 따로 없이 상태패턴이 같을 경우 
	-> 에너미 Attack 으로 묶어서 멤버 변수에 "Luke", "Jesse" 등을 아래와 같이 넣어준다. */
	char clipName[32];
	if (enemy->enemyinfo->GetDir() == false)
	{
		sprintf_s(clipName, "%s_run_right", enemy->enemyinfo->GetName().c_str());
		enemy->ChangeClip(clipName, true);
	}
	else
	{
		sprintf_s(clipName, "%s_run_left", enemy->enemyinfo->GetName().c_str());
		enemy->ChangeClip(clipName, true);
	}
	//-------------------------------------------------------------------------------
}

void LukeRunState::Exit(EnemyAI* enemy)
{

}