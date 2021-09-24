#include "stdafx.h"
#include "PlayerWakeupState.h"
#include "PlayerIdleState.h"

PlayerState * PlayerWakeupState::InputHandle(Player * player)
{
	if (player->animator->GetEnd())
	{
		return new PlayerIdleState();
	}
	return nullptr;
}

void PlayerWakeupState::Update(Player * player)
{


}

void PlayerWakeupState::Enter(Player * player)
{
	if (player->dir == false)
	{
		player->ChangeClip("wakeup_right", true);
	}
	else
	{
		player->ChangeClip("wakeup_left", true);
	}
}

void PlayerWakeupState::Exit(Player * player)
{
	player->hitable = true;
}
