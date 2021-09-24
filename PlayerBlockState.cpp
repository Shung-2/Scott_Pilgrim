#include "stdafx.h"
#include "PlayerBlockState.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"
#include "PlayerAttackState.h"
#include "PlayerKickAttackState.h"
#include "Player.h"

PlayerState * PlayerBlockState::InputHandle(Player * player)
{

	if (player->animator->GetEnd())
	{
		return new PlayerIdleState();
	}

	//막고 움직이기
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (player->dir == false)
		{
			player->ChangeClip("walk_right", true);
			player->animator->Resume();
			return new PlayerWalkState();
		}
		else
		{
			player->animator->Resume();
			return new PlayerWalkState();
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (player->dir == false)
		{
			player->animator->Resume();
			return new PlayerWalkState();
		}
		else
		{
			player->ChangeClip("walk_left", true);
			player->animator->Resume();
			return new PlayerWalkState();
		}

	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player->animator->Resume();

		return new PlayerWalkState();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player->animator->Resume();

		return new PlayerWalkState();
		
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		player->animator->Resume();
		return new PlayerAttackState();
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		player->animator->Resume();
		return new PlayerKickAttackState();
	}


	return nullptr;
}

void PlayerBlockState::Update(Player * player)
{
	if (player->animator->currentFrame >= 3)
	{
		player->animator->Pause();
	}

	if (KEYMANAGER->isOnceKeyUp('K'))
	{
		player->block = false;
		player->runKeyPress = false;
	}

	if (player->block == false && player->runKeyPress == false)
	{
		player->animator->Resume();
	}

}

void PlayerBlockState::Enter(Player * player)
{

	if (player->dir == false)
	{
		player->ChangeClip("block_right", true);
	}
	else
	{
		player->ChangeClip("block_left", true);
	}
}

void PlayerBlockState::Exit(Player * player)
{
}

