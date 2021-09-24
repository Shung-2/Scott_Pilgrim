#include "stdafx.h"
#include "MatthewRunState.h"
#include "Matthew.h"
#include "MatthewAttackState.h"
#include "MatthewAttack2State.h"
#include "MatthewAttack3State.h"
#include "MatthewMoveState.h"
#include "MatthewPalmwindState.h"

Matthewstate * MatthewRunState::Update(Matthew * matthew)
{
	if (matthew->transform->GetX() < matthew->GetPlayer()->GetX())
	{
		if (matthew->Getdir()==true)
		{
			matthew->ChangeCilp("matthew_run_right", false);
			matthew->Setdir(false);
		}
	}
	else
	{
		if (matthew->Getdir()==false)
		{
			matthew->ChangeCilp("matthew_run_left", false);
			matthew->Setdir(true);
		}
	}
	if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) > 400)
	{
		return new MatthewMoveState();
	}


	if (GetDistance(matthew->transform->GetX(), matthew->gameObject->GetComponent<ZOrder>()->GetZ(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->gameObject->GetComponent<ZOrder>()->GetZ()) < 100)
	{
		switch (RND->getInt(4))
		{
		case 0:
			return new MatthewAttackState();
			break;
		case 1:
			return new MatthewAttack2State();
			break;
		case 2:
			return new MatthewAttack3State();
			break;
		case 3:
			return new MatthewPalmwindState();
			break;
		}
	}
	float angle = GetAngle(matthew->transform->GetX(), matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY());
	matthew->transform->MoveX((matthew->GetSpeed() * 2)*TIMEMANAGER->getElapsedTime()*cosf(angle));
	matthew->zOrder->MoveZ((matthew->GetSpeed() * 2)*TIMEMANAGER->getElapsedTime()*-sinf(angle));

	return nullptr;
}

void MatthewRunState::Enter(Matthew * matthew)
{
	if (matthew->Getdir()==false)
	{
		matthew->ChangeCilp("matthew_run_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_run_left", true);
	}
}

void MatthewRunState::Exit(Matthew * matthew)
{
}
