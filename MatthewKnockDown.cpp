#include "stdafx.h"
#include "MatthewKnockDown.h"
#include "Matthewidlestate.h"
#include "MatthewComeBack.h"
#include "Matthew.h"

Matthewstate * MatthewKnockDown::Update(Matthew * matthew)
{
	 
	if (matthew->animator->GetEnd()==true)
	{
		return new MatthewComeBack();
	}
	return nullptr;
}

void MatthewKnockDown::Enter(Matthew * matthew)
{
	matthew->jumpPower = 0;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_knockdown_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_knockdown_left", true);
	}
}

void MatthewKnockDown::Exit(Matthew * matthew)
{
	matthew->hitable = true;

}
