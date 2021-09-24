#pragma once
#include "MatthewState.h"
class MatthewBlockState : public Matthewstate
{
private:
	float _blockTime;

public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);


};

