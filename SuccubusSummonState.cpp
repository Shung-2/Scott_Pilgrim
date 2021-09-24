#include "stdafx.h"
#include "SuccubusSummonState.h"
#include "Succubus.h"
#include "SuccubusIdleState.h"

SuccubusState * SuccubusSummonState::Update(Succubus * succubus)
{
	if (succubus->animator->GetEnd()==true)
	{
		return new SuccubusIdleState();
	}
	return nullptr;
}

void SuccubusSummonState::Enter(Succubus * succubus)
{
	succubus->ChangeClip("summon_succubus", true);
}

void SuccubusSummonState::Exit(Succubus * succubus)
{
}
