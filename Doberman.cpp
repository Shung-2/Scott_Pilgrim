#include "stdafx.h"
#include "EnemyState.h"
#include "Doberman.h"
#include "Dobermanidlestate.h"
#include "DobermanHitState.h"
#include "DobermanDieState.h"
Doberman::Doberman()
{
	CLIPMANAGER->FindClip("doberman_attack_left")->isLoop = false;
	CLIPMANAGER->FindClip("doberman_attack_right")->isLoop = false;

	animator->AddClip("doberman_idle_left", CLIPMANAGER->FindClip("doberman_idle_left"));
	animator->AddClip("doberman_idle_right", CLIPMANAGER->FindClip("doberman_idle_right"));
	animator->AddClip("doberman_move_left", CLIPMANAGER->FindClip("doberman_move_left"));
	animator->AddClip("doberman_move_right", CLIPMANAGER->FindClip("doberman_move_right"));
	animator->AddClip("doberman_attack_left", CLIPMANAGER->FindClip("doberman_attack_left"));
	animator->AddClip("doberman_attack_right",CLIPMANAGER->FindClip("doberman_attack_right"));
	animator->AddClip("doberman_hit_left", CLIPMANAGER->FindClip("doberman_hit_left"));
	animator->AddClip("doberman_hit_right", CLIPMANAGER->FindClip("doberman_hit_right"));

	enemyAI->SetState(new DobermanIdleState());
}

Doberman::~Doberman()
{
}

void Doberman::Init()
{
	zOrder->SetZ(transform->GetY() + 96 / 2);
	enemyinfo->SetSpeed(60.0f);
	enemyinfo->SetSpeed(30.f);
	enemyAI->hitState = new DobermanHitState();
	enemyAI->dieState = new DobermanDieState();
}