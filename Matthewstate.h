#pragma once
class Matthew;
class Matthewstate
{
public:
	virtual Matthewstate* Update(Matthew* matthew) = 0;
	virtual void Enter(Matthew* matthew) = 0;
	virtual void Exit(Matthew* matthew) = 0;
};

