#include "stdafx.h"
#include "SuccubusIdleState.h"
#include "Succubus.h"

SuccubusState * SuccubusIdleState::Update(Succubus * succubus)
{
	_angle += 0.04f;
	//succubus->transform->Move(succubus->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(_angle), 
	//						  succubus->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(_angle));
	succubus->transform->MoveX(succubus->GetSpeed()*TIMEMANAGER->getElapsedTime()*cosf(_angle));
	succubus->gameObject->GetComponent<ZOrder>()->MoveZ(succubus->GetSpeed()*TIMEMANAGER->getElapsedTime()*-sinf(_angle));
	return nullptr;
}

void SuccubusIdleState::Enter(Succubus * succubus)
{
	_angle = 0;
	succubus->ChangeClip("succubus_idle", true);
}

void SuccubusIdleState::Exit(Succubus * succubus)
{
}
