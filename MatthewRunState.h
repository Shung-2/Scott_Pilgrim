#pragma once
#include "MatthewState.h"
class MatthewRunState :
	public Matthewstate
{
private:
	float _runTime;

public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);

};

