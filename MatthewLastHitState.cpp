#include "stdafx.h"
#include "MatthewLastHitState.h"
#include "Matthew.h"
#include "MatthewKnockDown.h"

Matthewstate * MatthewLastHitState::Update(Matthew * matthew)
{
	matthew->jumpPower -= matthew->GetGravity()*TIMEMANAGER->getElapsedTime();
	matthew->transform->MoveY(-matthew->jumpPower*TIMEMANAGER->getElapsedTime());

	if (matthew->Getdir() == false)
	{
		matthew->transform->MoveX(-matthew->GetSpeed() * TIMEMANAGER->getElapsedTime());
	}
	else
	{
		matthew->transform->MoveX(matthew->GetSpeed()* TIMEMANAGER->getElapsedTime());
	}

	if (matthew->transform->GetY() + 60 >= matthew->zOrder->GetZ())
	{
		return new MatthewKnockDown();
	}

	return nullptr;
}

void MatthewLastHitState::Enter(Matthew * matthew)
{
	matthew->jumpPower = 150;
	matthew->hitable = false;
	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_lasthit_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_lasthit_left", true);
	}
}

void MatthewLastHitState::Exit(Matthew * matthew)
{
}
