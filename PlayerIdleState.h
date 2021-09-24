#pragma once
#include "PlayerState.h"
class PlayerIdleState :
	public PlayerState
{
private:
	bool _playerJump;
public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player* player);
	virtual void Enter(Player* player);
	virtual void Exit(Player* player);
};

