#pragma once
#include "MatthewState.h"
class MatthewKnockDown : public Matthewstate
{
private:
	float _knockDownTime;
public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

