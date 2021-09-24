#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerBreakState.h"
#include "PlayerJumpState.h"
#include "PlayerKickAttackState.h"
#include "PlayerAttackState.h"
#include "PlayerTwoHandAttackState.h"
#include "PlayerFallState.h"
#include "PlayerKickSkillState.h"
#include "Player.h"

PlayerState * PlayerRunState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		return new PlayerBreakState();
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		return new PlayerBreakState();
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		player->isJump = true;
		return new PlayerJumpState();
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (player->isCatch == false)
		{
			return new PlayerAttackState();
		}
		else
		{
			return new PlayerTwoHandAttackState();
;		}
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		return new PlayerKickAttackState();
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		return new PlayerKickSkillState();
	}

	if (player->zOrder->GetZ() == 1000)
	{
		return new PlayerFallState();
	}
	if (GROUNDMANAGER->CheckGround(player->groundCheckRc, player->zOrder->GetZ()) == 0 && player->onGround == true)
	{
		player->onGround = false;
		return new PlayerFallState();
	}

	return nullptr;
}

void PlayerRunState::Update(Player * player)
{
	if (player->dir == false)
	{
		player->transform->MoveX(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
			player->zOrder->MoveZ(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
		if (player->isCatch == true)
		{
			if (player->animator->currentFrame == 0)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 51, player->transform->GetY() - 64);
			}
			if (player->animator->currentFrame == 1)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 41, player->transform->GetY() - 74);
			}
			if (player->animator->currentFrame == 2)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 29, player->transform->GetY() - 77);
			}
			if (player->animator->currentFrame == 3)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 44, player->transform->GetY() - 77);
			}
			if (player->animator->currentFrame == 4)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 50, player->transform->GetY() - 62);
			}
			if (player->animator->currentFrame == 5)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 50, player->transform->GetY() - 75);
			}
			if (player->animator->currentFrame == 6)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 36, player->transform->GetY() - 80);
			}
			if (player->animator->currentFrame == 7)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 45, player->transform->GetY() - 80);
			}
		}
	}
	else
	{
		player->transform->MoveX(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true) {
			player->zOrder->MoveZ(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(-player->GetSpeed() * 2 * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
		if (player->isCatch == true)
		{
			if (player->animator->currentFrame == 0)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 51, player->transform->GetY() - 64);
			}
			if (player->animator->currentFrame == 1)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 41, player->transform->GetY() - 74);
			}
			if (player->animator->currentFrame == 2)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 29, player->transform->GetY() - 77);
			}
			if (player->animator->currentFrame == 3)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 44, player->transform->GetY() - 77);
			}
			if (player->animator->currentFrame == 4)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 50, player->transform->GetY() - 62);
			}
			if (player->animator->currentFrame == 5)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 50, player->transform->GetY() - 75);
			}
			if (player->animator->currentFrame == 6)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 36, player->transform->GetY() - 80);
			}
			if (player->animator->currentFrame == 7)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 45, player->transform->GetY() - 80);
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

}

void PlayerRunState::Enter(Player * player)
{
	if (player->dir == false)
	{
		EFFECTMANAGER->EmissionEffect("run_or_break_effect_left", player->transform->GetX() - 20, player->zOrder->GetZ() - 12);
	}
	else
	{
		EFFECTMANAGER->EmissionEffect("run_or_break_effect_right", player->transform->GetX() + 20, player->zOrder->GetZ() - 12);
	}

	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->GetItemTransform()->SetPosition(player->transform->GetX() - 38, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_run_right", false);
		}
		else
		{
			player->GetItemTransform()->SetPosition(player->transform->GetX() + 38, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_run_left", false);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("run_right", true);
		}
		else
		{
			player->ChangeClip("run_left", true);
		}
	}
	
}

void PlayerRunState::Exit(Player * player)
{
}
