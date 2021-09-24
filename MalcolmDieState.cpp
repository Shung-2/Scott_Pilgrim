#include "stdafx.h"
#include "MalcolmDieState.h"

EnemyState* MalcolmDieState::Update(EnemyAI* enemy)
{
    return nullptr;
}

void MalcolmDieState::Enter(EnemyAI* enemy)
{
    enemy->gameObject->SetActive(false);
    ENEMYMANAGER->DeadEvent(enemy->gameObject);
}

void MalcolmDieState::Exit(EnemyAI* enemy)
{
}
