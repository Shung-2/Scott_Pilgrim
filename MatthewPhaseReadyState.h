#pragma once
#include "MatthewState.h"
class MatthewPhaseReadyState :public Matthewstate
{
private:
	float _readyTime;


public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

