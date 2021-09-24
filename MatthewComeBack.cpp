#include "stdafx.h"
#include "MatthewComeBack.h"
#include "Matthew.h"
#include "Matthewidlestate.h"

Matthewstate * MatthewComeBack::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd() == true)
	{
		matthew->hitable = true;
		return new MatthewIdleState();
	}
	return nullptr;
}

void MatthewComeBack::Enter(Matthew * matthew)
{
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_comeback_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_comeback_left", true);
	}
}

void MatthewComeBack::Exit(Matthew * matthew)
{
}
