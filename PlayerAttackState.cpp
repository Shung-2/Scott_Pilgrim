#include "stdafx.h"
#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerDoubleAttackState.h"
#include "Player.h"

PlayerState * PlayerAttackState::InputHandle(Player * player)
{
	//타임매니저로 공격이 마무리되면 idle 스테이트로 변경

	_attackTime += TIMEMANAGER->getElapsedTime();

	if (_attackTime > 0.5f)
	{
		if (_doubleAttack == false)
			return new PlayerIdleState();
		else
			return new PlayerDoubleAttackState();
	}

	return nullptr;
}

void PlayerAttackState::Update(Player * player)
{
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->pressL == false)
		{
			_attackTime = 0;
			player->pressL = true;
		}
		else {
			_doubleAttack = true;
		}
		//최대 프레임이되면 attack2이미지로 
		if (player->animator->GetEnd())
		{
			if (player->pressL == true && _doubleAttack == false)
			{
				//거리내에 에너미가 있을 때 3타 공격은 어퍼컷으로 한다.

				if (player->dir == false)
				{
					player->ChangeClip("attack2_right", true);
				}
				else
				{
					player->ChangeClip("attack2_left", true);
				}

				// 그리고 1연타 공격이 마무리되고 L키를 누를 시 2연타 공격으로 넘어간다.
			}
			Attack(player);
			player->BossAttack();
		}
	}
}

void PlayerAttackState::Enter(Player * player)
{
	Attack(player);
	player->BossAttack();
	player->pressL = false;
	_doubleAttack = false;
	_attackTime = 0;
	player->isUppercut = false;
	if (player->dir == false)
	{
		player->ChangeClip("attack1_right", true);
	}
	else
	{
		player->ChangeClip("attack1_left", true);
	}
}

void PlayerAttackState::Exit(Player * player)
{

}

void PlayerAttackState::Attack(Player* player)
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
		if (distance < 100 && distanceZ < 10)
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(player->damage);

			if (player->pressL == true)
				player->isUppercut = true;

			if (player->dir == false)
			{
				EFFECTMANAGER->EmissionEffect("attack_effect", player->transform->GetX() + 60, player->transform->GetY() - 10);
			}
			else
			{
				EFFECTMANAGER->EmissionEffect("attack_effect", player->transform->GetX() - 60, player->transform->GetY() - 10);
			}
		}
	}
}