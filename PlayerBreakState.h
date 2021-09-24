#pragma once
#include "PlayerState.h"
class PlayerBreakState :
	public PlayerState
{
private:
	float _dashSpeed;		//달리고 난 뒤 스피드 값
public:
	virtual PlayerState* InputHandle(Player* player);
	virtual void Update(Player* player);
	virtual void Enter(Player* player);
	virtual void Exit(Player* player);
};

