#pragma once
#include "PlayerState.h"
class PlayerKnockoutState :
	public PlayerState
{
private:
	float _knockoutTime;
public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player* player);
	virtual void Enter(Player* player);
	virtual void Exit(Player* player);
};

