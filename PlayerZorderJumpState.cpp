#include "stdafx.h"
#include "PlayerZorderJumpState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "Player.h"

PlayerState * PlayerZorderJumpState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc, player->zOrder->GetZ());
	if (intersectHeight != 0)
	{
		player->jumpZ = false;
		player->transform->MoveY(-intersectHeight);
		return new PlayerGroundState();
	}

	if (player->transform->GetY() + 52 >= player->zOrder->GetZ()) {
		return new PlayerGroundState();
	}
	return nullptr;
}

void PlayerZorderJumpState::Update(Player * player)
{
	_jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime() * 2;

	if (player->dirZ == true)
	{
		player->zOrder->MoveZ(-_speedZ * TIMEMANAGER->getElapsedTime());

		player->transform->MoveY(-_jumpPower * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		player->zOrder->MoveZ(_speedZ * TIMEMANAGER->getElapsedTime());

		player->transform->MoveY(-_jumpPower * TIMEMANAGER->getElapsedTime());
	}
}

void PlayerZorderJumpState::Enter(Player * player)
{
	_jumpPower = 150;
	_speedZ = 70;
	player->isZJump = true;

	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_Zorder_right", true);
		}
		else
		{
			player->ChangeClip("two_hand_Zorder_left", true);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("jump_Zorder_right", true);
		}
		else
		{
			player->ChangeClip("jump_Zorder_left", true);
		}
	}
}

void PlayerZorderJumpState::Exit(Player * player)
{
}
