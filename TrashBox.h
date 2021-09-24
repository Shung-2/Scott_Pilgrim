#pragma once
#include "GameObject.h"

class TrashBox :
	public Component
{
private:
	Animator* animator;
public:
	virtual void Init();
};

