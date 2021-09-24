#pragma once
#include "MatthewState.h"
class MatthewComeBack : public Matthewstate
{
public:
	virtual Matthewstate* Update(Matthew* matthew);
	virtual void Enter(Matthew* matthew);
	virtual void Exit(Matthew* matthew);
};

