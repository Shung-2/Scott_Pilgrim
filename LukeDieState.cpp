#include "stdafx.h"
#include "LukeDieState.h"

EnemyState* LukeDieState::Update(EnemyAI* enemy)
{
	_dieTime += TIMEMANAGER->getElapsedTime();
	if (_dieTime >= 5.f)
	{
		enemy->gameObject->SetActive(false);
		ENEMYMANAGER->DeadEvent(enemy->gameObject);
	}

	enemy->transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());
	enemy->transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
	_speedY += _gravity * TIMEMANAGER->getElapsedTime();

	if (enemy->transform->GetY() + 55 >= enemy->zOrder->GetZ())
	{
		_speedY = 0;
		_gravity = 0;
		_speedX = 0;
	}
	return nullptr;
}

void LukeDieState::Enter(EnemyAI* enemy)
{
	enemy->hitable = false;
	_speedY = -200.f;
	_gravity = 150.f;
	_dieTime = 0;

	if (enemy->enemyinfo->GetDir() == false)
	{
		enemy->ChangeClip("luke_die_right", true);
		_speedX = -50;
	}
	else
	{
		enemy->ChangeClip("luke_die_left", true);
		_speedX = 50;
	}
}

void LukeDieState::Exit(EnemyAI* enemy)
{

}
