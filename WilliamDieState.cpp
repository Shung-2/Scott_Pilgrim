#include "stdafx.h"
#include "WilliamDieState.h"

EnemyState* WilliamDieState::Update(EnemyAI* enemy)
{
    return nullptr;
}

void WilliamDieState::Enter(EnemyAI* enemy)
{
    enemy->gameObject->SetActive(false);
    ENEMYMANAGER->DeadEvent(enemy->gameObject);
}

void WilliamDieState::Exit(EnemyAI* enemy)
{
}
