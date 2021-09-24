#include "stdafx.h"
#include "MatthewPhaseEndState.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthewPhaseEndState::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd()==true)
	{
		matthew->transform->MoveY(150);
		return new MatthewIdleState();
	}
	return nullptr;
}

void MatthewPhaseEndState::Enter(Matthew * matthew)
{
	_endTime = 0;
	if (matthew->Getdir() == false)
	{

		matthew->ChangeCilp("matthew_phase_end_right",false);
	}
	else
	{
		matthew->ChangeCilp("matthew_phase_end_left", false);
	}

}

void MatthewPhaseEndState::Exit(Matthew * matthew)
{
}
