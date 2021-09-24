#include "stdafx.h"
#include "MatthewPalmwindState.h"
#include "Matthewidlestate.h"
#include "MatthewHitState.h"
#include "MatthewBlockState.h"
#include "MatthewPhaseReadyState.h"
#include "Matthew.h"

Matthewstate * MatthewPalmwindState::Update(Matthew * matthew)
{
	if (matthew->animator->currentFrame == 12 && _ishit == false)
	{
		float distanceZ = matthew->_player->GetComponent<ZOrder>()->GetZ() - matthew->zOrder->GetZ();
		if (distanceZ < 0)
			distanceZ *= -1;
		if (GetDistance(matthew->transform->GetX(), matthew->transform->GetY(),
			matthew->GetPlayer()->GetX(), matthew->GetPlayer()->GetY()) < 150 & distanceZ<10)
		{
			matthew->GetPlayer()->gameObject->GetComponent<Player>()->Hit(matthew->GetDamage() + 4);
		}
		_ishit = true;
	}

	if (matthew->animator->GetEnd() == true)
	{

		if (matthew->Getdir() == false)
		{
			matthew->transform->Move(-90, 40);
		}
		else
		{
			matthew->transform->Move(90, 40);


		}
		return new MatthewPhaseReadyState();
	}
	return nullptr;
}

void MatthewPalmwindState::Enter(Matthew * matthew)
{
	if (matthew->Getdir() == false)
	{
		matthew->transform->Move(90, -40);

		matthew->ChangeCilp("matthew_palmwind_right", true);
	}
	else
	{
		matthew->transform->Move(-90, -40);

		matthew->ChangeCilp("matthew_palmwind_left", true);
	}
}

void MatthewPalmwindState::Exit(Matthew * matthew)
{
}
