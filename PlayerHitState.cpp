#include "stdafx.h"
#include "PlayerHitState.h"
#include "PlayerIdleState.h"
#include "PlayerLastHitState.h"

PlayerState * PlayerHitState::InputHandle(Player* player)
{
	

	if (player->isJump == true)
	{
		player->isJump = false;
		return new PlayerLastHitState();
	}
	if (player->animator->GetEnd())
		return new PlayerIdleState();
	if (player->hitCount == 3 && player->isCatch == false)
	{
		player->hitCount = 0;
		return new PlayerLastHitState();
	}



	return nullptr;
}

void PlayerHitState::Update(Player* player)
{

	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		player->block = false;
	}
	

}

void PlayerHitState::Enter(Player* player)
{

	if (player->dir == false)
	{
		player->ChangeClip("hit1_right", true);
	}
	else
	{
		player->ChangeClip("hit1_left", true);
	}

	if (player->hitCount == 2)
	{
		if (player->dir == false)
		{
			player->ChangeClip("hit2_right", true);
		}
		else
		{
			player->ChangeClip("hit2_left", true);
		}
		
	}
}

void PlayerHitState::Exit(Player* player)
{

}
