#pragma once
#include "MatthewState.h"
class MatthewPhaseEndState : public Matthewstate
{
private:
	float _endTime;

public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

