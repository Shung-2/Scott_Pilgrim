#include "stdafx.h"
#include "MatthewPhaseSpotlightState.h"
#include "MatthewPhaseEndState.h"
#include "Matthew.h"
#include "Succubus.h"

Matthewstate * MatthewPhaseSpotlightState::Update(Matthew * matthew)
{
	if (spotLightMax <=10)
	{
		float distanceZ = matthew->_player->GetComponent<ZOrder>()->GetZ() - matthew->zOrder->GetZ();
		if (distanceZ < 0)
			distanceZ *= -1;
		
		if (matthew->transform->GetX() - 60 <= matthew->GetPlayer()->GetX() &&
			matthew->transform->GetX() + 60 >= matthew->GetPlayer()->GetX() &&
			distanceZ < 10 && matthew->_player->GetComponent<Player>()->hitable == true)
		{
			spotLightMax++;
			matthew->GetPlayer()->gameObject->GetComponent<Player>()->Hit(matthew->GetDamage() + 5);

			EFFECTMANAGER->EmissionEffect("attack_effect", matthew->_player->transform->GetX(), matthew->_player->transform->GetY() - 10);
		}
	}
	_spotLightTime += TIMEMANAGER->getElapsedTime();
	if (_spotLightTime >= 10.0f)
	{
		for (int i = 0; i < SUCCUBUSMAX; i++)
		{
			matthew->_succubus[i]->SetActive(false);
		}
		return new MatthewPhaseEndState();
	}

	return nullptr;
}

void MatthewPhaseSpotlightState::Enter(Matthew * matthew)
{
	_spotLightTime = 0;
	if (matthew->Getdir() == false)
	{
		matthew->transform->MoveY(-150);
		matthew->ChangeCilp("matthew_phase_spotlight_right",true);
	}
	else
	{
		matthew->transform->MoveY(-150);
		matthew->ChangeCilp("matthew_phase_spotlight_left", true);
	}
	matthew->_succubus[0]->transform->SetPosition(matthew->transform->GetX() + 100, matthew->transform->GetY());
	matthew->_succubus[1]->transform->SetPosition(matthew->transform->GetX() - 100, matthew->transform->GetY());
	matthew->_succubus[2]->transform->SetPosition(matthew->transform->GetX(), matthew->transform->GetY()+50);
	matthew->_succubus[3]->transform->SetPosition(matthew->transform->GetX(), matthew->transform->GetY()-50);
	for (int i = 0; i < SUCCUBUSMAX; i++)
	{
		matthew->_succubus[i]->SetActive(true); 
		matthew->_succubus[i]->GetComponent<Succubus>()->Init(); // 페이즈 종료 후에도 서큐버스 소환 페이즈부터 하려면 초기화부분도 시작해야함.
		matthew->_succubus[i]->GetComponent<ZOrder>()->SetZ(matthew->_succubus[i]->transform->GetY() + 250);

	}

	//matthew->_succubus[0]->GetComponent<ZOrder>()->SetZ(matthew->_succubus[0]->transform->GetY() + 100);
	//matthew->_succubus[1]->GetComponent<ZOrder>()->SetZ(matthew->_succubus[1]->transform->GetY() + 100);
	//matthew->_succubus[2]->GetComponent<ZOrder>()->SetZ(matthew->_succubus[2]->transform->GetY() + 100);
	//matthew->_succubus[3]->GetComponent<ZOrder>()->SetZ(matthew->_succubus[3]->transform->GetY() + 100);


}

void MatthewPhaseSpotlightState::Exit(Matthew * matthew)
{
}
