#include "stdafx.h"
#include "MatthewPhaseReadyState.h"
#include "Matthew.h"
#include "MatthewPhaseStartState.h"

Matthewstate * MatthewPhaseReadyState::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd() == true)
	{
		return new MatthewPhaseStartState();
	}

	return nullptr;
}

void MatthewPhaseReadyState::Enter(Matthew * matthew)
{
	if (matthew->Getdir()== false)
	{
		matthew->ChangeCilp("matthew_phase_ready_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_phase_ready_left", true);
	}
}

void MatthewPhaseReadyState::Exit(Matthew * matthew)
{
}
