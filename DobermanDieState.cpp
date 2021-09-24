#include "stdafx.h"
#include "DobermanDieState.h"

EnemyState* DobermanDieState::Update(EnemyAI* enemy)
{
    return nullptr;
}

void DobermanDieState::Enter(EnemyAI* enemy)
{
    enemy->gameObject->SetActive(false);
    ENEMYMANAGER->DeadEvent(enemy->gameObject);
}

void DobermanDieState::Exit(EnemyAI* enemy)
{
}
