#include "stdafx.h"
#include "PlayerTwoHandAttackState.h"
#include "PlayerIdleState.h"
#include "Player.h"

PlayerState * PlayerTwoHandAttackState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
	{
		player->GetItemTransform()->SetPosition(player->transform->GetX() - 15, player->transform->GetY() - 77);
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerTwoHandAttackState::Update(Player * player)
{	
	if (player->isRun == false)
	{
		if (player->dir == false)
		{
			if (player->animator->currentFrame == 0)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 50, player->transform->GetY() - 76);
			}
			if (player->animator->currentFrame == 1)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 55, player->transform->GetY() - 68);
			}
			if (player->animator->currentFrame == 2)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 55, player->transform->GetY() - 68);
			}
			if (player->animator->currentFrame == 3)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 55, player->transform->GetY() - 73);
			}
			if (player->animator->currentFrame == 4)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 70, player->transform->GetY() + 15);
			}
			if (player->animator->currentFrame == 5)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 60, player->transform->GetY() + 5);
			}
			if (player->animator->currentFrame == 6)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 37, player->transform->GetY() + 2);
			}
		}
		else
		{
			if (player->animator->currentFrame == 0)
			{
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 50, player->transform->GetY() - 76);
			}																	  
			if (player->animator->currentFrame == 1)							  
			{																	  
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 55, player->transform->GetY() - 68);
			}																	  
			if (player->animator->currentFrame == 2)							  
			{																	  
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 55, player->transform->GetY() - 68);
			}																	  
			if (player->animator->currentFrame == 3)							  
			{																	  
				player->GetItemTransform()->SetPosition(player->transform->GetX() + 55, player->transform->GetY() - 73);
			}																	  
			if (player->animator->currentFrame == 4)							  
			{																	  
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 70, player->transform->GetY() + 15);
			}																	  
			if (player->animator->currentFrame == 5)							  
			{																	  
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 60, player->transform->GetY() + 5);
			}																	  
			if (player->animator->currentFrame == 6)							  
			{																	  
				player->GetItemTransform()->SetPosition(player->transform->GetX() - 37, player->transform->GetY() + 2);
			}
		}

	}
}

void PlayerTwoHandAttackState::Enter(Player * player)
{
	player->equipItem->GetComponent<Item>()->itemAttack = true;
	if (player->isRun == false)
	{
		if (player->dir == false)
		{
			player->ChangeClip("two_hand_walk_attack_right", true);
			player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_walk_attack_right", false);
		}
		else
		{
			player->ChangeClip("two_hand_walk_attack_left", true);
			player->equipItem->GetComponent<Item>()->ChangeClip("trashbox_walk_attack_left", false);
		}
	}
	else
	{
		player->isRun = false;

		if (player->dir == false)
		{
			player->ChangeClip("two_hand_run_attack_right", true);

		}
		else
			player->ChangeClip("two_hand_run_attack_left", true);
	}

}

void PlayerTwoHandAttackState::Exit(Player * player)
{

}
