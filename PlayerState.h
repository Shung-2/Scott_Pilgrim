#pragma once
class Player;

class PlayerState
{
public:
	virtual PlayerState* InputHandle(Player* player) = 0;
	virtual void Update(Player* player) = 0;
	virtual void Enter(Player* player) = 0;
	virtual void Exit(Player* player) = 0;



};

