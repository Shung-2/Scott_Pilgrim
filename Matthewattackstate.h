#pragma once
#include "Matthewstate.h"
class MatthewAttackState :
	public Matthewstate
{
private:
	float _attackTime;
public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

