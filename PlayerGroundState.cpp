#include "stdafx.h"
#include "PlayerGroundState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerGroundState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyUp('A'));
	if (KEYMANAGER->isOnceKeyUp('D'));
	if (KEYMANAGER->isOnceKeyUp('W'));
	if (KEYMANAGER->isOnceKeyUp('S'));

	if (player->isZJump == true && _jumpTime >= 0.4f)
	{
		player->jumpZ = false;
		return new PlayerIdleState();
	}

	if (player->isZJump == false && _jumpTime >= 0.7f) 
	{
		player->jumpZ = false;
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerGroundState::Update(Player * player)
{
	_jumpTime += TIMEMANAGER->getElapsedTime();
}

void PlayerGroundState::Enter(Player * player)
{
	_jumpTime = 0;
	player->isRun = false;
	player->runKeyPress = false;
	EFFECTMANAGER->EmissionEffect("ground_effect", player->transform->GetX(), player->zOrder->GetZ());
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_ground_right", true);
		}
		else
		{
			player->ChangeClip("two_hand_ground_left", true);
		}
		player->equipItem->transform->MoveY(50);
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("ground_right", true);
		}
		else
		{
			player->ChangeClip("ground_left", true);
		}
	}
}

void PlayerGroundState::Exit(Player * player)
{
	player->hitable = true;
	player->isJump = false;
}
