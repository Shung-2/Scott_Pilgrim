#include "stdafx.h"
#include "Enemy.h"
#include "JesseIdleState.h"
#include "JesseWalkState.h"
#include "JesseRunState.h"
#include "JesseAttack1State.h"
#include "JesseKickState.h"

EnemyState* JesseRunState::Update(EnemyAI* enemy)
{
	if (enemy->transform->GetX() < enemy->GetPlayerTransform()->GetX())
	{
		if (enemy->enemyinfo->GetDir() == true)
		{
			enemy->ChangeClip("jesse_run_right", false);
			enemy->enemyinfo->SetDir(false);
		}
	}
	else
	{
		if (enemy->enemyinfo->GetDir() == false)
		{
			enemy->ChangeClip("jesse_run_left", false);
			enemy->enemyinfo->SetDir(true);
		}
	}

	/* RUN 상태 내 PLAYER가 범위를 벗어날 경우 */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) > 200)
	{
		return new JesseWalkState();
	}

	/* RUN 상태 내 PLAYER 범위 내 있으며, Z축도 정해진 값과 비슷해질 경우 */
	if (GetDistance(enemy->transform->GetX(), enemy->transform->GetY(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayerTransform()->GetY()) < 100 &&
		enemy->zOrder->GetZ() - 6 <= enemy->GetPlayerTransform()->gameObject->GetComponent<ZOrder>()->GetZ() &&
		enemy->zOrder->GetZ() + 6 >= enemy->GetPlayerTransform()->gameObject->GetComponent<ZOrder>()->GetZ())
	{
		/* 콤보공격 OR 발차기 공격 중 랜덤선택 */
		int randomAttack = RND->getInt(2);
		switch (randomAttack)
		{
		case 0:
			return new JesseAttack1State();
		case 1:
			return new JesseKickState();
		}
	}

	float angle = GetAngle(enemy->transform->GetX(), enemy->zOrder->GetZ(),
		enemy->GetPlayerTransform()->GetX(), enemy->GetPlayer()->GetComponent<ZOrder>()->GetZ());

	enemy->transform->MoveX(_speed * TIMEMANAGER->getElapsedTime() * cosf(angle));
	enemy->zOrder->MoveZ(_speed * TIMEMANAGER->getElapsedTime() * -sinf(angle));

	return nullptr;
}

void JesseRunState::Enter(EnemyAI* enemy)
{
	/* 걷는 속도와 뛰는 속도는 다르므로, 속도 * 1.5 설정 */
	_speed = enemy->enemyinfo->GetSpeed() * 1.5;

	if (enemy->enemyinfo->GetDir() == false)
		enemy->ChangeClip("jesse_run_right", true);
	else
		enemy->ChangeClip("jesse_run_left", true);
}

void JesseRunState::Exit(EnemyAI* enemy)
{
}
