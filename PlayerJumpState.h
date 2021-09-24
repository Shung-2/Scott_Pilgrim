#pragma once
#include "PlayerState.h"
class PlayerJumpState :
	public PlayerState
{

private:
	int _gravity;		//플레이어 중력값
	float _speedX;
public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player * player);
	virtual void Enter(Player * player);
	virtual void Exit(Player * player);
};

