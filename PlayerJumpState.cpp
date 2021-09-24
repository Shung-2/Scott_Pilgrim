#include "stdafx.h"
#include "PlayerJumpState.h"
#include "PlayerIdleState.h"
#include "PlayerGroundState.h"
#include "PlayerFallState.h"
#include "PlayerJumpKickState.h"
#include "Player.h"

PlayerState * PlayerJumpState::InputHandle(Player * player)
{
	if (player->jumpPower < 0)
	{
		return new PlayerFallState();
	}
	
	return nullptr;
}

void PlayerJumpState::Update(Player * player)
{
	player->jumpPower -= player->GetGravity()*TIMEMANAGER->getElapsedTime();
	player->transform->MoveY(-player->jumpPower * TIMEMANAGER->getElapsedTime());


	if (player->isRun == true)
	{
		if (player->dir == false)
		{
			player->transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true)
			{
				player->zOrder->MoveZ(_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
		else
		{
			player->transform->MoveX(-_speedX * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
				player->zOrder->MoveZ(-_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(-_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
	}
	else
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true)
			{
				player->zOrder->MoveZ(_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			player->transform->MoveX(-_speedX * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
				player->zOrder->MoveZ(-_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(-_speedX * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
	}
	
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (player->isCatch == true)
		{
			player->dir = false;
			player->ChangeClip("two_hand_jump_right", true);
		}
		else
		{
			player->dir = false;
			player->ChangeClip("jump_right", false);
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_jump_left", true);
		}
		else
		{
			player->dir = true;
			player->ChangeClip("jump_left", false);
		}
	
	}
}

void PlayerJumpState::Enter(Player * player)
{
	player->jumpPower = 200;
	player->isZJump = false;

	if (player->isRun == true)
		_speedX = player->GetSpeed() * 2;
	else
		_speedX = player->GetSpeed();
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_jump_right", true);
			player->equipItem->transform->SetPosition(player->transform->GetX() - 15, player->transform->GetY() - 95);
		}
		else
		{
			player->ChangeClip("two_hand_jump_left", true);
			player->equipItem->transform->SetPosition(player->transform->GetX() + 15, player->transform->GetY() - 95);

		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("jump_right", true);
		}
		else
		{
			player->ChangeClip("jump_left", true);
		}
	}
	
}

void PlayerJumpState::Exit(Player * player)
{
}
