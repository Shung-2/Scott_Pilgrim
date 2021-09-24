#pragma once
#include "Matthewstate.h"
class MatthewAttack2State :
	public Matthewstate
{
private:
	float _attackTime2;


public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);

};

