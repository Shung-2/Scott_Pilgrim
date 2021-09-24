#include "stdafx.h"
#include "PlayerWalkState.h"
#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerJumpState.h"
#include "PlayerKickAttackState.h"
#include "PlayerAttackState.h"
#include "PlayerFallState.h"
#include "PlayerTwoHandAttackState.h"
#include "PlayerKickSkillState.h"
#include "Player.h"

PlayerState * PlayerWalkState::InputHandle(Player * player)
{
	if (KEYMANAGER->isOnceKeyDown('D')) 
	{
		if (player->isCatch == true)
		{
			player->dir = false;
			player->ChangeClip("two_hand_walk_right", true);
		}
		else
		{
			player->dir = false;
			player->ChangeClip("walk_right", true);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('D') && !KEYMANAGER->isStayKeyDown('W') && !KEYMANAGER->isStayKeyDown('S'))
	{
		if (player->dir == true)
			player->runKeyPress = false;
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isOnceKeyDown('A')) 
	{
		if (player->isCatch == true)
		{
			player->dir = true;
			player->ChangeClip("two_hand_walk_left", true);
		}
		else
		{
			player->dir = true;
			player->ChangeClip("walk_left", true);
		}
	}
	if (KEYMANAGER->isOnceKeyUp('A') && !KEYMANAGER->isStayKeyDown('W') && !KEYMANAGER->isStayKeyDown('S'))
	{
		if (player->dir == false)
			player->runKeyPress = false;
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('W') && !KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isStayKeyDown('A'))
	{
		player->runKeyPress = false;
		return new PlayerIdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('S') && !KEYMANAGER->isStayKeyDown('D') && !KEYMANAGER->isStayKeyDown('A'))
	{
		player->runKeyPress = false;
		return new PlayerIdleState();
	}

	if (KEYMANAGER->isStayKeyDown('J'))
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
		}
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		return new PlayerKickAttackState();
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		return new PlayerKickSkillState();
	}
	if (GROUNDMANAGER->CheckGround(player->groundCheckRc, player->zOrder->GetZ()) == 0 && player->onGround == true)
	{
		player->onGround = false;
		return new PlayerFallState();
	}

	if (player->zOrder->GetZ() == 1000)
	{
		return new PlayerFallState();
	}
	return nullptr;
}

void PlayerWalkState::Update(Player * player)
{
	if (KEYMANAGER->isStayKeyDown('D') && player->dir == false)
	{
		player->transform->MoveX(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true)
		{
			player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
		if (player->isCatch == true)
		{
			if (player->dir == false)
			{
				if (player->animator->currentFrame == 0)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 18, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 1)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 81);
				}
				if (player->animator->currentFrame == 2)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 3)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 86);
				}
				if (player->animator->currentFrame == 4)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 18, player->transform->GetY() - 79);
				}
				if (player->animator->currentFrame == 5)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 80);
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown('A') && player->dir == true)
	{
		player->transform->MoveX(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		if (MAPMANAGER->IsInSlope1(player->gameObject) == true)
		{
			player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
			MainCam->transform->MoveY(-player->GetSpeed() * TIMEMANAGER->getElapsedTime() / tanf(MAPMANAGER->slopeAngle1));
		}
		if (player->isCatch == true)
		{
			if (player->animator->currentFrame == 0)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 18, player->transform->GetY() - 83);
			}
			if (player->animator->currentFrame == 1)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 81);
			}
			if (player->animator->currentFrame == 2)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 83);
			}
			if (player->animator->currentFrame == 3)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 86);
			}
			if (player->animator->currentFrame == 4)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 18, player->transform->GetY() - 79);
			}
			if (player->animator->currentFrame == 5)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 80);
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->runKeyPress = false;
		player->zOrder->MoveZ(-player->GetSpeed() * TIMEMANAGER->getElapsedTime());

		if (player->isCatch == true)
		{
			if (player->dir == false)
			{
				if (player->animator->currentFrame == 0)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 18, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 1)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 81);
				}
				if (player->animator->currentFrame == 2)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 3)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 86);
				}
				if (player->animator->currentFrame == 4)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 18, player->transform->GetY() - 79);
				}
				if (player->animator->currentFrame == 5)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 80);
				}
			}
			else
			{
				if (player->animator->currentFrame == 0)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 18, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 1)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 81);
				}
				if (player->animator->currentFrame == 2)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 3)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 86);
				}
				if (player->animator->currentFrame == 4)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 18, player->transform->GetY() - 79);
				}
				if (player->animator->currentFrame == 5)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 80);
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->runKeyPress = false;
		player->zOrder->MoveZ(player->GetSpeed() * TIMEMANAGER->getElapsedTime());
		if (player->isCatch == true)
		{
			if (player->dir == false)
			{
				if (player->animator->currentFrame == 0)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 18, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 1)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 81);
				}
				if (player->animator->currentFrame == 2)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 3)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 86);
				}
				if (player->animator->currentFrame == 4)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 18, player->transform->GetY() - 79);
				}
				if (player->animator->currentFrame == 5)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() - 16, player->transform->GetY() - 80);
				}
			}
			else
			{
				if (player->animator->currentFrame == 0)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 18, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 1)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 81);
				}
				if (player->animator->currentFrame == 2)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 83);
				}
				if (player->animator->currentFrame == 3)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 86);
				}
				if (player->animator->currentFrame == 4)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 18, player->transform->GetY() - 79);
				}
				if (player->animator->currentFrame == 5)
				{
					player->GetItemTransform()->SetPosition(player->transform->GetX() + 16, player->transform->GetY() - 80);
				}
			}
		}
	}
}

void PlayerWalkState::Enter(Player * player)
{	
	if (player->isCatch == true)
	{
		if (player->dir == false)
		{
			player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_right", false);
			player->GetItemTransform()->SetPosition(player->transform->GetX() - 14, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_walk_right", false);
		}
		else
		{
			player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_left", false);
			player->GetItemTransform()->SetPosition(player->transform->GetX() + 14, player->transform->GetY() - 77);
			player->ChangeClip("two_hand_walk_left", false);
		}
	}
	else
	{
		if (player->dir == false)
		{
			player->ChangeClip("walk_right", true);
		}
		else
		{
			player->ChangeClip("walk_left", true);
		}
	}
}

void PlayerWalkState::Exit(Player * player)
{
}