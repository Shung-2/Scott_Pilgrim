#include "stdafx.h"
#include "PlayerKickSkillState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerKickSkillState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
	{
		return new PlayerIdleState();
	}

	return nullptr;
}

void PlayerKickSkillState::Update(Player * player)
{
}

void PlayerKickSkillState::Enter(Player * player)
{
	Attack(player);
	if (player->dir == false)
	{
		player->ChangeClip("kick_skill_right", true);
	}
	else
	{
		player->ChangeClip("kick_skill_left", true);
	}

}

void PlayerKickSkillState::Exit(Player * palyer)
{
}

void PlayerKickSkillState::Attack(Player * player)
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
		if (distance < 130 && distanceZ < 50)
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(player->skillDamage);
			EFFECTMANAGER->EmissionEffect("attack_effect", _sectorEnemyV[i]->transform->GetX(), _sectorEnemyV[i]->transform->GetY() - 10);
		}
	}


}
