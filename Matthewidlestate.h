#pragma once
#include "Matthewstate.h"
class MatthewIdleState : public Matthewstate
{
public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};