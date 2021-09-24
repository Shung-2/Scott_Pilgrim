#include "stdafx.h"
#include "MatthewPhaseStartState.h"
#include "Matthew.h"
#include "MatthewPhaseSpotlightState.h"

Matthewstate * MatthewPhaseStartState::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd()==true)
	{
		return new MatthewPhaseSpotlightState();
	}
	return nullptr;
}

void MatthewPhaseStartState::Enter(Matthew * matthew)
{
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_phase_start_right", false);
	}
	else
	{
		matthew->ChangeCilp("matthew_phase_start_left", false);
	}
}

void MatthewPhaseStartState::Exit(Matthew * matthew)
{
}
