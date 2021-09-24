#include "stdafx.h"
#include "PlayerLastHitState.h"
#include "PlayerKnockoutState.h"

PlayerState * PlayerLastHitState::InputHandle(Player* player)
{
	if (player->transform->GetY() + 42>= player->zOrder->GetZ()) {
		return new PlayerKnockoutState();
	}
	return nullptr;
}

void PlayerLastHitState::Update(Player* player)
{
	player->jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime();
	player->transform->MoveY(-player->jumpPower * TIMEMANAGER->getElapsedTime());

	if (player->dir == false)
	{
		player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true)
		{
			player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
	}
	else
	{
		player->transform->MoveX(player->GetSpeed()* TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
			player->zOrder->MoveZ(player->GetSpeed()* TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
	}


}

void PlayerLastHitState::Enter(Player* player)
{
	player->jumpPower = 150;
	player->hitable = false;
	if (player->dir == false)
	{
		player->ChangeClip("last_hit_right", true);
	}
	else
	{
		player->ChangeClip("last_hit_left", true);
	}
}

void PlayerLastHitState::Exit(Player* player)
{
}
