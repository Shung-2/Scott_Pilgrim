#pragma once
#include "MatthewState.h"
class MatthewHitState :
	public Matthewstate
{
private:
	float _hitTime;

public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);

};

