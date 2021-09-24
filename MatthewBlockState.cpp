#include "stdafx.h"
#include "MatthewBlockState.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthewBlockState::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd()==true)
	{
		return new MatthewIdleState();
	}


	return nullptr;
}

void MatthewBlockState::Enter(Matthew * matthew)
{
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_block_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_block_left", true);
	}

}

void MatthewBlockState::Exit(Matthew * matthew)
{
}
