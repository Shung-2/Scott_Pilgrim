#include "stdafx.h"
#include "PlayerKickAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "Player.h"

PlayerState * PlayerKickAttackState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
	{
		return new PlayerIdleState();
	}
	
	return nullptr;
}

void PlayerKickAttackState::Update(Player * player)
{

}

void PlayerKickAttackState::Enter(Player * player)
{
	Attack(player);
	player->hitable = false;

	if (player->dir == false)
	{
		player->ChangeClip("kick_attack_right", true);
	}
	else
	{
		player->ChangeClip("kick_attack_left", true);
	}

}


void PlayerKickAttackState::Exit(Player * player)
{
}

void PlayerKickAttackState::Attack(Player * player)
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
		if (distance < 120 && distanceZ < 5)
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(player->damage);

			if (player->dir == false)
			{
				EFFECTMANAGER->EmissionEffect("attack_effect", player->transform->GetX() + 70, player->transform->GetY() - 10);
			}
			else
			{
				EFFECTMANAGER->EmissionEffect("attack_effect", player->transform->GetX() - 70, player->transform->GetY() - 10);
			}
		}
	}

}
