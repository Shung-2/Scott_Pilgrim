#include "stdafx.h"
#include "Succubus.h"
#include "SuccubusIdleState.h"
#include "SuccubusState.h"
#include "SuccubusSummonState.h"

Succubus::Succubus()
{
}

Succubus::~Succubus()
{
}

void Succubus::Init()
{
	animator = gameObject->GetComponent<Animator>();
	collision = gameObject->GetComponent<BoxCollider>();
	animator->AddClip("summon_succubus", CLIPMANAGER->AddClip("summon_succubus", "matthew/succubus_summon.bmp", 1870, 136, 10, 0.3f));
	animator->AddClip("succubus_idle", CLIPMANAGER->AddClip("succubus_idle", "matthew/succubus_idle.bmp", 885, 136, 5, 0.3f));
	CLIPMANAGER->FindClip("summon_succubus")->isLoop = false;
	_hp = 10;
	_speed = 100;
	_succubusstate = new SuccubusSummonState();
	_succubusstate->Enter(this);
}

void Succubus::Release()
{
}

void Succubus::Update()
{
	SuccubusState* newSuccubusState = _succubusstate->Update(this);
	if (newSuccubusState !=nullptr)
	{
		SAFE_DELETE(_succubusstate);
		_succubusstate = newSuccubusState;
		_succubusstate->Enter(this);
	}

}

void Succubus::Render()
{
}

void Succubus::ChangeClip(string name, bool isInitFrame)
{
	if (isInitFrame == true)
	{
		animator->SetClip(animator->GetClip(name));
	}
	else
	{
		animator->SetClip(animator->GetClip(name), animator->curClip->currentFrame);
	}
}
