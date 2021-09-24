#pragma once
#include "PlayerState.h"
class PlayerGroundState :
	public PlayerState
{
private:
	float _jumpTime;


public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player* player);
	virtual void Enter(Player* player);
	virtual void Exit(Player* player);

};

