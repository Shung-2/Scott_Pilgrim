#pragma once
#include "PlayerState.h"
class PlayerFallState :
	public PlayerState
{
private:
	float _speedX;
public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);
};

