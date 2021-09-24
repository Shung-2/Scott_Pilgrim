#include "stdafx.h"
#include "MatthewAttack2State.h"
#include "MatthewAttack3State.h"
#include "MatthewAttackState.h"
#include "MatthewIdleState.h"
#include "Matthew.h"

Matthewstate * MatthewAttack2State::Update(Matthew * matthew)
{
	if (matthew->animator->GetEnd()==true)
	{
		if (matthew->_attackTime == 3)
		{
			matthew->_attackTime = 0;
			return new MatthewIdleState();
		}
		switch (RND->getInt(2))
		{
		case 0:
			return new MatthewAttackState();
			break;
		case 1:
			return new MatthewAttack3State();
			break;
		}
	}

	return nullptr;
}

void MatthewAttack2State::Enter(Matthew * matthew)
{
	matthew->_attackTime++;
	float distanceZ = matthew->_player->GetComponent<ZOrder>()->GetZ() - matthew->zOrder->GetZ();
	if (distanceZ<0)
		distanceZ *= -1;
	if (GetDistance(matthew->transform->GetX(),matthew->transform->GetY(),
		matthew->GetPlayer()->GetX(),matthew->GetPlayer()->GetY())<100&& distanceZ<10)
	{
		matthew->GetPlayer()->gameObject->GetComponent<Player>()->Hit(matthew->GetDamage());
		if (matthew->Getdir() == false)
		{
			EFFECTMANAGER->EmissionEffect("attack_effect", matthew->transform->GetX() + 60, matthew->transform->GetY() - 10);
		}
		else
		{
			EFFECTMANAGER->EmissionEffect("attack_effect", matthew->transform->GetX() - 60, matthew->transform->GetY() - 10);
		}
	}


	if (matthew->Getdir() == false)
	{
		matthew->ChangeCilp("matthew_attack2_right", true);
	}
	else
	{
		matthew->ChangeCilp("matthew_attack2_left", true);
	}
}

void MatthewAttack2State::Exit(Matthew * matthew)
{
}
