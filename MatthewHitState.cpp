#include "stdafx.h"
#include "MatthewHitState.h"
#include "MatthewIdleState.h"
#include "MatthewLastHitState.h"
#include "Matthew.h"

Matthewstate * MatthewHitState::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd()==true)
	{
		return new MatthewIdleState();
	}
	if (matthew->hitCount ==3)
	{
		matthew->hitCount = 0;
		return new MatthewLastHitState();
	}

	return nullptr;
}

void MatthewHitState::Enter(Matthew * matthew)
{
	_hitTime = 0;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_hit_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_hit_left", true);
	}

}

void MatthewHitState::Exit(Matthew * matthew)
{
}
