#pragma once
class Succubus;
class SuccubusState
{
public:
	virtual SuccubusState* Update(Succubus* succubus) = 0;
	virtual void Enter(Succubus* succubus) = 0;
	virtual void Exit(Succubus* succubus) = 0;
};

