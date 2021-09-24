#pragma once
#include "Matthewstate.h"
class MatthewPalmwindState :
	public Matthewstate
{
private:
	bool _ishit;
public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

