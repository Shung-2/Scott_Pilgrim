#pragma once
#include "MatthewState.h"
class MatthewPhaseStartState : public Matthewstate
{
private:
	float _startTime;

public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

