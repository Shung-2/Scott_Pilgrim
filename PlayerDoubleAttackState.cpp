#include "stdafx.h"
#include "PlayerDoubleAttackState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerDoubleAttackState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
	{
		player->isUppercut = false;
		player->pressL = false;
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerDoubleAttackState::Update(Player * player)
{


}

void PlayerDoubleAttackState::Enter(Player * player)
{
	player->BossAttack();
	
	if (player->isUppercut == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("attack4_right", true);
		}
		else
		{
			player->ChangeClip("attack4_left", true);
		}
		Attack(player);
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("attack3_right", true);
		}
		else
		{
			player->ChangeClip("attack3_left", true);
		}
		Attack(player);
	}
}

void PlayerDoubleAttackState::Exit(Player * player)
{
}

void PlayerDoubleAttackState::Attack(Player* player)
{
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		if (_sectorEnemyV[i]->isActive == false) continue;
		float distance =
			GetDistance(player->transform->GetX(), player->transform->GetY(),
				_sectorEnemyV[i]->transform->GetX(), _sectorEnemyV[i]->transform->GetY());
		float distanceZ = player->zOrder->GetZ() - _sectorEnemyV[i]->GetComponent<ZOrder>()->GetZ();
		if (distanceZ < 0)
			distanceZ *= -1;
		if (distance < 100 && distanceZ < 5)
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(player->damage);
			EFFECTMANAGER->EmissionEffect("attack_effect", player->transform->GetX() + 60, player->transform->GetY() - 10);
			player->isUppercut = true;
		}
	}
}