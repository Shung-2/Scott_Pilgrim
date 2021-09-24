#include "stdafx.h"
#include "PlayerFallState.h"
#include "PlayerGroundState.h"
#include "PlayerJumpKickState.h"
#include "Player.h"

PlayerState * PlayerFallState::InputHandle(Player * player)
{
	int intersectHeight = GROUNDMANAGER->CheckGround(player->collider->rc, player->zOrder->GetZ());
	if (intersectHeight != 0)
	{
		player->transform->MoveY(-intersectHeight);
		player->onGround = true;
		return new PlayerGroundState();
	}

	if (player->transform->GetY() + 52 >= player->zOrder->GetZ()) {
		return new PlayerGroundState();
	}

	
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if(player->isCatch == false)
		{ 
			return new PlayerJumpKickState();
		}

	}
	return nullptr;
}

void PlayerFallState::Update(Player * player)
{
	//중력값을 올려서 좀 더 빨리 떨어지는 효과를 보여줌
	player->jumpPower += player->GetGravity()*TIMEMANAGER->getElapsedTime();

	player->transform->MoveY(player->jumpPower * TIMEMANAGER->getElapsedTime());

	if (player->isRun == true)
	{
		if(player->dir == false)
		{
			player->transform->MoveX(_speedX * 1.2f * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true)
			{
				player->zOrder->MoveZ(_speedX * 1.2f * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(_speedX * 1.2f * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
		else
		{
			player->transform->MoveX(-_speedX * 1.2f * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
				player->zOrder->MoveZ(-_speedX * 1.2f * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
				MainCam->transform->MoveY(-_speedX * 1.2f * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			}
		}
		
	}
	else
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
			if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
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
			player->ChangeClip("two_hand_fall_right", true);

		}
		else
		{
			player->dir = false;
			player->ChangeClip("fall_right", false);

		}
	
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_fall_left", true);

		}
		else
		{
			player->dir = true;
			player->ChangeClip("fall_left", false);

		}
	}
}

void PlayerFallState::Enter(Player * player)
{
	player->jumpPower = 0;
	if (player->isRun == true)
		_speedX = player->GetSpeed() * 2;
	else
		_speedX = player->GetSpeed();
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_fall_right", true);
		}
		else
		{
			player->ChangeClip("two_hand_fall_left", true);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("fall_right", true);
		}
		else
		{
			player->ChangeClip("fall_left", true);
		}
	}
}

void PlayerFallState::Exit(Player * player)
{
	
}
